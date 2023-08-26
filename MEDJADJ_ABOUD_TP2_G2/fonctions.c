#include "LnOF.h"
#include "display.h"
#include <conio.h>

/**----------{ FONCTIONS DE BASE }----------**/

// cette fonction enleve le saut de ligne a la fin de chaque mot
int filtreur_mot(char* ligne,int taille_ligne) {
    bool stop = false;
    int cpt =0;
    while(!stop){                    // quand on rencontre le saut de ligne, on l'enleve
        if (ligne[cpt]=='\n'){
            stop=true;
            ligne[cpt]='\0';
        }
        cpt++;
    }
    return 0;
}

// chargement de memoire secondaire (fich txt) ver la memoir centrale
int charg_Tab_Wilaya(char T_Wilaya[MAX_INDEX_WILAYA][MAX_NOM_WILAYA],char *nom_fichier) {
    FILE *f = NULL;
    int i;
    char ligne[MAX_NOM_WILAYA];
    f=fopen(nom_fichier,"r");
    rewind(f);
    if (f==NULL) {
        fclose(f);
        return 1;
    }
    for (i=0;i<MAX_INDEX_WILAYA;i++){                   // lecture consecutive de chaque ligne
        if(!feof(f)){
            fgets(ligne,sizeof(ligne),f);
            filtreur_mot(ligne,MAX_NOM_WILAYA);         // enlever le saut de ligne de chaque mot qu'on lit
            strcpy(T_Wilaya[i],ligne);                  // sauvgarder dans la memoire centrale
        }
    }
    fclose(f);
    return 0;

}

// chargement de memoire secondaire (fich txt) ver la memoir centrale
int charg_Tab_Etablissement(char T_Etablissement[MAX_INDEX_UNIV][MAX_NOM_UNIV],char *nom_fichier) {
    FILE *f = NULL;
    int i;
    char ligne[MAX_NOM_UNIV];
    f=fopen(nom_fichier,"r");
    rewind(f);
    if (f==NULL) {
        fclose(f);
        return 1;
    }
    for (i=0;i<MAX_INDEX_UNIV;i++){                             // lecture consecutive de chaque ligne
        if(!feof(f)){
            fgets(ligne,sizeof(ligne),f);
            filtreur_mot(ligne,110);                            // enlever le saut de ligne de chaque mot qu'on lit
            strcpy(T_Etablissement[i],ligne);                   // sauvgarder dans la memoire centrale
        }
    }
    fclose(f);
    return 0;
}

// initialisation du bitmap
int init_bit_map(){
    tableau_bit_map=malloc(MAX_INDEX_MAT*sizeof(bool));
    for (int i=0 ; i<MAX_INDEX_MAT ; i++){
        tableau_bit_map[i]=false;
    }
    return 0;
}

// fonction booléenne qui verifie si un fichier de nom (fname) est deja existant dans le repertoire du projet
int fichier_existant(const char* fname) {
    FILE *file;
    if ((file = fopen(fname, "r"))) {
        fclose(file);
        return 1;                                             // (1) pour existant
    }
    return 0;                                                 // (0) pour non-existant
}

// fonction d'entrée-utilisateur sercurisée
void secure_read(int x, int y, char in[30], int max) {
    int cpt = 0;
    char c;
    char input[30];
    bool continu = true;

    while (continu) {
        gotoxy(x+cpt, y);
        c = getch();
        if (cpt < max) {
            if (c != 10 && c != 8 && c >= 32 && c <= 122) {
                input[cpt] = c;
                cpt++;
                putc(c, stdout);
            }
        }
        if (c == 8 && cpt != 0) {
            input[cpt] = '\0';
            if (cpt == max) printf("\e[?25h");
            cpt--;
            gotoxy(x+cpt, y); printf(" ");
            putc(c, stdout);
        }
        if (c == 13) continu = false;
        if (cpt == max) printf("\e[?25l");
    }
    input[cpt] = '\0';
    strcpy(in, input);
}

// fonction qui calcule la taille d'un fichier
void maj_taille_fich(TypeFich* F) {
    fseek(F->fptr, 0, SEEK_END);
    F->entete.taille = ftell(F->fptr);
    if (!F->entete.taille) F->entete.taille = sizeof(TypeEntete);
    rewind(F->fptr);
}

// fonction qui convertie la taille en KB, MB, GB
void format_size(int sz, char size[30]) {
    float sizeKB = 1024;
    char tmp[30];


    if (sz < sizeKB) {                                      // B
        sprintf(tmp, "%.1fB", sz/1.0);
    }
    else if (sz < sizeKB*sizeKB) {                          // KB
        sprintf(tmp, "%.1fKB", sz/sizeKB);
    }
    else if (sz < sizeKB*sizeKB*sizeKB) {                   // MB
        sprintf(tmp, "%.1fMB", sz/(sizeKB*sizeKB));
    }
    else if (sz < sizeKB*sizeKB*sizeKB*sizeKB) {            // GB
        sprintf(tmp, "%.1fGB", sz/(sizeKB*sizeKB*sizeKB));
    }

    strcpy(size, tmp);
}

// fonction qui valide une date donnée (d = jour, m = mois, y = année)
int check_date(int y, int m, int d, int minY, int maxY) {

    if (y>=minY && y<=maxY && m>=1 && m<=12 && d>=1 && d<=31) {
        if ((y%4 == 0) && (m == 2)) {                                           // année bissextile + fevrier
            if (d>=1 && d<=29) return 1;
            else return 0;
        }
        else if (m == 2) {                                                      // année non-bissextile + fevrier
            if (d>=1 && d<=28) return 1;
            else return 0;
        }
        else if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12)) {
            if (d>=1 && d<=31) return 1;
            else return 0;
        }
        else {
            if (d>=1 && d<=30) return 1;
            else return 0;
        }
    }
    else return 0;
}
