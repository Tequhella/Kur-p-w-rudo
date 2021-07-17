all: main.o gestionMem.o gestionMap.o gestionAffichage.o gestionEntitee.o gestionFichier.o
	gcc main.o gestionMem.o gestionMap.o gestionAffichage.o gestionEntitee.o gestionFichier.o -o Jeu-v0-8-1 -lSDL2

main.o:
	gcc -c sources/main.c -o main.o

gestionMem.o:
	gcc -c sources/gestionMem.c -o gestionMem.o

gestionMap.o:
	gcc -c sources/gestionMap.c -o gestionMap.o

gestionAffichage.o:
	gcc -c sources/gestionAffichage.c -o gestionAffichage.o

gestionEntitee.o:
	gcc -c sources/gestionEntitee.c -o gestionEntitee.o

gestionFichier.o:
	gcc -c sources/gestionFichier.c -o gestionFichier.o