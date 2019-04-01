#ifndef _JSON_H_
#define _JSON_H_

#include "struct.h"

/*
 * Update json file
 */
void write_file(Clients object, Clients client);

/*
 * Add data client to json file
 */
void add_client_json(Client new_client, Clients clients);

/*
 * Parse the json file contais\ning the client data
 */
Clients parse_json(void);

#endif
