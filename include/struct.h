#ifndef _STRUCT_H_
#define _STRUCT_H_

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre handling the menu
 */
typedef struct symbol *Symbol;

/*-------------Constructor------------*/

/*
 * Constructor of symbol structure
 */
Symbol new_symbol(void);

/*---------------Getters--------------*/

/*
 *Get flag value from the structure
 */
int get_flag(Symbol s);

/*
 *Get exit value from the structure
 */
int get_exit(Symbol s);

/*
 *Get index value from the structure
 */
int get_index(Symbol s);

/*--------------Setters---------------*/

/*
 *Set value to flag in structure
 */
void set_flag(Symbol s ,int *val);

/*
 *Set value to exit in structure
 */
void set_exit(Symbol s ,int *val);

/*
 *Set value to index in structure
 */
void set_index(Symbol s, int *val);

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre handling the connexion feauture
 */
typedef struct security *Security;

/*-------------Constructor------------*/

/*
 * Constructor of the structure
 */
Security new_security(void);

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

/*-----------------------------------Structures-------------------------------*/

/*
 * Introduce a simple structre handling the json file
 */
typedef struct json *Json;

/*-------------Constructor------------*/

/*
 * Constructor of structure
 */
Json new_json(void);

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

#endif
