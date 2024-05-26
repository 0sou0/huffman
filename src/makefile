CC = gcc
CDFLAGS = -W -Wall -pedantic -std=c89 -O2

all : huffman5 

huffman5 : main.o arbre.o tableau.o decoder.o encoder.o outils.o
	$(CC) $(CDFLAGS) $^ -o $@

main.o : main.c arbre.h tableau.h type.h
	$(CC) $(CDFLAGS) -c $<

arbre.o : arbre.c type.h
	$(CC) $(CDFLAGS) -c $<

tableau.o : tableau.c type.h
	$(CC) $(CDFLAGS) -c $<

decoder.o : decoder.c type.h
	$(CC) $(CDFLAGS) -c $<

encoder.o : encoder.c type.h
	$(CC) $(CDFLAGS) -c $<

outils.o : outils.c type.h
	$(CC) $(CDFLAGS) -c $<



ouverture:
	chmod +x ouverture.sh

pdf:
	pdflatex Sans-ti.tex
	open Sans-ti.pdf
	
clean :
	rm -f *.o huffman5 *.txt 