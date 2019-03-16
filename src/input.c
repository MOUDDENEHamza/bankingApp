#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "../include/input.h"

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
        char *last_name;
        printf("\nEnter your last name :");
        scanf("%s",last_name);
        set_last_name(get_perso_info(client),last_name);
}

/*
 * Ask to user or administrator to input her first name
 */

void input_first_name(Client client){
        char *first_name;
        printf("\nEnter your first name :");
        scanf("%s",first_name);
        set_last_name(get_perso_info(client),first_name);
}

/*
 * Ask to user or administrator to input his Email address
 */

void input_mail(Client client){
        char *mail;
        printf("\nEnter your Email-address :");
        scanf("%s",mail);
        set_mail(get_coordinates(get_perso_info(client)),mail);
}

/*
 * Ask to user or administrator to input her phone number
 */

void input_phone(Client client){
        char *phone;
        printf("\nEnter your phone number :");
        scanf("%s",phone);
        set_phone(get_coordinates(get_perso_info(client)),phone);
}

/*
 * Ask to user or administrator to input his address
 */

void input_address(Client client){
        char *address;
        printf("\nEnter your address :");
        scanf("%s",address);
        set_address(get_coordinates(get_perso_info(client)),address);
}

/*
 * Ask to user or administrator to input his birthday
 */

void input_birthday(Client client){
        char *birthday;
        printf("\nEnter your birthday :");
        scanf("%s",birthday);
        set_birthday(get_perso_info(client),birthday);
}

/*
 * input all personnal information
 */

void input_perso_info(Client client){
        input_last_name(client);
        input_first_name(client);
        input_mail(client);
        input_phone(client);
        input_birthday(client);
        input_address(client);
}

/*
 * Ask to the administrator de to enter a new balance
 */

void input_new_balance(Account account){
        float* balance;
        printf("\nEnter new balance :");
        scanf("%s",balance);
        set_balance(account,balance);
}
