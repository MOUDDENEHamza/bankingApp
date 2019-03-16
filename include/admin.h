#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "struct.h"

/*
 *Create account to the client
 */
void create_account(Client client);

/*
 *Edit account to the client
 */
void edit_account(Client client);

/*
 *delete account
 */
void delete_account(Client client);

/*
 *Add client
 */
void add_client(void);

/*
 *Edit the personal information of the client
 */
void edit_perso_info_client(Client client);

#endif
