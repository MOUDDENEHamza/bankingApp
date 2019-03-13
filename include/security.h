#ifndef _SECURITY_H_
#define _SECURITY_H_

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
 * Allow to client to connect to the application
 */
void connect_client(void);

/*
 * Allow to administrator to connect to the application
 */
int connect_admin(char *passwd);

#endif
