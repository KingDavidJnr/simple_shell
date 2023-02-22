#include "string.h"

/**
 * _strcmp - compares string1 and string2
 * @s1: string 1
 * @s2: string 2
 *
 * Description: Function takes two strings, s1 and s2, and compares to see if
 * they are equal
 * Return: 0 if equal or diff between s1 and s2
 */
int _strcmp(char *s1, char *s2)
{
  int j;

  for (j = 0; s1[j] == s2[j]; j++)
    if (s1[j] == '\0')
      return (0);
  return (s1[j] - s2[j]);
}

/**
 * _atoi - convert str to int
 * @s: str to be converted
 * Description: Find int in a str and returns it as an int
 * Return: int
 */
int _atoi(char *s)
{

  int negative = 1, i = 0;
  unsigned int num = 0;

  for (; (s[i] < '0' || s[i] > '9') && s[i] != '\0'; i++)
    if (s[i] == '-')
      negative *= -1;
  for (; s[i] >= '0' && s[i] <= '9'; i++)
    num = (num * 10) + s[i] - '0';
  num *= negative;
  return (num);
}

/**
 * _strcat - conat two strings and adds forward slash between them
 * @s1: string1
 * @s2: string2
 * @mt: memory tracker
 *
 * Description: Func takes two strs and combines them together into
 * a new string. A forward slash is inserted into the new str between the
 * two strs.
 * Return: Concatenated string or NULL
 */
char *_strcat(char *s1, char *s2, list_t **mt)
{
  size_t len1 = 0, len2 = 0, i = 0;
  char *newstr = NULL;

  if (s1)
    len1 = _strlen(s1);
  if (s2)
    len2 = _strlen(s2);

  newstr = malloc(sizeof(char) * (len1 + len2 + 1));
  if (!newstr)
    return (NULL);
  add_node(mt, NULL, newstr);

  reset_buffer(newstr, len1 + len2 + 1);

  for (i = 0; i < len1; i++)
    newstr[i] = s1[i];
  for (; i < len1 + len2; i++)
    newstr[i] = s2[i - len1];

  newstr[i] = '\0';
  return (newstr);
}

/**
 * _itoa - num to str convertor
 * @num: the num of type ssize_t to be converted
 * @mt: ptr to the memo tracker link list
 * Return: return str
 */
char *_itoa(ssize_t num, list_t **mt)
{
  int index = 0, sign = 1, tmps = 0, numsize = 0;
  char *result = NULL;

  if (num == 0)
    {
      result = malloc(sizeof(char) * 2);
      if (!result)
	return (NULL);
      add_node(mt, NULL, result);
      result[0] = '0';
      result[1] = '\0';
    }
  else
    {
      if (num < 0)
	sign = -1;
      tmps = num;
      while (tmps)
	{
	  tmps /= 10;
	  numsize++;
	}
      if (sign == -1)
	numsize++;
      result = malloc(sizeof(char) * (numsize + 1));
      if (!result)
	return (NULL);
      add_node(mt, NULL, result);
      while (num)
	{
	  result[index] = '0' + sign * (num % 10);
	  num /= 10;
	  index++;
	}
      if (sign == -1)
	{
	  result[index] = '-';
	  index++;
	}
      result[index] = '\0';
      reverse_str(result);
    }
  return (result);
}

/**
 * reverse_str - in place str reversal
 * @s: str to be revers
 * Return: void
 */
char *reverse_str(char *s)
{
  int front = 0, back = _strlen(s) - 1;
  char tmp;

  if (s)
    {
      while (front < back)
	{
	  tmp = s[front];
	  s[front] = s[back];
	  s[back] = tmp;
	  front++;
	  back--;
	}
    }
  return (s);
}
