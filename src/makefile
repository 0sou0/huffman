CC = gcc
CDFLAGS = -W -Wall -pedantic -std=c89 -O2

huffman : main.o arbre.o tableau.o decoder.o encoder.o outils.o
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

clean :
	rm -f *.o huffman fich_decomp.txt res.txt ./decompression/fich_decomp.txt

