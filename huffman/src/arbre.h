#ifndef ARBRE_H_
#define ARBRE_H_

/****************************************
 * fonction : allouer
 * description : Alloue l'emplacement nécessaire pour un nouveau noeud d'arbre
 * entree : aucune
 * sortie : (noeud*) pointeur vers le nouveau noeud alloué
 ****************************************/
noeud * allouer();

/****************************************
 * fonction : arbre_vide
 * description : Retourne un pointeur NULL pour indiquer un arbre vide
 * entree : aucune
 * sortie : (noeud*) NULL, représentant un arbre vide
 ****************************************/
noeud * arbre_vide();

/****************************************
 * fonction : est_vide
 * description : Teste si l'arbre est vide
 * entree : pointeur vers noeud a
 * sortie : (int) 1 si vide, 0 sinon
 ****************************************/
int est_vide(noeud * a);

/****************************************
 * fonction : est_feuille
 * description : Teste si le noeud est une feuille
 * entree : pointeur vers noeud a
 * sortie : (int) 1 si c'est une feuille, 0 sinon
 ****************************************/
int est_feuille(noeud * a);

/****************************************
 * fonction : arbre
 * description : Initialise le tableau d'arbres avec des noeuds pour chaque caractère ayant une occurrence non nulle
 * entree : tableau de pointeurs vers noeud a, tableau d'entiers tab représentant les occurrences des caractères
 * sortie : aucune (void)
 ****************************************/
void arbre(noeud **a, int *tab);

/****************************************
 * fonction : creer_feuille
 * description : Crée une feuille selon l'index donné et initialise la structure d'arbre
 * entree : tableau d'entiers tab, entier index
 * sortie : (noeud*) pointeur vers la feuille créée
 ****************************************/
noeud * creer_feuille(int *tab, int index);

/****************************************
 * fonction : affichage_car
 * description : Affiche le caractère passé en paramètre et son nombre d'occurrences
 * entree : tableau de pointeurs vers noeud a
 * sortie : aucune (void)
 ****************************************/
void affichage_car(noeud **a);

/****************************************
 * fonction : afficher_arbre
 * description : Affiche l'arbre de manière récursive
 * entree : pointeur vers noeud racine
 * sortie : aucune (void)
 ****************************************/
void afficher_arbre(noeud * racine);

/****************************************
 * fonction : creer_noeud
 * description : Recherche les noeuds avec les plus petites occurrences pour créer un nouveau noeud 
 *               qui les combine, puis le sauvegarde dans le même tableau utilisé pour l'arbre de Huffman
 * entree : tableau de pointeurs vers noeud tab, entier taille
 * sortie : aucune (void)
 ****************************************/
void creer_noeud(noeud **tab, int taille);

/****************************************
 * fonction : plus_petit_noeud
 * description : Recherche et identifie les indices des deux plus petits noeuds en termes d'occurrence 
 *               dans un tableau de noeuds
 * entree : tableau de pointeurs de noeuds tab, pointeurs entiers ind1 et ind2 pour stocker les indices
 * sortie : aucune (void), modifie les valeurs aux adresses pointées par ind1 et ind2
 ****************************************/
void plus_petit_noeud(noeud **tab, int *ind1, int *ind2);

#endif
