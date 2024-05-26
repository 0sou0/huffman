#include "type.h"
#include "arbre.h"

/****************************************
 * fonction : affichage_code
 * description : Affiche le code binaire d'un caractère 
 * entree : entier nbr_bits (nombre de bits du codage), entier codage (valeur du codage)
 * sortie : aucune (void), affiche le code 
 ****************************************/
void affichage_code(int nbr_bits, int codage){
int i;
  for (i = 0; i < nbr_bits; i++) {
    printf("%d", (codage >> (nbr_bits - i - 1))   & 1);
  }
  printf("\n");
}



/****************************************
 * fonction : creer_code
 * description : Crée le codage de Huffman pour un caractère et le stocke dans 'codage'
 * entree : pointeur vers noeud element, entier code (valeur du code), entier profondeur (nombre de bits),
 *          tableau de pointeurs vers noeud alphabet[]
 * sortie : aucune (void)
 ****************************************/
void creer_code(noeud *element, int code, int profondeur, noeud *alphabet[]) {
  if (est_feuille(element)) {
    alphabet[(int)element->initial] = element;
    /*if(element->initial == '\n'){
      printf("\"\\n\" code : ");
    }
    else{
      printf("\"%c\" code : ", element->initial);
    }
    affichage_code(profondeur, code);*/
    element->codage = code;
    element->bits = profondeur;
  }
  else{
    creer_code(element->gauche, (code << 1) | 0, (profondeur + 1), alphabet);
    creer_code(element->droit, (code << 1) | 1, (profondeur + 1), alphabet);
  }
}




 /****************************************
 * fonction : ecrire_bit
 * description : Écrit un bit dans un buffer et écrit le buffer dans un fichier si le buffer est plein
 * entree : pointeur vers fichier fichier, entier bit, pointeur vers char buffer, pointeur vers entier pos
 * sortie : aucune (void)
 ****************************************/
void ecrire_bit(FILE *fichier, int bit, char *buffer, int *pos) {
  
  if (bit) {
    *buffer |= (bit << (7 - *pos));
  }
  (*pos)++;
    
  if (*pos == 8) {
    fwrite(buffer, 1, 1,fichier);
    *pos = 0;
    *buffer = 0;
  }
    
}


 /****************************************
 * fonction : ecrire_code_huffman
 * description : Écrit le code de Huffman dans un fichier, bit par bit, en utilisant un buffer
 * entree : pointeur vers fichier fichier, entier codage, entier bits (nombre de bits du codage),
 *          pointeur vers char buffer, pointeur vers entier pos
 * sortie : aucune (void), écrit les bits dans le fichier
 ****************************************/
void ecrire_code_huffman(FILE *fichier,  int codage, int bits, char *buffer, int *pos) {
int i,bit;
    for (i = bits-1; i >= 0; i--) {
      bit = (codage >> i) & 1;
      ecrire_bit(fichier, bit, buffer, pos);
    }
}



/****************************************
 * fonction : ecrire_entete
 * description : Écrit l'en-tête dans le fichier compressé, incluant le nombre de feuilles
 *               et pour chaque feuille, son caractère, son occurrence,
 *               la taille de son codage, et son codage binaire selon l'arbre de Huffman.
 * entree : pointeur vers FILE (fichier_compresse), tableau de pointeurs vers noeud (alphabet),
 *          entier nombre_feuilles indiquant le nombre de caractères uniques
 * sortie : aucune (void)
 ****************************************/
void ecrire_entete(FILE *fichier_compresse, noeud *alphabet[], int nombre_feuilles){
    int i, j;
    char buffer = 0;
    int pos=0;
 
    fprintf(fichier_compresse, "%d\n", nombre_feuilles);

    for ( i = 0; i < 256; i++) {
        if (alphabet[i] != NULL && alphabet[i]->occ > 0) {
	  ecrire_code_huffman(fichier_compresse, alphabet[i]->initial, sizeof(char) * 8, &buffer, &pos);
	  
	  fprintf(fichier_compresse, " %d ",alphabet[i]->occ);
	  fprintf(fichier_compresse, "%d ",alphabet[i]->bits);
  
	  for (j=0; j < alphabet[i]->bits; j++) {
	    fprintf(fichier_compresse, "%d",(alphabet[i]->codage >> (alphabet[i]->bits - j - 1))   & 1);
	  }
	  fprintf(fichier_compresse, "\n");

    }
  }
  

}


   
/****************************************
 * fonction : contenu_compresse
 * description : Parcourt le fichier à compresser, calcule la taille totale des données compressées
 *               en se basant sur le codage de Huffman et écrit les données compressées dans
 *               le fichier de sortie. Utilise la fonction ecrire_code_huffman pour chaque caractère.
 * entree : pointeur vers FILE (fichier) à compresser, pointeur vers FILE (fichier_compresse) pour
 *          écrire le contenu compressé, tableau de pointeurs vers noeud (alphabet) représentant
 *          l'arbre de Huffman
 * sortie : aucune (void)
 ****************************************/
void contenu_compresse(FILE *fichier, FILE *fichier_compresse, noeud *alphabet[]) {
  int c;
  char buffer = 0; 
  int pos = 0;
  int taille = 0;


  while((c = fgetc(fichier)) != EOF){
    if (alphabet[c] != NULL && alphabet[c]->occ > 0) {
        taille +=alphabet[c]->bits;
      }
    }
    fprintf(fichier_compresse, "%d", taille);

  rewind(fichier);



  while((c = fgetc(fichier)) != EOF){
    if (alphabet[c] != NULL && alphabet[c]->occ > 0) {
      ecrire_code_huffman(fichier_compresse, alphabet[c]->codage, alphabet[c]->bits, &buffer, &pos );
    }
  }
  if(pos > 0){
        fwrite(&buffer, 1, 1, fichier_compresse);
  }
  
}




