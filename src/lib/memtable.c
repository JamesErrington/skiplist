#include <stdlib.h>
#include <string.h>

#include "./memtable.h"

LinkedList list_init() {
	LinkedList list = { .head = NULL, .curr = NULL };
	return list;
}

void list_append(LinkedList *list, entry_t value) {
	node_t *node = malloc(sizeof(node_t));
	node->data = value;

	if (list->head == NULL) {
		list->head = node;
		list->curr = node;
	} else {
		list->curr->next = node;
		list->curr = node;
	}
}

entry_t *list_find(LinkedList *list, char *key) {
	node_t *current = list->head;
	while (current != NULL) {
		if (strcmp(current->data.key, key) == 0) {
			return &current->data;
		}

		current = current->next;
	}

	return NULL;
}
