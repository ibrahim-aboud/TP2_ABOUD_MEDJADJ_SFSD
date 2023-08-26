#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include "main.h"
#include "LnOF.h"

/**----------{ FONCTIONS DE BASE }----------**/

/*Des fonction general qui n'ont pas une relation directe avec le fichier MS*/

int filtreur_mot(char* ligne,int taille_ligne);
int charg_Tab_Wilaya(char T_Wilaya[MAX_INDEX_WILAYA][MAX_NOM_WILAYA],char *nom_fichier);
int charg_Tab_Etablissement(char T_Etablissement[MAX_INDEX_UNIV][MAX_NOM_UNIV],char *nom_fichier);
int init_bit_map();
int fichier_existant(const char* fname);
void secure_read(int x, int y, char input[30], int max);
void maj_taille_fich(TypeFich* Fich);
int check_date(int y, int m, int d, int minY, int maxY);
void selectionner_fichier(int x, int* y, int debut);
#endif // FONCTIONS_H_INCLUDED
