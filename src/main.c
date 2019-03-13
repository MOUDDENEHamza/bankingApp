#include <stdio.h>
#include <string.h>
#include "displayShell.h"
#include "input.h"
#include "setting.h"
#include "security.h"
#include "json.h"

/*Main function*/
int main(int argc, char *argv[]) {
	/*Initialize variables*/
	Symbol s = new_symbol();
	Security p = new_security();
	Json j = new_json();
	int flag = 0;
	int exit = 1;
	int index = 0;
	char passwd[255] = "";
	char id[255] = "";
	set_exit(s, &exit);
        set_flag(s, &flag);
	set_index(s, &index);
	set_passwd(p, passwd);
	set_id(p, passwd);
        exit = get_exit(s);
        flag = get_flag(s);
	index = get_index(s);
	strcpy(passwd, get_passwd(p));
	strcpy(id, get_id(p));
	printf("ID : %s\n", get_id_json(j));
        printf("Passwd : %s\n", get_passwd_json(j));
	/*Start program*/	
	init_bar(); //Display the init bar.
	display_menu(&exit); //Display the main menu.
	choose_feature(s, &flag); //Choose the feature you want to run
	while (exit){
		handle_menu(s, p, &flag, &exit, &index, passwd, id); //Define the function handling the main menu
		continue;
	}
	
	return 0;
}
