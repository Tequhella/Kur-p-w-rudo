/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : curseur.cpp                           */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/curseur.h"

Curseur::Curseur(){}

Curseur::Curseur(Coord coord) : coord(coord) {}

Curseur::~Curseur(){}

Coord& Curseur::getCoord()
{
	return coord;
}

void Curseur::setCoord(Coord coord)
{
	this->coord = coord;
}

bool Curseur::deplacement(char* touche)
{
	switch(*touche)
	{
		case 'w': if (coord.y > 0) /*------------->*/ coord.y--; break;
		case 's': if (coord.y < HAUTEUR - 1) /*--->*/ coord.y++; break;
		case 'a': if (coord.x > 0) /*------------->*/ coord.x--; break;
		case 'd': if (coord.x < LARGEUR - 1) /*--->*/ coord.x++; break;
		default: return false; break;
	}
	return true;
}

bool Curseur::action(char* touche, Carte* carte)
{
	
	// Les variables contenant la case d'élément où l'action se fait et celles autours
	Case* element = carte->getElement(coord.x, coord.y);
	Case* element_haut = carte->getElement(coord.x, coord.y - 1);
	Case* element_bas = carte->getElement(coord.x, coord.y + 1);
	Case* element_gauche = carte->getElement(coord.x - 1, coord.y);
	Case* element_droite = carte->getElement(coord.x + 1, coord.y);
	
	
	switch(*touche)
	{
		case 'c': return true; break;
		case 'f': 
			if (element->getTypeElement() == BLOCK)
			{
				carte->setCoordBlockCasse(this->coord);
			}
			else /*--->*/ cout << "Vous ne pouvez pas casser de bloc !" << endl;
			return true;
			break;
		case '1':
			if (!(element->getEntitee()))
			{
				if (element_bas->getTypeElement() == BLOCK && element->getTypeElement() == VIDE)
				{
					element->setEntitee(REACTEUR, carte);
					element->setTypeElement(ENTITEE);
				}
				else /*--->*/ cout << "Impossible de placer un réacteur ici." << endl;
			}
			else /*------->*/ cout << "Il y a déjà une entitée ici !" << endl;
			return true;
			break;
		case '2':
			if (!(element->getEntitee()))
			{
				if (element_bas->getTypeElement() == BLOCK && element->getTypeElement() == VIDE)
				{
					element->setEntitee(MINEUR, carte);
					element->setTypeElement(ENTITEE);
				}
				else /*--->*/ cout << "Impossible de placer un mineur ici." << endl;
			}
			else /*------->*/ cout << "Il y a déjà une entitée ici !" << endl;
			break;
		case '3':
			if (!(element->getEntitee()))
			{
				if (element->getTypeElement() == VIDE)
				{
					element->setEntitee(BOUCLIER, carte);
					element->setTypeElement(ENTITEE);
				}
				else /*--->*/ cout << "Impossible de placer un bouclier ici." << endl;
			}
			else /*------->*/ cout << "Il y a déjà une entitée ici !" << endl;
			return true;
			break;
		case '4':
			if (!(element->getEntitee()))
			{
				if ((element_bas->getTypeElement() == BLOCK    ||
					element_haut->getTypeElement() == BLOCK	   ||
					element_droite->getTypeElement() == BLOCK  ||
					element_gauche->getTypeElement() == BLOCK) &&
					element->getTypeElement() == VIDE)
				{
					element->setEntitee(PHARE, carte);
					element->setTypeElement(ENTITEE);
				}
				else /*--->*/ cout << "Impossible de placer un phare ici." << endl;
			}
			else /*------->*/ cout << "Il y a déjà une entitée ici !" << endl;
			return true;
			break;
		case '5':
			if (!(element->getEntitee()))
			{
				if (element->getTypeElement() == VIDE)
				{
					element->setEntitee(BOMBE, carte);
					element->setTypeElement(ENTITEE);
				}
				else /*--->*/ cout << "Impossible de placer une bombe ici." << endl;
			}
			else /*------->*/ cout << "Il y a déjà une entitée ici !" << endl;
			return true;
			break;
		default: return false; break;
	}
	
	return true;
}