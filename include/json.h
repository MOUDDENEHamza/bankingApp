#ifndef _JSON_H_
#define _JSON_H_

#include "struct.h"

/*
 * Update json file
 */
void write_file(Json_object json_object, Json_object json_client);

/*
 * Add data client to json file
 */
void add_client_json(Client client, Json_object json_clients);

/*
 * Parse the json file containing the client data
 */
Json_object parse_json(void);

#endif
