/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : carte.cpp                             */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/carte.h"
#include "../headers/type.h"
#include "../headers/case.h"
#include "../headers/block.h"
#include "../headers/entitee.h"

/*************************************************************************
*                       Constructeur & Destructeur                       *
*************************************************************************/

/**
 * Créer un nouvel objet Carte
 * 
 * @param dimX La largeur de la carte.
 * @param dimY La hauteur de la carte.
 * @param nomDeLaCarte Le nom de la carte.
 */
Carte::Carte (int dimX, int dimY, const char* nomDeLaCarte) :
	coordEntiteeConstr(nullptr),
	coordBlockCasse(nullptr),
	nbEntiteeConstr(0),
	nbBlockCasse(0),
	nomDeLaCarte(nomDeLaCarte)
{
	if (dimX == 0 || dimY == 0)
	{
		elements           = nullptr ;
		this->dimX         = 0 ;
		this->dimY         = 0 ;
	}
	else
	{
		elements = new Case [dimX * dimY] ;
		
		if (elements)
		{
			for (int i = 0; i < dimX * dimY; i++)
			{
				elements[i].setTypeElement(VIDE) ;
				elements[i].creerVide() ;
				elements[i].setCoord(i % dimX, i / dimX) ;
			}
			this->dimX = dimX ;
			this->dimY = dimY ;
			
			elements[LARGEUR * 2 + LARGEUR / 2].setTypeElement(ENTITEE);
			elements[LARGEUR * 2 + LARGEUR / 2].setEntitee(VAISSEAU, this);

			elements[LARGEUR * 3 + LARGEUR / 2].setTypeElement(CURSEUR);
			elements[LARGEUR * 3 + LARGEUR / 2].setCurseur(elements[LARGEUR * 3 + LARGEUR / 2].getCoord());
		}
		else
		{
			cerr << "Erreur allocation des éléments de la carte." << endl ;
			exit (-1) ;
		}
		
	}

}

/**
 * Le destructeur de la classe Carte est responsable de la suppression du tableau d'éléments
 */
Carte::~Carte ()
{
	if (elements)
	{
		for (unsigned int i = 0; i < dimX * dimY; i++) /*--->*/ this->elements[i].detruireElement(this->elements[i].getTypeElement()) ;
		delete[] this->elements ;
		this->elements = nullptr;
		if (coordEntiteeConstr)
		{
			delete this->coordEntiteeConstr;
			this->coordEntiteeConstr = nullptr;
		}
		if (coordBlockCasse)
		{
			delete this->coordBlockCasse;
			this->coordBlockCasse = nullptr;
		}
		
		cout << "Désallocation de la carte reussi." << endl ;
	}
	else
	{
		cerr << "Erreur allocation des éléments de la carte." << endl ;
		exit (-1);
	}

}
	
/*************************************************************************
*                                 Méthode                                *
*************************************************************************/

/**
 * Il remplit la carte avec des éléments aléatoires.
 */
void Carte::remplirHasard ()
{
	// Initialisation du random
	srand(time(NULL));
	
	int terre 	= 0 ;
	int roche 	= 0 ;
	int minerai = 0 ;
	int relief  = 200; // variable se démécrantant à chaque ligne pour creer un relief

	for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
	{
		terre   = (rand() % 100 + 1) + relief ;
		roche   = (rand() % 100 + 1) + relief ;
		minerai = (rand() % 100 + 1) + relief ;

		this->elements[i].setCoord (i % LARGEUR, i / LARGEUR) ;
		
		if (minerai < 3)
		{
			this->elements[i].detruireElement (this->elements[i].getTypeElement()) ;
			this->elements[i].setTypeElement (BLOCK) ;
			this->elements[i].setBlock (MINERAI, 0) ;
		}
		else if (roche < 21)
		{
			int rocheType = (rand() % 100 + 1) ;

			if (rocheType <= 5) /*---------->*/ rocheType = ROCHE3 ;
			else if (rocheType <= 30) /*---->*/ rocheType = ROCHE2 ;
			else if (rocheType <= 100) /*--->*/ rocheType = ROCHE1 ;

			this->elements[i].detruireElement (this->elements[i].getTypeElement()) ;
			this->elements[i].setTypeElement (BLOCK) ;
			this->elements[i].setBlock (ROCHE, rocheType) ;
		}
		else if (terre <= 100)
		{
			this->elements[i].detruireElement (this->elements[i].getTypeElement()) ;
			this->elements[i].setTypeElement (BLOCK) ;
			this->elements[i].setBlock (TERRE, 0) ;
		}
		else if (this->elements[i].getTypeElement() == ENTITEE) ;

		if (relief > 0 && i % LARGEUR == 0) /*--->*/ relief -= 25;

	}
}

/**
 * Crée une grotte dans la carte
 * 
 * @param pos La position du bloc où commence la grotte.
 * @param randMoins Plus le nombre est élevé, plus la grotte sera petite.
 */
void Carte::creerCaverne (unsigned int pos, int randMoins)
{
	
	while (pos > LARGEUR * HAUTEUR || this->elements[pos].getTypeElement() != BLOCK) /*--->*/ pos = rand() % LARGEUR * HAUTEUR + 280;
	
	if (this->elements[pos].getTypeElement() == BLOCK)
	{
		int droite = rand() % 100 - randMoins;
		while (droite < 0) /*--->*/ droite = rand() % 100 - randMoins;
		
		int bas    = rand() % 100 - randMoins;
		while (bas < 0) /*------>*/ bas = rand() % 100 - randMoins;

		int gauche = rand() % 100 - randMoins;
		while (gauche < 0) /*--->*/ gauche = rand() % 100 - randMoins;

		int haut   = rand() % 100 - randMoins;
		while (haut < 0) /*----->*/ haut = rand() % 100 - randMoins;

		this->elements[pos].detruireElement (BLOCK) ;
		this->elements[pos].setTypeElement (VIDE) ;
		this->elements[pos].creerVide() ;

		randMoins += 5;

		if (droite > 30 && pos < LARGEUR * HAUTEUR)
			if(this->elements[pos + 1].getTypeElement() == BLOCK) /*--------->*/ creerCaverne (pos + 1, randMoins);
		if (haut > 30	&& pos >= 0)
			if (this->elements[pos + LARGEUR].getTypeElement() == BLOCK) /*------>*/ creerCaverne (pos + LARGEUR, randMoins);
		if (gauche > 30 && pos >= 0)
			if (this->elements[pos - 1].getTypeElement() == BLOCK) /*--------->*/ creerCaverne (pos - 1, randMoins);
		if (bas > 30	&& pos < LARGEUR * HAUTEUR)
			if (this->elements[pos - LARGEUR].getTypeElement() == BLOCK) /*------>*/ creerCaverne (pos - LARGEUR, randMoins);
	}
	
}

/**
 * Crée un certain nombre d'ennemis
 * 
 * @param nbEnnemie le nombre d'ennemis à créer
 */
void Carte::creerEnnemie (int nbEnnemie)
{
	int pos = 0;

	for (int i = 0; i < nbEnnemie; i++)
	{
		while (elements[pos].getTypeElement() != VIDE || pos < 350) /*--->*/ pos = rand() % (LARGEUR * HAUTEUR) + 1;

		elements[pos].setTypeElement(ENTITEE);
		elements[pos].setEntitee(CREEPER_EMETTEUR, this);
		elements[pos].getEntitee()->setId(i);
	}
}

/**
 * Il imprime la carte
 */
void Carte::afficherCarte () const
{
	cout << "Nom de la carte : " << nomDeLaCarte << endl;

	unsigned int k = 0;

	for (unsigned int i = 0; i < HAUTEUR + 2; i++)
	{
		for (unsigned int j = 0; j < LARGEUR + 2; j++)
		{
			switch (i)
			{
				case 0:
					switch (j)
					{
						case 0: cout << "╔"; break;
						case LARGEUR + 1: cout << "╗"; break;
						default: cout << "═"; break;
					}
					break;
				case HAUTEUR + 1:
					switch (j)
					{
						case 0: cout << "╚"; break;
						case LARGEUR + 1: cout << "╝"; break;
						default: cout << "═"; break;
					}
					break;
				default:
					if (j == 0 || j == LARGEUR + 1) /*--->*/ cout << "║";
					else
					{
						switch (elements[k].getTypeElement())
						{
							case VIDE: cout << " "; break;
							case BLOCK:
								switch (elements[k].getBlock()->getType())
								{
									case TERRE: cout << "░"; break;
									case ROCHE:
										switch (elements[k].getBlock()->getRocheType())
										{
											case ROCHE1: cout << "▒"; break;
											case ROCHE2: cout << "▓"; break;
											case ROCHE3: cout << "█"; break;
										}
										break;
									case MINERAI: cout << "▚"; break;
								}
								break;
							case ENTITEE:
								switch (elements[k].getEntitee()->getType())
								{
									case VAISSEAU: cout << "◈"; break;
									case REACTEUR:
										if (elements[k].getEntitee()->getConstr() <= 0) /*--->*/ cout << "◬";
										else /*--->*/ cout << " ";
										break;
									case MINEUR:
										if (elements[k].getEntitee()->getConstr() <= 0) /*--->*/ cout << "◭";
										else /*--->*/ cout << " ";
										break;
									case BOUCLIER:
										if (elements[k].getEntitee()->getConstr() <= 0) /*--->*/ cout << "◩";
										else /*--->*/ cout << " ";
										break;
									case PHARE:
										if (elements[k].getEntitee()->getConstr() <= 0) /*--->*/ cout << "◉";
										else /*--->*/ cout << " ";
										break;
									case BOMBE:
										if (elements[k].getEntitee()->getConstr() <= 0) /*--->*/ cout << "◘";
										else /*--->*/ cout << " ";
										break;
									case CREEPER_EMETTEUR: cout << "◎"; break;
								}
								break;
							case CURSEUR: cout << "○"; break;
						}

						k++;

					}
					break;
			}

		}

		cout << endl;
		
	}
	
}

/**
 * @brief Méthode afficherAdresse, affiche l'adresse de l'élément de la carte.
 *
 * @param pos
 */
void Carte::afficherAdresse (unsigned int x, unsigned int y) const
{
	cout << "L'adresse de l'élément est : " << &elements[LARGEUR * y + x] << endl;
}

/**
 * Méthode gestionConstruction, décrémente les points de construction des entitée.
 */
void Carte::gestionConstruction()
{
	if (coordEntiteeConstr)
	{
		for (uint8_t i = 0; i < nbEntiteeConstr; i++)
		{
			cout << "Coordonnée dans coordEntiteeConstr[i] : " << coordEntiteeConstr->at(i).x << " " << coordEntiteeConstr->at(i).y << endl;
			Entitee* entitee = this->getElement(coordEntiteeConstr->at(i).x, coordEntiteeConstr->at(i).y)->getEntitee();
			switch (entitee->getType())
			{
				case VAISSEAU:			break;
				case CREEPER_EMETTEUR:	break;
				default:
					if (entitee->getConstr() > 0) /*--->*/ entitee->decConstr(1);
					else
					{
						/*
						 * Enlève l'entitée du tableau d'entitée et realloue la mémoire du tableau en fonction de la taille.
						 */
						for (uint8_t j = i; j < nbEntiteeConstr - 1; j++)
						{
							coordEntiteeConstr->at(j) = coordEntiteeConstr->at(j + 1);
						}
						coordEntiteeConstr->resize(nbEntiteeConstr - 1);
						nbEntiteeConstr--;
						i--;
						if (nbEntiteeConstr == 0)
						{
							delete coordEntiteeConstr;
							coordEntiteeConstr = nullptr;
						}
					}
					break;
			}
		}
	}
}

/**
 * @brief Méthode gestionCasseBlock, décrémente les points de durabilité des blocks.
 */
void Carte::gestionCasseBlock()
{
	if (coordBlockCasse)
	{
		for (uint8_t i = 0; i < nbBlockCasse; i++)
		{
			cout << "Coordonnée dans coordBlockCasse[i] : " << coordBlockCasse->at(i).x << " " << coordBlockCasse->at(i).y << endl;
			Block* block = this->getElement(coordBlockCasse->at(i).x, coordBlockCasse->at(i).y)->getBlock();
			if (block->getSoliditee() > 0) /*--->*/ block->decSoliditee(1);
			else
			{
				this->getElement(coordBlockCasse->at(i).x, coordBlockCasse->at(i).y)->detruireElement(BLOCK);
				this->getElement(coordBlockCasse->at(i).x, coordBlockCasse->at(i).y)->creerVide();
				this->getElement(coordBlockCasse->at(i).x, coordBlockCasse->at(i).y)->setTypeElement(VIDE);
				/*
				* Enlève le block du tableau de coordonnées des blocks à casser et realloue la mémoire
				* du tableau en fonction de la taille.
				*	*/
				for (uint8_t j = i; j < nbBlockCasse - 1; j++)
				{
					coordBlockCasse->at(j) = coordBlockCasse->at(j + 1);
				}
				coordBlockCasse->resize(nbBlockCasse - 1);
				nbBlockCasse--;
				i--;
				if (nbBlockCasse == 0)
				{
					delete coordBlockCasse;
					coordBlockCasse = nullptr;
				}
			}
		}
	}
}

////////////
// Getter //
////////////

/**
 * Renvoie la valeur de la variable membre privée dimX
 * 
 * @return La valeur de la variable membre dimX.
 */
unsigned int Carte::getDimX ()
{
	return dimX ;
}

/**
 * Renvoie la valeur de la variable membre dimY
 * 
 * @return La valeur de la variable membre dimY.
 */
unsigned int Carte::getDimY ()
{
	return dimY ;
}

/**
 * Renvoie l'élément de la carte
 * 
 * @return L'élément de la carte.
 */
Case* Carte::getElement (unsigned int x, unsigned int y)
{
	return &elements[LARGEUR * y + x];
}

/**
 * @Méthode getCoordEntiteeConstr, récupère le tableau de coordonnée d'entitée en construction.
 */
vector<Coord>* Carte::getCoordEntiteeConstr()
{
	return coordEntiteeConstr;
}

/**
 * @brief getCoordBlockCasse, récupère le tableau de coordonnée de blocks à casser.
 *
 * @return un tableau de coordonnée.
 */
vector<Coord>* Carte::getCoordBlockCasse()
{
	return coordBlockCasse;
}

/**
 * Renvoyer le nom de la carte
 * 
 * @return Le nom de la carte.
 */
const char* Carte::getNomDeLaCarte ()
{
	return nomDeLaCarte ;
}

////////////
// Setter //
////////////

/**
 * @brief Méthode setNomDeLaCarte, modifie le nom de la carte.
 *
 * @param nomDeLaCarte le nouveau nom de la carte.
 */
void Carte::setNomDeLaCarte (const char* nomDeLaCarte)
{
	this->nomDeLaCarte = nomDeLaCarte;
}

/**
 * @brief Méthode setCoordEntiteeConstr, modifie le tableau de coordonnée d'entitée en construction.
 *
 * @param coord la nouvelle coordonnée.
 */
void Carte::setCoordEntiteeConstr (Coord coord)
{
	if (coordEntiteeConstr)
	{
		coordEntiteeConstr->resize(nbEntiteeConstr + 1);
		coordEntiteeConstr->at(nbEntiteeConstr) = coord;
		nbEntiteeConstr++;
	}
	else
	{
		coordEntiteeConstr = new vector<Coord>(1);
		if (coordEntiteeConstr)
		{
			coordEntiteeConstr->at(0) = coord;
			nbEntiteeConstr++;
		}
		else
		{
			cout << "Erreur : impossible de créer le tableau de coordonnée d'entitée en construction." << endl;
		}
	}
}

/**
 * @brief Méthode setCoordBlockCasse, modifie le tableau de coordonnée de block à casser.
 *
 * @param coord la nouvelle coordonnée.
 */
void Carte::setCoordBlockCasse(Coord coord)
{
	if (coordBlockCasse)
	{
		coordBlockCasse->resize(nbBlockCasse + 1);
		coordBlockCasse->at(nbBlockCasse) = coord;
		nbBlockCasse++;
	}
	else
	{
		coordBlockCasse = new vector<Coord>(1);
		if (coordBlockCasse)
		{
			coordBlockCasse->at(0) = coord;
			nbBlockCasse++;
		}
		else
		{
			cout << "Erreur : impossible de créer le tableau de coordonnée de block à casser." << endl;
		}
	}
}