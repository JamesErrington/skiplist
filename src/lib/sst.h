#ifndef jstore_sst_h
#define jstore_sst_h

#include "./storage/skiplist.h"

#define MAX_BLOCK_BYTES 4 * 1024

void sst_write(const char *file_path, sl_node_t *head);

void sst_read();

#endif
