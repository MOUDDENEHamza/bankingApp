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
 * Generate unique id for the client
 */
void generate_unique_id(Client client);

/*
 * Ask to user or administrator to input the password
 */
void input_passwd(Client client,char *passwd);

/*
 * Ask to user to create his own password
 */
void create_passwd(Client client);

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
 * Ask to user or administrator to input his birthday
 */
void input_birthday(Client client);

/*
 * input all personnal information
 */
Client input_perso_info(Client new_client);

/*
 * Ask to the administrator de to enter a new balance
 */
void input_new_balance(Account account);


/* input the account type choosen*/
void input_type(Account account);

/*input the entitled of the account*/
void input_entitled(Account account);

/*input all account information*/
void input_create_account(Client client);

/*input a new account*/
void input_add_account(Client client);


#endif
