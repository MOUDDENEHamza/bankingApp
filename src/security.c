#include <stdio.h>
#include <stdlib.h>
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
char* get_id(Security p) {
        return p->id;
}

/*
 *Get exit value from the structure
 */
char* get_passwd(Security p) {
        return p->passwd;
}

/*---------------Setters--------------*/

/*
 *Set value to id in structure
 */
void set_id(Security p ,char *id) {
        strcpy(p->id, id);
}

/*
 *Set value to passwd in structure
 */
void set_passwd(Security p ,char *passwd) {
        strcpy(p->passwd, passwd);
}

/*----------------------------------------------------------------------------*/

/*
 * Constructor of the structure
 */
Security new_security(void) {
	Security p = (Security) malloc(sizeof(Security));
	p->id = malloc(sizeof(char *));
	p->passwd = malloc(sizeof(char *));
 	strcpy(p->id, "");
	strcpy(p->passwd, "");
	return p;
}

/*
 * Allow to client to connect to the application
 */
void connect_client(void) {
	
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
