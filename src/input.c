#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "input.h"

#define SIZE 255

/*
 * Choose the feature you want to run
 */
void choose_feature(Symbol s, int *flag) {
	printf("\nEnter your choice : ");
	scanf("%d", flag);
	set_flag(s , flag);
}

/*
 * input and encrypt the password by putting * character
 */
void hide_passwd(char *passwd) {
	char *in = passwd;
        struct termios  tty_orig;
	tcgetattr(STDIN_FILENO, &tty_orig);
        char c;
        struct termios  tty_work = tty_orig;
        tcgetattr(STDIN_FILENO, &tty_orig);
        tty_work.c_lflag &= ~(ECHO | ICANON);
        tty_work.c_cc[VMIN]  = 1;
        tty_work.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty_work);
        write(STDOUT_FILENO, "\nPlease enter your password : ", 30);
	while (1) {
                if (read(STDIN_FILENO, &c, sizeof c) > 0) {
                        if ('\n' == c) {
                                break;
                        }
                        *in++ = c;
                        write(STDOUT_FILENO, "*", 1);
                }
        }
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty_orig);
        *in = '\0';
        fputc('\n', stdout);
}

/*
 * Ask to user or administrator to input the id
 */
void input_id(Client client,char *id) {
        printf("\nEnter your id : ");
	scanf("%s", id);
        set_id(client , id);
}

/*
 * Ask to user or administrator to input the password
 */
void input_passwd(Client client,char *passwd) {
	hide_passwd(passwd);
       	set_passwd(client , passwd);
}

/*
 * Ask to user or administrator to input her last name
 */
void input_last_name(Client client){
        char *last_name = malloc(SIZE);
        printf("\nEnter your last name : ");
        scanf("%s", last_name);
        set_last_name(get_perso_info(client), last_name);
}

/*
 * Ask to user or administrator to input her first name
 */
void input_first_name(Client client){
        char *first_name = malloc(SIZE);
        printf("\nEnter your first name : ");
        scanf("%s", first_name);
        set_last_name(get_perso_info(client), first_name);
}

/*
 * Ask to user or administrator to input his Email address
 */
void input_mail(Client client){
        char *mail = malloc(SIZE);
        printf("\nEnter your Email-address : ");
        scanf("%s", mail);
        set_mail(get_coordinates(get_perso_info(client)), mail);
}

/*
 * Ask to user or administrator to input her phone number
 */
void input_phone(Client client){
        char *phone = malloc(SIZE);
        printf("\nEnter your phone number : ");
        scanf("%s", phone);
        set_phone(get_coordinates(get_perso_info(client)), phone);
}

/*
 * Ask to user or administrator to input his address
 */
void input_address(Client client){
        char *address = malloc(SIZE);
        printf("\nEnter your address : ");
        scanf("%s", address);
        set_address(get_coordinates(get_perso_info(client)), address);
}

/*
 * Ask to user or administrator to input his birthday
 */
void input_birthday(Client client){
        char *birthday = malloc(SIZE);
        printf("\nEnter your birthday : ");
        scanf("%s", birthday);
        set_birthday(get_perso_info(client), birthday);
}

/*
 * input all personnal information
 */
void input_perso_info(Client client){
	FILE *fp = fopen("data/account_list.json", "a+");
	printf("\nAdd client...\n");
	input_last_name(client);
        input_first_name(client);
        input_mail(client);
        input_phone(client);
        input_birthday(client);
        input_address(client);
	fprintf(fp,"{\n\t\"last name\" : \"%s\",\n\t\"first name\" : \"%s\",\n\t\"email\" : \"%s\",\n\t\"phone\" : \"%s\",\n\t\"birthday\" : \"%s\",\n\t\"address\" : \"%s\"\n}\n", get_last_name(get_perso_info(client)), get_first_name(get_perso_info(client)), get_mail(get_coordinates(get_perso_info(client))), get_phone(get_coordinates(get_perso_info(client))), get_birthday(get_perso_info(client)), get_address(get_coordinates(get_perso_info(client))));
	printf("\nClient added. back to administrator menu.\n");
	fclose(fp);
}

/*
 * Ask to the administrator de to enter a new balance
 */
void input_new_balance(Account account){
        float balance;
        printf("\nEnter new balance :");
        scanf("%f", &balance);
        set_balance(account, &balance);
}
