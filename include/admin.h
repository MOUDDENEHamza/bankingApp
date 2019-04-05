#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "struct.h"

/**
 * Add new client to the bank
 */
void add_client(Client client);

/**
 * Create a new account to a given client
 */
void admin_create_account(Client client, Json_object json_clients);

/**
 * Create a new account to a given client
 */
Json_object admin_delete_account(Client client, Json_object json_clients);

/**
 * Display the account list by type of whole client in the bank
 */
void display_account_list_by_type(Json_object json_clients);

#endif
