#ifndef TABLEAU_H_
#define TABLEAU_H_

/****************************************
 * fonction : init_tab
 * description : Initialise un tableau d'entiers à 0
 * entree : pointeur vers un tableau d'entiers tab
 * sortie : aucune (void), modifie le tableau pour mettre toutes ses valeurs à 0
 ****************************************/
void init_tab(int *tab);

/****************************************
 * fonction : occurence
 * description : Compte le nombre d'occurrences de chaque caractère lu dans un fichier 
 *               et les insère dans le tableau fourni
 * entree : pointeur vers un fichier fic, tableau d'entiers tab de taille 256
 * sortie : aucune (void), modifie le tableau pour refléter les occurrences des caractères
 ****************************************/
void occurence(FILE * fic, int tab[256]);


/****************************************
 * fonction : affichage
 * description : Affiche les caractères qui apparaissent au moins une fois dans le tableau 
 *               avec leur nombre d'occurrences
 * entree : pointeur vers un tableau d'entiers tab
 * sortie : aucune (void), effectue des affichages sur la sortie standard
 ****************************************/
void affichage(int *tab);



#endif
