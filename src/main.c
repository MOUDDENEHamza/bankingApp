#include <stdio.h>
#include "displayShell.h"
#include "setting.h"
#include "input.h"

/*Main function*/
int main(int argc, char *argv[]) {
	/*Initialize variables*/
 	int flag = 0;

	/*Start program*/	
        init_bar();//Display the init bar.
	while (quit(&flag)) {//Check if the user want to quit the program
		display_menu();//Display the main menu.
		choose_feature(&flag);//Choose the feature you want to run
		continue;
	}

	return 0;
}
