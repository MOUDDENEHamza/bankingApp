#ifndef _INPUT_H_
#define _INPUT_H_

#include "struct.h"

/**
 * Choose the feature you want to run
 */
void choose_feature(Symbol s, int *flag);

/**
 * Input and encrypt the password by putting * character
 */
void hide_passwd(char *passwd);

/**
 * Generate unique id for the client
 */
char *generate_unique_id(void);

/**
 * Ask to client to input his id
 */
void input_id(char *id);

/**
 * Ask to user or administrator to input the password
 */
void input_passwd(char *passwd);

/**
 * Ask to user to create his own password
 */
char *create_passwd(void);

/**
 * Ask to user or administrator to input her last name
 */
char *input_last_name(void);

/**
 * Ask to user or administrator to input her first name
 */
char *input_first_name(void);

/**
 * Ask to user or administrator to input his birthday
 */
char *input_birthday(void);

/**
 * Ask to user or administrator to input his Email address
 */
char *input_mail(void);

/**
 * Ask to user or administrator to input her phone number
 */
char *input_phone(void);

/**
 * Ask the user to input an integer
 */
int input_choice(void);

/**
 * Ask the user to input the account type
 */
char *input_type(int *choice);

/**
 * Ask the user to input the entitled of the account
 */
char *input_entitled(void);

/**
 * Ask the user to input the joint entitled of the account
 */
char *input_joint_entitled(void);

/**
 * input all personal information
 */
Client input_perso_info(Client client);

/**
 * Input the period you want consult the transfer list
 */
void input_period(char *period);

#endif