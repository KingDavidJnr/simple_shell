#include "builtin.h"

/**
 * exit_sh - exit shell
 * @sev: struct contain shell vars
 *
 * Description: Func to exit
 * Return: void
 */
void exit_sh(sev_t *sev)
{
  char **av = sev->p_input;
  char *signal = "0";
  unsigned long siglong = 0, i, max = (long) INT_MAX;
  int sgint;

  if (av[1])
    signal = av[1];

  for (i = 0; signal[i]; i++)
    {
      if (signal[i] == '-' || (signal[i] < '0' || signal[i] > '9'))
	{
	  siglong = -1;
	  break;
	}

      siglong = (siglong * 10) + signal[i] - '0';
      if (siglong > max)
	{
	  siglong = -1;
	  break;
	}
    }

  sgint = (int) siglong;
  if (sgint >= 0 && sgint <= INT_MAX)
    {
      sigint &= BYTE;
      sev->error = sgint;
      if (!av[1])
	sev->error = sev->olderror;
      sev->skywalker = 0;
    }
  else
    {
      sigint = 2;
      sev->error = sigint;
      sev->errmsg = illegalnum(sev);
      sev->skywalker = 1;
    }
}

/**
 * _printenv - print env vars
 * @sev: struct contain shell vars
 *
 * Description: Func prints all env vars
 * Return: void
 */
void _printenv(sev_t *sev)
{
  list_t *ev = reverse_list(&(sev->env));
  char *st = NULL;

  if (sev->p_input[1] != NULL)
    {
      sev->errmsg = invalidenv(sev);
      sev->error = 127;
      reverse_list(&(sev->env));
      return;
    }
  if (ev)
    {
      for (; ev; ev = ev->next)
	{
	  st = ev->value;
	  write(STDOUT_FILENO, st, _strlen(st));
	  write(STDOUT_FILENO, "\n", 1);
	}
    }

  reverse_list(&(sev->env));
}

/**
 * _setenv - set environment variable
 * @sev: struct of shell variable
 *
 * Description: Function checks to see if environment variable exists. If
 * exists, the value will be overwritten with new value passed in by user. If
 * it does not exist, a new variable will be created.
 * Return: void
 */
void _setenv(sev_t *sev)
{
  list_t **mt = &(sev->mem);
  char **av = sev->p_input;
  char *variabl, *value, *new;

  variabl = av[1];
  value = av[2];

  if (variabl && value)
    {
      new = _strcat(variabl, "=", mt);
      new = _strcat(new, value, mt);

      if (!_setenv_helper(sev, variabl, value))
	add_node(&(sev->env), NULL, _strdup(new, mt));
    }
  else
    {
      sev->errmsg = "Usage: setenv VARIABLE VALUE\n";
      sev->error = 1;
    }
}

/**
 * _unsetenv - rmv env var
 * @sev: struct of shell vars
 *
 * Description: Func checks to see if env var exists. If it
 * exists, it will be rmv from the list of env vars.
 * Return: void
 */
void _unsetenv(sev_t *sev)
{
  list_t *ev = sev->env;
  unsigned int i = 0, index_count = 0, found = 0;
  char **av = sev->p_input;
  char *variabl, *envar;

  variabl = av[1];

  if (variabl)
    {
      for (; ev; ev = ev->next)
	{
	  envar = ev->value;
	  for (i = 0; i < _strlen(variabl); i++)
	    {
	      if (variabl[i] != envar[i])
		break;
	    }
	  if (!variabl[i])
	    {
	      found = 1;
	      break;
	    }
	  index_count++;
	}

      if (found)
	delete_node_at_index(&(sev->env), index_count);
      else
	{
	  sev->errmsg = "Unable to find VARIABLE\n";
	  sev->error = 1;
	}
    }
  else
    {
      sev->errmsg = "Usage: unsetenv VARIABLE\n";
      sev->error = 1;
    }
}

/**
 * check_builtin - call builtin func
 * @sev: struct contain shell vars
 *
 * Description: Func checks if builtin func exists. If it does,
 * builtin func will be exec.
 * Return: 1 in success; 0 in fail
 */
int check_builtin(sev_t *sev)
{
  int i = 0;
  char *cmd = NULL;
  char **av = sev->p_input;

  built_t funclist[] = {
    {"exit", exit_sh},
    {"env", _printenv},
    {"setenv", _setenv},
    {"unsetenv", _unsetenv},
    {"cd", change_dir},
    {"history", history},
    {"alias", alias},
    {"help", _help},
    {NULL, NULL}
  };

  if (av && *av)
    {
      cmd = av[0];
      for (i = 0; funclist[i].funcname; i++)
	{
	  if (!_strcmp(cmd, funclist[i].funcname))
	    {
	      funclist[i].func(sev);
	      return (1);
	    }
	}
    }
  return (0);
}
