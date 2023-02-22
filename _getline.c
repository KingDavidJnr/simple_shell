#include "shell.h"
#include "./memofile/memo.h"
/**
 * _getline - get line from file descrip
 * @lineptr: p to buff
 * @n: size of buff
 * @fd: file descrip
 * @mt: p to memo tracker link list
 * Return: num of chars read or -1 upon fail
 */
ssize_t _getline(char **lineptr, size_t *n, int fd, list_t **mt)
{
	static char *buff;
	ssize_t char_read = 0, char_to_read = BUF_SIZE / 2;
	ssize_t buf_size = BUF_SIZE, count = 0;

	buff = malloc(buf_size);
	add_node(mt, NULL, buff);
	if (!buff)
		return (-1);
	if (!lineptr || !n)
		return (-1);
	if (*lineptr)
	{
		buff = *lineptr;
		buf_size = *n;
		if (*n == 1)
			char_to_read = 1;
		else
			char_to_read = buf_size / 2;
	}
	reset_buffer(buff, buf_size);
	char_read = read(fd, buff + count, char_to_read);
	if (char_read == -1)
	{
		free(buff);
		return (-1);
	}
	if (char_read == 0)
		return (-2);
	char_read = _strlen(buff);
	count += char_read;
	if (count > 0)
	{
		if (buff[count - 1] == '\n')
			char_read = 0;
	}
	while (char_read)
	return (count);
}
