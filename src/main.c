#include <stdio.h>
#include "../include/displayShell.h"
#include "../include/input.h"
#include "../include/setting.h"


/*Main function*/
int main(int argc, char *argv[]) {
	int value = 1;
	/*Start program*/	
 	Symbol s = new_symbol();
	s->exit = 1;
	printf("\nOKKKKKKKKKK : %d\n", s->exit);
	init_bar();//Display the init bar.
	display_menu(&s->exit);//Display the main menu.
	choose_feature(&s->flag);//Choose the feature you want to run
	while (s->exit){
		handle_menu(s);//Define the function handling the main menu
		continue;
	}

	return 0;
}
