#include "../shell.h"

/**
 * sig_hand - handle interrup signal
 * @signum: signal num
 *
 * Description: Func takes signal and performs certain task instead of
 * exec orig func
 * Return: void
 */
void sig_hand(int signum)
{
  (void) signum;
  PS2;
}

/**
 * dis_prompt - displays the prompt if in interac mode
 * @sev: shell env var
 * Return: nada
 */
void dis_prompt(sev_t sev)
{
  if (sev.ia_mode)
    PS1;
}

/**
 * getcom - get command from the user and return a str
 * @sev: ptr to the shell env var struct
 * Return: char * str output or NULL if no input
 */
char *getcom(sev_t *sev)
{
  char *buffer = NULL, *tmp = NULL;
  size_t size = 0, len = 0, ws = 0;
  ssize_t numread = -1;

  if (!sev->cmd_q)
    {
      numread = _getline(&buffer, &size, STDIN_FILENO, &sev->mem);
      if (numread == -2 || numread == -1)
	{
	  sev->skywalker = 0;
	  sev->error = sev->olderror;
	  if (sev->ia_mode)
	    NEWLINE;
	}
      if (numread > 0)
	{
	  len = _strlen(buffer);
	  if (buffer[len - 1] == '\n')
	    buffer[len - 1] = '\0';
	}
      process_input(buffer, sev);
    }
  if (sev->cmd_q)
    {
      tmp = _strdup(sev->cmd_q->value, &sev->mem);
      ws = _strspn(tmp, DELIM);
      if (*(tmp + ws))
	sev->input = tmp + ws;
      else
	{
	  sev->input = "";
	}
      delete_node_at_index(&sev->cmd_q, 0);
    }
  else
    sev->input = NULL;
  add_log(sev);
  sev->p_input = make_array_str(sev->input, DELIM, sev);
  var_expan(sev);
  return (sev->input);
}

/**
 * make_array_str - makes an arr of strs from an input str
 * @s: input str
 * @sev: shell env var struct
 * @delim: const char * used to split each token
 *
 * Description: Func takes in a str and breaks it down into tokens and
 * returns an arr of strs.
 * Return: result NULL terminated char ** arr of strs. Will return
 * NULL if input s is empty.
 */
char **make_array_str(char *s, const char *delim, sev_t *sev)
{
  char *token = NULL;
  list_t *head = NULL, *walker = NULL;
  int numnodes = 0;
  char **argv = NULL;

  token = _strtok(s, delim);
  while (token)
    {
      numnodes++;
      add_node(&head, NULL, token);
      token = _strtok(NULL, delim);
    }
  if (numnodes)
    {
      reverse_list(&head);
      argv = malloc(sizeof(char *) * (numnodes + 1));
      add_node(&sev->mem, NULL, (void *)argv);
      for (; numnodes >= 0; numnodes--)
	argv[numnodes] = NULL;
      walker = head;
      numnodes = 0;
      while (walker)
	{
	  argv[numnodes] = (char *)walker->value;
	  walker = walker->next;
	  numnodes++;
	}
      free_list(&head, 0);
    }
  return (argv);
}

/**
 * actions - func use to fork and exec coms entered by the user
 * @sev: ptr to the shell env vars struct
 * Return: error code from execve.
 */
int actions(sev_t *sev)
{
  pid_t pid;
  char *fullpath = NULL, **evp;
  int result = 0;
  int stat;

  if (_strlen(sev->input))
    fullpath = pathfind(sev);
  if (sev->error)
    return (0);
  if (fullpath)
    {
      pid = fork();
      if (pid == -1)
	{
	  sev->error = -1;
	  sev->errmsg = "Error spawning child process\n";
	}
      else if (pid == 0)
	{
	  evp = make_evp_array(sev);
	  result = execve(fullpath, sev->p_input, evp);
	  if (result == -1)
	    perror("Error");
	}
      else
	{
	  wait(&stat);
	  sev->error = WEXITSTATUS(status);
	  if (sev->error)
	    sev->errmsg = NULL;
	}
    }
  return (0);
}
