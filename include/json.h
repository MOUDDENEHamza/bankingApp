#ifndef _JSON_H_
#define _JSON_H_

/*-----------------------------------Structures-------------------------------*/

/*
 * Introduce a simple structre handling the json file
 */
typedef struct json *Json;

/*--------------Getters---------------*/

/*
 * Get id from structure
 */
char *get_id_json(Json j);

/*
 * Get password from structure
 */
char *get_passwd_json(Json j);

/*----------------------------------------------------------------------------*/


/*
 * Constructor of structure
 */
Json new_json(void);

#endif
