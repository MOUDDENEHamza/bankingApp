#include <stdio.h>
#include "displayShell.h"
#include "setting.h"
#include "input.h"

/*Main function*/
int main(int argc, char *argv[]) {
	/*Initialize variables*/
 	int flag = 0;
	int exit = 3;

	/*Start program*/	
        init_bar();//Display the init bar.
	display_menu(&exit);//Display the main menu.
	choose_feature(&flag);//Choose the feature you want to run
	handle_menu(&flag, &exit);//Define the function handling the main menu 
	while (quit(&flag, &exit)) {//Check if the user want to quit the program
		handle_menu(&flag, &exit);//Define the function handling the main menu	
		continue;
	}

	return 0;
}
