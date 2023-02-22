#ifndef _SHELLVAR_H_
#define _SHELLVAR_H_
#include "shell.h"
/**
 * struct sev_s - shell env vars
 * @skywalker: flag to continue or not continue with shell
 * @log: ptr to log link list for the current shell session
 * @log_cnt: num of log entries for the curent shell session
 * @cmd_cnt: cmd counter separate from log counter
 * @mem: ptr to mem alloc for the current shell session
 * @env: ptr to the os env vars
 * @evp: ptr to env vars in arr
 * @input: ptr to the user's input
 * @p_input: ptr to the procssed input
 * @error: error num from current command
 * @errmsg: error mess associated with the error num
 * @olderror: error from previous command
 * @pid: pid of current shell
 * @alias: ptr to link list of all alias created by user
 * @cmd_q: ptr to the list of commands in the queue
 * @shell_d: current working dir
 * @arg0: command executed to run shell
 * Description: Struct contain all shell env vars.
 * This one struct will be passed from func to func and contain
 * all the shell env vars for the current session.
 */
typedef struct sev_s
{
	int skywalker;
	int ia_mode;
	list_t *log;
	int log_cnt;
	int cmd_cnt;
	list_t *mem;
	list_t *env;
	char **evp;
	char *input;
	char **p_input;
	int error;
	char *errmsg;
	int olderror;
	pid_t pid;
	list_t *alias;
	list_t *cmd_q;
	char *shell_d;
	char *arg0;

	sev_t;
#endif /* _SHELLVAR_H_ */
