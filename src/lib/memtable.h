#ifndef memtable_h
#define memtable_h

typedef struct {
	const char  *key;
	const char *value;
} entry_t;

struct node {
	struct node *next;
	entry_t data;
};

typedef struct node node_t;

typedef struct {
	node_t *head;
	node_t *curr;
} LinkedList;

LinkedList list_init();

void list_append(LinkedList *list, entry_t value);

entry_t *list_find(LinkedList *list, char *key);

#endif
