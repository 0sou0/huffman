#ifndef TYPE_H
#define TYPE_H


#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/stat.h>
#define N 256


typedef struct noeud{
	char initial;
	int occ;
	int codage;
	int bits;
  	struct noeud * gauche;
  	struct noeud * droit;
}noeud;


#endif

