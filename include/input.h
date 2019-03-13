#ifndef _INPUT_H_
#define _INPUT_H_

#include "setting.h"
#include "security.h"

/*
 * Choose the feature you want to run
 */
void choose_feature(Symbol s, int *flag);

/*
 * Ask to user or administrator to inout the password
 */
void input_passwd(Security p, char *passwd);

#endif
