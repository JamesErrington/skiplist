#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../lib/memtable.h"

static char *read_line(FILE *fd) {
	char *line = NULL;
	size_t len = 0;
	ssize_t read = getline(&line, &len, fd);
	// Remove newline at end if detected.
	if (read > 0 && line[read - 1] == '\n') {
		line[read - 1] = '\0';
	}

	return line;
}

int main() {
    LinkedList list = list_init();

    char *line = NULL;
    while (true) {
    	printf("jstore> ");
	    line = read_line(stdin); // TODO we leak this memory

		if (strncmp("store ", line, 6) == 0) {
			line = &line[6];
			printf("Arguments '%s'\n", line);
			// TODO strip whitespace

			char *space = strchr(line, ' ');
			if (space == NULL) {
				// No second argument provided
				printf("No second argument\n");
				continue;
			}

			*space = '\0';
			char *first = line;
			char *second = space + 1;

			printf("Input: STORE ('%s', '%s')\n", first, second);
			entry_t entry = { .key = first, .value = second };
			list_append(&list, entry);
		} else if (strncmp("get ", line, 4) == 0) {
			line = &line[4];

			char *key = line;
			printf("Input: GET ('%s')\n", key);

			entry_t *result = list_find(&list, key);
			if (result == NULL) {
				printf("No data found for key '%s'\n", key);
			} else {
				printf("Output: ('%s', '%s') \n", result->key, result->value);
			}
		} else {
			printf("Line not matched\n");
			continue;
		}
    }
}
