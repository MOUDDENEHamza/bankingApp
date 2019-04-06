#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "struct.h"

typedef enum boolean bool;

int absolut_value(int *i);

char* concatenate(char* str1,char* str2);

/*get the number of accounts that have the client*/
int nb_accounts(Client client);

/*return true if the input of admin or user is in list of choice*/
bool in_1__nb_accounts(int choice, int nb);


Client create_new_account(int *nb_accounts);

/*
 *Create account to the client
 */
void create_account(Client client);

/*
 *Edit account to the client
 */
Json_object edit_account(Client client, Json_object json_clients);

void display_accounts_list();


/*
 *Add client
 */
void add_client(Client client);

/*
 *Edit the personal information of the client
 */
Client edit_perso_info_client(void);

Client edit_client_coordonates(int *nb_accounts);

Json_object admin_delete_account(Client client, Json_object json_clients);

void display_entiled(void);

#endif
