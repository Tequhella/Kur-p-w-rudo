all: main.o gestionMem.o gestionMap.o gestionAffichage.o gestionEntitee.o
	gcc main.o gestionMem.o gestionMap.o gestionAffichage.o gestionEntitee.o -o Jeu-v0-6.1

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