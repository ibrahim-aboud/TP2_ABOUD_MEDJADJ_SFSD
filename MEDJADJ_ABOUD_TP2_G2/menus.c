#include "menus.h"
#include "display.h"
#include "conio.h"
#include "LnOF.h"


// fonction qui affiche les menus de selection

void selectionner(char* str_array[], int tai, int x, int* y, int debut) {
    int initial_y = *y ;
    *y = 0;
    printf("\n");
    for (int i = 0; i < tai; i++) {                           // affichage du menu
        fade_in(str_array[i],debut,x,(*y)+initial_y+i);
    }
    printf("\n\t\t\t\t\t\t       ___________________________________________________");

    printf("\n\n");
    strprintblink("\t\t\t\t\t\t\t            <SELECTIONNER UNE ENTREE>",2,100*debut);
    clrline();
    printf("\n\n\n");

    gotoxy(x,(*y)+initial_y);
    printf("\e[107m");
    printf("\e[30m");
    printf("%s",str_array[0]);
    printf("\033[0m");
    gotoxy(x,(*y)+initial_y);

    time_t t_origine = time(NULL);

    char command = getch();                                   // une variable qui contient la derniere touche du clavier frappée par l'utilisateur
    while (command == 13 && (time(NULL)-t_origine)<0.5) {
        command = getch();
    }

    while(1)                                                  // 13 pour <ENTRER> , 72 pour <HAUT> , 80 pour <BAS>
    {

        if ( command == 72) {
            *y = ((*y) + tai-1 )%tai ;

            printf("%s",str_array[((*y)+1) % tai]);

            gotoxy(x,(*y)+initial_y);
            printf("\e[107m");
            printf("\e[30m");
            printf("%s",str_array[(*y)]);
            printf("\033[0m");
            gotoxy(x,(*y)+initial_y);
        }

        else if (command == 80) {
            *y = ((*y) +1 )%tai;
            printf("%s",str_array[((*y)+(tai-1)) % tai]);
            gotoxy(x,(*y)+initial_y);
            printf("\e[107m");
            printf("\e[30m");
            printf("%s",str_array[(*y)]);
            printf("\033[0m");
            gotoxy(x,(*y)+initial_y);
        }
        else if ( command == 13){
            break ;
        }
        command = getch();
    }
}


/*--------- page_de_chargement ---------*/

// page de chargement (+ animation de chargement)
void loading_page() {
    int nombre = rand()%6;                                    // nombre aleatoire entre 0 et 5 pour choisir une astuce aleatoire (ci-dessous)
    char* astuce[10] =  {"                                            Sur une echelle de 0 a 10, combien notez-vous cet ecran de chargement ?",
                         "                                                           Ce TP n'est pas pour les ames sensibles !",
                         "                                       Vous pouvez sauter l'introduction du programme en appuyant sur la touche <ENTRER>",
                         "                                Saviez vous que notre bibliotheque graphique est constituee de 95% de procedures faites maison !",
                         "                                     Veuillez utiliser les fleches <BAS> et <HAUT> pour selectionner une option sur le MENU",
                         "                      Si on genrere aleatoirement 1100 matricules (XXXXXX) en meme temps, il ya 50% de chance d'avoir au moin une collision !"};

    unsigned char before = 177, after = 219;
    clrscr();                                                 // mise en page
    esi_logo();
    screen_on();
    sleep(1);
    gotoxy(75, 26);
    printf("CHARGEMENT");
    printf("\e[38;5;30m");
    gotoxy(30, 28);
    for (int k = 1; k <= 100; k++) {
            printf("%c", before);
    }

    gotoxy(0, 32);
    printf("\e[38;5;45m%s\e[38;5;32m\n",astuce[nombre]);

    float j = 0.1;
    int i;
    for (int k = 0; k < 100; k++) {
        gotoxy(30+k, 28);
        printf("%c", after);
        if (k%3 == 0) {
            if (k%9 == 0) {gotoxy(85, 26); printf("   "); i = 0;}
            gotoxy(85+i, 26);
            printf("\e[0m.\e[38;5;32m");
            i++;
        }
        usleep(30000*j); j = j*1.0345;
    }

    gotoxy(0, 26);
    printf("\e[38;5;32m");
    printf("                                                                            TERMIN%c!                                                     \e[0m", 144);
    sleep(1);
}



/*----------- menu_principal -----------*/

void menu(int debut) {

    bool quit = false;
    TypeFich Fich;
    Fich_anc FichAnc;
    char tmp[40];
    char* menu_list [7] = { "        1. CREER/OUVRIR UN FICHIER                 ",
                            "        2. AFFICHER SELON UN CRITERE               ",
                            "        3. AJOUTER UN ENSEIGNANT                   ",
                            "        4. MODIFIER/SUPPRIMER ENSEIGNANT(S)        ",
                            "        5. CODER/DECODER LE FICHIER (.bin)         ",
                            "        6. A PROPOS DE NOTRE APPLICATION           ",
                            "        7. QUITTER L'APPLICATION                   "};
    int y;
    clrscr();                                             // mise en page
    entete();
    printf("\n\n\n");
    titre_logo();
    gotoxy(0, NB_LINES-1);
    pied();
    nombre_lect=0;
    nombre_ecr=0;
    do {
        // affichage de l'interface
        statusbar();
        if (!ouvert) {gotoxy(78, 18); printf("\e[38;5;64m            ---           \e[38;5;0m");}
        else {gotoxy(78, 18); printf("\e[38;5;114m%s\e[38;5;0m", Fich.nomFich);}
        gotoxy(36, 18);
        printf("\e[38;5;114m%07d\e[38;5;0m",nombre_ecr);
        gotoxy(135, 18);
        printf("\e[38;5;114m%07d\e[38;5;0m",nombre_lect);
        gotoxy(0, 22); clrline2(); gotoxy(73, 22);
        strprintAnimate("\e[1;93mMENU PRINCIPAL",40*debut);
        printf("\e[0m");
        printf("\n\t\t\t\t\t\t       ___________________________________________________");
        y = 25 ;
        selectionner(menu_list,7, 55, &y,debut);                    // menu de selection, (y) etant le choix effectué

        debut = 0;
        switch (y) {                                                // selection d'un choix
            case 0:                                                 // creer un nouveau fichier
                creer_ouvrirFich(&Fich, &FichAnc);
                break;

            case 1:                                                 // affichage
                if (ouvert) {
                    affichage(Fich);
                }
                else { // !ouvert
                    inErrAnimate("\e[91mERREUR: AUCUN FICHIER N'EST OUVERT!\e[0m", 63, 35);
                    sleep(1);
                    gotoxy(63, 35); clrline2();
                }
                break;

            case 2:                                                 // ajout d'un enseignant
                if (ouvert) {
                    ajouter(&Fich);
                }
                else { // !ouvert
                    inErrAnimate("\e[91mERREUR: AUCUN FICHIER N'EST OUVERT!\e[0m", 63, 35);
                    sleep(1);
                    gotoxy(63, 35); clrline2();
                }
                break;

            case 3:                                                 // Modification/suppression d'un/des enregistrement(s)
                if (ouvert) {
                    modif_supp(&Fich);
                }
                else { // !ouvert
                    inErrAnimate("\e[91mERREUR: AUCUN FICHIER N'EST OUVERT!\e[0m", 63, 35);
                    sleep(1);
                    gotoxy(63, 35); clrline2();
                }
                break;

            case 4:                                                 // Coder / Decoder
                de_code(&Fich);
                break;

            case 5:                                                 // Apropos
                apropos();
                clrscr();
                entete();
                printf("\n\n\n");
                titre_logo();
                gotoxy(0, NB_LINES-1);
                pied();
                break;

            case 6:                                                 // Quitter l'application
                // sauvegarde/fermeture du fichier courant s'il y en a
                if (ouvert) {
                    if (est_ouvert.type == 1) { // principal
                        FERMER(&Fich);
                        sprintf(tmp, "ENSEIGNANT-MESRS_V%d_IndANC.bin", est_ouvert.numero);
                        Anc_Sauv(FichAnc, tmp);
                    }
                    else {      // decodé  ( == 2 )
                        FERMER(&Fich);
                        sprintf(tmp, "ENSEIGNANT-MESRS_V%d_DECODE_IndANC.bin", est_ouvert.numero);
                        Anc_Sauv(FichAnc, tmp);
                    }
                }
                clrscr();
                reverse_esi_logo(10);
                fade_in("Merci d'avoir utiliser notre application!", 70, 59, 20);
                sleep(2);
                fade_out("Merci d'avoir utiliser notre application!", 70, 59, 20);
                quit = true;
                break;
        }
    } while (!quit);
}



/**_______________Sous_Menus_________________**/

void creer_ouvrirFich(TypeFich* Fich, Fich_anc* FichAnc) {
    char* menu_list [5] = { "     1. CREER UN NOUVEAU FICHIER                   ",
                            "     2. OUVRIR LA VERSION LA PLUS RECENTE          ",
                            "     3. OUVRIR UN FICHIER                          ",
                            "     4. OUVRIR UN FICHIER DECODE                   ",
                            "     <- RETOUR A LA PAGE PRECEDANTE                "};
    int y, t, i = 1;
    bool stop;
    bool retour = false;
    char c;
    char fname[40], data[30], tmp[40];
    do {
        clrscr();                                               // mise en page
        entete();
        printf("\n\n\n");
        titre_logo();
        gotoxy(0, NB_LINES-1);
        pied();
        gotoxy(69, 22);
        printf("\e[1;93mOUVERTURE D'UN FICHIER");
        printf("\e[0m");
        printf("\n\t\t\t\t\t\t       ___________________________________________________");
        y = 25 ;
        selectionner(menu_list,5, 55, &y,0);                    // menu de selection, (y) etant le choix effectué
        charg_Tab_Wilaya(wilaya,"wilaya.txt");
        charg_Tab_Etablissement(etablissement,"univ.txt");

        switch (y) {
            case 0:                                             // Creer un nouveau fichier
                t = 1;
                strcpy(fname, "ENSEIGNANT-MESRS_V0.bin");       // on verifie si un fichier avec le meme nom deja exist, si c'est le cas on reserve un autre nom
                while (fichier_existant(fname)) {
                    sprintf(fname, "ENSEIGNANT-MESRS_V%d.bin", t);
                    t++;
                }

                // sauvegarde/fermeture du fichier courant s'il y en a
                if (ouvert) {
                    if (est_ouvert.type == 1) {                 // principal
                        FERMER(Fich);
                        sprintf(tmp, "ENSEIGNANT-MESRS_V%d_IndANC.bin", est_ouvert.numero);
                        Anc_Sauv(*FichAnc, tmp);
                    }
                    else {                                      // decodé  ( == 2 )
                        FERMER(Fich);
                        sprintf(tmp, "ENSEIGNANT-MESRS_V%d_DECODE_IndANC.bin", est_ouvert.numero);
                        Anc_Sauv(*FichAnc, tmp);
                    }
                }

                OUVRIR(Fich, fname, 'N');
                nombre_ecr=0;
                nombre_lect=0;

                rectangle(44, 32, 4, 70);
                for (int i=0; i<3; i++) {
                    gotoxy(46, 32+i);
                    printf("\e[48;5;252m                                                                      \e[0m");
                }
                do{
                    gotoxy(47, 33); printf("\e[48;5;252m\e[38;5;0m> Veuillez introduire le nombre d'enregistrements a generer: ");
                    gotoxy(108, 33); printf("\e[?25h\e[48;5;231m\e[38;5;0m       "); secure_read(108, 33, data, 6); printf("\e[0m");

                }while(atoi(data)<=0);

                chargement_initial(Fich, atoi(data));
                printf("\e[?25l");

                gotoxy(77, 36);
                strprintAnimate("\e[92mSUCC",10);
                printf("%c",144);
                printf("S\e[0m");
                sleep(1);
                for (int i=0; i<8; i++) {
                    gotoxy(46, 30+i);
                    clrline2();
                }
                retour = true;
                ouvert = true;
                est_ouvert.numero = t-1;
                est_ouvert.type = 1;
                break;
            case 1:                                             //Ouvrir la version la plus recente
                i = 0;
                strcpy(fname, "ENSEIGNANT-MESRS_V0.bin");         // on verifie si un fichier avec le meme nom deja exist, si c'est le cas on reserve un autre nom
                while (fichier_existant(fname)) {
                    i++;
                    sprintf(fname, "ENSEIGNANT-MESRS_V%d.bin", i);
                }
                i--;
                if (i == -1) { // erreur, pas de fichiers recents
                    inErrAnimate("\e[91mERREUR: AUCUN FICHIER EXISTANT!\e[0m", 65, 32);
                    sleep(1);
                    gotoxy(56, 32); clrline2();
                }
                else {

                    // sauvegarde/fermeture du fichier courant s'il y en a
                    if (ouvert) {
                        if (est_ouvert.type == 1) { // principal
                            FERMER(Fich);
                            sprintf(tmp, "ENSEIGNANT-MESRS_V%d_IndANC.bin", est_ouvert.numero);
                            Anc_Sauv(*FichAnc, tmp);
                        }
                        else {      // decodé  ( == 2 )
                            FERMER(Fich);
                            sprintf(tmp, "ENSEIGNANT-MESRS_V%d_DECODE_IndANC.bin", est_ouvert.numero);
                            Anc_Sauv(*FichAnc, tmp);
                        }
                    }

                    sprintf(fname, "ENSEIGNANT-MESRS_V%d.bin", i);
                    OUVRIR(Fich, fname, 'A');
                    gotoxy(77, 32);
                    strprintAnimate("\e[92mSUCC",10);
                    printf("%c",144);
                    printf("S\e[0m");

                    nombre_ecr=0;
                    nombre_lect=0;

                    Index_charg(Fich);   // chargement des indexes
                    sprintf(fname, "ENSEIGNANT-MESRS_V%d_IndANC.bin", i);
                    Anc_charg(*FichAnc, fname);

                    ouvert = true;
                    est_ouvert.numero = i;
                    est_ouvert.type = 1;
                    sleep(1);
                    gotoxy(77, 32); clrline2();
                    retour = true;
                }

                break;
            case 2:                                             //Ouvrir Un fichier quelconque
                strcpy(fname, "ENSEIGNANT-MESRS_V0.bin");         // on verifie si un fichier avec le meme nom deja exist, si c'est le cas on reserve un autre nom
                if (fichier_existant(fname)) {
                    for (int t = 0; t < 17; t++) {gotoxy(0, 22+t); clrline2();}
                    gotoxy(64, 22);
                    printf("\e[1;93mSELECTIONNEZ UN FICHIER A OUVRIR");
                    printf("\e[0m");
                    printf("\n\t\t\t\t\t\t       ___________________________________________________");

                    int k = 0;
                    strcpy(fname, "ENSEIGNANT-MESRS_V0.bin");         // on verifie si un fichier avec le meme nom deja exist, si c'est le cas on reserve un autre nom
                    while (fichier_existant(fname)) {
                        k++;
                        sprintf(fname, "ENSEIGNANT-MESRS_V%d.bin", k);
                    }

                    // sauvegarde/fermeture du fichier courant s'il y en a
                    if (ouvert) {
                        if (est_ouvert.type == 1) { // principal
                            FERMER(Fich);
                            sprintf(tmp, "ENSEIGNANT-MESRS_V%d_IndANC.bin", est_ouvert.numero);
                            Anc_Sauv(*FichAnc, tmp);
                        }
                        else {      // decodé  ( == 2 )
                            FERMER(Fich);
                            sprintf(tmp, "ENSEIGNANT-MESRS_V%d_DECODE_IndANC.bin", est_ouvert.numero);
                            Anc_Sauv(*FichAnc, tmp);
                        }
                    }


                    for (int t = 0; t < 14; t++) {gotoxy(0, 25+t); clrline2();}
                    rectangle(34, 25, 7, 90);
                    for (int i=0; i<6; i++) {
                        gotoxy(36, 25+i);
                        printf("\e[48;5;252m                                                                                        \e[0m");
                    }
                    gotoxy(52, 27); printf("\e[48;5;252m\e[38;5;0m> Fichier %c ouvrir [ 0 - %2d ]: \"ENSEIGNANT-MESRS_V\e[48;5;243m  \e[48;5;252m.bin\"\e[48;5;0m", 133, k-1);
                    gotoxy(0, 34); clrline2(); gotoxy(0, 33); clrline2();
                    do {
                        gotoxy(102, 27); printf("\e[?25h\e[48;5;231m\e[38;5;0m  "); secure_read(102, 27, data, 2); printf("\e[0m\e[?25l");
                    } while (atoi(data) < 0 || atoi(data) >= k);

                    sprintf(fname, "ENSEIGNANT-MESRS_V%d.bin", atoi(data));
                    OUVRIR(Fich, fname, 'A');
                    gotoxy(77, 32);
                    strprintAnimate("\e[92mSUCC",10);
                    printf("%c",144);
                    printf("S\e[0m");

                    nombre_ecr=0;
                    nombre_lect=0;

                    Index_charg(Fich);   // chargement des indexes
                    sprintf(fname, "ENSEIGNANT-MESRS_V%d_IndANC.bin", atoi(data));
                    Anc_charg(*FichAnc, fname);

                    ouvert = true;
                    est_ouvert.numero = atoi(data);
                    est_ouvert.type = 1;
                    sleep(1);
                    for (int t=0; t<15; t++) {gotoxy(0, 25+t); clrline2();}
                    retour = true;
                }
                else {
                    inErrAnimate("\e[91mERREUR: AUCUN FICHIER EXISTANT!\e[0m", 65, 32);
                    sleep(1);
                    gotoxy(0, 32); clrline2();
                }
                break;
            case 3:                                             // Ouvrir un fichier decodé
                stop = false;
                for (int t = 0; t < 17; t++) {gotoxy(0, 22+t); clrline2();}
                gotoxy(64, 22);
                printf("\e[1;93mSELECTIONNEZ UN FICHIER A OUVRIR");
                printf("\e[0m");
                printf("\n\t\t\t\t\t\t       ___________________________________________________");

                // sauvegarde/fermeture du fichier courant s'il y en a
                if (ouvert) {
                    if (est_ouvert.type == 1) { // principal
                        FERMER(Fich);
                        sprintf(tmp, "ENSEIGNANT-MESRS_V%d_IndANC.bin", est_ouvert.numero);
                        Anc_Sauv(*FichAnc, tmp);
                    }
                    else {      // decodee  ( == 2 )
                        FERMER(Fich);
                        sprintf(tmp, "ENSEIGNANT-MESRS_V%d_DECODE_IndANC.bin", est_ouvert.numero);
                        Anc_Sauv(*FichAnc, tmp);
                    }
                }


                for (int t = 0; t < 14; t++) {gotoxy(0, 25+t); clrline2();}
                rectangle(34, 25, 7, 90);
                for (int i=0; i<6; i++) {
                    gotoxy(36, 25+i);
                    printf("\e[48;5;252m                                                                                        \e[0m");
                }
                gotoxy(54, 27); printf("\e[48;5;252m\e[38;5;0m> Fichier %c ouvrir : \"ENSEIGNANT-MESRS_V\e[48;5;243m  \e[48;5;252m_DECODE.bin\"\e[48;5;0m", 133);
                gotoxy(0, 34); clrline2(); gotoxy(0, 33); clrline2();
                do {
                    gotoxy(0, 33); clrline2(); gotoxy(0, 35); clrline2();
                    gotoxy(94, 27); printf("\e[?25h\e[48;5;231m\e[38;5;0m  "); secure_read(94, 27, data, 2); printf("\e[0m\e[?25l");
                    sprintf(fname, "ENSEIGNANT-MESRS_V%d_DECODE.bin", atoi(data));
                    if (!fichier_existant(fname)) {
                        inErrAnimate("\e[91mERREUR: FICHIER INEXISTANT!\e[0m", 66, 33);
                        gotoxy(56,35); printf("\e[38;5;159m[ ECHAP ] : annuler       [ ENTRER ] : r%cessayer\e[0m", 130);

                        do {c = getch();} while ( c != 27 && c != 13);
                        if (c == 27) stop = true;
                    }
                    else stop = true;
                } while (!stop);

                if (fichier_existant(fname)) {

                    OUVRIR(Fich, fname, 'A');

                    gotoxy(77, 32);
                    strprintAnimate("\e[92mSUCC",10);
                    printf("%c",144);
                    printf("S\e[0m");

                    nombre_ecr=0;
                    nombre_lect=0;

                    Index_charg(Fich);   // chargement des indexes


                    sprintf(fname, "ENSEIGNANT-MESRS_V%d_DECODE_IndANC.bin", atoi(data));
                    if (!fichier_existant(fname)) {
                        sprintf(fname, "ENSEIGNANT-MESRS_V%d_IndANC.bin", atoi(data));
                    }
                    Anc_charg(*FichAnc, fname);

                    ouvert = true;
                    est_ouvert.numero = atoi(data);
                    est_ouvert.type = 2;
                    sleep(1);
                    for (int t=0; t<15; t++) {gotoxy(0, 25+t); clrline2();}
                    retour = true;
                }
                break;
            case 4:                                             //Retour a la page precedente
                retour = true;
                break;
        }
    } while (!retour);
}


// Contient tous type d'affichage d'informations contenu dans le fichier en MS, selon certaines conditions
void affichage(TypeFich Fich) {
    char command;
    char* menu_list [5] = { "    1. AFFICHER SELON L'ETABLISSEMENT/ANCIENNETE   ",
                            "    2. AFFICHER SELON UNE REGION DONNEE            ",
                            "    3. AFFICHER TOUT LE FICHIER                    ",
                            "    4. AFFICHER L'EN-TETE                          ",
                            "    <- RETOUR A LA PAGE PRECEDANTE                 "};
    int y;
    bool retour = false;
    char c;
    do {
        clrscr();                                             // mise en page
        entete();
        printf("\n\n\n");
        titre_logo();
        gotoxy(0, NB_LINES-1);
        pied();
        gotoxy(69, 22);
        printf("\e[1;93mAFFICHAGE D'UN FICHIER");
        printf("\e[0m");
        printf("\n\t\t\t\t\t\t       ___________________________________________________");

        y = 25 ;
        selectionner(menu_list,5, 55, &y,0);                    // menu de selection, (y) etant le choix effectué

        switch (y) {
            case 0:                                             // Afficher avec critères : Etablissement et Ancientée
                clrscr();
                affiche_ens_etab_anc_input(Fich);
                break;
            case 1:                                             // Afficher selon la region
                clrscr();
                affiche_ens_region_input(Fich);
                break;
            case 2:                                             // Affichage de tout le contenu du fichier
                clrscr();
                if(Fich.entete.nb_enr_ins!=0){
                    naviguer_bloc(Fich);
                }
                else{

                    clrscr();
                    gotoxy(0,0);
                    entete();
                    gotoxy(0,39);
                    pied();
                    gotoxy(72,20);
                    printf("     FICHIER VIDE    ");
                    gotoxy(30,34);
                    printf("\e[38;5;159m                                           [ ECHAP ] : sortir\e[0m");
                    while(1){
                        command=getch();
                        if (command==27){
                            break;
                        }
                    }
                }

                break;
            case 3:                                             // Affichage de l'entete
                clrscr();
                afficher_entete(Fich);
                c = getch();
                while (c != 27) {
                    c = getch();
                }
                break;
            case 4:
                retour = true;
                break;
        }
    } while (!retour);
}

// fonction qui permet d'ajouter un enregistrement au fichier en MS
void ajouter(TypeFich* Fich) {
    char* menu_list [3] = { "       1. GENERER ALEATOIREMENT                    ",
                            "       2. ENTRER LES INFORMATIONS VOUS-MEME        ",
                            "       <- RETOUR A LA PAGE PRECEDANTE              "};
    char* diplome_list [6] = {  "                  Doctorat d'Etat                  ",
                                "                Doctorat en sciences               ",
                                "                   Doctorat D-LMD                  ",
                                "                        PhD                        ",
                                "             Habilitation Universitaire            ",
                                "                     Magistere                     "};
    char* grade_list [6] = {"                   Professeur(e)                   ",
                            "            Maitre de conferences Rang A           ",
                            "            Maitre de conferences Rang B           ",
                            "             Maitre assistant(e) Rang A            ",
                            "             Maitre assistant(e) Rang B            ",
                            "                   Assistant(e)                    "};
    char* specialite_list [10] = {"                   Informatique                    ",
                                  "                   Architecture                    ",
                                  "                     Medecine                      ",
                                  "                     Physique                      ",
                                  "                   Mathematiques                   ",
                                  "                      Chimie                       ",
                                  "                 Sciences Humaines                 ",
                                  "                   Electronique                    ",
                                  "                     Economie                      ",
                                  "                       Droit                       "};

    int y;
    bool retour = false;
    TypeEnreg e;
    char data[128], c;
    do {
        clrscr();                                               // mise en page
        entete();
        printf("\n\n\n");
        titre_logo();
        gotoxy(0, NB_LINES-1);
        pied();
        gotoxy(69, 22);
        printf("\e[1;93mAJOUTER UN ENSEIGNANT");
        printf("\e[0m");
        printf("\n\t\t\t\t\t\t       ___________________________________________________");

        y = 25 ;
        selectionner(menu_list,3, 55, &y,0);                    // menu de selection, (y) etant le choix effectué
        char tmp[30];

        switch (y) {
            case 0:                                             // ajouter un enregistrement avec donne aleatoire
                while (1) {
                    genEnreg(&e);
                    afficher_enreg(e, ENTETE(*Fich, 3)+1);
                    gotoxy(56,34); printf("\e[38;5;159m[ ECHAP ] : annuler       [ ENTRER ] : confirmer\e[0m");
                    c = getch();
                    if (c == 27) {
                        break;
                    }
                    if (c == 13) {
                        if ((ins_enreg(Fich, e))) {inErrAnimate("\e[91mERREUR: MATRICULE DEJA EXISTANT!\e[0m", 64, 32); sleep(1);}
                        else {
                            strcpy(tmp, Fich->nomFich);
                            FERMER(Fich);
                            OUVRIR(Fich, tmp, 'A');
                            gotoxy(72,34); clrline2(); gotoxy(77, 34);
                            strprintAnimate("\e[92mSUCC",10); printf("%c",144); printf("S\e[0m");
                            sleep(1);
                        }
                        break;
                    }
                }
                break;
            case 1:                                             //ajout d'un enregistrement avec un contenu personalisé
                // entree utilisateur
                clrmenu(6); gotoxy(0, 22); clrline2(); gotoxy(0, 23); clrline2(); gotoxy(0, 24); clrline2();
                rectangle(38, 20, 16, 80);
                for (int i=0; i<16; i++) {
                    gotoxy(40, 19+i);
                    printf("\e[48;5;252m                                                                                \e[0m");
                }
                gotoxy(43, 19); printf("\e[48;5;255m\e[38;5;0m NOUVEAU ENSEIGNANT ");
                gotoxy(45, 21); printf("\e[48;5;252m\e[38;5;0m- MATRICULE ------------------         - SEXE ----------------------- ");
                gotoxy(45, 22); printf("\e[48;5;250m                              \e[48;5;0m\e[48;5;252m         \e[48;5;250m                              \e[48;5;0m");
                gotoxy(45, 24); printf("\e[48;5;252m\e[38;5;0m- NOM ------------------------         - PRENOM --------------------- ");
                gotoxy(45, 25); printf("\e[48;5;250m                              \e[48;5;0m\e[48;5;252m         \e[48;5;250m                              \e[48;5;0m");
                gotoxy(45, 27); printf("\e[48;5;252m\e[38;5;0m- DATE DE NAISSANCE ----------         - WILAYA DE NAISSANCE -------- ");
                gotoxy(45, 28); printf("\e[38;5;240m JJ: \e[48;5;250m   \e[48;5;252m  MM: \e[48;5;250m   \e[48;5;252m  AAAA: \e[48;5;250m     \e[48;5;0m\e[48;5;252m         \e[48;5;250m                              \e[48;5;0m");
                gotoxy(45, 30); printf("\e[48;5;252m\e[38;5;0m- DATE DE RECRUTEMENT --------         - GROUPE SANGUIN ------------- ");
                gotoxy(45, 31); printf("\e[38;5;240m JJ: \e[48;5;250m   \e[48;5;252m  MM: \e[48;5;250m   \e[48;5;252m  AAAA: \e[48;5;250m     \e[48;5;0m\e[48;5;252m         \e[48;5;250m                              \e[48;5;0m");
                for (int i = 0; i < 12; i++) {gotoxy(80, 21+i); printf("\e[48;5;252m\e[38;5;0m%c", 179);}
                printf("\e[48;5;0m");

                // cases a remplir
                gotoxy(57, 37); strprintAnimate("\e[48;5;0m\e[38;5;159mChoisissez un entier entre [ 111111 - 999999 ]\e[0m", 3);
                do {
                    gotoxy(45, 22); printf("\e[?25h\e[48;5;231m\e[38;5;0m                              "); secure_read(45, 22, data, 30); printf("\e[0m");
                } while (atoi(data) < 111111 || atoi(data) > 999999);
                e.matricule = atoi(data);


                gotoxy(0, 37); clrline2();
                gotoxy(56, 37); printf("\e[48;5;0m\e[38;5;159mEntrez \"1\" pour MASCULIN ou \"2\" pour FEMININ\e[0m");
                do {
                    gotoxy(84, 22); printf("\e[?25h\e[48;5;231m\e[38;5;0m                              "); secure_read(84, 22, data, 30); printf("\e[0m");
                } while (atoi(data) != 1 && atoi(data) != 2);
                e.sexe = atoi(data)-1;


                gotoxy(0, 37); clrline2();
                gotoxy(62, 37); printf("\e[48;5;0m\e[38;5;159mEntrer un nom [ 4 - 30 CARACTERES ]\e[0m");
                do {
                    gotoxy(45, 25); printf("\e[?25h\e[48;5;231m\e[38;5;0m                              "); secure_read(45, 25, data, 30); printf("\e[0m");
                } while (strlen(data) < 4);
                strcpy(e.nom, data);


                gotoxy(0, 37); clrline2();
                gotoxy(60, 37); printf("\e[48;5;0m\e[38;5;159mEntrer un prenom [ 4 - 30 CARACTERES ]\e[0m");
                do {
                    gotoxy(84, 25); printf("\e[?25h\e[48;5;231m\e[38;5;0m                              "); secure_read(84, 25, data, 30); printf("\e[0m");
                } while (strlen(data) < 4);
                strcpy(e.prenom, data);

                int d, m, y;
                gotoxy(0, 37); clrline2();
                gotoxy(69, 37); printf("\e[48;5;0m\e[38;5;159mEntrer une date valide\e[0m");
                do {
                    gotoxy(45, 28); printf("\e[?25h\e[48;5;252m\e[38;5;240m JJ: \e[48;5;231m   \e[48;5;252m  MM: \e[48;5;231m   \e[48;5;252m  AAAA: \e[48;5;231m     \e[48;5;231m\e[38;5;0m"); secure_read(50, 28, data, 2); printf("\e[0m");
                    d = atoi(data);
                    gotoxy(59, 28); printf("\e[?25h\e[48;5;231m\e[38;5;0m"); secure_read(59, 28, data, 2); printf("\e[0m");
                    m = atoi(data);
                    gotoxy(70, 28); printf("\e[?25h\e[48;5;231m\e[38;5;0m"); secure_read(70, 28, data, 4); printf("\e[0m");
                    y = atoi(data);
                } while (!check_date(y, m, d, 1953, 1998));
                e.date_Naissance = y*10000+m*100+d;


                gotoxy(0, 37); clrline2();
                gotoxy(64, 37); printf("\e[48;5;0m\e[38;5;159mChoisissez une Wilaya [ 1 - 58 ]\e[0m");
                do {
                    gotoxy(84, 28); printf("\e[?25h\e[48;5;231m\e[38;5;0m                              "); secure_read(84, 28, data, 30); printf("\e[0m");
                } while (atoi(data) < 1 || atoi(data) > 58);
                e.wilaya_Naissance = atoi(data)-1;


                gotoxy(0, 37); clrline2();
                gotoxy(69, 37); printf("\e[48;5;0m\e[38;5;159mEntrer une date valide\e[0m");
                do {
                    gotoxy(45, 31); printf("\e[?25h\e[48;5;252m\e[38;5;240m JJ: \e[48;5;231m   \e[48;5;252m  MM: \e[48;5;231m   \e[48;5;252m  AAAA: \e[48;5;231m     \e[48;5;231m\e[38;5;0m"); secure_read(50, 31, data, 2); printf("\e[0m");
                    d = atoi(data);
                    gotoxy(59, 31); printf("\e[?25h\e[48;5;231m\e[38;5;0m"); secure_read(59, 31, data, 2); printf("\e[0m");
                    m = atoi(data);
                    gotoxy(70, 31); printf("\e[?25h\e[48;5;231m\e[38;5;0m"); secure_read(70, 31, data, 4); printf("\e[0m");
                    y = atoi(data);
                } while (!check_date(y, m, d, 1985, 2022));
                e.date_recrutement = y*10000+m*100+d;


                gotoxy(0, 37); clrline2();
                gotoxy(37, 37); printf("\e[48;5;0m\e[38;5;159m\"1\" : O+ | \"2\" : A+ | \"3\" : B+ | \"4\" : O- | \"5\" : A- | \"6\" : AB+ | \"7\" : B- | \"8\" : AB-\e[0m");
                do {
                    gotoxy(84, 31); printf("\e[?25h\e[48;5;231m\e[38;5;0m                              "); secure_read(84, 31, data, 30); printf("\e[0m");
                } while (atoi(data) < 1 || atoi(data) > 8);
                e.groupe_sanguin = atoi(data)-1;


                for (int t = 0; t < 19; t++) {gotoxy(0, 19+t); clrline2();}
                gotoxy(73, 22); printf("\e[1;93mDERNIER DIPLOME\e[0m"); printf("\n\t\t\t\t\t\t       ___________________________________________________");
                y = 25;
                selectionner(diplome_list, 6, 55, &y, 0);
                e.dernier_diplome = y;


                for (int t = 0; t < 19; t++) {gotoxy(0, 19+t); clrline2();}
                gotoxy(75, 22); printf("\e[1;93mSPECIALITE\e[0m"); printf("\n\t\t\t\t\t\t       ___________________________________________________");
                y = 25;
                selectionner(specialite_list, 10, 55, &y, 0);
                e.specialite = y;


                for (int t = 0; t < 19; t++) {gotoxy(0, 19+t); clrline2();}
                gotoxy(77, 22); printf("\e[1;93mGRADE\e[0m"); printf("\n\t\t\t\t\t\t       ___________________________________________________");
                y = 25;
                selectionner(grade_list, 6, 55, &y, 0);
                e.grade = y;


                for (int t = 0; t < 19; t++) {gotoxy(0, 19+t); clrline2();}
                rectangle(33, 20, 8, 90);
                for (int i=0; i<7; i++) {
                    gotoxy(35, 20+i);
                    printf("\e[48;5;252m                                                                                        \e[0m");
                }
                gotoxy(42, 22); printf("\e[48;5;252m\e[38;5;0m> Veuillez introduire le numero de l'etablissement [ 1 - 112 ]: ");
                gotoxy(39, 25); printf("\e[48;5;255m\e[38;5;0m RQUE: consultez le fichier \"univ.txt\" pour recuperer le numero d'etablissement ");
                do {
                    gotoxy(109, 22); printf("\e[?25h\e[48;5;231m\e[38;5;0m       "); secure_read(109, 22, data, 3); printf("\e[0m");
                } while (atoi(data) < 1 || atoi(data) > 112);
                e.etablissement_univ = atoi(data)-1;


                // confirmation puis insertion dans le fichier
                afficher_enreg(e, ENTETE(*Fich, 3)+1);
                gotoxy(56,34); printf("\e[38;5;159m[ ECHAP ] : annuler       [ ENTRER ] : confirmer\e[0m\e[?25l");
                c = getch();
                if (c == 27) {
                    break;
                }
                if (c == 13) {
                    if ((ins_enreg(Fich, e))) {inErrAnimate("\e[91mERREUR: MATRICULE DEJA EXISTANT!\e[0m", 64, 32); sleep(1);}
                    else {
                        ins_enreg(Fich, e);
                        strcpy(tmp, Fich->nomFich);
                        FERMER(Fich);
                        OUVRIR(Fich, tmp, 'A');
                        gotoxy(72,34); clrline2(); gotoxy(77, 34);
                        strprintAnimate("\e[92mSUCC",10); printf("%c",144); printf("S\e[0m");
                        sleep(1);
                    }
                    break;
                }
                break;
            case 2:
                retour = true;
                break;
        }
    } while (!retour);
}


// cette fonction permet de modifier/supprimer des enregistrments du fichier selon certain critere
void modif_supp(TypeFich* Fich) {
    char* menu_list [4] = { "     1. MODIFIER ETABLISSEMENT                     ",
                            "     2. SUPPRIMER ENSEIGNANT                       ",
                            "     3. SUPPRIMER ENSEIGNANTS D'UNE SPECIALITE     ",
                            "     <- RETOUR A LA PAGE PRECEDANTE                "};
    char* specialite_list [10] = {"                   Informatique                    ",
                                  "                   Architecture                    ",
                                  "                     Medecine                      ",
                                  "                     Physique                      ",
                                  "                   Mathematiques                   ",
                                  "                      Chimie                       ",
                                  "                 Sciences Humaines                 ",
                                  "                   Electronique                    ",
                                  "                     Economie                      ",
                                  "                       Droit                       "};
    int y, mat;
    bool retour = false, continu = false;
    char data[30], c;

    do {
        clrscr();                                             // mise en page
        entete();
        printf("\n\n\n");
        titre_logo();
        gotoxy(0, NB_LINES-1);
        pied();
        gotoxy(66, 22);
        printf("\e[1;93mMODIFICATION ET SUPPRESSION");
        printf("\e[0m");
        printf("\n\t\t\t\t\t\t       ___________________________________________________");

        y = 25 ;
        selectionner(menu_list, 4, 55, &y, 0);                    // menu de selection, (y) etant le choix effectué

        switch (y) {
            case 0:                                             // modifier l'etablissement d'un enseignant
                // entrée utilisateur (matricule)
                for (int t = 0; t < 14; t++) {gotoxy(0, 25+t); clrline2();}
                rectangle(34, 25, 7, 90);
                for (int i=0; i<6; i++) {
                    gotoxy(36, 25+i);
                    printf("\e[48;5;252m                                                                                        \e[0m");
                }
                gotoxy(43, 27); printf("\e[48;5;252m\e[38;5;0m> Veuillez introduire un matricule %c rechercher [111111 - 999999]: \e[48;5;0m", 133);
                // recherche index matricule et verification de l'existance du matricule
                do {
                    gotoxy(0, 34); clrline2(); gotoxy(0, 33); clrline2();
                    do {
                        gotoxy(110, 27); printf("\e[?25h\e[48;5;231m\e[38;5;0m       "); secure_read(110, 27, data, 6); printf("\e[0m\e[?25l");
                    } while (atoi(data) < 111111 || atoi(data) > 999999);
                    if (!(ind_mat[atoi(data)-111111].exist)) {
                        inErrAnimate("\e[91mERREUR: MATRICULE INEXISTANT!\e[0m", 65, 33);
                        gotoxy(56,35); printf("\e[38;5;159m[ ECHAP ] : annuler       [ ENTRER ] : r%cessayer\e[0m", 130);
                        c = getch();
                        while (c != 27 && c != 13) {
                            c = getch();
                        }
                        if (c == 27) continu = false;
                        else continu = true;
                    }
                    else continu = false;
                } while (continu);

                if (ind_mat[atoi(data)-111111].exist) {// s'il existe, on modifie l'etablissement
                    // entrée utilisateur (numéro etablissement)
                    mat = atoi(data);
                    for (int t = 0; t < 14; t++) {gotoxy(0, 25+t); clrline2();}
                    rectangle(34, 25, 8, 90);
                    for (int i=0; i<7; i++) {
                        gotoxy(36, 25+i);
                        printf("\e[48;5;252m                                                                                        \e[0m");
                    }
                    gotoxy(43, 27); printf("\e[48;5;252m\e[38;5;0m> Veuillez introduire le num%cro de l'%ctablissement [ 1 - 112 ]: ", 130, 130);
                    gotoxy(40, 31); printf("\e[48;5;255m\e[38;5;0m RQUE: consultez le fichier \"univ.txt\" pour r%ccup%crer le numero d'%ctablissement ", 130, 130, 130);
                    do {
                        gotoxy(110, 27); printf("\e[?25h\e[48;5;231m\e[38;5;0m       "); secure_read(110, 27, data, 3); printf("\e[0m\e[?25l");
                    } while (atoi(data) < 1 || atoi(data) > 112);

                    // modification
                    modif_et_reg(Fich, mat, atoi(data)-1);
                    gotoxy(72,34); clrline2(); gotoxy(77, 34);
                    strprintAnimate("\e[92mSUCC",10); printf("%c",144); printf("S\e[0m");
                    sleep(1);
                }
                break;
            case 1:                                             // supprimer un enregistrement donné par son matricule
                // entrée utilisateur (matricule)
                for (int t = 0; t < 14; t++) {gotoxy(0, 25+t); clrline2();}
                rectangle(34, 25, 7, 90);
                for (int i=0; i<6; i++) {
                    gotoxy(36, 25+i);
                    printf("\e[48;5;252m                                                                                        \e[0m");
                }
                gotoxy(43, 27); printf("\e[48;5;252m\e[38;5;0m> Veuillez introduire un matricule %c rechercher [111111 - 999999]: \e[48;5;0m", 133);
                // recherche index matricule et verification de l'existance du matricule
                do {
                    gotoxy(0, 34); clrline2(); gotoxy(0, 33); clrline2();
                    do {
                        gotoxy(110, 27); printf("\e[?25h\e[48;5;231m\e[38;5;0m       "); secure_read(110, 27, data, 6); printf("\e[0m\e[?25l");
                    } while (atoi(data) < 111111 || atoi(data) > 999999);
                    if (!(ind_mat[atoi(data)-111111].exist)) {
                        inErrAnimate("\e[91mERREUR: MATRICULE INEXISTANT!\e[0m", 65, 33);
                        gotoxy(56,35); printf("\e[38;5;159m[ ECHAP ] : annuler       [ ENTRER ] : r%cessayer\e[0m", 130);
                        c = getch();
                        while (c != 27 && c != 13) {
                            c = getch();
                        }
                        if (c == 27) continu = false;
                        else continu = true;
                    }
                    else continu = false;
                } while (continu);

                if (ind_mat[atoi(data)-111111].exist) { // s'il existe, on modifie l'etablissement

                    // suppression
                    suppr_enr(Fich, atoi(data));
                    gotoxy(72,34); clrline2(); gotoxy(77, 34);
                    strprintAnimate("\e[92mSUCC",10); printf("%c",144); printf("S\e[0m");
                    sleep(1);
                }
                break;
            case 2:                                             // supprimer tout les enregistrement dans une specialité donnée

                gotoxy(61, 22);
                printf("\e[1;93mSELECTIONNEZ LA SP%cCIALIT%c A SUPPRIMER", 144, 144);
                printf("\e[0m");
                printf("\n\t\t\t\t\t\t       ___________________________________________________");
                // entrée utilisateur (specialité)
                y = 25;
                selectionner(specialite_list, 10, 55, &y, 0);
                suppr_all_spec(Fich, y);
                gotoxy(72,37); clrline2(); gotoxy(77, 37);
                strprintAnimate("\e[92mSUCC",10); printf("%c",144); printf("S\e[0m");
                sleep(1);
                break;
            case 3:
                retour = true;
                break;
        }
    } while (!retour);
}

void de_code(TypeFich* Fich) {
    char* menu_list [3] = { "           1. CODER LE FICHIER COURANT             ",
                            "           2. DECODER UN FICHIER                   ",
                            "           <- RETOUR A LA PAGE PRECEDANTE          "};
    int y;
    bool retour = false;

    do {
        clrscr();                                             // mise en page
        entete();
        printf("\n\n\n");
        titre_logo();
        gotoxy(0, NB_LINES-1);
        pied();
        gotoxy(71, 22);
        printf("\e[1;93mCODAGE ET DECODAGE");
        printf("\e[0m");
        printf("\n\t\t\t\t\t\t       ___________________________________________________");

        y = 25 ;
        selectionner(menu_list,3, 55, &y,0);                    // menu de selection, (y) etant le choix effectué

        switch (y) {
            case 0:                                             // Coder le fichier courant
                if (ouvert) {
                    clrscr();
                    FERMER(Fich);
                    OUVRIR(Fich,Fich->nomFich,'A');
                    coder_input(Fich);
                }
                else { // !ouvert
                    inErrAnimate("\e[91mERREUR: AUCUN FICHIER N'EST OUVERT!\e[0m", 63, 35);
                    sleep(1);
                    gotoxy(63, 35); clrline2();
                }
                break;
            case 1:                                             // Decoder un fichier au choix
                clrscr();
                decoder_input();
                break;
            case 2:
                retour = true;
                break;
        }

    } while (!retour);
}

// Affichage de la page "apropos"
int apropos(){

    char command;
    clrscr();
    gotoxy(0,0);
    entete();
    gotoxy(0,39);
    pied();
    gotoxy(40,4);

    strprintAnimate("\e[38;5;147mBIENVENUE DANS L'APPLICATION DE GESTION ENSEIGNANT MESRS,",10);
    sleep(1);

    strprintAnimate(" (OU \"GEM\" EN UN MOT)\e[0m",10);

    fade_in("Cette application permet de manipuler les fichiers en memoire secondaire (de type LnOF)",30,20,7);
    fade_in("Le fichier sauvgarde des informations sur les enseignants inscrit en MESRS (chaque enseignant pour un enregistrement)",30,20,8);
    fade_in("Elle permet aussi d'effectuer les operations suivants :",30,20,9);
    fade_in(" - Creer, ouvrir et fermer un fichier.",10,20,11);
    fade_in(" - Affichage du contenu de tout le fichier dans une representation graphique elegante.",10,20,12);
    fade_in(" - Codage et decodage du fichier.",10,20,13);
    fade_in(" - Avoir une liste d'enseignant selon une requete personalisee.",10,20,14);
    fade_in(" - Modification et suppression des enseignants du fichier.",10,20,15);
    fade_in(" - ... etc",10,20,16);
    fade_in("Cet application a etait un fruit du travail serieux des deux etudiants 2CP : (en decembre 2022)",10,33,22);
    fade_in("\e[38;5;229mMEDJADJ ABDERAOUF : lm_medjadj@esi.dz               ABOUD IBRAHIM : li_aboud@esi.dz\e[0m",10,39,24);
    fade_in("On espere que vous passiez une bonne experience en decouvrant notre application !",10,40,30);

    gotoxy(71,34); printf("\e[38;5;159m[ ECHAP ] : sortir\e[0m");

    command=getch();
    while(command!=27){
        command=getch();
    }

    return 0;
}
