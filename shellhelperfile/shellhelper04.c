#include "../shell.h"

/**
 * process_inputs - takes in user input and parses for multiple commands.
 * Makes a link list and contain all commands and queues it for
 * for process.
 * @cmd: string input from the user
 * @sev: ptr to the shell environment variables
 * Return: Nada
 */
void process_inputs(char *cmd, sev_t *sev)
{
  char *token1 = NULL;

  token1 = _strtok(cmd, "\n");
  while (token1)
    {
      add_node(&sev->cmd_q, NULL, _strdup(token1, &sev->mem));
      token1 = _strtok(NULL, "\n");
    }
  reverse_list(&sev->cmd_q);
}

/**
 * check_alias - check if alias exists
 * @sev: struct contain shell vars
 *
 * Description: Func check if an alias exist. If it does, the alias is
 * replaced by the value of the alias instead.
 * Return: void
 */
void checker_alias(sev_t *sev)
{
  char *input = NULL;
  list_t *alias = sev->alias;
  int found = 1;

  if (sev->p_input && alias)
    {
      while (found)
	{
	  input = sev->p_input[0];
	  found = 0;
	  for (alias = sev->alias; alias; alias = alias->next)
	    {
	      if (!_strcmp(alias->key, input))
		{
		  sev->p_input[0] = alias->value;
		  sev->input = alias->value;
		  found = 1;
		}
	      if (!_strcmp(alias->key, alias->value))
		found = 0;
	    }
	  if (!found)
	    break;
	}
    }
}

/**
 * dis_banner - displays the shell banner
 * @ia_mode: interactive mode flag
 * Return - nothing
 */
void dis_banner(int ia_mode)
{
  if (!ia_mode)
    return;
  NEWLINE;
  write(STDOUT_FILENO, "AUTHORS:\n", 9);
  write(STDOUT_FILENO, "\tMohamed Mehdi Bouchoucha <mehdiboch@gmail.com>\n", 40);
  write(STDOUT_FILENO, "\tSami Lafine <samibenomar84@gmail.com>\n\n", 40);
  write(STDOUT_FILENO, "=======================", 23);
  write(STDOUT_FILENO, "=======================\n", 24);
  write(STDOUT_FILENO, "     WELCOME TO  ", 26);
  write(STDOUT_FILENO, "  MANDALORIAN SHELL    \n", 22);
  write(STDOUT_FILENO, "=======================", 23);
  write(STDOUT_FILENO, "=======================\n", 24);
  NEWLINE;
}
