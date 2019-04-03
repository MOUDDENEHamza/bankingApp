#ifndef _SECURITY_H_
#define _SECURITY_H_

#include "struct.h"

/**
 * Encrypt the password
 */
char* encrypt_passwd(char *passwd);

/**
 * Check if the ID and the password of the client is valid when connecting
 */
int valid_client(Client client, Json_object json_clients, char *id, char *passwd);

/**
 * Allow to administrator to connect to the application
 */
int connect_admin(char *passwd);

/**
 * Change the client password
 */
void change_client_passwd(Client client, Json_object json_clients);

/**
 * Change the administrator password
 */
int change_administrator_passwd(void);

#endif
