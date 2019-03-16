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
void input_id(Client client,char *id);

/*
 * Ask to user or administrator to input the password
 */
void input_passwd(Client client,char *passwd);

/*
 * Ask to user or administrator to input her last name
 */

void input_last_name(Client client);

/*
 * Ask to user or administrator to input her first name
 */

void input_first_name(Client client);

/*
 * Ask to user or administrator to input his Email address
 */

void input_mail(Client client);

/*
 * Ask to user or administrator to input her phone number
 */

void input_phone(Client client);

/*
 * Ask to user or administrator to input his address
 */

void input_address(Client client);

/*
 * Ask to user or administrator to input his birthday
 */

void input_birthday(Client client);

/*
 * input all personnal information
 */

void input_perso_info(Client client);

/*
 * Ask to the administrator de to enter a new balance
 */

void input_new_balance(Account account);

#endif
