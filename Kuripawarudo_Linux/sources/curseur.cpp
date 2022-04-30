/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : curseur.cpp                           */
/* Numéro de version : 0.3.6                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/curseur.h"

Curseur::Curseur(){}

/**
 * @brief Le constructeur de la classe Curseur crée un nouvel objet Curseur et initialise sa variable membre coord à la valeur de l'objet Coord {LARGEUR / 2, 3}.
 */
Curseur::Curseur(Coord coord) : coord(coord) {}

Curseur::~Curseur(){}

/**
 * @brief Renvoie les coordonnées du curseur
 * 
 * @return Les coordonnées du curseur.
 */
Coord* Curseur::getCoord()
{
	return &coord;
}

/**
 * @brief Définit la coordonnée du curseur sur la coordonnée donnée.
 * 
 * @param coord La coordonnée du curseur.
 */
void Curseur::setCoord(Coord coord)
{
	this->coord = coord;
}

/**
 * @brief Déplace le curseur en fonction de la touche appuyée et la limite de carte.
 * 
 * @param touche La touche appuyée.
 * 
 * @return Renvoie 1 si le curseur a été déplacé, 0 sinon.
 */
uint8_t Curseur::deplacement(char* touche)
{
	uint8_t ret;
	switch(*touche)
	{
		case 'w': if (coord.y > 0) /*------------->*/ coord.y--; ret = 1; break;
		case 's': if (coord.y < HAUTEUR - 1) /*--->*/ coord.y++; ret = 1; break;
		case 'a': if (coord.x > 0) /*------------->*/ coord.x--; ret = 1; break;
		case 'd': if (coord.x < LARGEUR - 1) /*--->*/ coord.x++; ret = 1; break;
		default: ret = 0; break;
	}
	return ret;
}

/**
 * @brief Place une structure en fonction de la touche appuyée.
 * 
 * @param touche La touche appuyée.
 * @param element La case d'élément où l'action se fait.
 * 
 * @return Renvoie 1 si l'action a été effectuée, 0 sinon.
 */
uint8_t Curseur::action(char* touche, Carte* carte)
{
	uint8_t ret;
	
	// Les variables contenant la case d'élément où l'action se fait et celles autours
	Case* element = carte->getElement(coord.x, coord.y);
	Case* element_haut = carte->getElement(coord.x, coord.y - 1);
	Case* element_bas = carte->getElement(coord.x, coord.y + 1);
	Case* element_gauche = carte->getElement(coord.x - 1, coord.y);
	Case* element_droite = carte->getElement(coord.x + 1, coord.y);
	
	
	switch(*touche)
	{
		case 'c': ret = 1; break;
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
			ret = 1;
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
			ret = 1;
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
			ret = 1;
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
			ret = 1;
			break;
		default: ret = 0; break;
	}
	
	return ret;
}