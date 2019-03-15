#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "security.h"

/*
 * Check if the id client is valid
 */
int valid_id_client(Json j, char *id) {
	if (strcmp(id, get_id_json(j)) == 0) {
                return 0;
        }
        return 1;
}

/*
 * Check if the password client is valid
 */
int valid_passwd_client(Json j, char *passwd) {
	if (strcmp(passwd, get_passwd_json(j)) == 0) {
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
