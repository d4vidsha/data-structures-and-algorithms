#include "extensions.h"
#include "options.h"

//////////////////////////////////////////////////////////////////////
// For sorting colors

int color_features_compare(const void* vptr_a, const void* vptr_b) {

	const color_features_t* a = (const color_features_t*)vptr_a;
	const color_features_t* b = (const color_features_t*)vptr_b;

	int u = cmp(a->user_index, b->user_index);
	if (u) { return u; }

	int w = cmp(a->wall_dist[0], b->wall_dist[0]);
	if (w) { return w; }

	int g = -cmp(a->wall_dist[1], b->wall_dist[1]);
	if (g) { return g; }

	return -cmp(a->min_dist, b->min_dist);

}

//////////////////////////////////////////////////////////////////////
// Place the game colors into a set order

void game_order_colors(game_info_t* info,
                       game_state_t* state) {

	if (g_options.order_random) {
    
		srand(now() * 1e6);
    
		for (size_t i=info->num_colors-1; i>0; --i) {
			size_t j = rand() % (i+1);
			int tmp = info->color_order[i];
			info->color_order[i] = info->color_order[j];
			info->color_order[j] = tmp;
		}

	} else { // not random

		color_features_t cf[MAX_COLORS];
		memset(cf, 0, sizeof(cf));

		for (size_t color=0; color<info->num_colors; ++color) {
			cf[color].index = color;
			cf[color].user_index = MAX_COLORS;
		}
    

		for (size_t color=0; color<info->num_colors; ++color) {
			
			int x[2], y[2];
			
			for (int i=0; i<2; ++i) {
				pos_get_coords(state->pos[color], x+i, y+i);
				cf[color].wall_dist[i] = get_wall_dist(info, x[i], y[i]);
			}

			int dx = abs(x[1]-x[0]);
			int dy = abs(y[1]-y[0]);
			
			cf[color].min_dist = dx + dy;
			
		

		}


		qsort(cf, info->num_colors, sizeof(color_features_t),
		      color_features_compare);

		for (size_t i=0; i<info->num_colors; ++i) {
			info->color_order[i] = cf[i].index;
		}
    
	}

	if (!g_options.display_quiet) {

		printf("\n************************************************"
		       "\n*               Branching Order                *\n");
		if (g_options.order_most_constrained) {
			printf("* Will choose color by most constrained\n");
		} else {
			printf("* Will choose colors in order: ");
			for (size_t i=0; i<info->num_colors; ++i) {
				int color = info->color_order[i];
				printf("%s", color_name_str(info, color));
			}
			printf("\n");
		}
		printf ("*************************************************\n\n");

	}

}

//////////////////////////////////////////////////////////////////////
// Check for dead-end regions of freespace where there is no way to
// put an active path into and out of it. Any freespace node which
// has only one free neighbor represents such a dead end. For the
// purposes of this check, cur and goal positions count as "free".

int game_check_deadends(const game_info_t* info,
                        const game_state_t* state) {
    
    //Get last head position
    pos_t head_pos = state->pos[state->last_color];
    return _game_check_deadends(info, state, head_pos, SEARCH_DEPTH);
}

//////////////////////////////////////////////////////////////////////
// Recursive function for `game_check_deadends`. Checks if the
// provided position has any neighbours with a deadend configuration.
// If there is a deadend, then the function returns 1. Otherwise, it
// returns 0. The `depth` parameter is used to limit the recursion
// depth. For example, if `depth` is 1, then the function will only
// check the neighbours of the provided position. If `depth` is 2, 
// then the function will check the neighbours of the neighbours,
// and so on.

int _game_check_deadends(const game_info_t* info,
                         const game_state_t* state,
                         pos_t pos, int depth) {
    
    pos_t neighbor_pos;
    int x, y;

    //Stop checks if the maximum depth is reached
    if (depth == 0) {
        return 0;
    }

    //For each direct neighbor of the head position
    for (int dir=0; dir<4; ++dir) {

        //Check if the neighbor is free and if it is a deadend
        neighbor_pos = pos_offset_pos(info, pos, dir);
	    pos_get_coords(neighbor_pos, &x, &y);
        if (game_is_free(info, state, x, y) &&
            game_is_deadend(info, state, neighbor_pos)) {
            return 1;
        } else if (_game_check_deadends(info, state, neighbor_pos, depth-1)) {
            return 1;
        }
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////
// Check if the position is a dead end. This function is heavily 
// influenced by the code in the original solver found here:
// https://github.com/mzucker/flow_solver/blob/master/flow_solver.c

int game_is_deadend(const game_info_t* info,
                    const game_state_t* state,
                    pos_t pos) {

    assert(pos != INVALID_POS && !state->cells[pos]);

    int x, y;
    pos_get_coords(pos, &x, &y);
  
    int num_free = 0;

    for (int dir = DIR_LEFT; dir <= DIR_DOWN; dir++) {
        pos_t neighbor_pos = offset_pos(info, x, y, dir);
        if (neighbor_pos != INVALID_POS) {
            if (!state->cells[neighbor_pos]) {
                ++num_free;
            } else {
                for (size_t color=0; color<info->num_colors; ++color) {
                    if (state->completed & (1 << color)) {
                        continue;
                    }
                    if (neighbor_pos == state->pos[color] ||
                        neighbor_pos == info->goal_pos[color]) {
                        ++num_free;
                    }
                }                                                             
            }
        }
    }

    return num_free <= 1;
}