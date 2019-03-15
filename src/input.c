#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "input.h"

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
void input_id(Account_owner ao, char *id) {
        printf("\nEnter your id : ");
	scanf("%s", id);
        set_id(ao , id);
}

/*
 * Ask to user or administrator to input the password
 */
void input_passwd(Account_owner ao, char *passwd) {
	hide_passwd(passwd);
       	set_passwd(ao , passwd);
}
