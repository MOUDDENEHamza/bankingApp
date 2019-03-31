#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "security.h"

/*
 * Check if the id and the password of the client is valid
 */
int valid_client(Client client, char *id, char *passwd) {
	if (strcmp(id, get_id(client)) && strcmp(passwd, get_passwd(client)) == 0) {
        	return 0;
        }
	return 1;
}

/*
 * Allow to administrator to connect to the application
 */
int connect_admin(char *passwd) {
	if (strcmp(passwd, "admin") == 0) {
		return 0;
	}
	return 1;
}

/*
 * Change the client password
 */
void change_client_password(void);

/*
 * Change the administrator password
 */
void change_administrator_password(void);
