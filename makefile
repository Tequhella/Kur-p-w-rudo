CC = g++

G++  = -g -Wall

all: Kuripawarudo_Linux/obj/main.o Kuripawarudo_Linux/obj/carte.o Kuripawarudo_Linux/obj/case.o Kuripawarudo_Linux/obj/block.o Kuripawarudo_Linux/obj/entitee.o Kuripawarudo_Linux/obj/vide.o Kuripawarudo_Linux/obj/curseur.o Kuripawarudo_Linux/obj/entitee/vaisseau.o Kuripawarudo_Linux/obj/entitee/reacteur.o Kuripawarudo_Linux/obj/entitee/mineur.o Kuripawarudo_Linux/obj/entitee/bouclier.o Kuripawarudo_Linux/obj/entitee/phare.o Kuripawarudo_Linux/obj/entitee/bombe.o Kuripawarudo_Linux/obj/entitee/creeperEmetteur.o
	$(CC) $(G++) Kuripawarudo_Linux/obj/main.o Kuripawarudo_Linux/obj/carte.o Kuripawarudo_Linux/obj/case.o Kuripawarudo_Linux/obj/block.o Kuripawarudo_Linux/obj/entitee.o Kuripawarudo_Linux/obj/vide.o Kuripawarudo_Linux/obj/curseur.o Kuripawarudo_Linux/obj/entitee/vaisseau.o Kuripawarudo_Linux/obj/entitee/reacteur.o Kuripawarudo_Linux/obj/entitee/mineur.o Kuripawarudo_Linux/obj/entitee/bouclier.o Kuripawarudo_Linux/obj/entitee/phare.o Kuripawarudo_Linux/obj/entitee/bombe.o Kuripawarudo_Linux/obj/entitee/creeperEmetteur.o -o kuripawarudo-v0-3-7-CPP

Kuripawarudo_Linux/obj/main.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/main.cpp -o Kuripawarudo_Linux/obj/main.o

Kuripawarudo_Linux/obj/carte.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/carte.cpp -o Kuripawarudo_Linux/obj/carte.o

Kuripawarudo_Linux/obj/case.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/case.cpp -o Kuripawarudo_Linux/obj/case.o

Kuripawarudo_Linux/obj/block.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/block.cpp -o Kuripawarudo_Linux/obj/block.o

Kuripawarudo_Linux/obj/entitee.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee.cpp -o Kuripawarudo_Linux/obj/entitee.o

Kuripawarudo_Linux/obj/vide.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/vide.cpp -o Kuripawarudo_Linux/obj/vide.o

Kuripawarudo_Linux/obj/curseur.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/curseur.cpp -o Kuripawarudo_Linux/obj/curseur.o

Kuripawarudo_Linux/obj/entitee/vaisseau.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee/vaisseau.cpp -o Kuripawarudo_Linux/obj/entitee/vaisseau.o

Kuripawarudo_Linux/obj/entitee/reacteur.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee/reacteur.cpp -o Kuripawarudo_Linux/obj/entitee/reacteur.o

Kuripawarudo_Linux/obj/entitee/mineur.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee/mineur.cpp -o Kuripawarudo_Linux/obj/entitee/mineur.o

Kuripawarudo_Linux/obj/entitee/bouclier.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee/bouclier.cpp -o Kuripawarudo_Linux/obj/entitee/bouclier.o

Kuripawarudo_Linux/obj/entitee/phare.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee/phare.cpp -o Kuripawarudo_Linux/obj/entitee/phare.o

Kuripawarudo_Linux/obj/entitee/bombe.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee/bombe.cpp -o Kuripawarudo_Linux/obj/entitee/bombe.o

Kuripawarudo_Linux/obj/entitee/creeperEmetteur.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee/creeperEmetteur.cpp -o Kuripawarudo_Linux/obj/entitee/creeperEmetteur.o

clean:
	rm kuripawarudo-v0-3-7-CPP Kuripawarudo_Linux/obj/main.o Kuripawarudo_Linux/obj/carte.o Kuripawarudo_Linux/obj/case.o Kuripawarudo_Linux/obj/block.o Kuripawarudo_Linux/obj/entitee.o Kuripawarudo_Linux/obj/vide.o Kuripawarudo_Linux/obj/curseur.o Kuripawarudo_Linux/obj/entitee/vaisseau.o Kuripawarudo_Linux/obj/entitee/reacteur.o Kuripawarudo_Linux/obj/entitee/mineur.o Kuripawarudo_Linux/obj/entitee/bouclier.o Kuripawarudo_Linux/obj/entitee/phare.o Kuripawarudo_Linux/obj/entitee/bombe.o Kuripawarudo_Linux/obj/entitee/creeperEmetteur.o
