#include "memo.h"

/**
 * _realloc - realloc more memo
 * @ptr: p to the alloc mem
 * @old_size: current size of ptr
 * @new_size: new size
 * @mt: doubl p to memo tracker link list
 * Return: po to new malloc'd space
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size,
	       list_t **mt)
{
  unsigned int i;
  char *new_arr, *tmp;

  if (new_size == old_size)
    return (ptr);
  if (!ptr)
    {
      tmp = malloc(new_size);
      add_node(mt, NULL, tmp);
      return (tmp);
    }

  if (!new_size && ptr)
    return (0);

  new_arr = malloc(new_size);
  add_node(mt, NULL, new_arr);
  reset_buffer(new_arr, new_size);

  if (new_arr)
    {
      for (i = 0; i < new_size; i++)
	new_arr[i] = *((char *) ptr + i);
    }
  return ((void *) new_arr);
}

/**
 * reset_buffer - set all the elems of a malloc'd space to zero
 * @buffer: po to malloc'd space
 * @buf_size: size of the buff
 * Return: nada
 */
void reset_buffer(char *buffer, ssize_t buf_size)
{
  ssize_t i = 0;

  while (i < buf_size)
    buffer[i++] = '\0';
}
