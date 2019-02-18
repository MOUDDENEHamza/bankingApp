#include <stdio.h>
#include "displayShell.h"

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

/*Display the init bar*/
void init_bar(void) {
	printf("
******************************************************************************
");
	printf("
				"GREEN"$$projectName"RESET"			
");
	printf("
******************************************************************************
");
}

/*Display the end bar*/
void end_bar(void) {
        printf("

				"GREEN"THE END"RESET"			
");
        printf("
******************************************************************************

");
}
