#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_

typedef struct _coordonnees* Coordonnees;
Coordonnees new_coordonnees(void);
void set_mail(Coordonnees c, char* m);
void set_telnumber(Coordonnees c, char* t);
void set_adresses(Coordonnees c, char* a);
char* get_mail(Coordonnees c);
char* get_telnumber(Coordonnees c);
char* get_adresses(Coordonnees c);

typedef struct _info_perso* Info_perso;
Info_perso new_Info_perso(void);
void set_nom(Info_perso I, char* n);
void set_prenom(Info_perso I, char* p);
void set_date_de_naissance(Info_perso I, char* da);
void set_coordonnees(Info_perso I, Coordonnees co);
char* get_nom(Info_perso d);
char* get_prenom(Info_perso I);
char* get_date_de_naissance(Info_perso I);
Coordonnees get_coordonnees(Info_perso I);

typedef struct _Compte* Compte;
Compte new_Compte(void);
void set_type(Compte c, char* t);
void set_intitule(Compte c, char* i);
void set_solde(Compte c, float *s);
char* get_type(Compte c);
char* get_intitule(Compte c);
float get_solde(Compte c);

typedef struct _Titulaire_Comptes* Titulaire_Comptes;
Titulaire_Comptes new_Titulaire_Comptes(void);
void set_identifient(Titulaire_Comptes t, int *i);
void set_passeword(Titulaire_Comptes t, int *p);
void set_info(Titulaire_Comptes t, Info_perso i);
void set_list_comptes(Titulaire_Comptes t, Compte c);
int get_identifient(Titulaire_Comptes t);
int get_passeword(Titulaire_Comptes t);
Info_perso get_info(Titulaire_Comptes t);
Compte get_list_comptes(Titulaire_Comptes t);

void creer_compte(Titulaire_Comptes t);
void modifier_compte(Titulaire_Comptes t);
void supprimer_compte(Titulaire_Comptes t);
void afficher_list_comptes(Titulaire_Comptes t);
void ajouter_client();
void modifier_infos_client(Titulaire_Comptes t);
void afficher_list_titulaires(Compte c);
void changer_mot(Compte c);

#endif
