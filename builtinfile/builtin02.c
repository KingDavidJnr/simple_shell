#include "../shell.h"

/**
 * change_dir - change directory
 * @sev: struct contain shell vars
 *
 * Description: Func changes current working dir
 * If no dir is given, then dir is changed to dir
 * in $HOME. User is also able to return to prev dir using a hyphen.
 * Return: void
 */
void change_dir(sev_t *sev)
{
  list_t **mt = &sev->mem;
  char *home = _getenv("HOME", sev), *envar = "PWD";
  char *targetdir = (sev->p_input)[1], *newpwd = NULL;
  char *pwd_to_print, *oldpwd = "OLDPWD", *oldcp = "OLDPWD";
  char cwd[4096];
  int rt_val;

  reset_buffer(cwd, 4096);
  getcwd(cwd, 4096);

  if (!_getenv(envar, sev))
    {
      newpwd = _strcat(envar, "=", mt);
      newpwd = _strcat(newpwd, cwd, mt);
      add_node(&sev->env, NULL, _strdup(newpwd, mt));
    }

  if (!_getenv(oldpwd, sev))
    {
      oldpwd = _strcat(oldpwd, "=", mt);
      oldpwd = _strcat(oldpwd, cwd, mt);
      add_node(&sev->env, NULL, _strdup(oldpwd, mt));
    }

  if (!targetdir)
    {
      if (home)
	targetdir = home;
      else
	targetdir = cwd;
    }

  else if (!_strcmp(targetdir, "-"))
    {
      targetdir = _getenv(oldcp, sev);
      pwd_to_print = _strcat(targetdir, "\n", mt);
      write(STDOUT_FILENO, pwd_to_print, _strlen(pwd_to_print));
    }
  else if (targetdir[0] == '-')
    {
      sev->errmsg = illegaloptions(sev);
      sev->error = 1;
      return;
    }

  rt_val = chdir(targetdir);

  if (rt_val == -1)
    {
      sev->error = 1;
      sev->errmsg = invaliddir(sev);
    }

  else
    {
      _setenv_helper(sev, oldcp, cwd);
      getcwd(cwd, 4096);
      _setenv_helper(sev, envar, cwd);
    }
}

/**
 * history - displays the user command history for the current session
 * @sev: ptr to the shell env var struct
 * Return: nothing
 */
void history(sev_t *sev)
{
  list_t *walker = NULL;
  char *entry = NULL;
  size_t counter = sev->log_cnt;
  unsigned int num_space = 0;

  reverse_list(&sev->log);
  walker = sev->log;
  while (walker)
    {
      counter--;
      walker = walker->next;
    }
  counter++;
  walker = sev->log;
  while (walker)
    {
      entry = _itoa(counter, &sev->mem);
      num_space = 5 - _strlen(entry);
      while (num_space)
	{
	  entry = _strcat(SPACE, entry, &sev->mem);
	  num_space--;
	}
      entry = _strcat(entry, SPACE, &sev->mem);
      entry = _strcat(entry, walker->value, &sev->mem);
      write(STDOUT_FILENO, entry, _strlen(entry));
      NEWLINE;
      counter++;
      walker = walker->next;
    }
  reverse_list(&sev->log);
}

/**
 * alias - assign and retrieve alias
 * @sev: struct of shell vars
 *
 * Description: Func allows for the assignment of a value to a var.
 * The value is retrievable by using this func with the alias.
 * Return: void
 */
void alias(sev_t *sev)
{
  list_t **mt = &(sev->mem);
  char *key = NULL, *value = NULL, *arg = NULL;
  char *arg_cp = NULL, *token = NULL;
  char **av = sev->p_input;
  int j = 1, found = 1, error = 0;

  if (!av[1])
    print_alias_val(sev, NULL, NULL, 1);

  while ((arg = av[j]))
    {
      arg_cp = _strdup(arg, mt);

      if (arg_cp)
	{
	  if (arg_cp[0] == '=')
	    {
	      key = _strcat(key, "=", mt);
	      token = _strtok(arg_cp + 1, EQUAL);
	      key = _strcat(key, token, mt);

	      value = _strchr(arg + 1, '=');
	      if (value)
		value += 1;
	    }

	  else
	    {
	      key = _strtok(arg_cp, EQUAL);
	      value = _strchr(arg, '=');

	      if (value)
		value += 1;
	    }
	}
      if (key && value)
	{
	  if (!print_alias_val(sev, key, value, -1))
	    add_node(&(sev->alias), key, value);
	}
      else if (key)
	{
	  found = print_alias_val(sev, key, value, 0);
	}
      if (!found)
	{
	  sev->errmsg = invalidalias(sev, j);
	  sev->error = 1;
	  display_error(sev);
	  error = 1;
	}
      j++;
      found = 1;
    }
  sev->error = error;
}
