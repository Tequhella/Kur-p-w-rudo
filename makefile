CC = g++

G++  = -g -Wall

all: obj/main.o obj/carte.o obj/case.o obj/block.o obj/entitee.o obj/vide.o obj/entitee/vaisseau.o obj/entitee/reacteur.o obj/entitee/mineur.o obj/entitee/bouclier.o obj/entitee/phare.o obj/entitee/bombe.o obj/entitee/creeperEmetteur.o
	$(CC) $(G++) obj/main.o obj/carte.o obj/case.o obj/block.o obj/entitee.o obj/vide.o obj/entitee/vaisseau.o obj/entitee/reacteur.o obj/entitee/mineur.o obj/entitee/bouclier.o obj/entitee/phare.o obj/entitee/bombe.o obj/entitee/creeperEmetteur.o -o kuripawarudo-v0-3-1-CPP

obj/main.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/main.cpp -o obj/main.o

obj/carte.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/carte.cpp -o obj/carte.o

obj/case.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/case.cpp -o obj/case.o

obj/block.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/block.cpp -o obj/block.o

obj/entitee.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee.cpp -o obj/entitee.o

obj/vide.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/vide.cpp -o obj/vide.o

obj/entitee/vaisseau.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee/vaisseau.cpp -o obj/entitee/vaisseau.o

obj/entitee/reacteur.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee/reacteur.cpp -o obj/entitee/reacteur.o

obj/entitee/mineur.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee/mineur.cpp -o obj/entitee/mineur.o

obj/entitee/bouclier.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee/bouclier.cpp -o obj/entitee/bouclier.o

obj/entitee/phare.o: 
	$(CC) $(G++) -c Kuripawarudo_Linux/sources/entitee/phare.cpp -o obj/entitee/phare.o

obj/entitee/bombe.o: 
	$(CC) $(CFLAGS) -c Kuripawarudo_Linux/sources/entitee/bombe.cpp -o obj/entitee/bombe.o

obj/entitee/creeperEmetteur.o: 
	$(CC) $(CFLAGS) -c Kuripawarudo_Linux/sources/entitee/creeperEmetteur.cpp -o obj/entitee/creeperEmetteur.o

clean:
	rm kuripawarudo-v0-3-1-CPP obj/main.o obj/carte.o obj/case.o obj/block.o obj/entitee.o obj/vide.o obj/entitee/vaisseau.o obj/entitee/reacteur.o obj/entitee/mineur.o obj/entitee/bouclier.o obj/entitee/phare.o obj/entitee/bombe.o obj/entitee/creeperEmetteur.o
