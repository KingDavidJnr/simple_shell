#include "string.h"

/**
 * _strchr - locates a char in a str
 * @s: input str
 * @c: input char
 * Description: Func takes a char and locates its position in a str
 * Return: P to position in str or 0 if not found
 */
char *_strchr(char *s, char c)
{
  int j = 0, len = 0;

  while (s[j++] != '\0')
    len++;
  j = 0;
  while (j <= len)
    {
      if (s[j] == c)
	return (s + j);
      j++;
    }
  return (NULL);
}

/**
 * _chartostr - convert a char to a str
 * @s: buffer
 * @c: input char
 * Return: void
 */
void _chartostr(char *s, char c)
{
  s[0] = c;
  s[1] = '\0';
}
