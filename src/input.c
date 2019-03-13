#include <stdio.h>
#include "input.h"
#include "security.h"

/*
 * Choose the feature you want to run
 */
void choose_feature(Symbol s, int *flag) {
	printf("\nEnter your choice : ");
	scanf("%d", flag);
	set_flag(s , flag);
}

/*
 * Ask to user or administrator to inout the password
 */
void input_passwd(Security p, char *passwd) {
	printf("\nEnter your password : ");
        scanf("%s", passwd);
        set_passwd(p , passwd);
}
