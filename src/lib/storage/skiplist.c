#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "skiplist.h"

// Skiplist code adapted from https://github.com/tdeck/c-skiplist/blob/master/skiplist.c

static void sl_free_node(sl_node_t *node);

sl_node_t *sl_init() {
	srand(2);

	sl_node_t *node = calloc(1, sizeof(sl_node_t));
	if (!node) {
		printf("Out of memory\n");
		exit(1);
	}
	node->height = SKIPLIST_MAX_HEIGHT;

	return node;
}

void sl_set(sl_node_t *head, char *key, char* value) {
	sl_node_t *prev[SKIPLIST_MAX_HEIGHT];
	sl_node_t *curr = head;
	for (int i = 0; i < SKIPLIST_MAX_HEIGHT; i++) {
		prev[i] = curr;
	}

	int depth = curr->height - 1;

	while (curr != NULL && depth >= 0) {
		prev[depth] = curr;
		sl_node_t *next = curr->link[depth];

		if (next == NULL) {
			depth--;
			continue;
		}

		int cmp = strcmp(next->key, key);
		if (cmp == 0) {
			free(next->value);
			next->value = strdup(value);
			return;
		} else if (cmp > 0) {
			depth--;
		} else {
			curr = next;
		}
	}

	sl_node_t *node = calloc(1, sizeof(sl_node_t));
	if (node == NULL) {
		printf("Out of memory\n");
		exit(1);
	}

	node->key = strdup(key);
	node->value = strdup(value);

	int i = 0;
	do {
		node->link[i] = prev[i]->link[i];
		prev[i]->link[i] = node;
		i++;
	} while(i < SKIPLIST_MAX_HEIGHT && (rand() % 2 == 0));

	node->height = i;
}

char *sl_get(sl_node_t *head, char *key) {
	sl_node_t *curr = head;
	int depth = curr->height - 1;

	while (curr != NULL && depth >= 0) {
		sl_node_t *next = curr->link[depth];

		if (next == NULL) {
			depth--;
			continue;
		}

		int cmp = strcmp(next->key, key);
		if (cmp == 0) {
			return strdup(next->value);
		} else if (cmp > 0) {
			depth--;
		} else {
			curr = next;
		}
	}

	return NULL;
}

void sl_unset(sl_node_t *head, char *key) {
	sl_node_t *curr = head;
	int depth = curr->height - 1;

	int cmp = 1;
	while (curr != NULL && depth >= 0) {
		sl_node_t *next = curr->link[depth];

		if (next == NULL) {
			depth--;
			continue;
		}

		cmp = strcmp(next->key, key);
		if (cmp >= 0) {
			depth--;
		} else {
			curr = next;
		}
	}

 	if (curr != NULL && cmp == 0) {
		sl_node_t *node = curr->link[0];

		for (int i = curr->height - 1; i >= 0; i--) {
			curr->link[i] = node->link[i];
		}

		sl_free_node(node);
	}
}

static void sl_free_node(sl_node_t *node) {
	free(node->key);
	free(node->value);

	free(node);
}

void sl_deinit(sl_node_t *head) {
	sl_node_t *curr = head;
	sl_node_t *next = NULL;

	while (curr != NULL) {
		next = curr->link[0];
		sl_free_node(curr);
		curr = next;
	}
}
