#include "display.h"
#include "LnOF.h"
#include <math.h>

// effacer l'ecran
void clrscr() {
    system("cls||clear");
}

// initialisation de la console
void init_console() {
    clrscr();
    printf("\x1b[?25l");

    /**CONFIGURATION DE LA CONSOLE**/
    char config[64];
    sprintf(config, "mode con LINES=%d COLS=%d", NB_LINES, NB_COLONS);
    system(config);
    SetConsoleTitle("GESTION des ENSEIGNANTS MESRS");
    HWND hwnd = GetConsoleWindow();
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, style);
    SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE|SWP_FRAMECHANGED);

    // verrouillage du console
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    HMENU sm = GetSystemMenu(hwnd, 0);
    int i, j, c = GetMenuItemCount(sm);
    LPTSTR buf;
    j = -1;
    buf = (TCHAR*) malloc (256 *sizeof(TCHAR));
    for (i=0; i<c; i++) {
        GetMenuString(sm, i, buf, 255, MF_BYPOSITION);
        if (!strcmp(buf, "&Close")) {
            j = i;
            break;
        }
    }
    if (j >= 0) RemoveMenu(sm, j, MF_BYPOSITION);
}

// effacer une des line de l'ecran
void clrline() {
    printf("\e[2K");
    printf("\e[A");
}

void clrline2() {
    printf("\e[2K\r");
}

void clrlines(int x, int y, int nb_lines) {
    for (int i = 0; i < (nb_lines-y); i++) {
        gotoxy(x, y+i); clrline2();
    }
}

// effacer les menus de l'ecran
void clrmenu(int length) {
    for (int i = 0; i < length; i++) {
        gotoxy(20, 25+i);
        printf("                                                                                                                         ");
    }
}

// affichage de l'entete de la page
void entete() {
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\e[38;5;232m\e[48;5;188m     Date: %02d/%02d/%04d                                    Ecole nationale Superieure d'Informatique (ALGER)                                          TP SFSD     \e[0m", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
}

//affichage de pied de page
void pied() {
    printf("\e[38;5;232m\e[48;5;188m    MEDJADJ Abderraouf                                             UNE COLLABORATION EN 2022/2023                                              ABOUD Ibrahim    \e[0m");
}

// animation d'ecriture des chaines sur l'ecran ( typing-animation )
void strprintAnimate(char* str,int ms) {
    for (int i = 0; i < strlen(str); i++) {
        printf("%c", str[i]);
        usleep(ms*1000);
    }
}

// animation d'entrée d'erreur
void inErrAnimate(char* str, int x, int y) {
    gotoxy(x, y);
    for (int i = 1; i < 6; i++) {
        clrline2();
        gotoxy(x, y);
        printf("\e[38;5;202m%s ", str);
        usleep(25000);
        clrline2();
        gotoxy(x, y);
        printf("\e[38;5;196m %s", str);
        usleep(25000);
    }
    clrline2();
    gotoxy(x, y);
    printf("\e[0m%s", str);
}

// un logo animé personalisé de l'esi, pour le demarrage du programme
void esi_logo() {
    gotoxy(56,4);
    printf ("\e[49m  \e[38;5;253;49m%c\e[38;5;15;49m%c\e[38;5;15;48;5;15m%c\e[48;5;15m        \e[38;5;15;49m%c%c\e[49m     \e[38;5;15;49m%c\e[48;5;15m         \e[38;5;15;48;5;255m%c\e[38;5;15;49m%c\e[38;5;249;49m%c\e[49m  \e[38;5;25;49m%c\e[38;5;25;48;5;25m%c%c%c%c%c%c%c\e[38;5;25;48;5;31m%c\e[49m    \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    usleep(1000);
    gotoxy(56,5);
    printf ("\e[49m \e[38;5;15;48;5;255m%c\e[48;5;15m             \e[38;5;15;48;5;15m%c\e[49m  \e[38;5;15;49m%c\e[38;5;15;48;5;15m%c\e[48;5;15m             \e[38;5;15;48;5;7m%c\e[49m \e[38;5;25;48;5;25m%c%c\e[48;5;235m      \e[38;5;25;48;5;25m \e[49m    \e[m\n", 220, 220, 220, 220, 220, 220, 220);
    usleep(1000);
    gotoxy(56,6);
    printf ("\e[49m \e[48;5;15m      \e[38;5;15;48;5;15m%c\e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49;38;5;252m%c\e[48;5;15m       \e[49m \e[38;5;25;48;5;25m%c%c\e[48;5;235m      \e[38;5;25;48;5;25m \e[49m    \e[m\n", 220, 223, 220, 220);
    usleep(1000);
    gotoxy(56,7);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m \e[38;5;25;48;5;25m%c%c%c%c%c%c%c%c\e[38;5;60;48;5;25m%c\e[49m    \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220);
    usleep(1000);
    gotoxy(56,8);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[49;38;5;25m%c\e[38;5;25;48;5;25m%c%c%c%c%c%c%c%c\e[38;5;61;48;5;25m%c\e[49;38;5;25m%c\e[49m \e[m\n", 223, 220, 220, 220, 220, 220, 220, 220, 220, 220, 223);
    usleep(1000);
    gotoxy(56,9);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[38;5;15;49m%c%c%c\e[38;5;15;48;5;25m\e[38;5;15;48;5;67m\e[38;5;15;49m%c%c\e[49m     \e[m\n", 220, 220, 220, 220, 220);
    usleep(1000);
    gotoxy(56,10);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n");
    usleep(1000);
    gotoxy(56,11);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n");
    usleep(1000);
    gotoxy(56,12);
    printf ("\e[49m \e[48;5;15m      \e[38;5;15;48;5;15m%c\e[38;5;15;49m%c\e[48;5;15m       \e[49m  \e[48;5;15m        \e[38;5;15;49m%c%c%c%c%c%c%c%c\e[49m  \e[48;5;15m       \e[49m     \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    usleep(1000);
    gotoxy(56,13);
    printf ("\e[49m \e[48;5;15m               \e[49m  \e[48;5;15m                \e[49m  \e[48;5;15m       \e[49m     \e[m\n");
    usleep(1000);
    gotoxy(56,14);
    printf ("\e[49m \e[48;5;15m      \e[38;5;15;48;5;15m%c\e[48;5;15m        \e[49m  \e[38;5;240;48;5;15m%c%c%c%c%c%c%c%c\e[38;5;248;48;5;15m%c\e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    usleep(1000);
    gotoxy(56,15);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[38;5;15;49m%c%c%c%c%c%c%c\e[49m  \e[38;5;15;49m%c%c%c%c%c%c%c%c\e[49m \e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    usleep(1000);
    gotoxy(56,16);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n");
    usleep(1000);
    gotoxy(56,17);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n");
    usleep(1000);
    gotoxy(56,18);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n");
    usleep(1000);
    gotoxy(56,19);
    printf ("\e[49m \e[48;5;15m      \e[38;5;15;48;5;15m%c\e[38;5;15;49m%c\e[48;5;15m       \e[49m  \e[48;5;15m        \e[38;5;15;49m%c\e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n", 220, 220, 220);
    usleep(1000);
    gotoxy(56,20);
    printf ("\e[49m \e[49;38;5;254m%c\e[48;5;15m \e[38;5;15;48;5;15m%c\e[48;5;15m          \e[38;5;15;48;5;15m%c\e[49;38;5;15m%c\e[49m   \e[48;5;15m \e[38;5;15;48;5;15m%c\e[48;5;15m          \e[38;5;15;48;5;15m%c\e[48;5;15m \e[49;38;5;15m%c\e[49m  \e[48;5;15m       \e[49m     \e[m\n", 223, 220, 220, 223, 220, 220, 223);
    usleep(1000);
    gotoxy(56,21);
    printf ("\e[49m   \e[49;38;5;255m%c\e[49;38;5;15m%c%c%c%c%c%c%c%c%c%c\e[49m       \e[49;38;5;15m%c%c%c%c%c%c%c%c%c%c\e[49;38;5;254m%c\e[49m    \e[49;38;5;15m%c%c%c%c%c%c%c\e[49m     \e[m\n", 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223);
}

// meme logo precedant, animé en inverse, pour la fermeture du programme
void reverse_esi_logo(int y) {

    gotoxy(56,y);
    printf ("\e[49m  \e[38;5;253;49m%c\e[38;5;15;49m%c\e[38;5;15;48;5;15m%c\e[48;5;15m        \e[38;5;15;49m%c%c\e[49m     \e[38;5;15;49m%c\e[48;5;15m         \e[38;5;15;48;5;255m%c\e[38;5;15;49m%c\e[38;5;249;49m%c\e[49m  \e[38;5;25;49m%c\e[38;5;25;48;5;25m%c%c%c%c%c%c%c\e[38;5;25;48;5;31m%c\e[49m    \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    gotoxy(56,y+1);
    printf ("\e[49m \e[38;5;15;48;5;255m%c\e[48;5;15m             \e[38;5;15;48;5;15m%c\e[49m  \e[38;5;15;49m%c\e[38;5;15;48;5;15m%c\e[48;5;15m             \e[38;5;15;48;5;7m%c\e[49m \e[38;5;25;48;5;25m%c%c\e[48;5;235m      \e[38;5;25;48;5;25m \e[49m    \e[m\n", 220, 220, 220, 220, 220, 220, 220);
    gotoxy(56,y+2);
    printf ("\e[49m \e[48;5;15m      \e[38;5;15;48;5;15m%c\e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49;38;5;252m%c\e[48;5;15m       \e[49m \e[38;5;25;48;5;25m%c%c\e[48;5;235m      \e[38;5;25;48;5;25m \e[49m    \e[m\n", 220, 223, 220, 220);
    gotoxy(56,y+3);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m \e[38;5;25;48;5;25m%c%c%c%c%c%c%c%c\e[38;5;60;48;5;25m%c\e[49m    \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220);
    gotoxy(56,y+4);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[49;38;5;25m%c\e[38;5;25;48;5;25m%c%c%c%c%c%c%c%c\e[38;5;61;48;5;25m%c\e[49;38;5;25m%c\e[49m \e[m\n", 223, 220, 220, 220, 220, 220, 220, 220, 220, 220, 223);
    gotoxy(56,y+5);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[38;5;15;49m%c%c%c\e[38;5;15;48;5;25m\e[38;5;15;48;5;67m\e[38;5;15;49m%c%c\e[49m     \e[m\n", 220, 220, 220, 220, 220);
    gotoxy(56,y+6);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n");
    gotoxy(56,y+7);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n");
    gotoxy(56,y+8);
    printf ("\e[49m \e[48;5;15m      \e[38;5;15;48;5;15m%c\e[38;5;15;49m%c\e[48;5;15m       \e[49m  \e[48;5;15m        \e[38;5;15;49m%c%c%c%c%c%c%c%c\e[49m  \e[48;5;15m       \e[49m     \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    gotoxy(56,y+9);
    printf ("\e[49m \e[48;5;15m               \e[49m  \e[48;5;15m                \e[49m  \e[48;5;15m       \e[49m     \e[m\n");
    gotoxy(56,y+10);
    printf ("\e[49m \e[48;5;15m      \e[38;5;15;48;5;15m%c\e[48;5;15m        \e[49m  \e[38;5;240;48;5;15m%c%c%c%c%c%c%c%c\e[38;5;248;48;5;15m%c\e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    gotoxy(56,y+11);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[38;5;15;49m%c%c%c%c%c%c%c\e[49m  \e[38;5;15;49m%c%c%c%c%c%c%c%c\e[49m \e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    gotoxy(56,y+12);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n");
    gotoxy(56,y+13);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n");
    gotoxy(56,y+14);
    printf ("\e[49m \e[48;5;15m       \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m        \e[49m \e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n");
    gotoxy(56,y+15);
    printf ("\e[49m \e[48;5;15m      \e[38;5;15;48;5;15m%c\e[38;5;15;49m%c\e[48;5;15m       \e[49m  \e[48;5;15m        \e[38;5;15;49m%c\e[48;5;15m       \e[49m  \e[48;5;15m       \e[49m     \e[m\n", 220, 220, 220);
    gotoxy(56,y+16);
    printf ("\e[49m \e[49;38;5;254m%c\e[48;5;15m \e[38;5;15;48;5;15m%c\e[48;5;15m          \e[38;5;15;48;5;15m%c\e[49;38;5;15m%c\e[49m   \e[48;5;15m \e[38;5;15;48;5;15m%c\e[48;5;15m          \e[38;5;15;48;5;15m%c\e[48;5;15m \e[49;38;5;15m%c\e[49m  \e[48;5;15m       \e[49m     \e[m\n", 223, 220, 220, 223, 220, 220, 223);
    gotoxy(56,y+17);
    printf ("\e[49m   \e[49;38;5;255m%c\e[49;38;5;15m%c%c%c%c%c%c%c%c%c%c\e[49m       \e[49;38;5;15m%c%c%c%c%c%c%c%c%c%c\e[49;38;5;254m%c\e[49m    \e[49;38;5;15m%c%c%c%c%c%c%c\e[49m     \e[m\n", 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223);
    sleep(0.9);
    screen_off();
    sleep(1);
    for (int i = 0; i < 18; i++) {gotoxy(56, y+i); clrline2(); usleep(40000);}
}

// logo titre: "GEM"
void titre_logo() {
    gotoxy(18, 4); printf ("\e[49m  \e[38;5;32;48;5;25m%c\e[38;5;33;48;5;33m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[38;5;32;48;5;33m%c\e[48;5;33m    \e[49m    \e[38;5;33;48;5;33m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[49m    \e[38;5;33;48;5;33m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[38;5;32;48;5;33m%c\e[48;5;33m   \e[38;5;33;48;5;33m%c%c%c%c%c%c%c%c%c%c%c\e[48;5;33m    \e[49m  \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    gotoxy(18, 5); printf ("\e[49m  \e[38;5;32;48;5;25m%c\e[38;5;33;48;5;33m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[38;5;32;48;5;33m%c\e[48;5;33m    \e[49m    \e[38;5;33;48;5;33m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[49m    \e[38;5;33;48;5;33m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[38;5;32;48;5;33m%c\e[48;5;33m   \e[38;5;33;48;5;33m%c%c%c%c%c%c%c%c%c%c%c\e[48;5;33m    \e[49m  \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    gotoxy(18, 6); printf ("\e[49m                                 \e[48;5;25m \e[48;5;33m    \e[49m                                                             \e[48;5;25m \e[48;5;33m   \e[49m               \e[48;5;33m    \e[49m  \e[m\n");
    gotoxy(18, 7); printf ("\e[49m                                                                                                   \e[48;5;25m \e[48;5;33m   \e[49m               \e[48;5;33m    \e[49m  \e[m\n");
    gotoxy(18, 8); printf ("\e[49m  \e[38;5;25;48;5;32m%c\e[38;5;33;48;5;33m%c%c%c\e[38;5;33;48;5;39m%c\e[49m               \e[48;5;33m \e[38;5;33;48;5;33m%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[38;5;33;48;5;39m%c\e[49m    \e[38;5;33;48;5;33m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[49m    \e[48;5;33m \e[38;5;33;48;5;33m%c%c%c\e[38;5;32;49m%c\e[49m              \e[48;5;25m \e[48;5;33m   \e[49m               \e[48;5;33m    \e[49m  \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    gotoxy(18, 9); printf ("\e[49m  \e[48;5;25m \e[48;5;33m    \e[49m               \e[38;5;33;48;5;33m%c%c%c%c%c%c%c%c%c%c%c%c\e[48;5;33m    \e[49m    \e[38;5;33;48;5;33m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[49m    \e[48;5;33m    \e[48;5;32m \e[49m              \e[48;5;25m \e[48;5;33m   \e[49m               \e[48;5;33m    \e[49m  \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    gotoxy(18, 10); printf ("\e[49m  \e[48;5;25m \e[48;5;33m    \e[49m               \e[49;38;5;24m%c%c%c%c%c%c%c%c%c%c%c\e[38;5;25;48;5;25m%c\e[48;5;33m    \e[49m    \e[49;38;5;24m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[49m    \e[48;5;33m    \e[48;5;32m \e[49m              \e[48;5;25m \e[48;5;33m   \e[49m               \e[48;5;33m    \e[49m  \e[m\n", 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 220, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223);
    gotoxy(18, 11); printf ("\e[49m  \e[48;5;25m \e[48;5;33m    \e[49m                          \e[48;5;25m \e[48;5;33m    \e[49m                                          \e[48;5;33m    \e[48;5;32m \e[49m              \e[48;5;25m \e[48;5;33m   \e[49m               \e[48;5;33m    \e[49m  \e[m\n");
    gotoxy(18, 12); printf ("\e[49m  \e[48;5;25m \e[48;5;33m   \e[38;5;32;48;5;33m%c\e[38;5;25;49m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[38;5;32;48;5;25m%c\e[48;5;33m    \e[49m    \e[38;5;25;49m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[49m    \e[48;5;33m    \e[48;5;32m \e[49m              \e[48;5;25m \e[48;5;33m   \e[49m               \e[48;5;33m    \e[49m  \e[m\n", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
    gotoxy(18, 13); printf ("\e[49m  \e[48;5;25m \e[48;5;33m                                   \e[49m    \e[48;5;33m                                  \e[49m    \e[48;5;33m    \e[48;5;32m \e[49m              \e[48;5;25m \e[48;5;33m   \e[49m               \e[48;5;33m    \e[49m  \e[m\n");
    gotoxy(18, 14); printf ("\e[49m  \e[49;38;5;26m%c\e[49;38;5;33m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[49m    \e[49;38;5;33m%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\e[49m    \e[49;38;5;33m%c%c%c%c\e[49;38;5;32m%c\e[49m              \e[49;38;5;25m%c\e[49;38;5;33m%c%c%c\e[49m               \e[49;38;5;33m%c%c%c%c\e[49m  \e[m\n\n\n", 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223);

    for (int i = 0; i < 160; i++) {
        printf("%c", 196);
    }
}

// animation du texte clignotant sur l'ecran
void strprintblink (char* word, int blink_number, int blink_rate) {
    while( blink_number != 1 ){
        usleep(blink_rate*10000);
        printf("\r");
        printf("\033[1;90m");
        printf("%s",word);

        usleep(100000);
        printf("\r");
        printf("\033[0m");

        printf("%s",word);

        usleep(100000);
        printf("\r");
        printf("\033[1;37m");

        printf("%s",word);

        usleep(blink_rate*10000/2);
        printf("\r");
        printf("\033[0m");

        printf("%s",word);

        usleep(100000);
        printf("\r");
        printf("\033[1;90m");

        printf("%s",word);

        usleep(100000);
        printf("\r");
        for (int i = 1 ; i <= strlen(word); i++) {
            printf(" ");
        }
        blink_number = blink_number - 1 ;
    }
    printf("\033[0m");
}

// meme animation precedante + l'option de l'arreter suite a une frappe du clavier (keyboard hit)
void strprintblinkkbhit(char* word, int blink_number, int blink_rate,int x,int y) {


    while((!kbhit()) && (blink_number != 1 )){

        fade_in(word,blink_rate,x,y);
        if (kbhit()) {break;}
        gotoxy(x,y);
        printf("\e[38;5;255m");
        printf("%s",word);
        printf("\e[0m");
        if (kbhit()) {break;}
        sleep(2);
        if (kbhit()) {break;}
        gotoxy(x, y);
        fade_out(word, blink_rate,x,y);
        if (kbhit()) {break;}
        Sleep(1);



        for (int i = 1 ; i <= strlen(word); i++) {
            printf(" ");
        }
        blink_number = blink_number - 1 ;
    }
    printf("\033[0m");
}

// page d'introduction du projet
void intro() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    strprintblinkkbhit("  ABOUD Ibrahim & MEDJADJ Raouf presentent ...",2,20,55,19);
    strprintblinkkbhit("  Sous la supervision du Professeur KERMI Adel",2,10,55,19);
    strprintblinkkbhit("            Retenez vos souffles !!!",2,20,55,19);
    Sleep(2);
}

// fonction tres utilis�e pour deplacer le curseur sur l'ecran
void gotoxy(SHORT x1, SHORT y1) {
    COORD c;
    c.X = x1;
    c.Y = y1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// animation du texte (fade-in)
void fade_in(char* word , int speed_ms, int x,int y) {

    for (int i=232;i<=255;i++){
        gotoxy(x,y);
        usleep(speed_ms*1000);
        printf("\e[38;5;%dm",i);
        printf("%s",word);
    }

    usleep(speed_ms*1000);
    gotoxy(x,y);
    printf("\e[1m");
    printf("%s",word);
    printf("\e[0m");
}
// animation du text (fade-out)
void fade_out(char* word, int speed_ms,int x,int y) {

    for (int i=255;i>=232;i--){
        usleep(speed_ms*1000);
        gotoxy(x,y);
        printf("\e[38;5;%dm",i);
        printf("%s",word);
    }

    usleep(100000);
    gotoxy(x,y);
    printf("\e[38;5;0m");
    printf("%s",word);
    printf("\e[0m");
}
// animation du text (fade-in-out)
void fade_in_out(char* text,int text_size,int x,int y){
    fade_in(text,text_size,x,y);
    gotoxy(x,y);
    printf("\e[38;5;255m");
    printf("%s",text);
    printf("\e[0m");
    Sleep(3);
    gotoxy(x, y);
    fade_out(text, text_size,x,y);
    Sleep(1);
}

// animation de l'ecran du pc sur la lettre "I" du logo "ESI"
void screen_on() {
    printf("\e[38;5;238m");
    for (int i=238;i<=253;i++){
        gotoxy(93,5);
        usleep(30000);
        printf("\e[48;5;%dm      ",i);
        gotoxy(93,6);
        printf("\e[48;5;%dm      ",i);
    }
    gotoxy(93,5);
    usleep(30000);
    printf("\e[48;5;195m      ");
    gotoxy(93,6);
    printf("\e[48;5;195m      ");
    printf("\e[0m");
}

// animation de l'ecran du pc sur la lettre "I" du logo "ESI"
void screen_off() {
    gotoxy(93,11);
    usleep(30000);
    printf("\e[48;5;195m      ");
    gotoxy(93,12);
    printf("\e[48;5;195m      ");
    printf("\e[38;5;238m");
    for (int i=253;i>=238;i--){
        gotoxy(93,11);
        usleep(30000);
        printf("\e[48;5;%dm      ",i);
        gotoxy(93,12);
        printf("\e[48;5;%dm      ",i);
    }
    gotoxy(93,11);
    usleep(30000);
    printf("\e[48;5;235m      ");
    gotoxy(93,12);
    printf("      ");
    printf("\e[0m");
}

// creation d'un rectangle
void rectangle(int x, int y, int l, int w) {
    gotoxy(x, y); printf("%c", 218); gotoxy(x+w-1, y); printf("%c", 191); gotoxy(x, y+l-1); printf("%c", 192); gotoxy(x+w-1, y+l-1); printf("%c", 217);
    for (int i = 1; i < l-1; i++) {
        gotoxy(x, y+i); printf("%c", 179);          // Vertical #1
        gotoxy(x+w-1, y+i); printf("%c", 179);      // Vertical #2
    }
    for (int k = 1; k < w-1; k++) {
        gotoxy(x+k, y); printf("%c", 196);          // Horizontal #1
        gotoxy(x+k, y+l-1); printf("%c", 196);      // Horizontal #2
    }
}

// animation du codage
int codage_animation(int x,int y,char* mot,int taille_mot) {
    int k;
    for (int i=0;i<50;i++){
        k=rand()%taille_mot;
        if(mot[k]+k!='\n'){
            mot[k]=mot[k]+k;
        }

        gotoxy(x,y);
        printf("%s",mot);
        usleep(1000);
    }
    return 0;
}

/***______________________________________________________________________________________________________**/

// fonction qui dessine un bloc sur l'ecran
void cree_bloc(int x,int y,int blanc,int numero ){

    unsigned char couleur;
    if (blanc){
        couleur=178;
    }
    else {
        couleur=177;
    }

    gotoxy(x,y);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur);
    for (int i=0;i<=1;i++){
        gotoxy(x,i+1+y);
        printf("%c%c                %c%c\n",couleur,couleur,couleur,couleur);

    }

    gotoxy(x,3+y);
    printf("%c%c    bloc %03d    %c%c\n",couleur,couleur,numero,couleur,couleur);

    for (int i=3;i<=4;i++){
        gotoxy(x,i+1+y);
        printf("%c%c                %c%c\n",couleur,couleur,couleur,couleur);

    }
    gotoxy(x,y+6);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n",couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur,couleur);


}

//fonction qui dessine une fleche sur l'ecran
void flech(int x,int y){
    for(int i=0;i<=9;i++){
        gotoxy(x+i,y);
        printf("%c",254);
    }
}

//fonction qui dessine des pointiees sur l'ecran
void a_suivre(int x, int y){
    for(int i=0;i<=4;i++){
        gotoxy(x+2*i,y);
        printf("%c",254);
    }
}

//fonction qui dessine une fin de liste sur l'ecran
void queuee(int x,int y){
    flech(x,y);
    for(int i=-2;i<=1;i++){
        gotoxy(x+6,y+i);
        printf("%c%c%c%c",219,254,254,254);
    }
    gotoxy(x+6,y+2);
    printf("%c%c%c%c",219,254,254,254);
}

//fonction qui dessine un tableau sur l'ecran
void cree_table(int x,int y,int nombre,int taille){
    unsigned char horiz= 205;
    unsigned char verti= 186;
    unsigned char ctl= 201;
    unsigned char ctr= 187;
    unsigned char cdl= 200;
    unsigned char cdr= 188;
    unsigned char vl= 185;
    unsigned char vr= 204;
    gotoxy(x,y);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",ctl,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,ctr);
    gotoxy(x,y+1);
    printf("%c  Enreg %04d  %c\n",verti,nombre,verti);
    for (int i=2; i<=taille;i++) {
            gotoxy(x,2*(i-2)+y+2);
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",vr,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,vl);
            gotoxy(x,2*(i-2)+y+3);
            printf("%c  Enreg %04d  %c\n",verti,nombre+i-1,verti);
    }
    gotoxy(x,2*taille+y);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",cdl,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,horiz,cdr);



}

//fonction qui dessine une table deux dimensionel sur l'ecran
void cree_matrice(int x,int y,int nombre,int taille){
    entete();
    gotoxy(0,39);
    pied();
    for(int i=1;i<=taille/16;i++){
            cree_table(x+16*(i-1),y,(i-1)*16+nombre,16);
    }
    if(taille%16!=0){
        cree_table(x+16*(taille/16),y,(taille/16)*16+nombre,taille%16);
    }


}

//fonction qui affiche le contenu d'un enregistrement sur l'ecran
void afficher_enreg(TypeEnreg enreg,int num_enreg){
    clrscr();
    gotoxy(0,0);
    entete();
    gotoxy(0,39);
    pied();
    int x,y;
    x=21;
    y=13;
    rectangle(18,11,17,123);
    for(int i=-1 ;i<15;i++){
        gotoxy(20,12+i);
        printf("\e[48;5;252m                                                                                                                          \e[0m");
    }

    gotoxy(73,y-1);
    printf("\e[48;5;255m\e[38;5;235mEnregistrement (%04d)", num_enreg);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    MATRICULE:       ");
    print_space(104/2);
    printf("\e[48;5;252m\e[38;5;235m%06d\e[0m",enreg.matricule);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    NOM:             ");
    print_space((110-strlen(enreg.nom))/2);
    printf("\e[48;5;252m\e[38;5;235m%s\e[0m",enreg.nom);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    PRENOM:          ");
    print_space((110-strlen(enreg.prenom))/2);
    printf("\e[48;5;252m\e[38;5;235m%s\e[0m",enreg.prenom);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    DATE NAISSANCE:  ");
    print_space(100/2);
    printf("\e[48;5;252m\e[38;5;235m%02d/%02d/%04d\e[0m", (enreg.date_Naissance)%100, ((enreg.date_Naissance)%10000)/100, (enreg.date_Naissance)/10000);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    WILAYA NAISSANCE:");
    print_space((110-strlen(wilaya[enreg.wilaya_Naissance]))/2);
    printf("\e[48;5;252m\e[38;5;235m%s\e[0m",wilaya[enreg.wilaya_Naissance]);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    SEXE:            ");
    print_space((110-strlen(sexe[enreg.sexe]))/2);
    printf("\e[48;5;252m\e[38;5;235m%s\e[0m",sexe[enreg.sexe]);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    GROUPE SANGUIN:  ");
    print_space((110-strlen(grp_sanguin[enreg.groupe_sanguin]))/2);
    printf("\e[48;5;252m\e[38;5;235m%s\e[0m",grp_sanguin[enreg.groupe_sanguin]);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    DATE RECRUTEMENT:");
    print_space((100)/2);
    printf("\e[48;5;252m\e[38;5;235m%02d/%02d/%04d\e[0m", (enreg.date_recrutement)%100, ((enreg.date_recrutement)%10000)/100, (enreg.date_recrutement)/10000);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    GRADE:           ");
    print_space((110-strlen(grade[enreg.grade]))/2);
    printf("\e[48;5;252m\e[38;5;235m%s\e[0m",grade[enreg.grade]);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    SPECIALITE:      ");
    print_space((110-strlen(specialite[enreg.specialite]))/2);
    printf("\e[48;5;252m\e[38;5;235m%s\e[0m",specialite[enreg.specialite]);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    DERNIER DIPLOME: ");
    print_space((110-strlen(diplome[enreg.dernier_diplome]))/2);
    printf("\e[48;5;252m\e[38;5;235m%s\e[0m",diplome[enreg.dernier_diplome]);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    ETABLISSEMENT:   ");
    print_space((107-strlen(etablissement[enreg.etablissement_univ]))/2);
    printf("\e[48;5;252m\e[38;5;235m(%c) %s\e[0m", ind_et_reg[enreg.etablissement_univ].Region, etablissement[enreg.etablissement_univ]);


    gotoxy(71,34); printf("\e[38;5;159m[ ECHAP ] : sortir\e[0m");
}

// fonction qui ecrit le numero de l'enregistrment sur l'ecran
void ecrire_norm(int x,int y,int num_enreg){
    gotoxy(x,y);
    printf("  Enreg %04d  ",num_enreg);
}

// fonction qui ecrit le numero de l'enregistrement souligné sur l'ecran
void ecrire_soulign(int x,int y,int num_enreg){
    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m  Enreg %04d  \e[0m",num_enreg);
}

// fonction de representation graphique des  enregistrements dans un bloc donne (en plus de la navigation a traver des commands)
void naviguer_enreg(TypeBloc* buf,int n_bloc){
    char command1;
    int nb_enreg=buf->nb;
    int i=1;
    if(nb_enreg%128==0 && nb_enreg>0){
        cree_matrice(13,2,1,128);
        gotoxy(14,36);
        printf("\e[48;5;252m\e[38;5;235m  Bloc : %03d  \e[0m",n_bloc);
        gotoxy(126,36);
        printf("\e[48;5;252m\e[38;5;235m  Page : %d/%d  \e[0m",(i-1)/128+1,(nb_enreg-1)/128+1);
        gotoxy(31,36);
        printf("\e[38;5;159m  [ ECHAP ] : sortir   [ HAUT ] : reculer   [ BAS ] : avancer   [ ENTRER ] : selectionner\e[0m");
    }
    else if (nb_enreg>128){
        cree_matrice(13,2,1,128);
        gotoxy(14,36);
        printf("\e[48;5;252m\e[38;5;235m  Bloc : %03d  \e[0m",n_bloc);
        gotoxy(126,36);
        printf("\e[48;5;252m\e[38;5;235m  Page : %d/%d  \e[0m",(i-1)/128+1,(nb_enreg-1)/128+1);
        gotoxy(31,36);
        printf("\e[38;5;159m  [ ECHAP ] : sortir   [ HAUT ] : reculer   [ BAS ] : avancer   [ ENTRER ] : selectionner\e[0m");
    }
    else{
        cree_matrice(13,2,1,nb_enreg%128);
        gotoxy(14,36);
        printf("\e[48;5;252m\e[38;5;235m  Bloc : %03d  \e[0m",n_bloc);
        gotoxy(126,36);
        printf("\e[48;5;252m\e[38;5;235m  Page : %d/%d  \e[0m",(i-1)/128+1,(nb_enreg-1)/128+1);
        gotoxy(31,36);
        printf("\e[38;5;159m  [ ECHAP ] : sortir   [ HAUT ] : reculer   [ BAS ] : avancer   [ ENTRER ] : selectionner\e[0m");
    }
    ecrire_soulign(14,3,1);
    time_t t_origine = time(NULL);

    char command = getch();                                   // une variable qui contient la derniere touche du clavier frapp�e par l'utilisateur
    while (command == 13 && (time(NULL)-t_origine)<0.5) {
        command = getch();
    }

    while(1)                                                  // 13 pour <ENTRER> , 72 pour <HAUT> , 80 pour <BAS>
    {
        if ( command == 72) {
            if(i>1 && i%128!=1){
                i--;
                ecrire_soulign(14+(((i-1)%128)/16)*16,3+(i-1)%16*2,i);
                ecrire_norm(14+(((i)%128)/16)*16,3+(i)%16*2,i+1);
            }
            else if(i%128==1 && i>1){
                i--;
                clrscr();
                cree_matrice(13,2,i-127,128);
                gotoxy(14,36);
                printf("\e[48;5;252m\e[38;5;235m  Bloc : %03d  \e[0m",n_bloc);
                gotoxy(126,36);
                printf("\e[48;5;252m\e[38;5;235m  Page : %d/%d  \e[0m",(i-1)/128+1,(nb_enreg-1)/128+1);
                gotoxy(31,36);
                printf("\e[38;5;159m  [ ECHAP ] : sortir   [ HAUT ] : reculer   [ BAS ] : avancer   [ ENTRER ] : selectionner\e[0m");
                ecrire_soulign(14+(((i-1)%128)/16)*16,3+(i-1)%16*2,i);

            }
        }

        else if (command == 80) {
            if(i%128!=0 && i<nb_enreg){
                i++;
                ecrire_soulign(14+(((i-1)%128)/16)*16,3+(i-1)%16*2,i);
                ecrire_norm(14+(((i-2)%128)/16)*16,3+(i-2)%16*2,i-1);
            }
            else
            {
                i++;
                if(((nb_enreg-i)%128==0 && i>0)||(nb_enreg-i>128)){
                    clrscr();
                    cree_matrice(13,2,i,128);
                    gotoxy(14,36);
                    printf("\e[48;5;252m\e[38;5;235m  Bloc : %03d  \e[0m",n_bloc);
                    gotoxy(126,36);
                    printf("\e[48;5;252m\e[38;5;235m  Page : %d/%d  \e[0m",(i-1)/128+1,(nb_enreg-1)/128+1);
                    gotoxy(31,36);
                    printf("\e[38;5;159m  [ ECHAP ] : sortir   [ HAUT ] : reculer   [ BAS ] : avancer   [ ENTRER ] : selectionner\e[0m");
                    ecrire_soulign(14,3,i);
                }
                else if (i!=nb_enreg+1){
                    clrscr();
                    cree_matrice(13,2,i,(nb_enreg-i)%128+1);
                    gotoxy(14,36);
                    printf("\e[48;5;252m\e[38;5;235m  Bloc : %03d  \e[0m",n_bloc);
                    gotoxy(126,36);
                    printf("\e[48;5;252m\e[38;5;235m  Page : %d/%d  \e[0m",(i-1)/128+1,(nb_enreg-1)/128+1);
                    gotoxy(31,36);
                    printf("\e[38;5;159m  [ ECHAP ] : sortir   [ HAUT ] : reculer   [ BAS ] : avancer   [ ENTRER ] : selectionner\e[0m");
                    ecrire_soulign(14,3,i);
                }
                else {
                    i--;
                }


            }


        }
        else if ( command == 13){
            clrscr();
            afficher_enreg(buf->T[i-1],i);

            while (1) {
                command1 = getch();
                if(command1== 27){
                    break;
                }
            }







            clrscr();
            if((nb_enreg-((i-1)/128)*128-1)<128){
                cree_matrice(13,2,((i-1)/128)*128+1,(nb_enreg-((i-1)/128)*128-1)%128+1);
            }
            else{
                cree_matrice(13,2,((i-1)/128)*128+1,128);
            }

            gotoxy(14,36);
            printf("\e[48;5;252m\e[38;5;235m  Bloc : %03d  \e[0m",n_bloc);
            gotoxy(126,36);
            printf("\e[48;5;252m\e[38;5;235m  Page : %d/%d  \e[0m",(i-1)/128+1,(nb_enreg-1)/128+1);
            gotoxy(31,36);
            printf("\e[38;5;159m  [ ECHAP ] : sortir   [ HAUT ] : reculer   [ BAS ] : avancer   [ ENTRER ] : selectionner\e[0m");
            ecrire_soulign(14+(((i-1)%128)/16)*16,3+(i-1)%16*2,i);


        }
        else if ( command == 27){
            break;
        }
        command = getch();
    }

}


// fonction qui cree une representation graphique des blocs dans un fichier en MS , sur l'ecran
void cree_list_bloc(int x,int y,int num_initial,int nombr_bloc){
    gotoxy(0,0);
    entete();
    gotoxy(0,39);
    pied();
    int max;
    if ((nombr_bloc%15==0 && nombr_bloc>0) || nombr_bloc>15){
        max=15;
    }
    else{
        max = nombr_bloc % 15 ;
    }
    for(int i=0;i<max;i++){
        cree_bloc(x+(i%5)*30,(i/5)*10+y,0,i+num_initial);
        if(i==nombr_bloc-1){
            queuee(20+x+(i%5)*30,(i/5)*10+y+3);
        }
        else if(i%5==4){
            a_suivre(20+x+(i%5)*30,(i/5)*10+y+3);
        }
        else {
            flech(20+x+(i%5)*30,(i/5)*10+y+3);
        }
    }

}


// fonction de representation graphique des bloc du fichier en Ms (avec la possibliter de naviguation manuel avec des commandes)
void naviguer_bloc(TypeFich F) {
    TypeBloc buff;
    int nb_bloc=ENTETE(F,2);
    cree_list_bloc(5,5,1,nb_bloc);
    gotoxy(126,36);
    printf("\e[48;5;252m\e[38;5;235m  Page : %d/%d  \e[0m",1,(nb_bloc-1)/15+1);
    gotoxy(30,36);
    printf("\e[38;5;159m  [ ECHAP ] : sortir   [ <- ] : reculer  [ -> ] : avancer  [ ENTRER ] : selectionner\e[0m");

    int i=1;

    time_t t_origine = time(NULL);


    cree_bloc(5,5,1,1);
    char command = getch();                                   // une variable qui contient la derniere touche du clavier frapp�e par l'utilisateur
    while (command == 13 && (time(NULL)-t_origine)<0.5) {
        command = getch();
    }


    while(1)                                                  // 13 pour <ENTRER> , 72 pour <HAUT> , 80 pour <BAS>
    {

        if ( command == 75) {
            if(i>1 && i%15!=1){
                i--;
                cree_bloc(5+((i-1)%5)*30,(((i-1)/5)%3)*10+5,1,i);
                cree_bloc(5+((i)%5)*30,(((i)/5)%3)*10+5,0,i+1);
            }
            else if(i%15==1 && i>1){
                i--;
                clrscr();
                cree_list_bloc(5,5,(i/15-1)*15+1,nb_bloc-(i/15-1)*15-1);
                gotoxy(126,36);
                printf("\e[48;5;252m\e[38;5;235m  Page : %d/%d  \e[0m",(i-1)/15+1,(nb_bloc-1)/15+1);
                gotoxy(30,36);
                printf("\e[38;5;159m  [ ECHAP ] : sortir   [ <- ] : reculer  [ -> ] : avancer  [ ENTRER ] : selectionner\e[0m");
                cree_bloc(5+((i-1)%5)*30,(((i-1)/5)%3)*10+5,1,i);
            }
        }

        else if (command == 77) {
            if(i%15!=0 && i<nb_bloc){
                i++;
                cree_bloc(5+((i-1)%5)*30,(((i-1)/5)%3)*10+5,1,i);
                cree_bloc(5+((i-2)%5)*30,(((i-2)/5)%3)*10+5,0,i-1);
            }
            else
            {
                i++;
                if(((nb_bloc-i)%15==1 && nb_bloc-i>0)||(nb_bloc-i>15)){
                    clrscr();
                    cree_list_bloc(5,5,(i/15)*15+1,nb_bloc-(i/15)*15);
                    gotoxy(126,36);
                    printf("\e[48;5;252m\e[38;5;235m  Page : %d/%d  \e[0m",(i-1)/15+1,(nb_bloc-1)/15+1);
                    gotoxy(30,36);
                    printf("\e[38;5;159m  [ ECHAP ] : sortir   [ <- ] : reculer  [ -> ] : avancer  [ ENTRER ] : selectionner\e[0m");
                    cree_bloc(5+((i-1)%5)*30,(((i-1)/5)%3)*10+5,1,i);
                }
                else if (i!=nb_bloc+1){
                    clrscr();
                    cree_list_bloc(5,5,(i/15)*15+1,nb_bloc-(i/15)*15);
                    gotoxy(126,36);
                    printf("\e[48;5;252m\e[38;5;235m  Page : %d/%d  \e[0m",(i-1)/15+1,(nb_bloc-1)/15+1);
                    gotoxy(30,36);
                    printf("\e[38;5;159m  [ ECHAP ] : sortir   [ <- ] : reculer  [ -> ] : avancer  [ ENTRER ] : selectionner\e[0m");
                    cree_bloc(5+((i-1)%5)*30,(((i-1)/5)%3)*10+5,1,i);
                }
                else {
                    i--;
                }


            }


        }
        else if ( command == 13){
            clrscr();
            LireDir(F,i,&buff);
            naviguer_enreg(&buff,i);
            clrscr();
            cree_list_bloc(5,5,(i/15)*15+1,nb_bloc-(i/15)*15);
            gotoxy(126,36);
            printf("\e[48;5;252m\e[38;5;235m  Page : %d/%d  \e[0m",(i-1)/15+1,(nb_bloc-1)/15+1);
            gotoxy(30,36);
            printf("\e[38;5;159m  [ ECHAP ] : sortir   [ <- ] : reculer  [ -> ] : avancer  [ ENTRER ] : selectionner\e[0m");
            cree_bloc(5+((i-1)%5)*30,(((i-1)/5)%3)*10+5,1,i);

        }
        else if(command ==27){
            break;
        }
        command = getch();
    }


}


void print_space(int length){
    for (int i =0;i<length;i++){
        printf(" ");
    }

}

// fonction qui affiche l'entete du fichier
void afficher_entete(TypeFich F) {
    clrscr();
    gotoxy(0,0);
    entete();
    gotoxy(0,39);
    pied();
    int x, y;
    x=21;
    y=13;
    rectangle(18,11,17,123);
    for(int i=-1 ;i<15;i++) {
        gotoxy(20,12+i);
        printf("\e[48;5;252m                                                                                                                          \e[0m");
    }

    gotoxy(71,y-1);
    printf("\e[48;5;254m\e[38;5;235mEN-TETE DU FICHIER\e[48;5;252m");
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    NOM DU FICHER:");
    gotoxy(80, y);
    printf("\e[48;5;252m\e[38;5;235m%-30s\e[0m", F.nomFich);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    DATE DE CREATION:");
    gotoxy(80, y);
    printf("\e[48;5;252m\e[38;5;235m%02d-%02d-%04d %02d:%02d:%02d\e[0m", F.entete.tm.tm_mday, F.entete.tm.tm_mon+1, F.entete.tm.tm_year+1900, F.entete.tm.tm_hour, F.entete.tm.tm_min, F.entete.tm.tm_sec);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    TAILLE DU FICHIER:");
    gotoxy(80, y);
    char size[30];
    format_size(F.entete.taille, size);
    printf("\e[48;5;252m\e[38;5;235m%s\e[0m", size);
    y+=2;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    NOMBRE DE BLOCS:");
    gotoxy(80, y);
    int nb_blc = ENTETE(F, 2);
    if (nb_blc == -1) nb_blc++;
    printf("\e[48;5;252m\e[38;5;235m%d\e[0m", nb_blc);
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    NOMBRE D'ENREGISTREMENTS:");
    gotoxy(80, y);
    printf("\e[48;5;252m\e[38;5;235m%d\e[0m", ENTETE(F, 3));
    y+=2;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    TETE DE LA LObarreF:");
    gotoxy(80, y);
    printf("\e[48;5;252m\e[38;5;235m%d\e[0m", ENTETE(F, 1));
    y++;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    QUEUE:");
    gotoxy(80, y);
    printf("\e[48;5;252m\e[38;5;235m%d\e[0m", ENTETE(F, 2));
    y+=2;

    gotoxy(x,y);
    printf("\e[48;5;252m\e[38;5;235m    TETE LISTE VIDE:");
    gotoxy(80, y);
    printf("\e[48;5;252m\e[38;5;235m%d\e[0m", ENTETE(F, 4));
    y++;

    gotoxy(71,34); printf("\e[48;5;0m\e[38;5;159m[ ECHAP ] : sortir\e[0m");
}

// fonction qui affiche 3 informations : nombre de lectures, ecritures et en plus, le nom du fichier courant (ouvert)
void statusbar() {

    rectangle(50, 17, 3, 60);
    gotoxy(50, 17); printf("%c", 194); gotoxy(109, 17); printf("%c", 194);
    gotoxy(58, 18); printf("\e[48;5;235m FICHIER COURANT: \e[48;5;0m");

    rectangle(10, 17, 3, 40);
    gotoxy(10, 17); printf("%c", 194); gotoxy(49, 17); printf("%c", 194);
    gotoxy(18, 18); printf("\e[48;5;235m NB_ECRITURE: \e[48;5;0m");

    rectangle(110, 17, 3, 40);
    gotoxy(110, 17); printf("%c", 194); gotoxy(149, 17); printf("%c", 194);
    gotoxy(118, 18); printf("\e[48;5;235m NB_LECTURE: \e[48;5;0m");

}

// fonction d'affichage d'une sequence d'enregistrment suit a un filtrage donnée, avec la possiblitee de naviguer
void affiche_seq_mat(int *mat_tab,int tab_size,TypeFich* fich){
    int pas = sqrt(tab_size);
    TypeBloc buff;
    char command;
    int k =0;
    clrscr();
    LireDir(*fich,ind_mat[mat_tab[k]-111111].i,&buff);
    afficher_enreg(buff.T[ind_mat[mat_tab[k]-111111].j],ind_mat[mat_tab[k]-111111].j);
    gotoxy(130,34);
    printf("\e[48;5;252m\e[38;5;235m page %d/%d \e[0m",k+1,tab_size);
    gotoxy(35,34);
    printf("\e[38;5;159m  [ ECHAP ] : sortir   [ HAUT/GAUCHE ] : reculer/rapide   [ BAS/DROITE ] : avancer/rapide \e[0m");
    while(1){
        command=getch();
        if ( command == 72) {
            if(k>0){
                k--;
                LireDir(*fich,ind_mat[mat_tab[k]-111111].i,&buff);
                afficher_enreg(buff.T[ind_mat[mat_tab[k]-111111].j],ind_mat[mat_tab[k]-111111].j);
                gotoxy(130,34);
                printf("\e[48;5;252m\e[38;5;235m page %d/%d \e[0m",k+1,tab_size);
                gotoxy(35,34);
                printf("\e[38;5;159m  [ ECHAP ] : sortir   [ HAUT/GAUCHE ] : reculer/rapide   [ BAS/DROITE ] : avancer/rapide \e[0m");
            }
        }

        else if (command == 80) {
            if(k+1<tab_size){
                k++;
                LireDir(*fich,ind_mat[mat_tab[k]-111111].i,&buff);
                afficher_enreg(buff.T[ind_mat[mat_tab[k]-111111].j],ind_mat[mat_tab[k]-111111].j);
                gotoxy(130,34);
                printf("\e[48;5;252m\e[38;5;235m page %d/%d \e[0m",k+1,tab_size);
                gotoxy(35,34);
                printf("\e[38;5;159m  [ ECHAP ] : sortir   [ HAUT/GAUCHE ] : reculer/rapide   [ BAS/DROITE ] : avancer/rapide \e[0m");
            }
        }
        else if (command == 75) {
            if(k>0){
                if(k-pas>0){
                    k=k-pas;
                }
                else{
                    k=0;
                }
                LireDir(*fich,ind_mat[mat_tab[k]-111111].i,&buff);
                afficher_enreg(buff.T[ind_mat[mat_tab[k]-111111].j],ind_mat[mat_tab[k]-111111].j);
                gotoxy(130,34);
                printf("\e[48;5;252m\e[38;5;235m page %d/%d \e[0m",k+1,tab_size);
                gotoxy(35,34);
                printf("\e[38;5;159m  [ ECHAP ] : sortir   [ HAUT/GAUCHE ] : reculer/rapide   [ BAS/DROITE ] : avancer/rapide \e[0m");
            }
        }
        else if (command == 77) {
            if(k<tab_size){
                if (k+pas<tab_size){
                    k=k+pas;
                }
                else{
                    k=tab_size-1;
                }

                LireDir(*fich,ind_mat[mat_tab[k]-111111].i,&buff);
                afficher_enreg(buff.T[ind_mat[mat_tab[k]-111111].j],ind_mat[mat_tab[k]-111111].j);
                gotoxy(130,34);
                printf("\e[48;5;252m\e[38;5;235m page %d/%d \e[0m",k+1,tab_size);
                gotoxy(35,34);
                printf("\e[38;5;159m  [ ECHAP ] : sortir   [ HAUT/GAUCHE ] : reculer/rapide   [ BAS/DROITE ] : avancer/rapide \e[0m");
            }
        }
        else if ( command == 27){
            break ;
        }
    }

}

// fonction de l'interface homme-machine pour l'operation : affichage d'enregistrement selon ancientee et etablissement
void affiche_ens_etab_anc_input(TypeFich Fich){
    int etab;
    int bi , bs;
    etab=0;
    bi=0;
    bs=0;
    char data[128];


    clrscr();                                             // mise en page
    entete();
    printf("\n\n\n");
    titre_logo();
    gotoxy(0, NB_LINES-1);
    pied();
    rectangle(38, 20, 16, 80);
    for (int i=0; i<16; i++) {
        gotoxy(40, 19+i);
        printf("\e[48;5;252m                                                                                \e[0m");
    }
    gotoxy(0, 23); clrline2(); gotoxy(0, 24); clrline2();
    rectangle(38, 20, 16, 80);
    for (int i=0; i<16; i++) {
        gotoxy(40, 19+i);
        printf("\e[48;5;252m                                                                                \e[0m");
    }
    gotoxy(43, 19); printf("\e[48;5;255m\e[38;5;0m AFFICHAGE SELON %cTABLISSEMENT/ANCIENNET%c ", 144, 144);
    gotoxy(64, 22); printf("\e[48;5;252m\e[38;5;0m- ETABLISSEMENT --------------");
    gotoxy(64, 23); printf("\e[48;5;250m                              \e[48;5;0m");
    gotoxy(64, 26); printf("\e[48;5;252m\e[38;5;0m- ANNEE D'EXPERIENCE MIN -----");
    gotoxy(64, 27); printf("\e[48;5;250m                              \e[48;5;0m");
    gotoxy(64, 30); printf("\e[48;5;252m\e[38;5;0m- ANNEE D'EXPERIENCE MAX -----");
    gotoxy(64, 31); printf("\e[48;5;250m                              \e[48;5;0m");

    printf("\e[48;5;0m");

    // cases a remplir
    gotoxy(44, 37); strprintAnimate("\e[48;5;0m\e[38;5;159mChoisissez un entier entre [ 1 - 112 ] { veuillez consulter \"univ.txt\" }\e[0m", 1);
    do {
        gotoxy(64, 23); printf("\e[?25h\e[48;5;231m\e[38;5;0m                              "); secure_read(64, 23, data, 3); printf("\e[0m");
    } while (atoi(data) < 1 || atoi(data) > 112);
    etab = atoi(data)-1;

    gotoxy(0, 37); clrline2();
    gotoxy(54, 37); printf("\e[48;5;0m\e[38;5;159mEntrez le nombre d'annee d'experience minimal valide\e[0m");
    do {
        gotoxy(64, 27); printf("\e[?25h\e[48;5;231m\e[38;5;0m                              "); secure_read(64, 27, data, 2); printf("\e[0m");
    } while (atoi(data) < 0 || atoi(data) > 70 );
    bs = atoi(data);

    gotoxy(0, 37); clrline2();
    gotoxy(57, 37); printf("\e[48;5;0m\e[38;5;159mEntrez le nombre d'annee d'experience maximal\e[0m");
    do {
        gotoxy(64, 31); printf("\e[?25h\e[48;5;231m\e[38;5;0m                              "); secure_read(64, 31, data, 2); printf("\e[0m");
    } while (atoi(data) < bs || atoi(data) > 71);
    bi = atoi(data);
    printf("\e[?25l");

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    bi= (tm.tm_year+1900-bi)*10000+(tm.tm_mon+1)*100+tm.tm_mday;
    bs= (tm.tm_year+1900-bs)*10000+(tm.tm_mon+1)*100+tm.tm_mday;

    affiche_ens_etab_anc(etab,bi,bs,&Fich);
}

// fonction d'interface homme-macine qui affiche une suite d'enregistrement selon la region (avec la possiblite de navigation en utilisant des commandes)
void affiche_ens_region_input(TypeFich F) {
    char region='O';
    char data[128];
    clrscr();                                             // mise en page
    entete();
    printf("\n\n\n");
    titre_logo();
    gotoxy(0, NB_LINES-1);
    pied();

    gotoxy(0, 23); clrline2(); gotoxy(0, 24); clrline2();
    rectangle(38, 24, 7, 80);
    for (int i=0; i<7; i++) {
        gotoxy(40, 23+i);
        printf("\e[48;5;252m                                                                                \e[0m");
    }

    gotoxy(43, 23); printf("\e[48;5;255m\e[38;5;0m AFFICHAGE SELON REGION ");
    gotoxy(63, 26); printf("\e[48;5;252m\e[38;5;0mVeuillez choisir une r%cgion :  ", 130);
    gotoxy(96, 26); printf("\e[48;5;250m  \e[48;5;0m");
    printf("\e[48;5;0m");

    gotoxy(53, 35); strprintAnimate("\e[48;5;0m\e[38;5;159mChoisissez :  1 -> \"OUEST\"   2 -> \"CENTRE\"   3 -> \"EST\"\e[0m", 1);
    do {
        gotoxy(96, 26); printf("\e[?25h\e[48;5;231m\e[38;5;0m  "); secure_read(96, 26, data, 1); printf("\e[0m");
    } while (atoi(data) < 1 || atoi(data) > 3);

    if (atoi(data)==1){
        region = 'O';
    }
    else if(atoi(data)==2){
        region = 'C';
    }
    else {
        region = 'E';
    }
    printf("\e[?25l");
    affiche_ens_region(region,&F);
}

// fonction IHM representant l'operation : codage du fichier courant
int coder_input(TypeFich* fich) {
    char phrase[25]="codage en cours ...";
    char command;
    FILE* f;
    char nom_fich_codee[20] = "_CODE.bin";
    char nom_fich[100];
    strcpy(nom_fich,fich->nomFich);
    strtok(nom_fich,".bin");
    strcat(nom_fich,nom_fich_codee);
    char data[128];
    clrscr();                                             // mise en page
    entete();
    printf("\n\n\n");
    titre_logo();
    gotoxy(0, NB_LINES-1);
    pied();
    gotoxy(50, 22);
    printf("\e[1;93mCODER LE FICHIER COURANT");
    printf("\e[0m");
    printf("\n\t\t\t\t ___________________________________________________");
    rectangle(38, 20, 16, 80);
    for (int i=0; i<16; i++) {
        gotoxy(40, 19+i);
        printf("\e[48;5;252m                                                                                \e[0m");
    }
    clrline2(); gotoxy(0, 23); clrline2(); gotoxy(0, 24); clrline2();
    rectangle(38, 20, 16, 80);
    for (int i=0; i<16; i++) {
        gotoxy(40, 19+i);
        printf("\e[48;5;252m                                                                                \e[0m");
    }
    gotoxy(43, 19); printf("\e[48;5;255m\e[38;5;0m CODAGE ");
    gotoxy(65, 25); printf("\e[48;5;252m\e[38;5;0m- CLE ---------------------");
    gotoxy(65, 26); printf("\e[48;5;250m                           \e[48;5;0m");


    printf("\e[48;5;0m");

    // cases a remplir
    gotoxy(53, 37); strprintAnimate("\e[48;5;0m\e[38;5;159mENTRER UNE CLE ALPHANUMERIQUE DE TAILLE ENTRE 3 ET 30\e[0m", 3);
    do {
        gotoxy(65, 26); printf("\e[?25h\e[48;5;231m\e[38;5;0m                           "); secure_read(65, 26, data, 30); printf("\e[0m");
    } while (strlen(data)<4);
    f=fopen(nom_fich,"rb");
    printf("\e[?25l");
    for (int i=0; i<17; i++) {
        gotoxy(38, 19+i);
        printf("\e[0m                                                                                   ");
    }
    gotoxy(53, 37);
    clrline2();
    if(f!=NULL){
        fclose(f);
        gotoxy(55,25);
        strprintAnimate("\e[38;5;255mLe fichier code existe deja, ",10);
        usleep(500000);
        strprintAnimate("voulez vous l'ecraser?\e[0m",10);
        gotoxy(60,34); printf("\e[38;5;159m[ ECHAP ] : annuler    [ENTRER] : valider\e[0m");
        command=getch();
        while(command!=13 && command!=27 ){
            command=getch();
        }
        if(command==27){
            return 0;
        }
    }
    gotoxy(55,25);
    clrline2();
    gotoxy(60,34);
    clrline2();
    gotoxy(70,25);
    printf("\e[48;5;253;38;5;234m codage en cours ... ");


    coder(fich->fptr,nom_fich,data,strlen(data));
    codage_animation(71,25,phrase,19);

    gotoxy(77,30);
    printf("\e[0m\e[38;5;48m");
    strprintAnimate("SUCCES",10);
    sleep(1);
    printf("\e[0m");
    return 0;
}

//Fonction IHM representant l'operation: decodage d'un fichier donnée
int decoder_input() {
    char phrase[10]="%s#g^+";
    FILE* f;
    char fname[100];
    char fname_decoded[100];
    char data[128];
    clrscr();                                             // mise en page
    entete();
    printf("\n\n\n");
    titre_logo();
    gotoxy(0, NB_LINES-1);
    pied();
    gotoxy(50, 22);
    printf("\e[1;93mDECODER UN FICHIER");
    printf("\e[0m");
    printf("\n\t\t\t\t ___________________________________________________");
    rectangle(38, 20, 16, 80);
    for (int i=0; i<16; i++) {
        gotoxy(40, 19+i);
        printf("\e[48;5;252m                                                                                \e[0m");
    }
        clrline2(); gotoxy(0, 23); clrline2(); gotoxy(0, 24); clrline2();
        rectangle(38, 20, 16, 80);
        for (int i=0; i<16; i++) {
            gotoxy(40, 19+i);
            printf("\e[48;5;252m                                                                                \e[0m");
        }
        gotoxy(43, 19); printf("\e[48;5;255m\e[38;5;0m DECODAGE ");
        gotoxy(65, 22); printf("\e[48;5;252m\e[38;5;0m- INDICE ------------------");
        gotoxy(65, 23); printf("\e[48;5;250m                           \e[48;5;0m");
        gotoxy(65, 26); printf("\e[48;5;252m\e[38;5;0m- CLE ---------------------");
        gotoxy(65, 27); printf("\e[48;5;250m                           \e[48;5;0m");


        printf("\e[48;5;0m");

        // cases a remplir
        gotoxy(53, 37); strprintAnimate("\e[48;5;0m\e[38;5;159mENTRER L'INDICE DU FICHIER A DECODER - ENTIER POSITIF -\e[0m", 3);
        do {
            gotoxy(65, 23); printf("\e[?25h\e[48;5;231m\e[38;5;0m                           ");
            secure_read(65, 23, data, 50); printf("\e[0m");
        } while (atoi(data)<0);
        sprintf(fname,"ENSEIGNANT-MESRS_V%d_CODE.bin",atoi(data));

        f=fopen(fname,"rb");
        printf("\e[?25l");
        if(f==NULL){
            gotoxy(1,37);
            clrline2();
            inErrAnimate("le fichier n'existe pas !",69,37);
            sleep(1);
            return 0;

        }

        gotoxy(53, 37); clrline2();
        gotoxy(53, 37); strprintAnimate("\e[48;5;0m\e[38;5;159mENTRER UNE CLE ALPHANUMERIQUE DE TAILLE ENTRE 3 ET 50\e[0m", 3);
        do {
            gotoxy(65, 27); printf("\e[?25h\e[48;5;231m\e[38;5;0m                           ");
            secure_read(65, 27, data, 50); printf("\e[0m");
        } while (strlen(data)<4);
        printf("\e[?25l");

        strcpy(fname_decoded,fname);
        fname_decoded[19]='\0';
        strcat(fname_decoded,"_DECODE.bin");
        printf("\e[?25l");
        for (int i=0; i<17; i++) {
            gotoxy(38, 19+i);
            printf("\e[0m                                                                                   ");
        }
        gotoxy(70,25);
        printf("\e[48;5;253;38;5;234m decodage en cours \e[0m");

        decoder(fname,fname_decoded,data,strlen(data));

        gotoxy(77,30);
        printf("\e[0m\e[38;5;48m");
        codage_animation(77,30,phrase,6);

        gotoxy(78,30);
        printf("U");
        usleep(10000);
        gotoxy(80,30);
        printf("C");
        usleep(10000);
        gotoxy(82,30);
        printf("S");
        usleep(10000);
        gotoxy(77,30);
        printf("S");
        usleep(10000);
        gotoxy(79,30);
        printf("C");
        usleep(10000);
        gotoxy(81,30);
        printf("E");
        usleep(10000);

        sleep(1);
        printf("\e[0m");

        return 0;
}
