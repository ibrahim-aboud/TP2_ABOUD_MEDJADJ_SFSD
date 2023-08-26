#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>
#include "LnOF.h"
#define NB_LINES 40
#define NB_COLONS 160

/*Elle contient tout les fonctions basiques et peu avancés en relation avec l'interface homme-machine*/


void clrscr();

void init_console();

void clrline();

void clrline2();

void clrlines(int x, int y , int nb_lines);

void clrmenu(int length);

void entete();

void pied();

void strprintAnimate(char* str,int ms);

void inErrAnimate(char* str, int x, int y);

void esi_logo();

void reverse_esi_logo(int y);

void titre_logo();

void strprintblink (char* word, int blink_number , int blink_rate);

void strprintblinkkbhit(char* word, int blink_number, int blink_rate,int x,int y) ;

void intro();

void gotoxy(SHORT x1, SHORT y1);

void fade_in(char* word , int speed_ms, int x,int y);

void fade_out(char* word, int speed_ms,int x,int y);

void fade_in_out(char* text,int text_size,int x,int y);

void screen_on();

void screen_off();

void rectangle(int x, int y, int l, int w);

int codage_animation(int x,int y,char* mot,int taille_mot);

void afficher_enreg(TypeEnreg enreg,int num_enreg);

void print_space(int length);

void naviguer_bloc(TypeFich F);

void naviguer_enreg(TypeBloc* buf,int n_bloc);

void afficher_entete(TypeFich F);

void format_size(int sz, char sizee[30]);

void statusbar();

void affiche_seq_mat(int *mat_tab,int tab_size,TypeFich* fich);

void affiche_ens_etab_anc_input(TypeFich Fich);

void affiche_ens_region_input(TypeFich F);

int coder_input(TypeFich* fich);

int decoder_input();

#endif
