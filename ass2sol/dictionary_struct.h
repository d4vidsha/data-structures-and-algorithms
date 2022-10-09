/* NB: Void pointers would be possible, but as we couple the dictionary and
    QuadTree it is better for static type checking to make this visible. */

/* A node in the dictionary, used to allow quick lookup. */
struct dictionaryNode;
