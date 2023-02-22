#include "errors.h"

/**
 * helpfnotfound - create error mess for help
 * @sev: struct contain shell vars
 *
 * Description: Create error mess using args in sev.
 * Return: error mess
 */
char *helpfnotfound(sev_t *sev)
{
  char *errmsg = NULL;
  char *msg = "-JS: help: no help topics match `";

  errmsg = _strcat(msg, sev->p_input[1], &sev->mem);
  errmsg = _strcat(errmsg, "'.  Try `help help'.\n", &sev->mem);
  sev->errmsg = errmsg;

  return (errmsg);
}

/**
 * illoptions - create error mess for cd
 * @sev: struct contain shell vars
 *
 * Description: Create error mess using args in sev.
 * Return: error mess
 */
char *illoptions(sev_t *sev)
{
  char *errmsg = NULL;
  char chartoprint[2];

  _chartostr(chartoprint, sev->p_input[1][1]);

  errmsg = _strcat(sev->arg0, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
  errmsg = _strcat(errmsg, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, sev->input, &sev->mem);
  errmsg = _strcat(errmsg, COLON, &sev->mem);
  errmsg = _strcat(errmsg, SPACE, &sev->mem);
  errmsg = _strcat(errmsg, "Illegal option ", &sev->mem);
  errmsg = _strcat(errmsg, "-", &sev->mem);
  errmsg = _strcat(errmsg, chartoprint, &sev->mem);
  errmsg = _strcat(errmsg, "\n", &sev->mem);
  sev->errmsg = errmsg;

  return (errmsg);
}

/**
 * invalenv - invalid env
 * @sev: sev var
 * Return: str
 */
char *invalenv(sev_t *sev)
{
  char *errmsg = "env: ";

  errmsg = _strcat(errmsg, sev->p_input[1], &sev->mem);
  errmsg = _strcat(errmsg, ": No such file or directory\n", &sev->mem);
  sev->errmsg = errmsg;

  return (errmsg);
}
