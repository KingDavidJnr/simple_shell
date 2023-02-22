#include "string.h"

/**
 * _strdup - a func that returns a p to a newl alloc space
 * which contain a copy of a given str
 * @str: po to an input str
 * @mt: p to the memo tracker link list
 * Return: NULL if str is NULL or if fail to alloc memo, otherwise returns
 * po to the new alloc space
 */
char *_strdup(char *str, list_t **mt)
{
  unsigned int len = 0;
  char *st = NULL;

  if (str)
    {
      len = _strlen(str);
      st = malloc(sizeof(char) * (len + 1));
      add_node(mt, NULL, st);
      if (s)
	{
	  for (; len; len--)
	    st[len] = str[len];
	  st[len] = str[len];
	}
    }
  return (st);
}

/**
 * _strspn - get length of a prefix substr
 * @s: str s to process
 * @accept: target search characters
 * Return: num of bytes from the init segment of s that contain accept
 */
unsigned int _strspn(char *s, char *accept)
{
  unsigned int i = 0, r = 0;

  for (i = 0; s[i]; i++)
    {
      for (r = 0; accept[r]; r++)
	if (s[i] == accept[r])
	  break;
      if (!accept[r])
	break;
    }
  return (i);
}

/**
 * _strpbrk - searches a str for any of a set of bytes
 * @s: str s to search through
 * @accept: set of bytes to search with
 * Return: p to the byte in s that matches one of the bytes in accept;
 * will return NULL if nothing is found
 */
char *_strpbrk(char *s, char *accept)
{
  unsigned int i = 0, r = 0;

  for (i = 0; s[i]; i++)
    {
      for (r = 0; accept[r]; r++)
	if (s[i] == accept[r])
	  return (s + i);
    }
  return (NULL);
}

/**
 * _strlen - get the length of the input str
 * @s: input char * string
 * Return: unsigned int length of the input str. 0 for NULL input
 */
unsigned int _strlen(char *s)
{
  unsigned int len = 0;

  if (s && *s)
    for (len = 0; s[len]; len++)
      ;
  return (len);
}

/**
 * _strtok - takes in a str and splits it into tokens based on delim
 * @s: input char * string
 * @delim: str of delimiters to split up the input str
 * Return: p to the token or NULL if at the end
 */
char *_strtok(char *s, const char *delim)
{
  static char *remainder;
  char *tokens = NULL;

  if (!s)
    {
      s = remainder;
      if (!s)
	return (NULL);
    }
  s += _strspn(s, (char *)delim);
  if (!*s)
    {
      remainder = NULL;
      return (NULL);
    }
  tokens = s;
  s = _strpbrk(tokens, (char *)delim);
  if (s)
    {
      *s = '\0';
      remainder = s + 1;
    }
  else
    remainder = NULL;
  return (tokens);
}
