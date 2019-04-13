#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "struct.h"

/**
 * Create a new account to a given client
 */
void admin_create_account(Json_object json_clients);

/**
 * Create a new account to a given client
 */
Json_object admin_delete_account(Json_object json_clients);

/**
 * Display the account list by type of whole client in the bank
 */
void display_account_list_by_type(Json_object json_clients);

/**
 * Add new client to the bank
 */
void add_client(Client client);

/**
 * Edit the coordinates of the client
 */
void edit_coordinates(Json_object json_clients);

/**
 * Display the list of entitled of a given account
 */
void display_entitled_list_account(Json_object json_clients);

#endif
