#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include "input.h"
#include "admin.h"
#include "json.h"
#include "displayShell.h"

#define SIZE 64

/*
 * Choose the feature you want to run
 */
void choose_feature(Symbol s, int *flag) {
    printf("\nEnter your choice : ");
    scanf("%d", flag);
    set_flag(s, flag);
}

/*
 * input and encrypt the password by putting * character
 */
void hide_passwd(char *passwd) {
    char *in = passwd;
    struct termios tty_orig;
    tcgetattr(STDIN_FILENO, &tty_orig);
    char c;
    struct termios tty_work = tty_orig;
    tcgetattr(STDIN_FILENO, &tty_orig);
    tty_work.c_lflag &= ~(ECHO | ICANON);
    tty_work.c_cc[VMIN] = 1;
    tty_work.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty_work);
    write(STDOUT_FILENO, "\nEnter your password : ", 24);
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
 * Generate unique id for the client
 */
void generate_unique_id(Client client) {
    srand(clock());
    char *id = (char *) malloc(SIZE);
    int t = 0;
    char *szTemp = "xxxxxxxx";
    char *szHex = "0123456789ABCDEF-";
    int nLen = strlen(szTemp);
    for (t = 0; t < nLen + 1; t++) {
        int r = rand() % 16;
        char c = ' ';
        switch (szTemp[t]) {
            case 'x' : {
                c = szHex[r];
            }
                break;
            case 'y' : {
                c = szHex[r & 0x03 | 0x08];
            }
                break;
            case '-' : {
                c = '-';
            }
                break;
            case '4' : {
                c = '4';
            }
                break;
        }
        id[t] = (t < nLen) ? c : 0x00;
    }
    write(STDOUT_FILENO, "\nAdd client : loading...\n", 25);
    printf("\ngenerate ID : %s\n", id);
    set_id(client, id);
}

/*
 * Ask to client to input his id
 */
void input_id(char *id) {
    printf("\nEnter the client id : ");
    scanf("%s", id);
}

/*
 * Ask to user or administrator to input the password
 */
void input_passwd(char *passwd) {
    hide_passwd(passwd);
}

/*
 * Ask to user to create his own password
 */
void create_passwd(Client client) {
    char *passwd = (char *) malloc(SIZE);
    hide_passwd(passwd);
    set_passwd(client, passwd);
}

/*
 * Ask to user or administrator to input her last name
 */
void input_last_name(Client client) {
    char *last_name = (char *) malloc(SIZE);
    printf("\nEnter the client last name : ");
    scanf("%s", last_name);
    set_last_name(get_perso_info(client), last_name);
}

/*
 * Ask to user or administrator to input her first name
 */
void input_first_name(Client client) {
    char *first_name = (char *) malloc(SIZE);
    printf("\nEnter the client first name : ");
    scanf("%s", first_name);
    set_first_name(get_perso_info(client), first_name);
}

/*
 * Ask to user or administrator to input his Email address
 */
void input_mail(Client client) {
    char *mail = (char *) malloc(SIZE);
    printf("\nEnter the client E-mail : ");
    scanf("%s", mail);
    set_mail(get_coordinates(get_perso_info(client)), mail);
}

/*
 * Ask to user or administrator to input her phone number
 */
void input_phone(Client client) {
    char *phone = (char *) malloc(SIZE);
    printf("\nEnter the client phone : ");
    scanf("%s", phone);
    set_phone(get_coordinates(get_perso_info(client)), phone);
}

/*
 * Ask to user or administrator to input his birthday
 */
void input_birthday(Client client) {
    char *birthday = (char *) malloc(SIZE);
    printf("\nEnter the client birthday at format DD/MM/YYYY : ");
    back:
    scanf("%s", birthday);
    if(format_birthday(birthday)!=0){
        printf("\nYou need to enter the birthday at format DD/MM/YYYY !\n");
        printf("\nTry again : ");
        goto back;
    }
    set_birthday(get_perso_info(client), birthday);
}

/*
 * input all personnal information
 */
Client input_perso_info(Client client) {
    generate_unique_id(client);
    input_last_name(client);
    input_first_name(client);
    input_birthday(client);
    input_mail(client);
    input_phone(client);
    create_passwd(client);
    return client;
}

/*
 * Ask to the administrator de to enter a new balance
 */
void input_new_balance(Account a) {
    float balance;
    printf("\nEnter new balance : ");
    scanf("%f", &balance);
    set_balance(a, &balance);
}

void input_ida(Account a) {
    char*ida=malloc(sizeof(char*));
    long long int t= (long long int)time(NULL)*100+rand()%100;
    sprintf(ida,"%lld",ida);
    set_ida(a,ida);
}

/* input the account type choosen*/
void input_type(Account a, int *choice) {
    char *type =malloc(sizeof(char*));
    switch (*choice) {
        case 1 :
            strcpy(type, "CURRENT");
            set_type(a, type);
            break;
        case 2 :
            strcpy(type, "SAVINGS");
            set_type(a, type);
            break;
        case 3 :
            strcpy(type, "TERM");
            set_type(a, type);
            break;
        case 4 :
            strcpy(type, "TITLE");
            set_type(a, type);
            break;
        case 5 :
            strcpy(type, "INDIVIDUAL");
            set_type(a, type);
            break;
        case 6 :
            strcpy(type, "JOINT");
            set_type(a, type);
            break;
        default :
            display_wrong();
            break;
    }
}

/*input the entitled of the account*/
void input_entitled(Client client, Account a) {
    int choice;
    char *choice_char;
    char *civility = malloc(sizeof(char*));
    back:
    choice_char = malloc(sizeof(char*));
    printf("\n\nPlease specify, e.g.\n\t1 : Dr.\n\t2 : Mr.\n\t3 : Ms.\n\t4 : Mrs.\n\t5 : other\n");
    scanf("%s", choice_char);
    choice = atoi(choice_char);
    switch (choice)
    {
        case 1 :
            strcpy(civility , "Dr. ");
            break;
        
        case 2 :
            strcpy(civility , "Mr. ");

            break;

        case 3 :
            strcpy(civility , "Ms. ");
            break;

        case 4 :
            strcpy(civility , "Mrs. ");
            break;

        case 5 :
            strcpy(civility , ". ");
            break;
    
        default:
            display_wrong();
            goto back;
            break;
    }
    char *entitled = malloc(sizeof(char*));
    char* ent1=concatenate(civility,get_first_name(get_perso_info(client)));
    char* ent2=concatenate(ent1," ");
    entitled=concatenate(ent2,get_last_name(get_perso_info(client)));
    set_entitled(a, entitled);
}


void input_entitled_joint(Client client, Client client_joint){
    char* entitled_joint = concatenate(concatenate(get_entitled(get_account(client))," and "),get_entitled(get_account(client_joint)));
    set_entitled(get_account(client),entitled_joint);
    set_entitled(get_account(client_joint),entitled_joint);
}


/*input all account information*/
void input_create_account(Client client) {
    int choice_type;
    scanf("%d",&choice_type);
    input_type(get_account(client), &choice_type);
    input_ida(get_account(client));
    input_entitled(client,get_account(client));
    input_new_balance(get_account(client));
    set_account(client, get_account(client));
}


/*input a new account*/
Client input_add_account(Client client) {
    int choice;;
    Client temp=new_client();
    set_id(temp,get_id(client));
    set_passwd(temp,get_passwd(client));
    set_perso_info(temp,get_perso_info(client));
    Account a=new_account();
    input_ida(a);
    set_entitled(a,get_entitled(get_account(client)));
    scanf("%d",&choice);
    input_type(a,&choice);
    input_new_balance(a);
    set_account(temp,a);
    set_nextAccount(get_account(temp),get_account(client));
    return temp;
}
/*
Client input_add_account000joint(Client client) {
    Client temp=new_client();
    set_id(temp,get_id(client));
    set_passwd(temp,get_passwd(client));
    set_perso_info(temp,get_perso_info(client));
    Account a=new_account();
    input_new_balance(a);
    set_account(temp,a);
    set_nextAccount(get_account(temp),get_account(client));
    return temp;
}*/

Client input_add_account_joint(Client client,Client client_joint){
    Client temp=new_client();
    set_id(temp,get_id(client_joint));
    set_passwd(temp,get_passwd(client_joint));
    set_perso_info(temp,get_perso_info(client_joint));
    char* entitled_joint = concatenate(concatenate(get_entitled(get_account(client))," and "),get_entitled(get_account(client_joint)));
    set_entitled(get_account(client),entitled_joint);
    Account a=new_account();
    set_ida(a,get_ida(get_account(client)));
    set_entitled(a,entitled_joint);
    set_type(a,"JOINT");
    float balance=get_balance(get_account(client));
    set_balance(a,&balance);
    set_account(temp,a);
    set_nextAccount(get_account(temp),get_account(client_joint));
    return temp;
}


//void set_entitled_joint(Client client){}
