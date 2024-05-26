#include "type.h"
#include "arbre.h"
#include "encoder.h"


/****************************************
 * fonction : lire_entete
 * description : Lit l'en-tête du fichier compressé pour extraire l'alphabet utilisé, 
 *               avec les occurrences, les bits utilisés pour chaque caractère, et leur codage
 * entree : pointeur vers fichier FILE *fichier, tableau de pointeurs vers noeud alphabet[]
 * sortie : aucune (void), termine le programme en cas d'erreur de lecture
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
                printf("erreur allocation memoire");
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
 * fonction : lire_contenu
 * description : Lit le contenu compressé, décode les caractères selon l'alphabet et les écrit dans un fichier de sortie
 * entree : pointeur vers fichier FILE *fichier_compresse, tableau de pointeurs vers noeud alphabet[]
 * sortie : aucune (void)
 ****************************************/
void lire_contenu(FILE *fichier_compresse, noeud *alphabet[], char* chemin) {
    char codage, buffer = 0;
    int codage_bis = 0; 
    int bits_lus = 0;
    int pos = 0;
    int taille = 0; 
    int i, j;

    FILE *fichier_decompresse;
    
    fichier_decompresse= fopen(chemin, "w");
    if (fichier_decompresse == NULL) {
        perror("Erreur création fichier décompressé\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < 256; i++){
        if(alphabet[i] != NULL){
            taille += alphabet[i]->occ * alphabet[i]->bits;
        }
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
    }

    fclose(fichier_decompresse); 
}




  
