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
void create_account(Client client, Json_object json_clients);

#endif
