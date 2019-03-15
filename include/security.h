#ifndef _SECURITY_H_
#define _SECURITY_H_

#include "struct.h"

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
