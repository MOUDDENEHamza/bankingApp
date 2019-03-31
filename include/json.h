#ifndef _JSON_H_
#define _JSON_H_

#include "struct.h"

/*
 * Add data client to json file
 */
struct json_object *add_client_json(Client new_client, struct json_object *clients);

/*
 * Parse the json file contais\ning the client data
 */
struct json_object *parse_json(void);

#endif
