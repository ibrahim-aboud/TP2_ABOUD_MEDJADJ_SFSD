#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "display.h"
#include <stdbool.h>
#include "LnOF.h"

bool ouvert;

typedef struct Type_est_ouvert {

    int type;     // 1: principal,   2: decodé
    int numero;     // de 0 à ..

} Type_est_ouvert;
Type_est_ouvert est_ouvert;

/**Les fonctions globales presents dans le menu principale**/

void selectionner(char* str_array[], int tai, int x, int* y, int debut);

void loading_page();

void menu(int debut);

void creer_ouvrirFich(TypeFich* Fich, Fich_anc* FichAnc);

void affichage(TypeFich Fich);

void ajouter(TypeFich* Fich);

void modif_supp(TypeFich* Fich);

void de_code(TypeFich* Fich);

int apropos();

#endif // MENUS_H_INCLUDED
