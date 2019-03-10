#include <stdio.h>
#include "setting.h"
#include "displayShell.h"

/*
 * Define the exit feature
 */
int quit(int *flag) {
	if (*flag == 3) {
		printf("\nGOODBYE!\n");
		end_bar();//Display the end bar.
		return 0;
	}
	return 1;
}
