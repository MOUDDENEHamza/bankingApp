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
char* get_id(Security s);

/*
 *Get password from the structure
 */
char* get_passwd(Security s);

/*--------------Setters---------------*/

/*
 *Set value to id in structure
 */
void set_id(Security s ,char *id);

/*
 *Set value to password in structure
 */
void set_passwd(Security s ,char *passwd);

/*----------------------------------------------------------------------------*/


/*
 * Allow to client to connect to the application
 */
void connect_client(void);

/*
 * Allow to administrator to connect to the application
 */
int connect_admin(char *passwd);

#endif
