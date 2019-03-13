#ifndef _JSON_H_
#define _JSON_H_

/*-----------------------------------Structures-------------------------------*/

/*
 * Introduce a simple structre handling the json file
 */
struct json_object *parsed_json;

/*
 * Introduce a simple structre handling the json file's item
 */
struct json_object *last_name, *first_name, *id, *passwd;

/*--------------Getters---------------*/

/*
 * Get last name from structure
 */
void get_last_name_json(void);

/*
 * Get first name from structure
 */
void get_first_name_json(void);

/*
 * Get id from structure
 */
void get_id_json(void);

/*
 * Get password from structure
 */
void get_passwd_json(void);

/*----------------------------------------------------------------------------*/


/*
 * Open the file in reading mode
 */
void open_file(char *file_name, char *buffer);

/*
 * Close the file
 */
 void close_file(FILE *fp, char *buffer);

#endif
