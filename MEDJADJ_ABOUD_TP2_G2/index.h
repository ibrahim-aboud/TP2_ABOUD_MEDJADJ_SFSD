#include "fonctions.h"
#ifndef INDEX_H_INCLUDED
#define INDEX_H_INCLUDED

/**==={ STRUCTURES UTILISÉES Pour Les Indexes (selon l'attribus) }===**/


/*____________INDEXES MATRICULE______________*/

/*MEMOIRE CENTRALE*/

// un tableau de 888889 cases (corespondant a 888889 valeurs possibles pour le matricule) (les case contient les coordonee de l'enreg)
// la cle ici c'est le matricule qui vas etre inseree directement dans la case avec l'indice correspondant du tableau
// ex: 111 111 -> 0  | 111 222 -> 111 | 999 999 -> 888 888 ... etc
// tout case non occupe vas avoir le boolean "exist" a faux


typedef struct Tenr_ind_mat Tenr_ind_mat;

struct Tenr_ind_mat {
    int i;                                                      // numero du bloc ou se situe l'enregistrment
    int j;                                                      // numero de l'enregistrement a l'interieur du bloc
    bool exist;                                                 // si l'enregistrement existe dans le fichier ou pas
};


Tenr_ind_mat ind_mat[MAX_INDEX_MAT];


/*____________INDEXES SPECIALITE______________*/

/*MEMOIRE CENTRALE*/

// il ya 10 specialitees, donc on propose un tableau de 10 cases,
// chaqu'un contenant la tete d'une liste des enregistrements existants ayant la meme specialitee
// pour savoir la specialitee, on refere au variable globale (specialite)

typedef struct Tenr_mat Tenr_mat;

struct Tenr_mat{
    int matricule;
    Tenr_mat* suivant;
};

typedef Tenr_mat* ptr_enr_mat;

ptr_enr_mat ind_sp[MAX_INDEX_SP];


/*____________INDEXES Etablissement/Region______________*/

/*MEMOIRE CENTRALE*/

// meme concept de l'index specialite, on utilisera l'astuce que l'etablissement est liee a la region
// ou il se situe

typedef struct Tcase_tab_Et_Reg Tcase_tab_Et_Reg;

struct Tcase_tab_Et_Reg {
    char Region;                                                // 'O' pour Ouest, 'E' pour Est et 'C' pour Centre
    Tenr_mat* Tete;
};

Tcase_tab_Et_Reg ind_et_reg[MAX_INDEX_UNIV];

/*____________INDEXES Ancientee______________*/

/*MEMOIRE CENTRALE*/

// un tableau ordonne selon la date de recrutement
// chaque case contient une liste d'enregistrement
// indiquant les matricules ayant la meme date de recrutement

typedef struct Tcase_tab_Anc Tcase_tab_Anc;

struct Tcase_tab_Anc {
    int Date_Recrut;
    Tenr_mat* Tete;
};

//typedef Tcase_tab_Anc* Tp_ind_anc;
Tcase_tab_Anc ind_anc[MAX_INDEX_MAT];
int nbIndAnc;

/*MEMOIRE SECONDAIRE*/
/*_______TOF________*/

typedef struct Tenreg_anc{                                      // maintenant le fichier est ordonnee
    int dt_de_recrut;
    int matricule;
    bool supprimee;                                             // on ajoutera un bit de presence pour chaque enregistrement (pour suppression logique)
}Tenreg_anc;

typedef struct Bloc_anc{
    Tenreg_anc Tab[MAX_TAILLE_BLOC];
    int Nb;
}Bloc_anc;

typedef struct Bloc_entete_anc{
    int Der_bloc,Insertion,Suppression;
}Bloc_entete_anc;

typedef struct Fich_anc{
    FILE* f;
    Bloc_entete_anc entete_anc;
}Fich_anc;


/**===============FONCTION DE MANIPULATION D'INDEXE ================**/

void Anc_FERMER(Fich_anc* F);
void  Anc_OUVRIR(Fich_anc* F, char* nomFichier, char mode);
int init_ind_mat();
int init_ind_sp();
int init_ind_et_reg();
int init_ind_anc();
void rechDichoIncAnc(int dateRecrut, bool* trouv, int* k);
void insIndAnc(int dateRecrut, int matricule);
void Anc_Sauv(Fich_anc F,char nom_fich[30]);
void Anc_affiche_TOF(Fich_anc F,char nom_fich[30]);
void insIndMat(int matricule, int i, int j);
void insIndSp(int matricule, int spec);
void insIndEtReg(int matricule, int etab_univ);
void Anc_charg(Fich_anc F,char nom_fich[30]);
void rechListeMat(ptr_enr_mat tete, int matricule, bool* trouv, ptr_enr_mat* p, ptr_enr_mat* prec);
void supprListeMat(ptr_enr_mat* tete, int matricule);

#endif // INDEX_H_INCLUDED
