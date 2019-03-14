#ifndef _SECURITY_H_
#define _SECURITY_H_

#include "json.h"

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre handling the connexion feauture
 */
typedef struct security *Security;

/*---------------Getters--------------*/

/*
 *Get id from the structure
 */
char* get_id(Security p);

/*
 *Get password from the structure
 */
char* get_passwd(Security p);

/*--------------Setters---------------*/

/*
 *Set value to id in structure
 */
void set_id(Security p ,char *id);

/*
 *Set value to password in structure
 */
void set_passwd(Security p ,char *passwd);

/*----------------------------------------------------------------------------*/

/*
 * Constructor of the structure
 */
Security new_security(void);

/*
 * Check if the id client is valid
 */
int valid_id_client(Json j, char *id);

/*
 * Check if the password client is valid
 */
int valid_passwd_client(Json j, char *passwd);

/*
 * Allow to administrator to connect to the application
 */
int connect_admin(char *passwd);

#endif
