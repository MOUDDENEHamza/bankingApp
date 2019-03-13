#include <stdio.h>
#include "displayShell.h"
#include "input.h"
#include "setting.h"


/*Main function*/
int main(int argc, char *argv[]) {
	/*Initialize variables*/
	Symbol s = new_symbol();
	int flag = 0;
	int exit = 1;
	int index = 0;
	set_exit(s, &exit);
        set_flag(s, &flag);
	set_index(s, &index);
        exit = get_exit(s);
        flag = get_flag(s);
	index = get_index(s);

	/*Start program*/	
	init_bar();//Display the init bar.
	display_menu(&exit);//Display the main menu.
	choose_feature(s, &flag);//Choose the feature you want to run
	while (exit){
		handle_menu(s, &flag, &exit, &index);//Define the function handling the main menu
		continue;
	}
	
	return 0;
}
