#ifndef _BUILTIN_H
#define _BUILTIN_H

#include "../shell.h"
#include "../shellvar.h"

#define BYTE 255
#define BUF_SIZE 4096

/**
 * struct builtin - struct contain func name
 * @funcname: name of func
 * @func: func to be called when name is invoked
 *
 * Description: struct of func name and its respective func
 */
typedef struct builtin
{
  char *funcname;
  void (*func)(sev_t *);
} built_t;

/* builtin01.c */
void exit_sh(sev_t *sev);
void _printenv(sev_t *sev);
void _setenv(sev_t *sev);
void _unsetenv(sev_t *sev);
int check_builtin(sev_t *sev);

/* builtin02.c */
void change_dir(sev_t *sev);
void history(sev_t *sev);
void alias(sev_t *sev);

#endif
