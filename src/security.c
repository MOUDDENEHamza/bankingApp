#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "security.h"
#include "json.h"

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
