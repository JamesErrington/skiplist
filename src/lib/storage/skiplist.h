#ifndef jstore_skiplist_h
#define jstore_skiplist_h

// Skiplist code adapted from https://github.com/tdeck/c-skiplist/blob/master/skiplist.h

#define SKIPLIST_MAX_HEIGHT 4

typedef struct sl_node {
	char *key;
	char *value;
	int height;
	struct sl_node *link[SKIPLIST_MAX_HEIGHT];
} sl_node_t;

sl_node_t *sl_init();

void sl_set(sl_node_t *head, char *key, char *value);

char *sl_get(sl_node_t *head, char *key);

void sl_unset(sl_node_t *head, char *key);

void sl_deinit(sl_node_t *head);

sl_node_t *sl_next(sl_node_t *curr);

#endif
