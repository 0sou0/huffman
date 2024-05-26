
# Outil de Compression Huffman

Cet outil implémente le codage de Huffman pour la compression et la décompression de fichiers et dossiers.

## Compilation avec Makefile

Pour compiler le programme dans sa dernière version, ouvrez un terminal dans le répertoire contenant le code source et le Makefile, puis exécutez :

make

Pour les versions précédentes faire :

make huffman[numero_de_version]

Cela générera les exécutables, 'huffman' et 'generation'.

make pdf

Pour créer le beamer.

## Utilisation

Après la compilation, l'exécutable peut être utilisé avec différentes options :

### Compression

Pour compresser un fichier ou un répertoire, utilisez l'option `-c` suivie du chemin vers le fichier ou le répertoire à compresser, puis spécifiez le nom du fichier compressé de sortie :

./huffman -c chemin_vers_fichier_ou_dossier fichier_compresse.txt



Vous pouvez compresser plusieurs répertoires et fichiers en même temps, il suffit d'ajouter un chemin vers le fichier ou le répertoire à compresser : 

./huffman -c chemin_vers_fichier_ou_dossier chemin_vers_fichier_ou_dossier fichier_compressé.txt


### Décompression

Pour décompresser un fichier `.txt`, utilisez l'option `-d` suivie du chemin vers le fichier compressé :


./huffman -d fichier_compressé.txt


### Aide

Pour afficher l'aide et les options disponibles, utilisez l'option `-h` :


./huffman -h


## Exemples d'utilisation

- Compression d'un dossier `mes_documents` :
  
  ./huffman -c mes_documents documents.txt
 
- Décompression dans le dossier courant :
  
  ./huffman -d documents.txt

- Afficher l'aide :
  
  ./huffman -h
 

## Nettoyage

Pour supprimer les fichiers objets et l'exécutable généré lors de la compilation, utilisez :

make clean

Cela va nettoyer le répertoire de tous les fichiers générés par la commande `make`.
