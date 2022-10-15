#ifndef __EXTENSIONS__
#define __EXTENSIONS__


#include "utils.h"
#include "node.h"

//////////////////////////////////////////////////////////////////////
// Check deadends to the given depth. If depth is 1, then check all
// deadends that can be reached in one move. If depth is 2, then
// check all deadends that can be reached in two moves, and so on.
#define SEARCH_DEPTH 2

//////////////////////////////////////////////////////////////////////
// Place the game colors into a set order
void game_order_colors(game_info_t* info, game_state_t* state);

//////////////////////////////////////////////////////////////////////
// Check for dead-end regions of freespace where there is no way to
// put an active path into and out of it. Any freespace node which
// has only one free neighbor represents such a dead end. For the
// purposes of this check, cur and goal positions count as "free".

int game_check_deadends(const game_info_t* info, const game_state_t* state);

//////////////////////////////////////////////////////////////////////
// Recursive function for `game_check_deadends`. Checks if the
// provided position has any neighbours with a deadend configuration.
// If there is a deadend, then the function returns 1. Otherwise, it
// returns 0. The `depth` parameter is used to limit the recursion
// depth. For example, if `depth` is 1, then the function will only
// check the neighbours of the provided position. If `depth` is 2, 
// then the function will check the neighbours of the neighbours,
// and so on.

int _game_check_deadends(const game_info_t* info, const game_state_t* state, pos_t pos, int depth);

//////////////////////////////////////////////////////////////////////
// Check if the position is a dead end. This function is heavily 
// influenced by the code in the original solver found here:
// https://github.com/mzucker/flow_solver/blob/master/flow_solver.c

int game_is_deadend(const game_info_t* info, const game_state_t* state, pos_t pos);

#endif
