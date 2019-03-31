#ifndef _SECURITY_H_
#define _SECURITY_H_

#include "struct.h"

/*
 * Check if the id and the password of the client is valid
 */
int valid_client(Client client, char *id, char *passwd);

/*
 * Allow to administrator to connect to the application
 */
int connect_admin(char *passwd);

/*
 * Change the client password
 */
void change_client_password(void);

/*
 * Change the administrator password
 */
void change_administrator_password(void);

#endif
