#include <stdio.h>
#include <string.h>
#include "security.h"

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre handling the connexion feature
 */
struct security{
        char *id;
        char *passwd;
};

/*---------------Getters--------------*/

/*
 *Get id value from the structure
 */
char* get_id(Security s) {
        return s->id;
}

/*
 *Get exit value from the structure
 */
char* get_passwd(Security s) {
        return s->passwd;
}

/*---------------Setters--------------*/

/*
 *Set value to id in structure
 */
void set_id(Security s ,char *id) {
        strcpy(s->id, id);
}

/*
 *Set value to passwd in structure
 */
void set_passwd(Security s ,char *passwd) {
        strcpy(s->passwd, passwd);
}

/*----------------------------------------------------------------------------*/


/*
 * Allow to client to connect to the application
 */
void connect_client(void) {
	
}

/*
 * Allow to administrator to connect to the application
 */
int connect_admin(char *passwd) {
	if (strcmp(passwd, "admin") != 0) {
		return 0;
	}
	return 1;
}
