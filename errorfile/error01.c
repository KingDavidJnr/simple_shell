#include "error.h"

/**
 * fnotfound - construct the error mess for file not found
 * @sev: ptr to the shell env var
 * Return: the constructed error mess
 */
char *fnotfound(sev_t *sev)
{
  char *errmsg = NULL;

  errmsg = _strcat(sev->arg0, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
  errmsg = _strcat(errmsg, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, sev->input, &sev->mem);
  errmsg = _strcat(errmsg, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, "not found", &sev->mem);
  errmsg = _strcat(errmsg, "\n", &sev->mem);
  sev->errmsg = errmsg;

  return (errmsg);
}

/**
 * illnum - constructs the error mess for the illegal exit num
 * @sev: ptr to the shell env var
 * Return: the constructed error mess
 */
char *illnum(sev_t *sev)
{
  char *errmsg = NULL;

  errmsg = _strcat(sev->arg0, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
  errmsg = _strcat(errmsg, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, sev->input, &sev->mem);
  errmsg = _strcat(errmsg, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, "Illegal number: ", &sev->mem);
  errmsg = _strcat(errmsg, sev->p_input[1], &sev->mem);
  errmsg = _strcat(errmsg, "\n", &sev->mem);
  sev->errmsg = errmsg;

  return (errmsg);
}

/**
 * perdenied - constructs the permission denied mess
 * @sev: ptr to the shell env var struct
 * Return: the constructed error mess
 */
char *perdenied(sev_t *sev)
{
  char *errmsg = NULL;

  errmsg = _strcat(sev->arg0, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
  errmsg = _strcat(errmsg, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, sev->input, &sev->mem);
  errmsg = _strcat(errmsg, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, "Permission denied", &sev->mem);
  errmsg = _strcat(errmsg, "\n", &sev->mem);
  sev->errmsg = errmsg;

  return (errmsg);
}

/**
 * invaldir - contructs invalid dir error mess
 * @sev: struct contain shell vars
 *
 * Description: Func creates error mess based on args based on
 * sev.
 * Return: the constructed error mess
 */
char *invaldir(sev_t *sev)
{
  char *errmsg = NULL;

  errmsg = _strcat(sev->arg0, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
  errmsg = _strcat(errmsg, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, sev->input, &sev->mem);
  errmsg = _strcat(errmsg, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, "can't cd to ", &sev->mem);
  errmsg = _strcat(errmsg, (sev->p_input)[1], &sev->mem);
  errmsg = _strcat(errmsg, "\n", &sev->mem);
  sev->errmsg = errmsg;

  return (errmsg);
}

/**
 * invalalias - constructs invalid alias error mess
 * @sev: struct contain shell vars
 * @node: index of desired key
 *
 * Description: Func creates error mess based on args based on
 * sev.
 * Return: the constructed error mess
 */
char *invalalias(sev_t *sev, int node)
{
  char *errmsg = NULL;
  int i = node;

  errmsg = _strcat("alias: ", (sev->p_input)[i++], &sev->mem);
  errmsg = _strcat(errmsg, " not found", &sev->mem);
  errmsg = _strcat(errmsg, "\n", &sev->mem);
  sev->errmsg = errmsg;

  return (errmsg);
}
