#include <stdio.h>
#include "displayShell.h"
#include "setting.h"
#include "input.h"

/*Main function*/
int main(int argc, char *argv[]) {

	/*Start program*/	
 	Symbol s = symbol();//Constructor of the symbol structure
 	init_bar();//Display the init bar.
	display_menu(s->exit);//Display the main menu.
	choose_feature(s->flag);//Choose the feature you want to run
	while (s->exit){
		handle_menu(s);//Define the function handling the main menu
		continue;
	}

	return 0;
}
