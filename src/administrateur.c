#include <stdio.h>
#include <stdlib.h>
#include "../include/administrateur.h"

typedef struct _coordonnees
{
    char* mail;
    char* telnumber;
    char* adresses;
}_coordonnees;

void set_mail(Coordonnees c, char* m){
    c->mail=m;
}

void set_telnumber(Coordonnees c, char* t){
    c->telnumber=t;
}

void set_adresses(Coordonnees c, char* a){
    c->adresses=a;
}

char* get_mail(Coordonnees c){
    return c->mail;
}

char* get_telnumber(Coordonnees c){
    return c->telnumber;
}

char* get_adresses(Coordonnees c){
    return c->adresses;
}


typedef struct _info_perso
{
    char* nom;
    char* prenom;
    char* date_de_naissance;
    Coordonnees coordonnees;
}_info_perso;

void set_nom(Info_perso I, char* n){
    I->nom=n;
}

void set_prenom(Info_perso I, char* p){
    I->prenom=p;
}

void set_date_de_naissance(Info_perso I, char* da){
    I->date_de_naissance=da;
}

void set_coordonnees(Info_perso I, Coordonnees co){
    I->coordonnees=co;
}

char* get_nom(Info_perso d){
    return d->nom;
}

char* get_prenom(Info_perso I){
    return I->prenom;
}

char* get_date_de_naissance(Info_perso I){
    return I->date_de_naissance;
}

Coordonnees get_coordonnees(Info_perso I){
    return I->coordonnees;
}


typedef struct _Compte
{
    char* type;
    char* intitule;
    float solde;
}_Compte;

void set_type(Compte c, char* t){
    c->type=t;
}

void set_intitule(Compte c, char* i){
    c->intitule=i;
}

void set_solde(Compte c, float *s){
    c->solde=*s;
}

char* get_type(Compte c){
    return c->type;
}

char* get_intitule(Compte c){
    return c->intitule;
}

float get_solde(Compte c){
    return c->solde;
}


typedef struct _Titulaire_Comptes
{
    int identifient;
    int passeword;
    Info_perso info;
    Compte list_comptes;
}_Titulaire_Comptes;

void set_identifient(Titulaire_Comptes t, int *i){
    t->identifient=*i;
}

void set_passeword(Titulaire_Comptes t, int *p){
    t->passeword=*p;
}

void set_info(Titulaire_Comptes t, Info_perso i){
    t->info=i;
}

void set_list_comptes(Titulaire_Comptes t, Compte c){
    t->list_comptes=c;
}

int get_identifient(Titulaire_Comptes t){
    return t->identifient;
}

int get_passeword(Titulaire_Comptes t){
    return t->passeword;
}

Info_perso get_info(Titulaire_Comptes t){
    return t->info;
}

Compte get_list_comptes(Titulaire_Comptes t){
    return t->list_comptes;
}

void creer_compte(Titulaire_Comptes t){

}

void modifier_compte(Titulaire_Comptes t){

}

void supprimer_compte(Titulaire_Comptes t){
    free(t);
}

void afficher_list_comptes(Titulaire_Comptes t){

}

void ajouter_client(){

}

void modifier_infos_client(Titulaire_Comptes t){

}

void afficher_list_titulaires(Compte c){

}

void changer_mot(Compte c){
    
}