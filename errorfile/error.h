#ifndef _ERROR_H_
#define _ERROR_H_

#include "../shell.h"

/* error01.c */
char *fnotfound(sev_t *sev);
char *illnum(sev_t *sev);
char *perdenied(sev_t *sev);
char *invaldir(sev_t *sev);
char *invalalias(sev_t *sev, int reset);

/* error02.c */
char *helpfnotfound(sev_t *sev);
char *illoptions(sev_t *sev);
char *invalenv(sev_t *sev);

#endif /* _ERROR_H_ */
