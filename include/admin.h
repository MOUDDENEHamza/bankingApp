#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "struct.h"

/*
 *Create account to the client
 */
void create_account(Account_owner ao);

/*
 *Edit account to the client
 */
void edit_account(Account_owner ao);

/*
 *delete account
 */
void delete_account(Account_owner ao);

/*
 *Add client
 */
void add_client(void);

/*
 *Edit the personal information of the client
 */
void edit_perso_info_client(Account_owner ao);

#endif
