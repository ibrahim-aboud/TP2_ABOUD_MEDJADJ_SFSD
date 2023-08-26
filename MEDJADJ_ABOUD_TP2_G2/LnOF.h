#include "index.h"
#ifndef LNOF_H_INCLUDED
#define LNOF_H_INCLUDED

/**==={ STRUCTURES UTILISÉES Pour le fichier principale }===**/

typedef struct TypeEnreg {
    int matricule;                                              // Entre "111111" et "999999"
    char nom[MAX_NOM_PRENOM];                                   // Taille de chaine : entre 4 et 30
    char prenom[MAX_NOM_PRENOM];
    int date_Naissance;                                         // Entier de 8 chiffres : AAAAMMJJ
    int wilaya_Naissance;                                       // Liee a une table de correspondence
    int sexe;                                                   // 1 pour masculin et 2 pour feminin
    int groupe_sanguin;                                         // Liee a une table de correspondence
    int date_recrutement;                                       // Entier de 8 chiffres : AAAAMMJJ
    int grade;                                                  // Liee a une table de correspondence
    int specialite;                                             // Liee a une table de correspondence
    int dernier_diplome;                                        // Liee a une table de correspondence
    int etablissement_univ;                                     // Liee a une table de correspondence
} TypeEnreg;

typedef struct TypeBloc {
    TypeEnreg T[MAX_TAILLE_BLOC] ;                             // Le bloc est un tableau d'enregistrement
    int nb;                                                     // Indiquer le nombre d'enregistrement insere
    int suiv;                                                   // Une liste de blocs implique que chaque bloc a un suivant
}TypeBloc;

typedef struct TypeEntete {
    int tete;                                                   // Tete de la liste principal
    int queue;                                                  // Queue de la liste pour acces rapide a la fin
    int nb_enr_ins;                                             // nombre d'enregistrements inserés
    int liste_vide;                                             // Au cas ou on aura a supprimer des bloc entier, on genere une liste des blocs vides
    int taille;
    struct tm tm;
}TypeEntete;

typedef struct TypeFich {
    TypeEntete entete;                                          // L'entete avec les informations importante dedans
    FILE* fptr;                                                 // pointeur vers fichier
    char nomFich[30];
}TypeFich;

/**======================MACHINE ABSTRAITE===========================**/

void OUVRIR(TypeFich* F, char* nomFich, char mode);
void FERMER(TypeFich* F);
void LireDir(TypeFich F, int i, TypeBloc* buf);
void EcrireDir(TypeFich* F, int i, TypeBloc buf);
int ENTETE(TypeFich F, int i_caract);
void AFF_ENTETE(TypeFich* F, int i_caract, int val);
int ALLOC_BLOC(TypeFich* F);


/**===FONCTION DE MANIPULATION EN RELATION AVEC LE FICHIER EN MS=====**/

int genMatricule();
void genPre_Nom(char pre_nom[MAX_NOM_PRENOM]);
int genDate(int min, int max) ;
void genEnreg(TypeEnreg* e);
void affiche_Fich(TypeFich F);
int ins_enreg(TypeFich* F, TypeEnreg data);
void chargement_initial(TypeFich* F, int n);
void modif_et_reg(TypeFich* F,int matricule,int nouv_etab);
void suppr_enr(TypeFich* F, int matricule);
void Index_charg(TypeFich *F);
void suppr_all_spec(TypeFich *F,int spec);
void affiche_ens_region(const char region,TypeFich *F);
int affiche_ens_etab_anc(int etab, int date_min, int date_max,TypeFich *F);
int coder(FILE* F_origin,char* nom_fich_res,char* cle,int taille_cle);
int decoder(char* nom_fich_coded,char*nom_fich_decoded,char* cle,int taille_cle);

#endif // LNOF_H_INCLUDED
