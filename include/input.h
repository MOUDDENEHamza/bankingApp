#ifndef _INPUT_H_
#define _INPUT_H_

#include "struct.h"

/*
 * Choose the feature you want to run
 */
void choose_feature(Symbol s, int *flag);

/*
 * Input and encrypt the password by putting * character
 */
void hide_passwd(char *passwd);

/*
 * Ask to user or administrator to input the id
 */
void input_id(Account_owner ao, char *id);

/*
 * Ask to user or administrator to input the password
 */
void input_passwd(Account_owner ao, char *passwd);

#endif
