#include "type.h"
#include "arbre.h"
#include "encoder.h"




/****************************************
 * fonction : lire_entete
 * description : Lit l'en-tête du fichier compressé et initialise l'alphabet avec les noeuds
 *               correspondant à chaque caractère présent dans le fichier compressé.
 * entree : pointeur vers FILE (fichier), tableau de pointeurs vers noeud (alphabet)
 * sortie : aucune (void), termine le programme en cas d'erreur de lecture ou d'allocation mémoire
 ****************************************/
void lire_entete(FILE *fichier, noeud *alphabet[]){
    int nombre_feuilles = 0;
    int occ = 0;
    int codage_bis = 0;
    char codage = 0;
    int bits = 0;
    int i,j;
    char initial;

 if(fscanf(fichier, "%d", &nombre_feuilles) != 1){
        printf("Erreur lecture nombre feuille\n");
        exit(EXIT_FAILURE);
    }
    fgetc(fichier);
    for(i=0; i<nombre_feuilles; i++){
        if(fscanf(fichier, "%c", &initial) != 1){
            printf("Erreur lecture caractere numero %d\n", i );
            exit(EXIT_FAILURE);
        }
        printf("caractere = \"%c\"\n", initial);
         if(alphabet[(int)initial] == NULL) {
            alphabet[(int)initial] = malloc(sizeof(noeud));
            if(alphabet[(int)initial] == NULL){
                printf("erreur allocation memoire \n");
                return;
            }
         }
        alphabet[(int)initial]->initial = initial;

        if(fscanf(fichier, "%d %d ", &occ, &bits) !=2){
            printf("Erreur lecture occurence/bits\n");
            exit(EXIT_FAILURE);
        }
        printf("occurence = %d\nbits = %d\n",occ, bits );
        alphabet[(int)initial]->occ = occ;
        alphabet[(int)initial]->bits = bits;
        
        
       

        printf("codage = ");
        
        codage_bis = 0;
        for(j=0; j<bits; j++){
            if(fscanf(fichier, "%c", &codage) != 1){
                printf("Erreur lecture codage\n");
                exit(EXIT_FAILURE);
            }
            codage = codage - '0';
            codage_bis = codage_bis << 1 | codage; 
            printf("%d", codage);
        }
        alphabet[(int)initial]->codage = codage_bis;
        printf("\n");
        fgetc(fichier);

    }
}

/****************************************
 * fonction : creer_dossier
 * description : creer les differents dossiers necessaires pour la decompression
 * entree : nom du chemin du fichier
 * sortie : aucune (void), creer le dossier
 ****************************************/
void creer_dossier(char *cheminFichier) {
  char *cheminDossier = NULL;
  char *dernierSlash;
  size_t longueurCheminDossier = 0;
  char commande[2048];
    /*Trouver la dernière occurrence de '/'*/
    dernierSlash = strrchr(cheminFichier, '/');
    if (dernierSlash != NULL) {
        /*Calculer la longueur du chemin du dossier*/
        longueurCheminDossier = dernierSlash - cheminFichier;
        /*Allouer de la mémoire pour le chemin du dossier*/
        cheminDossier = (char *)malloc(longueurCheminDossier + 1);
        if (cheminDossier != NULL) {
            /*Copier le chemin du dossier dans la nouvelle chaîne*/
            strncpy(cheminDossier, cheminFichier, longueurCheminDossier);
            /*Ajouter le caractère de fin de chaîne*/
            cheminDossier[longueurCheminDossier] = '\0';
            /*Créer le dossier*/
        sprintf(commande, "%s %s", "mkdir -p ", cheminDossier);
            if(system(commande) != 0){
          printf("Erreur creation dossier \n");
        }
            /*Libérer la mémoire allouée*/
            free(cheminDossier);
        }
    }
}

/* Définition de la fonction */
char* changer_nom(char* nom_fichier) {
  FILE* fic = NULL;
  char base[100];
  char ext[10];   
  char nouveau_nom[2048]; 
  char* dernier_point;
  int taille_base;
  int i;

  fic = fopen(nom_fichier, "r");
  if(fic == NULL){
    return nom_fichier;
  }
  fclose(fic);
  
  /* Initialisation des chaînes de caractères */
  strcpy(base, "");
  strcpy(ext, "");
  strcpy(nouveau_nom, "");

  /* Trouve l'index du dernier point dans le nom du fichier */
  dernier_point = strrchr(nom_fichier, '.');
  if (dernier_point != NULL) {
    taille_base = dernier_point - nom_fichier;
    /* Copie le nom de base */
    for (i = 0; i < taille_base; ++i) {
      base[i] = nom_fichier[i];
    }
    base[taille_base] = '\0';

    /* Copie l'extension */
    strcpy(ext, dernier_point);

    /* Construit le nouveau nom avec (1) */
    sprintf(nouveau_nom, "%s_1%s", base, ext);
  } else {
    /* Si pas d'extension, copie simplement le nom */
    strcpy(nouveau_nom, nom_fichier);
  }

  /* Renvoie le nouveau nom */
  return strcpy(nom_fichier, nouveau_nom);
}

/****************************************
 * fonction : lire_contenu
 * description : Lit le contenu compressé du fichier, décode chaque caractère selon l'alphabet
 *               et écrit le résultat dans le fichier de sortie. Les fichiers sont lus séquentiellement
 *               et décompressés un par un.
 * entree : pointeur vers FILE (fichier_compresse), tableau de pointeurs vers noeud (alphabet)
 * sortie : aucune (void), termine le programme en cas d'erreur de lecture ou d'écriture de fichier
 ****************************************/
void lire_contenu(FILE *fichier_compresse, noeud *alphabet[]) {
    FILE *fichier_decompresse = NULL;
    char nom_fichier[2048];
    char codage, buffer = 0;
    int codage_bis = 0; 
    int bits_lus = 0;
    int pos = 0;
    int taille = 0; 
    int i, j;

    
    if(fscanf(fichier_compresse, "%s", nom_fichier)!=1){
        printf("Erreur lecture nom du fichier\n");
        exit(EXIT_FAILURE);
    }
    creer_dossier(nom_fichier);
    changer_nom(nom_fichier);
    fichier_decompresse = fopen(nom_fichier, "w");
    
    if (fichier_decompresse == NULL) {
        printf("Erreur création fichier décompressé\n");
        exit(EXIT_FAILURE);
    }

    if(fscanf(fichier_compresse, "%d", &taille)!=1){
        printf("erreur lecture taille fichier\n");
        return;
    }

    while (fread(&codage, sizeof(char), 1, fichier_compresse)) {
        for(j = 0; j < 8; j++){
            if(taille == 0){
            break;
        }
            buffer = (codage >> (7 - pos)) & 1;
            bits_lus++;
            pos++;
            codage_bis = (codage_bis << 1) | buffer;
            taille--;


        
            for (i = 0; i < 256; i++) {
                if (alphabet[i] != NULL && bits_lus == alphabet[i]->bits && codage_bis == alphabet[i]->codage) {
                    fputc(alphabet[i]->initial, fichier_decompresse); 
                    codage_bis = 0; 
                    bits_lus = 0; 
                    break; 
                }
            }
        }
        pos = 0;
        if(taille == 0){
            fclose(fichier_decompresse);
            if(fscanf(fichier_compresse, "%s", nom_fichier)!=1){
                return;
            }
            creer_dossier(nom_fichier);
        changer_nom(nom_fichier);
            fichier_decompresse = fopen(nom_fichier, "w");
            if(fscanf(fichier_compresse, "%d", &taille)!=1){
                fclose(fichier_decompresse);
                return;
            }
        }
    }

     
}