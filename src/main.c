#include <stdio.h>
#include "../include/displayShell.h"
#include "../include/input.h"
#include "../include/setting.h"


/*Main function*/
int main(int argc, char *argv[]) {
	int value1 = 0;
	int value2 = 1;
	/*Start program*/	
 	Symbol s = new_symbol();
	set_exit(s,&value1);
	set_flag(s,&value2);
	int texit = get_exit(s);
	int tflag = get_flag(s);
	printf("\nOKKKKKKKKKK : %d\n", get_exit(s));
	init_bar();//Display the init bar.
	printf("nada");
	display_menu(&texit);//Display the main menu.
	printf("nada");
	choose_feature(&tflag);//Choose the feature you want to run
	while (get_flag(s)){
		handle_menu(s);//Define the function handling the main menu
		continue;
	}

	return 0;
}
