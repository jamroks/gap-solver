# Indiquer quel compilateur est à utiliser
CC      ?= gcc

# Spécifier les options du compilateur
CFLAGS  ?= -g 
LDFLAGS ?= -L/usr/openwin/lib
LDLIBS  ?= -lX11 -lXext

# Reconnaître les extensions de nom de fichier *.c et *.o comme suffixe
SUFFIXES ?= .c .o 
.SUFFIXES: $(SUFFIXES) .

# Nom de l'exécutable
PROG  = life 

# Liste de fichiers objets nécessaires pour le programme final
OBJS  = main.o window.o Board.o Life.o BoundedBoard.o
 
all: $(PROG)

# Etape de compilation et d'éditions de liens
# ATTENTION, les lignes suivantes contenant "$(CC)" commencent par un caractère TABULATION et non pas des espaces
$(PROG): $(OBJS)
     $(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(PROG) $(OBJS)

.c.o:
     $(CC) $(CFLAGS) -c $*.c
