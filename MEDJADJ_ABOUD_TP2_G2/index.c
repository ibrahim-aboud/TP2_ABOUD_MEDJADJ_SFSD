#include "LnOF.h"

/**========{ FONCTIONS DE MANIPULATION DES TABLES INDEX }==========**/

// Fonction d'initialisation de l'index des matricules (ind_mat[])
int init_ind_mat() {
    for(int i=0;i<MAX_INDEX_MAT;i++) {
        ind_mat[i].exist=false;
    }
    return 0;

}

// Fonction qui initialise l'index des specialités (ind_sp[])
int init_ind_sp(){
    for(int i=0;i<MAX_INDEX_SP;i++) {
        ind_sp[i]=NULL;
    }
    return 0;
}

// Fonction qui initialise l'index des établissements/régions (ind_et_reg[])
int init_ind_et_reg() {
    for(int i=0;i<MAX_INDEX_UNIV;i++){
        ind_et_reg[i].Tete=NULL;
    }

    for(int i=0;i<17;i++){
        ind_et_reg[i].Region='C';
    }
    for(int i=17;i<39;i++){
        ind_et_reg[i].Region='E';
    }
    for(int i=39;i<54;i++){
        ind_et_reg[i].Region='O';
    }
    for(int i=54;i<75;i++){
        ind_et_reg[i].Region='C';
    }
    for(int i=75;i<83;i++){
        ind_et_reg[i].Region='E';
    }
    for(int i=83;i<91;i++){
        ind_et_reg[i].Region='O';
    }
    for(int i=91;i<95;i++){
        ind_et_reg[i].Region='C';
    }
    for(int i=95;i<100;i++){
        ind_et_reg[i].Region='E';
    }
    for(int i=100;i<103;i++){
        ind_et_reg[i].Region='O';
    }
    for(int i=103;i<106;i++){
        ind_et_reg[i].Region='C';
    }
    for(int i=106;i<108;i++){
        ind_et_reg[i].Region='E';
    }
    for(int i=108;i<112;i++){
        ind_et_reg[i].Region='O';
    }
    return 0;
}

// Fonction qui initialise l'index d'ancienneté (ind_anc[])
int init_ind_anc() {
    nbIndAnc = 0;
    for(int i=0;i<MAX_INDEX_MAT;i++) {
        ind_anc[i].Tete=NULL;
    }
    return 0;
}

// Fonction qui effectue la recherche dichotomique dans l'index ancienneté
void rechDichoIncAnc(int dateRecrut, bool* trouv, int* k) {
    int inf = 0, sup = nbIndAnc-1, c;
    *trouv = false;

    while (inf <= sup && !(*trouv)) {
        c = (inf+sup)/2;
        if (ind_anc[c].Date_Recrut > dateRecrut) sup = c-1;
        else if (ind_anc[c].Date_Recrut < dateRecrut) inf = c+1;
        else {
            *trouv = true;
            *k = c;
        }
    }
    if (!(*trouv)) {  // inf > sup
        *k = inf;
    }
}


/**LA MACHINE ABSTRAITE POUR LE FICHIER MS (INDEX ANCIENTEE)**/


// OUVRIR(F, nomfichier, mode) :  Ouvre ou crée un fichier
void  Anc_OUVRIR(Fich_anc* F, char* nomFichier, char mode) {

    if (mode == 'N') {
        F->f = fopen(nomFichier, "wb+");
        F->entete_anc.Der_bloc=0;
        F->entete_anc.Insertion=0;
        F->entete_anc.Suppression=0;
        fwrite(&(F->entete_anc), sizeof(Bloc_entete_anc), 1, F->f);
    }
    else if (mode == 'A') {
        F->f = fopen(nomFichier, "rb+");
        rewind(F->f);
        fread(&(F->entete_anc), sizeof(Bloc_entete_anc), 1, F->f);
    }
    else F->f= NULL;
}

// FERMER(F) :  Ferme le fichier. Les caract�ristiques seront sauvegarder en MS
void Anc_FERMER(Fich_anc* F) {
    rewind(F->f);
    fwrite(&(F->entete_anc), sizeof(Bloc_entete_anc), 1, F->f);
    fclose(F->f);
}

// ENTETE(F, i) :  Retourne la valeur de la caractéristique numéro i
int Anc_ENTETE(Fich_anc F, int i) {
    if (i == 1) {
        return F.entete_anc.Der_bloc;
    }
    else if (i == 2) {
        return F.entete_anc.Insertion;
    }
    else if (i == 3) {
        return F.entete_anc.Suppression;
    }
    else {
        printf("ERREUR: caracteristique non-existante"); // cas d'erreur
        return -1;
    }
}

// AFF_ENTETE(F, i, v) :  Affecte v à la caractéristique numéro i
void Anc_AFF_ENTETE(Fich_anc* F, int i, int v) {
    if (i == 1) {
        F->entete_anc.Der_bloc = v;
    }
    else if (i == 2) {
        F->entete_anc.Insertion= v;
    }
    else if (i == 3) {
        F->entete_anc.Suppression = v;
    }
    else {
        printf("ERREUR: caracteristique non-existante"); // cas d'erreur
    }
}

// LireDir(F, i, buf) :  Lecture du bloc numéro i de F dans la variable buf
void Anc_LireDir(Fich_anc F, int bloc_i, Bloc_anc* buf) {
    fseek(F.f, sizeof(Bloc_entete_anc) + (bloc_i-1)*sizeof(Bloc_anc), SEEK_SET);
    fread(buf, sizeof(Bloc_anc), 1, F.f);
}

// EcrireDir(F, i, buf) :  Ecriture de buf dans le bloc numéro i de F
void Anc_EcrireDir(Fich_anc* F, int bloc_i, Bloc_anc buf) {
    fseek(F->f, sizeof(Bloc_entete_anc) + (bloc_i-1)*sizeof(Bloc_anc), SEEK_SET);
    fwrite(&buf, sizeof(Bloc_anc), 1, F->f);
}


// Sauvegarde du tableau d'index (ancienneté) de la MC vers la MS
void Anc_Sauv(Fich_anc F,char nom_fich[30]){
    Anc_OUVRIR(&F,nom_fich,'N');
    Bloc_anc buffer;
    bool continu = true;
    bool dans_liste= false;
    Tenr_mat* maillon_courant;
    int i=0;                                                    // nombre d'enregistrement inseree dans un bloc
    int j=1;                                                    // nombre de bloc dans le fichier
    buffer.Nb=0;                                                // initialisation

    int nb_insertion=0;
    if(nbIndAnc!=0){
         do{
        buffer.Tab[buffer.Nb].dt_de_recrut=ind_anc[i].Date_Recrut; // insertion de la premier valeur, date de recrutement
        if (!dans_liste){
            maillon_courant=ind_anc[i].Tete;                       // avant d'inserer le matricule, il faut savoir si on est deja dans une liste
        }
        buffer.Tab[buffer.Nb].matricule=maillon_courant->matricule;// on insere le matricule
        buffer.Nb++;                                               // on increment le nombre denregistrement inseree
        if (maillon_courant->suivant!=NULL){                    // si la liste continue toujours, on ne touche pas a i
            dans_liste=true;
            maillon_courant=maillon_courant->suivant;
        }
        else{
            dans_liste=false ;                                      // sinon, on avance vers la nouvelle case
            i++;
        }
        if (i==nbIndAnc){                                          // si on a parcouru tous les enregistrement de l'index
            continu=false;
        }
        if(buffer.Nb==MAX_TAILLE_BLOC){                            // si le buffer est saturee, on l'ecrit dans MS
            Anc_EcrireDir(&F,j,buffer);
            nb_insertion=nb_insertion+buffer.Nb;
            j++;
            buffer.Nb=0;                                           // on revide le buffer
        }

        }while(continu);

    }

    if(buffer.Nb!=0){                                              // cas du dernier bloc non ecrit + modification de l'entete
        Anc_EcrireDir(&F,j,buffer);
        nb_insertion=nb_insertion+buffer.Nb;
        Anc_AFF_ENTETE(&F,1,j);
    }
    else{                                                          // modification de l'entete
        Anc_AFF_ENTETE(&F,1,j-1);
    }
    Anc_AFF_ENTETE(&F,2,nb_insertion);
    Anc_FERMER(&F);

}

// Chargement du fichier d'index (ancienneté) de la MS vers la MC
void Anc_charg(Fich_anc F,char nom_fich[30]) {
    Anc_OUVRIR(&F,nom_fich,'A');
    Bloc_anc buffer;
    int Nb_bloc = Anc_ENTETE(F,1);
    int cpt_bloc=1;
    while (cpt_bloc <=Nb_bloc){
        Anc_LireDir(F,cpt_bloc,&buffer);
        int cpt_enrg=0;
        while(cpt_enrg<buffer.Nb){
            insIndAnc(buffer.Tab[cpt_enrg].dt_de_recrut,buffer.Tab[cpt_enrg].matricule);
            cpt_enrg++;
        }
        cpt_bloc++;
    }
    Anc_FERMER(&F);
}

// Fonction qui affiche le fichier d'index (ancienneté) organisé en structure TOF
void Anc_affiche_TOF(Fich_anc F,char nom_fich[30]) {
    Anc_OUVRIR(&F,nom_fich,'A');
    Bloc_anc buf;
    int cpt1 = 1; // cpt de blocs
    int cpt2;     // cpt d'enregistrements
    int cpt3;     // cpt d'enregistrements a afficher

    printf("\n============================================\n");
    printf("|        AFFICHAGE DU FICHIER 'TOF'        |\n");
    printf("============================================\n\n");
    printf("=============\n");
    printf("|  ENTETE   |\n");
    printf("============================================\n");
    printf("| Nombre de blocs inseres:             %3d |\n", Anc_ENTETE(F, 1));
    printf("| Nombre d'enregistrements inseres:    %3d |\n", Anc_ENTETE(F, 2));
    printf("| Nombre d'enregistrements supprimes:  %3d |\n", Anc_ENTETE(F, 3));
    printf("============================================\n\n");
    printf("                CLE   EFF     INFO\n");
    while (cpt1 <= Anc_ENTETE(F, 1)) {
        Anc_LireDir(F, cpt1, &buf);
        cpt2 = 0;
        cpt3 = 0;
        printf("============================================\n");
        printf(" BLOC %3d  |                               |\n", cpt1);
        printf("============                               |\n");
        while (cpt2 < buf.Nb)  {
            //if (!buf.T[cpt2].eff) {
                printf(" Enreg %d:  %d %d           |\n", cpt3+1, buf.Tab[cpt2].matricule, buf.Tab[cpt2].dt_de_recrut);
                cpt3++;
            //}
            cpt2++;
        }
        cpt1++;
    }
    printf("============================================\n");
    Anc_FERMER(&F);
}

/**MODULES D'INSERTION DANS LES INDEXES**/

// Insertion dans l'index ancienneté
void insIndAnc(int dateRecrut, int matricule) {
    bool trouv;
    int k;

    rechDichoIncAnc(dateRecrut, &trouv, &k);
    if (!trouv) { // effectuer des decalages
        nbIndAnc++;
        for (int i=nbIndAnc-1; i>k; i--) {
            ind_anc[i] = ind_anc[i-1];
        }
        ind_anc[k].Date_Recrut = dateRecrut;
        ind_anc[k].Tete = NULL;
    }
    ptr_enr_mat p = malloc(sizeof(Tenr_mat));
    p->matricule = matricule;
    p->suivant = ind_anc[k].Tete;
    ind_anc[k].Tete = p;
}

// Insertion dans l'index des matricules
void insIndMat(int matricule, int i, int j){
    ind_mat[matricule-111111].exist = true;
    ind_mat[matricule-111111].i = i;
    ind_mat[matricule-111111].j = j;
}

// Insertion dans l'index des specialités
void insIndSp(int matricule, int spec) {
    ptr_enr_mat p = malloc(sizeof(Tenr_mat));
    p->matricule = matricule;
    p->suivant = ind_sp[spec];
    ind_sp[spec] = p;
}

// Insertion dans l'index des établissements/régions
void insIndEtReg(int matricule, int etab_univ){
    ptr_enr_mat q = malloc(sizeof(Tenr_mat));
    q->matricule = matricule;
    q->suivant = ind_et_reg[etab_univ].Tete;
    ind_et_reg[etab_univ].Tete = q;
}

// Recherche sequencielle dans la liste des matricules
void rechListeMat(ptr_enr_mat tete, int matricule, bool* trouv, ptr_enr_mat* p, ptr_enr_mat* prec) {
    *p = tete;
    *prec = NULL;
    *trouv = false;

    while (!(*trouv) && (*p != NULL)) {
        if ((*p)->matricule == matricule) {
            *trouv = true;
        }
        else {
            *prec = *p;
            *p = (*p)->suivant;
        }
    }
}

// Suppression d'un maillon de la liste des matricules
void supprListeMat(ptr_enr_mat* tete, int matricule) {
    bool trouv;
    ptr_enr_mat p, q;

    rechListeMat(*tete, matricule, &trouv, &p, &q);
    if (trouv) {
        // rechainage
        if (q==NULL) { // c'est la tete
            *tete = p->suivant;
        }
        else {
            q->suivant = p->suivant;
        }
        free(p);
    }
}
