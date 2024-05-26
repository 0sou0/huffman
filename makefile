CC = gcc
CFLAGS = -W -Wall -pedantic -std=c89 -O2
LDFLAGS =  -lm
SRC_DIR := huff_v5
OBJ_DIR := huff_v5
BIN_DIR := huff_v5

LISTEPROG = main.o arbre.o tableau.o decoder.o encoder.o outils.o


SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


all: huffman5 generation

# Nom de l'exécutable
EXECUTABLE := $(BIN_DIR)/huffman5

huffman5: $(EXECUTABLE)

# Règle pour créer l'exécutable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

# Règle pour compiler les fichiers sources en fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@






SOURCES := $(wildcard huff_v4/*.c)
OBJECTS := $(SOURCES:huff_v4/%.c=huff_v4/%.o)

# Nom de l'exécutable
EXECUTABLE := huff_v4/huffman4

huffman4: $(EXECUTABLE)

# Règle pour créer l'exécutable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

# Règle pour compiler les fichiers sources en fichiers objets
huff_v4/%.o: huff_v4/%.c
	$(CC) -c $< -o $@




SOURCES := $(wildcard huff_v3/*.c)
OBJECTS := $(SOURCES:huff_v3/%.c=huff_v3/%.o)

# Nom de l'exécutable
EXECUTABLE := huff_v3/huffman3

huffman3: $(EXECUTABLE)

# Règle pour créer l'exécutable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

# Règle pour compiler les fichiers sources en fichiers objets
huff_v3/%.o: huff_v3/%.c
	$(CC) -c $< -o $@





SOURCES := $(wildcard huff_v2/*.c)
OBJECTS := $(SOURCES:huff_v2/%.c=huff_v2/%.o)

# Nom de l'exécutable
EXECUTABLE := huff_v2/huffman2

huffman2: $(EXECUTABLE)

# Règle pour créer l'exécutable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

# Règle pour compiler les fichiers sources en fichiers objets
huff_v2/%.o: huff_v2/%.c
	$(CC) -c $< -o $@






SOURCES := $(wildcard huff_v1/*.c)
OBJECTS := $(SOURCES:huff_v1/%.c=huff_v1/%.o)

# Nom de l'exécutable
EXECUTABLE := huff_v1/huffman1

huffman1: $(EXECUTABLE)

# Règle pour créer l'exécutable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

# Règle pour compiler les fichiers sources en fichiers objets
huff_v1/%.o: huff_v1/%.c
	$(CC) -c $< -o $@



generation: generation.o
	$(CC) $(CFLAGS) $^ -o $@

generation.o : generation.c
	$(CC) $(CFLAGS) -c $<



pdf:
	pdflatex Sans-ti.tex
	open Sans-ti.pdf

clean: clean1 clean2 clean3 clean4 clean5 cleangenerer

clean5:
	rm -f huff_v5/*.o huff_v5/huffman5 huff_v5/*.txt

clean4:
	rm -f huff_v4/*.o huff_v4/huffman4

clean3:
	rm -f huff_v3/*.o huff_v3/huffman3

clean2:
	rm -f huff_v2/*.o huff_v2/huffman2

clean1:
	rm -f huff_v1/*.o huff_v1/huffman1 

cleangenerer:
	rm -f *.o generation

