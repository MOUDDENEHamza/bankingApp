#ifndef _DISPLAYSHELL_H_
#define _DISPLAYSHELL_H_

#include "setting.h"

/*
 * Display the init bar
 */
void init_bar(void);

/*
 * Display the main menu
 */
void display_menu(int *exit);

/*
 * Display the home menu
 */
void display_client(int *exit);

/*
 * Display the settings menu
 */
void display_administrator(int *exit);

/*
 * Display the end bar
 */
void end_bar(void);

#endif
