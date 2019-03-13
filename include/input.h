#ifndef _INPUT_H_
#define _INPUT_H_

#include "setting.h"

/*
 * Switch a integer to string
 */
char* integer_to_string(int *val);

/*
 * Check if the input is an integer
 */
int is_integer(int *val);


/*
 * Choose the feature you want to run
 */
void choose_feature(Symbol s, int *flag);

#endif
