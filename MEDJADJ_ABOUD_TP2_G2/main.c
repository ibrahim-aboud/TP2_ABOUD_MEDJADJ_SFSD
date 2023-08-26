#include "LnOF.h"
#include "display.h"
#include "menus.h"

/**=={ INITIALISATION DES STRUCTURES DE CORRESPONDENCE/RÉFERENCE }==**/

char *grp_sanguin[8]={"O+","A+","B+","O-","A-","AB+","B-","AB-"};
char *grade[6]={"Professeur(e)","Maitre de conferences Rang A", "Maitre de conferences Rang B", "Maitre assistant(e) Rang A", "Maitre assistant(e) Rang B", "Assistant(e)"};
char *diplome[6]={ "Doctorat d'Etat", "Doctorat en sciences", "Doctorat D-LMD", "PhD", "Habilitation Universitaire", "Magistere"};
char *specialite[MAX_INDEX_SP]={ "Informatique", "Architecture",  "Medecine", "Physique", "Mathematiques", "Chimie", "Sciences Humaines", "Electronique", "Economie", "Droit"};
char *sexe[2]={"Masculin", "Feminin"};

/**======{ PROGRAMME PRINCIPAL }======**/
int main() {

    srand(time(NULL));  // necessaire pour une bonne aleatoirisation
    init_console();
    intro();
    loading_page();
    ouvert = false;     // indique si le fichier à été déja ouvert ou pas
    menu(1);

    return 0;
}
/**______ABOUD_MEDJADJ_2022_2023______**/
