#ifndef _MEMO_H
#define _MEMO_H

#include <stdlib.h>
#include "../linklist.h"

void reset_buffer(char *buffer, ssize_t buf_size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size,
	       list_t **mt);

#endif
