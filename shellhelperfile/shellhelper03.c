#include "../shell.h"

/**
 * init_shell_env - init shell env vars
 * @sev: struct contain shell vars
 * @av: ptr to arr of args passed into shell program
 * @ev: ptr to arr of env vars
 *
 * Return: the init values of type sev_t
 */
sev_t *init_shell_env(sev_t *sev, char **av, char **ev)
{
  char cwd[4096];

  reset_buffer(cwd, 4096);
  sev->skywalker = 1;
  sev->ia_mode = isatty(STDIN_FILENO);
  sev->log = NULL;
  sev->log_cnt = 0;
  sev->cmd_cnt = 0;
  sev->mem = NULL;
  sev->env = NULL;
  sev->evp = ev;
  sev->input = NULL;
  sev->p_input = NULL;
  sev->error = 0;
  sev->errmsg = NULL;
  sev->olderror = 0;
  sev->pid = getpid();
  sev->alias = NULL;
  sev->cmd_q = NULL;
  sev->shell_d = NULL;
  sev->arg0 = av[0];

  sev->env = read_environment(sev, ev);
  sev->log_cnt = get_log_count(sev);
  sev->shell_d = _strdup(getcwd(cwd, 4096), &(sev->mem));

  signal(SIGINT, sig_hand);
  dis_banner(sev->ia_mode);

  return (sev);
}

/**
 * read_environment - read list of env and store in linked list
 * @sev: shell variable struct
 * @ev: list of env vars
 *
 * Description: Func parses a list of env vars and stores each str in
 * linked list
 * Return: head of linked list
 */
list_t *read_environment(sev_t *sev, char **ev)
{
  list_t **mt = &(sev->mem);
  list_t *head = NULL;

  for (; *ev; ev++)
    add_node(&head, NULL, _strdup(*ev, mt));

  return (head);
}

/**
 * dis_error - dis error
 * @sev: ptr to the shell env var link list
 * Return: nada
 */
void dis_error(sev_t *sev)
{
  sev->olderror = sev->error;
  if (sev->error)
    write(STDERR_FILENO, sev->errmsg, _strlen(sev->errmsg));
  if (sev->skywalker)
    {
      sev->error = 0;
      sev->errmsg = NULL;
    }
}

/**
 * var_expan - checks the inputs for $ and perform an expansion
 * @sev: ptr to the shell env var
 * Return: nada
 */
void var_expan(sev_t *sev)
{
  int index = 0;
  char *str = NULL;

  if (!sev->p_input)
    return;
  for (index = 0; sev->p_input[index]; index++)
    {
      if (sev->p_input[index][0] == '$')
	{
	  str = sev->p_input[index];
	  if (!_strcmp(sev->p_input[index], "$$"))
	    str = _itoa(sev->pid, &sev->mem);
	  else if (!_strcmp(sev->p_input[index], "$?"))
	    str = _itoa(sev->olderror, &sev->mem);
	  else if (sev->p_input[index][1] != '\0')
	    {
	      str = _getenvironment(sev->p_input[index] + 1, sev);
	      if (!str)
		str = "";
	    }
	  sev->p_input[index] = str;
	  if (index == 0)
	    sev->input = str;
	}
    }

  if (!_strcmp(sev->p_input[0], "cd"))
    {
      if (sev->p_input[1] && sev->p_input[1][0] == '~' &&
	  sev->p_input[1][1] == '\0')
	{
	  str = _getenvironment("HOME", sev);
	  str = _strcat(str, sev->p_input[1] + 1, &sev->mem);
	  sev->p_input[1] = str;
	}
    }

}

/**
 * p_alias_val - print retrieve alias
 * @sev: struct of shell vars
 * @key: alias
 * @value: value stored in alias
 * @flag: a flag to modify func's performance
 *
 * Description: Func has three modes: print specific alias (flag = 0),
 * set alias if alias exists (flag = -1), and print all aliases (flag != -1 &&
 * flag != 0). Use key and value inputs, func is able to parse
 * through alias linked list and perform desired functionality.
 * Return: 1 for success/found, zero for failure/not found.
 */
int p_alias_val(sev_t *sev, char *key, char *value, int flag)
{
  list_t *alias = reverse_list(&(sev->alias));
  list_t **mt = &(sev->mem);
  char *argstr = NULL;
  int success = 0;

  for (; alias; alias = alias->next)
    {
      argstr = alias->key;
      if (!flag)
	{
	  if (!_strcmp(argstr, key))
	    {
	      argstr = _strcat(argstr, "='", mt);
	      argstr = _strcat(argstr, alias->value, mt);
	      argstr = _strcat(argstr, "'\n", mt);
	      write(STDOUT_FILENO, argstr, _strlen(argstr));
	      alias = reverse_list(&(sev->alias));
	      return (1);
	    }
	}
      else if (flag == -1)
	{
	  if (!_strcmp(argstr, key))
	    {
	      alias->value = value;
	      alias = reverse_list(&(sev->alias));
	      return (1);
	    }
	}
      else
	{
	  argstr = _strcat(argstr, "='", mt);
	  argstr = _strcat(argstr, alias->value, mt);
	  argstr = _strcat(argstr, "'\n", mt);
	  write(STDOUT_FILENO, argstr, _strlen(argstr));
	  success = 1;
	}
    }
  alias = reverse_list(&(sev->alias));
  return (success);
}
