#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_NOM_PRENOM 30
#define MAX_TAILLE_BLOC 1024
#define MAX_INDEX_MAT 888889
#define MAX_INDEX_SP 10
#define MAX_INDEX_UNIV 112
#define MAX_NOM_UNIV 112
#define MAX_INDEX_WILAYA 58
#define MAX_NOM_WILAYA 22

/*ces structures sont des tableaux de correspondance afin de manipuler des entiers, et apres faire reference*/
/*a ces structures, pour par example afficher une information ... etc*/

char wilaya[MAX_INDEX_WILAYA][22];
char etablissement[MAX_INDEX_UNIV][MAX_NOM_UNIV];
char *grp_sanguin[8];
char *grade[6];
char *diplome[6];
char *specialite[MAX_INDEX_SP];
char *sexe[2];

// afin de faciliter la recherche des matricules selon plusieur attributs en meme temps


bool *tableau_bit_map;

// variables principales pour compter le nombre de lectures et d'ecritures en MS

int nombre_lect;
int nombre_ecr;


#endif // MAIN_H_INCLUDED
