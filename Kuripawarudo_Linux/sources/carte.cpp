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
#include "../headers/curseur.h"
#include <random>

/*************************************************************************
*                       Constructeur & Destructeur                       *
*************************************************************************/

Carte::Carte (int dimX, int dimY, const char* nomDeLaCarte) :
	nomDeLaCarte(nomDeLaCarte)
{
	if (dimX == 0 || dimY == 0)
	{
		elements           = nullptr;
		this->dimX         = 0;
		this->dimY         = 0;
        BOOST_LOG_TRIVIAL(error) << "Erreur : la largeur ou la hauteur de la carte est nulle.";
	}
	else
	{
		elements = new Case [dimX * dimY];
		
		if (elements)
		{
            std::shared_ptr<Curseur> curseur = make_shared<Curseur>(Coord {LARGEUR / 2, 3});
			for (int i = 0; i < dimX * dimY; i++)
			{
				elements[i].setTypeElement(VIDE);
				elements[i].creerVide();
				elements[i].setCoord(i % dimX, i / dimX);
                elements[i].setCurseur(curseur);
			}
			this->dimX = dimX;
			this->dimY = dimY;
			
			elements[LARGEUR * 2 + LARGEUR / 2].setTypeElement(ENTITEE);
			elements[LARGEUR * 2 + LARGEUR / 2].setEntitee(VAISSEAU, setCoordEntiteeCallback);

			elements[LARGEUR * 3 + LARGEUR / 2].setTypeElement(CURSEUR);
		}
		else
		{
			BOOST_LOG_TRIVIAL(error) << "Erreur allocation des éléments de la carte.";
			exit (-1);
		}
		
	}

    BOOST_LOG_TRIVIAL(info) << "Carte créée.";

}

Carte::~Carte ()
{
	if (elements)
	{
		for (unsigned int i = 0; i < dimX * dimY; i++) /*--->*/ this->elements[i].detruireElement(this->elements[i].getTypeElement());
		delete[] this->elements;
		this->elements = nullptr;
		
		BOOST_LOG_TRIVIAL(info) << "Désallocation de la carte reussi.";
	}
	else
	{
		BOOST_LOG_TRIVIAL(error) << "Erreur allocation des éléments de la carte.";
		exit (-1);
	}

}
	
/*************************************************************************
*                                 Méthode                                *
*************************************************************************/

void Carte::remplirHasard ()
{
	// Initialisation du random
	std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99); 
	
	int terre 	= 0;
	int roche 	= 0;
	int minerai = 0;
	int relief  = 200; // variable se démécrentant à chaque ligne pour creer un relief

	for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
	{
		terre   = (dis(gen) % 100 + 1) + relief;
		roche   = (dis(gen) % 100 + 1) + relief;
		minerai = (dis(gen) % 100 + 1) + relief;

		this->elements[i].setCoord(i % LARGEUR, i / LARGEUR);
		
		if (minerai < 3)
		{
			this->elements[i].detruireElement (this->elements[i].getTypeElement());
			this->elements[i].setTypeElement (BLOCK);
			this->elements[i].setBlock (MINERAI, NON_ROCHE);
		}
		else if (roche < 21)
		{
			RocheType rocheType = (RocheType) (dis(gen) % 100 + 1);

			if (rocheType <= 5) /*---------->*/ rocheType = ROCHE3;
			else if (rocheType <= 30) /*---->*/ rocheType = ROCHE2;
			else if (rocheType <= 100) /*--->*/ rocheType = ROCHE1;

			this->elements[i].detruireElement (this->elements[i].getTypeElement());
			this->elements[i].setTypeElement (BLOCK);
			this->elements[i].setBlock (ROCHE, rocheType);
		}
		else if (terre <= 100)
		{
			this->elements[i].detruireElement (this->elements[i].getTypeElement());
			this->elements[i].setTypeElement (BLOCK);
			this->elements[i].setBlock (TERRE, NON_ROCHE);
		}
		else if (this->elements[i].getTypeElement() == ENTITEE) // ne rien faire
            BOOST_LOG_TRIVIAL(debug) << "Entitée, ne rien faire.";
		if (relief > 0 && i % LARGEUR == 0)
        {
            relief -= 25;
        }
	}

    BOOST_LOG_TRIVIAL(debug) << "Carte remplie.";
}

void Carte::creerCaverne (int pos, int randMoins)
{
    if (pos < 0 || pos > LARGEUR * HAUTEUR)
    {
        BOOST_LOG_TRIVIAL(error) << "Erreur : la position est en dehors de la carte.";
        return;
    }
    
	std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99); 

    while (pos > LARGEUR * HAUTEUR || this->elements[pos].getTypeElement() != BLOCK)
    {
        pos = dis(gen) % LARGEUR * HAUTEUR + 280;
    }
    
	if (this->elements[pos].getTypeElement() == BLOCK)
	{
		int droite = dis(gen) % 100 - randMoins;
		while (droite < 0) /*--->*/ droite = dis(gen) % 100 - randMoins;
		
		int bas    = dis(gen) % 100 - randMoins;
		while (bas < 0) /*------>*/ bas = dis(gen) % 100 - randMoins;

		int gauche = dis(gen) % 100 - randMoins;
		while (gauche < 0) /*--->*/ gauche = dis(gen) % 100 - randMoins;

		int haut   = dis(gen) % 100 - randMoins;
		while (haut < 0) /*----->*/ haut = dis(gen) % 100 - randMoins;

		this->elements[pos].detruireElement (BLOCK);
		this->elements[pos].setTypeElement (VIDE);
		if (this->elements[pos].getVide())
        {
            BOOST_LOG_TRIVIAL(info) << "Vide déjà alloué.";
        }
        else
        {
            this->elements[pos].creerVide();
        }
        

		randMoins += 5;

		if (droite > 30 && (pos + 1) < LARGEUR * HAUTEUR && (pos % LARGEUR) != (LARGEUR - 1))
        {
            if (this->elements[pos + 1].getTypeElement() == BLOCK) creerCaverne(pos + 1, randMoins);
        }
        if (haut > 30 && (pos + LARGEUR) < LARGEUR * HAUTEUR)
        {
            if (this->elements[pos + LARGEUR].getTypeElement() == BLOCK) creerCaverne(pos + LARGEUR, randMoins);
        }
        if (gauche > 30 && (pos - 1) >= 0 && (pos % LARGEUR) != 0)
        {
            if (this->elements[pos - 1].getTypeElement() == BLOCK) creerCaverne(pos - 1, randMoins);
        }
        if (bas > 30 && (pos - LARGEUR) >= 0)
        {
            if (this->elements[pos - LARGEUR].getTypeElement() == BLOCK) creerCaverne(pos - LARGEUR, randMoins);
        }
	}
}

void Carte::creerEnnemie (int nbEnnemie)
{
    BOOST_LOG_TRIVIAL(debug) << "Création des ennemies.";

    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, LARGEUR * HAUTEUR); 

	int pos = 0;

	for (int i = 0; i < nbEnnemie; i++)
	{
		while (elements[pos].getTypeElement() != VIDE || pos < 350)
        {
            pos = dis(gen);
        }
		elements[pos].setTypeElement(ENTITEE);
		elements[pos].setEntitee(CREEPER_EMETTEUR, setCoordEntiteeCallback);
		elements[pos].getEntitee()->setId(i);
	}
}

void Carte::afficherCarte () const
{
	cout << "Nom de la carte : " << nomDeLaCarte << endl;

    cout << *(Vaisseau*) elements[LARGEUR * 2 + LARGEUR / 2].getEntitee() << endl;

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
                                            case NON_ROCHE: cout << " "; break;
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
                                    case NON_ENTITEE: cout << " "; break;
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

void Carte::afficherAdresse (unsigned int x, unsigned int y) const
{
	cout << "L'adresse de l'élément est : " << &elements[LARGEUR * y + x] << endl;
}

////////////
// Getter //
////////////

unsigned int Carte::getDimX ()
{
	return dimX;
}

unsigned int Carte::getDimY ()
{
	return dimY;
}

Case* Carte::getElement (unsigned int x, unsigned int y)
{
	return &elements[LARGEUR * y + x];
}

const char* Carte::getNomDeLaCarte ()
{
	return nomDeLaCarte;
}

////////////
// Setter //
////////////


void Carte::setNomDeLaCarte (const char* nomDeLaCarte)
{
	this->nomDeLaCarte = nomDeLaCarte;
}

void Carte::setSetCoordEntiteeCallback (std::function<void(const Coord&)> setCoordEntiteeCallback)
{
    this->setCoordEntiteeCallback = setCoordEntiteeCallback;

    // Définir le callback du curseur
    elements[LARGEUR * 3 + LARGEUR / 2].getCurseur()->setSetCoordEntiteeCallback(setCoordEntiteeCallback);
}

void Carte::setSetCoordBlockCasseCallback (std::function<void(const Coord&)> setCoordBlockCasseCallback)
{
    this->setCoordBlockCasseCallback = setCoordBlockCasseCallback;

    // Définir le callback du curseur
    elements[LARGEUR * 3 + LARGEUR / 2].getCurseur()->setSetCoordBlockCasseCallback(setCoordBlockCasseCallback);
}
