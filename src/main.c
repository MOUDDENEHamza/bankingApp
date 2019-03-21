#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "displayShell.h"
#include "input.h"
#include "setting.h"
#include "security.h"

#define SIZE 255

/*Main function*/
int main(int argc, char *argv[]) {
	/*Initialize variables*/
	Symbol s = new_symbol();
	Client client = new_client();
	Json j = NULL;
	int log_in;
	int exit = get_exit(s);
    int flag = get_flag(s);
	int index = get_index(s);
	char id[SIZE], passwd[SIZE];
	strcpy(id, get_id(client));
	strcpy(passwd, get_passwd(client));
	/*Start program*/	
	init_bar(); //Display the init bar.
	back:
	log_in = 0;
	display_menu(&exit); //Display the main menu.
	choose_feature(s, &flag); //Choose the feature you want to run
	while (exit){
		handle_menu(s, client, j, &flag, &exit, &index, passwd, id, &log_in); //Define the function handling the main menu
		if ((flag == 1 && index == 3) || (flag == 2 && index == 4)) {
			goto back;//If the user want to sign out the submenu
		} 
		continue;
	}
	return 0;
}
