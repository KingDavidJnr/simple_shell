#ifndef _STRING_H_
#define _STRING_H_

#include <stdlib.h>
#include "../linklist.h"
#include "../memofile/memo.h"

#define MAXNUMLEN 1024

/* strings01.c */
char *_strdup(char *str, list_t **mt);
unsigned int _strspn(char *s, char *accept);
char *_strpbrk(char *s, char *accept);
char *_strtok(char *s, const char *delim);
unsigned int _strlen(char *s);

/* string02.c */
int _strcmp(char *s1, char *s2);
int _atoi(char *s);
char *_strcat(char *s1, char *s2, list_t **mt);
char *_itoa(ssize_t num, list_t **mt);
char *reverse_str(char *s);

/* string03.c */
char *_strchr(char *s, char c);
void _chartostr(char *s, char c);

#endif /* _STRING_H_ */
