#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../lib/storage/skiplist.h"
#include "../lib/sst.h"

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
	sl_node_t *head = sl_init();

	char *line = NULL;
	while (true) {
		printf("jstore> ");
		line = read_line(stdin);

		if (strncmp("set ", line, 4) == 0) {
			char *chunk = &line[4];

			char *space = strchr(chunk, ' ');
			*space = '\0';
			char *key = chunk;
			char *value = space + 1;

			sl_set(head, key, value);
			printf("SET '%s' => '%s'\n", key, value);
		} else if (strncmp("get ", line, 4) == 0) {
			char *chunk = &line[4];

			char *key = chunk;

			char *value = sl_get(head, key);
			printf("GET '%s' => '%s'\n", key, value);
			free(value);
		} else if (strncmp("unset ", line, 6) == 0) {
			char *chunk = &line[6];

			char *key = chunk;

			sl_unset(head, key);
			printf("UNSET '%s'\n", key);
		} else if (strncmp("exit", line, 4) == 0) {
			printf("Exiting...\n");

			free(line);
			break;
		} else {
			printf("ERROR: Unknown command '%s'\n", line);
		}

		free(line);
	}

	sst_write("./store.sst", head);

	sl_deinit(head);
}
