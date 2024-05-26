#include "type.h"

/****************************************
 * fonction : allouer
 * description : alloue de la mémoire pour un nouveau noeud
 * entree : pointeur vers noeud a
 * sortie : (noeud*) pointeur vers le noeud alloué ou NULL en cas d'erreur
 ****************************************/
noeud* allouer(noeud * a){
  a = (noeud*)malloc(sizeof(noeud));
    if(a == NULL){
      printf("Erreur allocation memoire\n");
      return a;
    }
  
    a->bits = 0;
    a->occ = 0;
    a->codage = 0;
    a->gauche = NULL;
    a->droit = NULL;
    return a;
}

/****************************************
 * fonction : arbre_vide
 * description : retourne un pointeur NULL pour représenter un arbre vide
 * entree : aucune
 * sortie : (noeud*) NULL
 ****************************************/
noeud * arbre_vide(){
    return NULL;
}

/****************************************
 * fonction : est_vide
 * description : teste si l'arbre passé en paramètre est vide
 * entree : pointeur vers noeud a
 * sortie : (int) 1 si vide, 0 sinon
 ****************************************/
int est_vide(noeud * a){
  if (a == arbre_vide()){
    return 1;
  }
  else{
    return 0;
  }
}

/****************************************
 * fonction : est_feuille
 * description : teste si le noeud est une feuille
 * entree : pointeur vers noeud a
 * sortie : (int) 1 si c'est une feuille, 0 sinon
 ****************************************/
int est_feuille(noeud * a){
  return ((est_vide(a->gauche)) && (est_vide(a->droit)));
}

/****************************************
 * fonction : arbre
 * description : initialise le tableau d'arbres avec des noeuds pour chaque caractère ayant une occurrence non nulle
 * entree : tableau de pointeurs vers noeud a, tableau d'entiers tab représentant les occurrences des caractères
 * sortie : aucune (void), arrêt en cas d'erreur d'allocation
 ****************************************/
void arbre(noeud **a, int *tab){
  int i;
  char c;

  for(i = 0; i < 256; i++){
    if(tab[i] > 0){
      c = i;
      a[i] = (noeud*)malloc(sizeof(noeud));
      if(a[i] == NULL){
	    printf("Erreur allocation memoire\n");
	    return;
      }
      
      a[i]->initial = c;
      a[i]->bits = 0;
      a[i]->occ = tab[i];
      a[i]->codage = 0;
      a[i]->gauche = NULL;
      a[i]->droit = NULL;
    }
  }
}

/****************************************
 * fonction : creer_feuille
 * description : crée une feuille selon l'index donné et initialise la structure d'arbre
 * entree : tableau d'entiers tab, entier index
 * sortie : (noeud*) pointeur vers la feuille créée ou NULL en cas d'erreur d'allocation
 ****************************************/
noeud * creer_feuille(int *tab, int index){
  noeud * feuille = NULL;
  if(tab[index] > 0){
    feuille = (noeud*)malloc(sizeof(noeud));
    if(feuille == NULL){
      printf("Erreur allocation de memoire\n");
      return NULL;
    }
    feuille->initial = index;
    feuille->occ = tab[index];
    feuille->gauche = NULL;
    feuille->droit = NULL;
  }
  return feuille;
}

/****************************************
 * fonction : affichage_car
 * description : affiche le caractère passé en paramètre et son nombre d'occurrences
 * entree : tableau de pointeurs vers noeud a
 * sortie : aucune (void)
 ****************************************/
void affichage_car(noeud **a){
  int i;

  for(i = 0; i < 256; i++){
    if(a[i]->occ > 0){
      if(a[i]->initial == '\n'){
	    printf("initial = \\n \n");
      }else{
	    printf("initial = %c\n", a[i]->initial);
      }
      printf("occ = %d\n", a[i]->occ );
    }
  }
}

/****************************************
 * fonction : afficher_arbre
 * description : affiche l'arbre de manière récursive
 * entree : pointeur vers noeud racine
 * sortie : aucune (void)
 ****************************************/
void afficher_arbre(noeud * racine){
    if(racine != arbre_vide()){
	    printf("\"%c\" occ = ", racine->initial);
	    printf("%d \n", racine->occ);
	    afficher_arbre(racine->gauche);
	    afficher_arbre(racine->droit);
    }
}


/****************************************************************************************************
 * fonction : plus_petit_noeud
 * description : recherche et identifie les indices des deux plus petits noeuds 
 *               en termes d'occurrence dans un tableau de noeuds.
 * entree : tableau de pointeurs de noeuds tab, entier taille du tableau,
 *          pointeurs entiers ind1 et ind2 pour stocker les indices des deux plus petits noeuds
 * sortie : aucune (void), modifie les valeurs pointées par ind1 et ind2
 ***************************************************************************************************/
void plus_petit_noeud(noeud **tab, int taille, int *ind1, int *ind2) {
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    int i;
    *ind1 = -1;
    *ind2 = -1;

    for (i = 0; i < taille; i++) {
        if (tab[i] != NULL && tab[i]->occ < min1) {
            min2 = min1;
            *ind2 = *ind1;
            min1 = tab[i]->occ;
            *ind1 = i;
        } else if (tab[i] != NULL && tab[i]->occ < min2) {
            min2 = tab[i]->occ;
            *ind2 = i;
        }
    }
}

/****************************************
 * fonction : creer_noeud
 * description : recherche les noeuds avec les plus petites occurrences pour créer un nouveau noeud 
 *               qui les combine, puis le sauvegarde dans le même tableau utilisé pour l'arbre de Huffman
 * entree : tableau de pointeurs vers noeud tab, entier taille
 * sortie : aucune (void), peut arrêter l'exécution en cas d'erreur d'allocation mémoire
 ****************************************/
void creer_noeud(noeud **tab, int taille) {
  int ind1, ind2;
  int i;
  noeud *a;
  plus_petit_noeud(tab, taille, &ind1, &ind2);

  if (ind1 == -1 || ind2 == -1) {
      printf("Nous n'avons pas deux noeuds pour continuer la création de l'arbre.\n");
      return;
  }

  a = (noeud*)malloc(sizeof(noeud));
  if (a == NULL) {
      printf("Erreur d'allocation de mémoire\n");
      exit(EXIT_FAILURE);
  }

  a->initial = '\0'; 
  a->occ = tab[ind1]->occ + tab[ind2]->occ;
  a->gauche = tab[ind1];
  a->droit = tab[ind2];

  /*Fusionner dans le tableau*/
  tab[ind1] = a; 
  tab[ind2] = NULL;

  /*Réorganiser le tableau pour remplir le vide*/
  for (i = ind2; i < taille; i++) {
      tab[i] = tab[i + 1];
  }
  tab[taille] = NULL;  
}
