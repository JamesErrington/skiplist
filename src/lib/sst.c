#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sst.h"
#include "storage/skiplist.h"

void sst_write(const char *file_path, sl_node_t *head) {
	char buffer[MAX_BLOCK_BYTES];

	int i = 0;
	sl_node_t *curr = head->link[0];

	while (curr != NULL && i < MAX_BLOCK_BYTES) {
		uint8_t key_len = strlen(curr->key);
		buffer[i++] = key_len;
		memcpy(&buffer[i], curr->key, key_len);
		i += key_len;

		uint8_t value_len = strlen(curr->value);
		buffer[i++] = value_len;
		memcpy(&buffer[i], curr->value, value_len);
		i += value_len;

		curr = sl_next(curr);
	}

	FILE *fd = fopen(file_path, "wb");
	if (fd == NULL) {
		perror("ERROR: failed to open file");
		exit(1);
	}

	size_t written = fwrite(&buffer, sizeof(char), i, fd);
	printf("Wrote %ld bytes to file\n", written);

	fclose(fd);
}

// void sst_write(char *key, char *value) {
// 	FILE *fd = fopen("./sst.db", "wb");
// 	if (fd == NULL) {
// 		printf("ERROR: failed to open file\n");
// 		exit(1);
// 	}

// 	size_t written = 0;
// 	uint8_t key_len = strlen(key);
// 	fwrite(&key_len, sizeof(uint8_t), 1, fd);
// 	written = fwrite(key, sizeof(char),key_len, fd);
// 	if (written != sizeof(char) * key_len) {
// 		printf("ERROR: failed key fwrite\n");
// 		exit(1);
// 	}

// 	uint8_t value_len = strlen(value);
// 	fwrite(&value_len, sizeof(uint8_t), 1, fd);
// 	written = fwrite(value, sizeof(char),value_len, fd);
// 	if (written != sizeof(char) * value_len) {
// 		printf("ERROR: failed value fwrite\n");
// 		exit(1);
// 	}

// 	fclose(fd);
// }

// void sst_read() {
// 	FILE *fd = fopen("./sst.db", "rb");

// 	uint8_t key_len;
// 	fread(&key_len, sizeof(uint8_t), 1, fd);
// 	printf("%d\n", sizeof(char) * key_len + 1);

// 	char *key = malloc(sizeof(char) * key_len + 1);
// 	fread(&key, sizeof(char), key_len, fd);
// 	key[key_len] = '\0';

// 	printf("%s\n", key);
// }
