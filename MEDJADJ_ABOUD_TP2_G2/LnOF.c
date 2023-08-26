#include "LnOF.h"
#include "display.h"




/**==={ MACHINE ABSTRAITE }===**/

// OUVRIR(F, nomfichier, mode) : Ouvre ou cr�e un fichier
void OUVRIR(TypeFich* F, char* nomFich, char mode) {
    time_t t;
    if (mode == 'A') {                                // mode ancien: on ouvre le fichier et on charge l'entete dans la MC (dans la structure TypeEnreg)
        F->fptr = fopen(nomFich, "rb+");
        if (F->fptr == NULL) printf("ERREUR: fichier non-existant!");
        else {
            rewind(F->fptr);
            fread(&(F->entete), sizeof(TypeEntete), 1, F->fptr);
        }
    }
    else if (mode == 'N') {                           // mode nouveau: on ouvre un nouveau fichier et on initialise son entete
        F->fptr = fopen(nomFich, "wb+");
        if (F->fptr == NULL) printf("ERREUR: espace insuffisant pour creer un nouveau fichier!");
        else {
            F->entete.nb_enr_ins = 0;
            F->entete.tete = -1;                      // -1 represente le NIL
            F->entete.queue = -1;
            F->entete.liste_vide = -1;
            t = time(NULL);
            F->entete.tm = *localtime(&t);
            maj_taille_fich(F);
            fwrite(&(F->entete), sizeof(TypeEntete), 1, F->fptr);
        }
    }
    else {
        F->fptr = NULL;
        printf("ERREUR: verifier le mode d'ouverture!");
    }
    strcpy(F->nomFich, nomFich);                     // sauvegarde du nom de fichier
}

// FERMER(F) : Ferme le fichier. Les caract�ristiques seront sauvegarder en MS
void FERMER(TypeFich* F) {
    rewind(F->fptr);
    fwrite(&(F->entete), sizeof(TypeEntete), 1, F->fptr);
    fclose(F->fptr);
}

// LireDir(F, i, buf) : Lecture du bloc num�ro i de F dans la variable buf
void LireDir(TypeFich F, int i, TypeBloc* buf) {
    fseek(F.fptr, sizeof(TypeEntete)+(i-1)*sizeof(TypeBloc), SEEK_SET);
    fread(buf, sizeof(TypeBloc), 1, F.fptr);
    nombre_lect++;
}

// EcrireDir(F, i, buf) : Ecriture de buf dans le bloc num�ro i de F
void EcrireDir(TypeFich* F, int i, TypeBloc buf) {
    fseek(F->fptr, sizeof(TypeEntete)+(i-1)*sizeof(TypeBloc), SEEK_SET);
    fwrite(&buf, sizeof(TypeBloc), 1, F->fptr);
    nombre_ecr++;
}

// ENTETE(F, i) : Retourne la valeur de la caract�ristique num�ro i
int ENTETE(TypeFich F, int i_caract) {

    switch(i_caract) {
        case 1:
            return F.entete.tete;
            break;
        case 2:
            return F.entete.queue;
            break;
        case 3:
            return F.entete.nb_enr_ins;
            break;
        case 4:
            return F.entete.liste_vide;
            break;
        case 5:
            return F.entete.taille;
            break;
        default:
            printf("ERREUR: caracteristique non-existante"); // cas d'erreur
            return -2;
            break;
    }
}

// AFF_ENTETE(F, i, v) : Affecte v � la caract�ristique num�ro i
void AFF_ENTETE(TypeFich* F, int i_caract, int val) {

    switch(i_caract) {
        case 1:
            F->entete.tete = val;
            break;
        case 2:
            F->entete.queue = val;
            break;
        case 3:
            F->entete.nb_enr_ins = val;
            break;
        case 4:
            F->entete.liste_vide = val;
            break;
        case 5:
            F->entete.taille = val;
            break;
        default:
            printf("ERREUR: caracteristique non-existante"); // cas d'erreur
            break;
    }
}

// ALLOC_BLOC(F) : Retourne le num�ro d�un nouveau bloc allou� � F  (cas d'une liste de blocs)
int ALLOC_BLOC(TypeFich* F) {
    TypeBloc buf;
    int n, q;                                             // q : pour ancienne queue,  n : nouveau bloc allou�

    q = ENTETE(*F, 2);                                    // recuperer la queue (pour effectuer les chainages necessaires)
    if (F->entete.liste_vide > 0) {                       // allocation d'un bloc de la liste_vide
        n = F->entete.liste_vide;
        LireDir(*F, n, &buf);
        F->entete.liste_vide = buf.suiv;
    }
    else {                                                // allocation d'un bloc a la fin si la liste_vide est vide
        if (ENTETE(*F, 1) != -1) n = ENTETE(*F, 2)+1;
        else {                                            // queue = tete = -1
            AFF_ENTETE(F, 1, 1);
            n = 1;
            q = 1;
        }
    }
    if (n != 1) {
        LireDir(*F, q, &buf);
        buf.suiv = n;
        EcrireDir(F, q, buf);
    }
    buf.nb = 0;
    buf.suiv = -1;
    EcrireDir(F, n, buf);
    AFF_ENTETE(F, 2, n);
    return n;
}

/**==================================================================**/

// Fonction qui génère un matricule entre 111111 et 999999
int genMatricule() {
    //srand(time(NULL));
    return ((rand()*rand())%MAX_INDEX_MAT)+111111;
}

// Fonction qui génère un nom/prénom
void genPre_Nom(char pre_nom[MAX_NOM_PRENOM]) {
    //srand(time(NULL));
    int taille = (rand()%(MAX_NOM_PRENOM-4+1))+4;
    //printf("\ntest: %d", taille);
    char* nom = malloc((taille+1)*sizeof(char));
    nom[0] = (rand()%26)+65;
    for (int i = 1; i < taille; i++) {
        nom[i] = (rand()%26)+97;
    }
    nom[taille] = '\0';
    strcpy(pre_nom, nom);
    free(nom);
}

// Fonction qui génère une date valide
int genDate(int min, int max) {
    //srand(time(NULL));
    int y, m, d;

    y = (rand()%(max-min+1))+min;
    m = (rand()%12)+1;

    if ((y%4 == 0) && (m == 2)) {                                           // ann�e bissextile + fevrier
        d = (rand()%29)+1;
    }
    else if (m == 2) {                                                      // ann�e non-bissextile + fevrier
        d = (rand()%28)+1;
    }
    else if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12)) {
        d = (rand()%31)+1;
    }
    else if ((m == 4) || (m == 6) || (m == 9) || (m == 11)) {
        d = (rand()%30)+1;
    }

    // construction du nombre AAAAMMJJ
    return (y*10000+m*100+d);
}

// Fonction qui génère une enregistrement aléatoirement
void genEnreg(TypeEnreg* e) {
    //srand(time(NULL));
    e->matricule = genMatricule();
    genPre_Nom(e->nom);
    genPre_Nom(e->prenom);
    e->date_Naissance = genDate(1953, 1998);
    e->wilaya_Naissance = (rand()%58);              // entre 0 et 57 pour acceder directement au tableau des wilayas
    e->sexe = rand()%2;                             // 0: masculin, 1: feminin
    e->groupe_sanguin = rand()%8;                   // entre 0 et 7 pour acceder directement au tableau des grp_sanguin
    e->date_recrutement = genDate(1985, 2022);
    e->grade = rand()%6;
    e->specialite = rand()%10;
    e->dernier_diplome = rand()%6;
    e->etablissement_univ = rand()%112;
}




/**==={ FONCTIONS_LnOF }===**/


// Insertion d'un enregistrement
int ins_enreg(TypeFich* F, TypeEnreg data) {
    TypeBloc buf;
    int j, k = ENTETE(*F, 2);

    if (ind_mat[data.matricule-111111].exist == 0) {

        // insertion dans L�F
        if (k > 0) {
            LireDir(*F, k, &buf);
            j = buf.nb+1;                                   // pour voir si le prochain enreg a inserer va poser un probleme
            if (j > MAX_TAILLE_BLOC) {
                j = 1;
                k = ALLOC_BLOC(F);
            }
            buf.T[j-1] = data;
            buf.nb = j;
            EcrireDir(F, k, buf);
        }
        else {                                              // k == -1  :  Fichier vide
            j = 1;
            buf.T[j-1] = data;
            buf.nb = j;
            buf.suiv = -1;
            k = ALLOC_BLOC(F);
            EcrireDir(F, k, buf);
        }
        AFF_ENTETE(F, 3, ENTETE(*F, 3)+1);

        // insertion dans les indexes
        insIndMat(data.matricule,k,j-1);
        insIndSp(data.matricule,data.specialite);
        insIndEtReg(data.matricule,data.etablissement_univ);
        insIndAnc(data.date_recrutement, data.matricule);
        maj_taille_fich(F);
        return 0;
    }
    else return 1;
}

// Suppression d'un enregistrement recherché par son matricule, dans la structure LnOF
void suppr_LnOF(TypeFich* F, int matricule) {
    int i, j, q = ENTETE(*F, 2);
    TypeBloc buf, bufq;

    if (ind_mat[matricule-111111].exist) {
        i = ind_mat[matricule-111111].i;
        j = ind_mat[matricule-111111].j;
        LireDir(*F, i, &buf);
        if (q == i) {
            buf.T[j] = buf.T[buf.nb-1];
            ind_mat[buf.T[buf.nb-1].matricule-111111].i = i;
            ind_mat[buf.T[buf.nb-1].matricule-111111].j = j;
            buf.nb--;
            if (buf.nb == 0) {
                q--;
                if (q == 0) {
                    AFF_ENTETE(F, 1, -1);
                    q = -1;
                }
                AFF_ENTETE(F, 2, q);
                if (q != -1) {
                    LireDir(*F, q, &bufq);
                    bufq.suiv = -1;
                    EcrireDir(F, q, bufq);
                }
            }
            else {
                EcrireDir(F, i, buf);
            }
        }
        else { // q != i
            LireDir(*F, q, &bufq);
            buf.T[j] = bufq.T[bufq.nb-1];
            ind_mat[bufq.T[bufq.nb-1].matricule-111111].i = i;
            ind_mat[bufq.T[bufq.nb-1].matricule-111111].j = j;
            bufq.nb--;
            if (bufq.nb == 0) {
                q--;
                AFF_ENTETE(F, 2, q);
                LireDir(*F, q, &bufq);
                bufq.suiv = -1;
                EcrireDir(F, q, bufq);
            }
            else {
                EcrireDir(F, q, bufq);
            }
            EcrireDir(F, i, buf);
        }
    }
}


// Chargement initial de la structure LnOF
void chargement_initial(TypeFich* F, int n) {
    TypeEnreg data;
    int j=0;    // cpt d'enregistrements inser�s dans le dernier bloc a inserer
    int k=0;    // cpt de blocs inser�s
    int cpt=0;  // cpt d'enregistrements totales inserees
    TypeBloc buf;

    init_ind_anc();
    init_ind_et_reg();
    init_ind_mat();
    init_ind_sp();

    gotoxy(0, 2);
    // insertion dans LoF
    for (int i=0; i<n; i++) {
        genEnreg(&data);
        if (ind_mat[data.matricule-111111].exist == 0) {
            cpt++;
            j++;

            if (j > MAX_TAILLE_BLOC) {   // j = MAX  =>  buf plein
                buf.nb = j-1;
                buf.suiv = -1;
                k = ALLOC_BLOC(F);
                EcrireDir(F, k, buf);
                j = 1;

            }
            buf.T[j-1] = data;

            // insertion dans les indexes
            insIndMat(data.matricule,k+1,j-1);
            insIndSp(data.matricule,data.specialite);
            insIndEtReg(data.matricule,data.etablissement_univ);
            insIndAnc(data.date_recrutement, data.matricule);
        }
    }
    if (j) {
        k = ALLOC_BLOC(F);
        buf.nb = j;
        buf.suiv = -1;
        EcrireDir(F, k, buf);
        gotoxy(0, 3);
    }
    AFF_ENTETE(F, 2, k);
    AFF_ENTETE(F, 3, cpt);
    maj_taille_fich(F);
}


// Fonction de modification d'un enregistrement selon l'etablissement
void modif_et_reg(TypeFich* F,int matricule,int nouv_etab){
    int i = ind_mat[matricule-111111].i;                        // recherche instantanee
    int j = ind_mat[matricule-111111].j;
    Tenr_mat *ptr_parcour;
    Tenr_mat *ptr_prec;
    bool continu=false;
    bool trouv=false;
    int ancient_etab;
    TypeEnreg enreg_courant;                                    // enregistrement que l'on veut rechercher
    TypeBloc buffer;

    if (ind_mat[matricule-111111].exist){
        LireDir(*F,i,&buffer);                                      // recuperation du bloc qui contien l'enregistrement en question
        enreg_courant= buffer.T[j];                                 // recuperation de l'enregistement
        ancient_etab= enreg_courant.etablissement_univ;             // recuperation de l'ancient etablissement pour des modification en memoire centrale
        enreg_courant.etablissement_univ=nouv_etab;
        buffer.T[j]=enreg_courant;                                  // mise a jour de l'enregistement
        EcrireDir(F,i,buffer);                                     // mise a jour du bloc dans le fichier
        ptr_parcour=ind_et_reg[ancient_etab].Tete;                  // variable de parcour de liste
        if(ptr_parcour!=NULL){
            continu= true;
            ptr_prec=NULL;
        }
        while(continu){                                         // recherche du maillon dans la liste
            if(ptr_parcour->matricule==matricule){
                continu=false;
                trouv = true;
            }
            else{
                if (ptr_parcour->suivant!=NULL){
                    ptr_prec=ptr_parcour;
                    ptr_parcour=ptr_parcour->suivant;
                }
                else{
                    continu=false;
                }
            }
        }
        if(trouv){
            if(ptr_prec==NULL){                                 // le maillon a supprimer est le premier
                ind_et_reg[ancient_etab].Tete=ptr_parcour->suivant;
            }
            else{
                ptr_prec->suivant=ptr_parcour->suivant;
            }
            free(ptr_prec);
            free(ptr_parcour);
            insIndEtReg(matricule,nouv_etab);
        }

    }
    else{
        printf("\nERREUR: enregistrement non-existant!\n");
    }
}

// Fonction de suppression d'un enregistrement, de la structure LnOF + les indexes
void suppr_enr(TypeFich* F, int matricule) {
    int i, j;
    TypeBloc buf;
    i = ind_mat[matricule-111111].i;
    j = ind_mat[matricule-111111].j;
    LireDir(*F, i, &buf);

    suppr_LnOF(F, matricule);



    ind_mat[matricule-111111].exist = 0;

    ptr_enr_mat tete = ind_sp[buf.T[j].specialite];
    supprListeMat(&tete, matricule);
    ind_sp[buf.T[j].specialite] = tete;

    tete = ind_et_reg[buf.T[j].etablissement_univ].Tete;
    supprListeMat(&tete, matricule);
    ind_et_reg[buf.T[j].etablissement_univ].Tete = tete;

    bool trouv;
    int k;
    rechDichoIncAnc(buf.T[j].date_recrutement, &trouv, &k);
    tete = ind_anc[k].Tete;
    supprListeMat(&tete, matricule);
    ind_anc[k].Tete = tete;
    if (tete == NULL) {
        // decalages
        for (int l = k; l < nbIndAnc-1; l++) {
            ind_anc[l] = ind_anc[l+1];
        }
        nbIndAnc--;
    }
    AFF_ENTETE(F, 3, ENTETE(*F, 3)-1);
}

// Fonction qui charge les indexes matricules, specialités, établissements/régions à partir de la structure LnOF
void Index_charg(TypeFich *F) {
    init_ind_et_reg();
    init_ind_mat();
    init_ind_sp();
    int nb_bloc = ENTETE(*F,2);                                 // recuperation du nombre de bloc
    TypeEnreg Enreg;
    TypeBloc buffer;
    int i = 1;
    int j = 0;
    while (i<=nb_bloc){
        LireDir(*F,i,&buffer);
        while (j< buffer.nb){
            Enreg=buffer.T[j];
            insIndEtReg(Enreg.matricule,Enreg.etablissement_univ);
            insIndMat(Enreg.matricule,i,j);
            insIndSp(Enreg.matricule,Enreg.specialite);
            j++;
        }
        j=0;
        i++;
    }
}

// Fonction qui supprime tous les enregistrements relatifs à une specialité
void suppr_all_spec(TypeFich *F,int spec){


    Tenr_mat *ptr_maillon=ind_sp[spec];

    while(ptr_maillon!= NULL){

        suppr_enr(F,ptr_maillon->matricule);
        ptr_maillon=ind_sp[spec];

    }
}

// Fonction qui consulte tous les enseignants d'une region donnée
void affiche_ens_region(const char region,TypeFich *F) {
    char command;
    int* tab_mat_trouvee;
    tab_mat_trouvee=malloc(888888*sizeof(int));
    int size_tab=0;
    ptr_enr_mat p;
    for (int i = 0; i < 112; i++) {
        if (ind_et_reg[i].Region == region) {
            p = ind_et_reg[i].Tete;
            while (p!=NULL) {
                tab_mat_trouvee[size_tab]=p->matricule;         // on affiche le matricule (le 'et' logique est validee)
                size_tab++;
                p = p->suivant;
            }
        }
    }
    if(size_tab !=0){
        affiche_seq_mat(tab_mat_trouvee,size_tab,F);
    }
    else{
        clrscr();
        gotoxy(0,0);
        entete();
        gotoxy(0,39);
        pied();
        gotoxy(72,20);
        printf("Pas de correspondance");
        gotoxy(30,34);
        printf("\e[38;5;159m                                           [ ECHAP ] : sortir\e[0m");
        while(1){
            command=getch();
            if (command==27){
                break;
            }
        }
    }
    free(tab_mat_trouvee);
}

// Fonction qui affiche les enseignants apparatenants à un etablissement donné ayants une ancienneté entre deux bornes (sup et inf)
int affiche_ens_etab_anc(int etab, int date_min, int date_max,TypeFich *F){
    char command;
    int* tab_mat_trouvee;
    tab_mat_trouvee=malloc(888888*sizeof(int));
    int size_tab=0;
    int bi_precis;
    int bs_precis;
    bool trouv;
    ptr_enr_mat p;
    if(date_min<=date_max){
        init_bit_map();                                             // on vas utiliser un bit map pour effectuer un
                                                                    // "ET" logique entre (dans etab) et (a une ancientee)

        p=ind_et_reg[etab].Tete;
        while(p!=NULL){                                             // lecture de tout les matricules tq leurs proprietaires travail dans l'etablissement (etab)
            tableau_bit_map[(p->matricule)-111111]=true;            // mettre a vrais tous les cases correspondant
            p=p->suivant;

        }

        rechDichoIncAnc(date_min,&trouv,&bi_precis);
        rechDichoIncAnc(date_max,&trouv,&bs_precis);

        if(!trouv && bs_precis!=0){
            bs_precis=bs_precis-1;
        }
        for(int i = bi_precis;i<=bs_precis;i++){
            p=ind_anc[i].Tete;
            while(p!=NULL){
                if(tableau_bit_map[(p->matricule)-111111]) {        // si la case pointee par le matricule est vraie (donc elle a etait mis a vraie dans la loop precedente)
                    tab_mat_trouvee[size_tab]=p->matricule;         // on affiche le matricule (le 'et' logique est validee)
                    size_tab++;

                }
                p=p->suivant;
            }


        }

    free(tableau_bit_map);
    if(size_tab !=0){
        affiche_seq_mat(tab_mat_trouvee,size_tab,F);
    }
    else{
        clrscr();
        gotoxy(0,0);
        entete();
        gotoxy(0,39);
        pied();
        gotoxy(72,20);
        printf("Pas de correspondance");
        gotoxy(30,34);
        printf("\e[38;5;159m                                           [ ECHAP ] : sortir\e[0m");
        while(1){
            command=getch();
            if (command==27){
                break;
            }
        }
    }




    free(tab_mat_trouvee);
    return 0;
    }
    else {
        return 1;
    }

}

// Fonction qui effectue le codage d'un fichier donné
int coder(FILE* F_origin,char* nom_fich_res,char* cle,int taille_cle){
    // pour f_ptr, le fichier correspondant (originale) dois etre deja ouvert avant l'appelle de cette fct
    FILE *F_chiffree;
    F_chiffree=fopen(nom_fich_res,"wb");

    fseek(F_origin,0,SEEK_END);
    long int cpt = ftell(F_origin);
    fseek(F_origin,0,SEEK_SET);
    char *buffer=malloc(sizeof(char));

    if (F_chiffree!=NULL){
        fseek(F_origin,0,SEEK_SET);
        fseek(F_chiffree,0,SEEK_SET);

        for(int i =0; i<cpt;i++){
            fread(buffer,sizeof(char),1,F_origin);
            *buffer=*buffer+cle[i%taille_cle];
            fwrite(buffer,sizeof(char),1,F_chiffree);
        }
        fclose(F_chiffree);
        free(buffer);
        return 0;
    }
    else {
        free(buffer);
        return 1;
    }
}

// Fonction qui effectue le décodage d'un fichier chiffré donné
int decoder(char* nom_fich_coded,char*nom_fich_decoded,char* cle,int taille_cle){
    // pour f_ptr, le fichier correspondant (originale) dois etre deja ouvert avant l'appelle de cette fct
    FILE* F_coded=fopen(nom_fich_coded,"rb");
    FILE* F_decoded=fopen(nom_fich_decoded,"wb");
    long int cpt;
    char *buffer=malloc(sizeof(char));
    if (F_coded!=NULL){
        fseek(F_coded,0,SEEK_END);
        cpt=ftell(F_coded);
        fseek(F_coded,0,SEEK_SET);
    }

    if (F_decoded!=NULL){
        fseek(F_decoded,0,SEEK_SET);
        fseek(F_coded,0,SEEK_SET);

        for(int i =0; i<cpt;i++){
            fread(buffer,sizeof(char),1,F_coded);
            *buffer=*buffer-cle[i%taille_cle];
            fwrite(buffer,sizeof(char),1,F_decoded);
        }
        fclose(F_decoded);
        free(buffer);
        return 0;
    }
    else {
        free(buffer);
        return 1;
    }
}
