/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : case.cpp                              */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/case.h"
#include "../headers/entitee.h"
#include "../headers/vide.h"
#include "../headers/block.h"
#include "../headers/curseur.h"

/**
 * Le constructeur initialise l'objet Case
 */
Case::Case ()
{
	block   = nullptr ;
	entitee = nullptr ;
	vide    = nullptr ;
	curseur = nullptr ;
}

Case::~Case(){}

/*************************************************************************
*                                 Méthode                                *
*************************************************************************/


/**
 * * Si l'élément est un bloc, le supprime.
 * * Si l'élément est une entitée, le supprime ainsi que son élément vide associé.
 * * Si l'élément est un curseur, le supprime ainsi que son élément vide associé.
 * * Si l'élément est un élément vide, le supprime
 * 
 * @param type le type d'élément à supprimer.
 */
void Case::detruireElement (uint8_t type)
{
	switch (type)
	{
		case VIDE:
			if (vide)
			{
				delete vide ;
				vide  = nullptr ;
			}
			else /*--------->*/ cerr << "Erreur : l'élément vide n'existe pas." << endl ;
			break ;
		case BLOCK:
			if (block)
			{
				delete block ;
				block = nullptr ;
			}
			else /*--------->*/ cerr << "Erreur : l'élément block n'existe pas." << endl ;
			break ;
		case ENTITEE:
			if (entitee)
			{
				delete entitee ;
				entitee = nullptr ;
			}
			else /*--->*/ cerr << "Erreur : l'entité n'existe pas." << endl ;

			if (vide)
			{
				delete vide ;
				vide = nullptr ;
			}
			else /*--->*/ cerr << "Erreur : l'entité n'a pas d'élément vide associé." << endl ;
			break ;
		case CURSEUR:
			if (curseur)
			{
				delete curseur ;
				curseur = nullptr ;
			}
			else /*--->*/ cerr << "Erreur : le curseur n'existe pas." << endl ;

			if (vide)
			{
				delete vide ;
				vide = nullptr ;
			}
			else /*--->*/ cerr << "Erreur : le curseur n'a pas d'élément vide associé." << endl ;
			break;
	}
}

////////////
// Getter //
////////////

/**
 * Renvoyer le type de case
 * 
 * @return Le type de l'élément.
 */
uint8_t Case::getTypeElement()
{
	return type ;
}

/**
 * Renvoie la valeur du membre privée vide
 * 
 * @return La valeur de la variable vide.
 */
Vide* Case::getVide()
{
	return vide ;
}

/**
 * Retourne le bloc de la case
 * 
 * @return Le bloc de la case actuelle.
 */
Block* Case::getBlock()
{
	return block ;
}

/**
 * Renvoye l'entitée.
 * 
 * @return L'entitée de la case.
 */
Entitee* Case::getEntitee()
{
	return entitee ;
}

/**
 * Retourne le curseur.
 * 
 * @return Le curseur de la case.
 */
Curseur* Case::getCurseur()
{
	return curseur ;
}

/**
 * Renvoie la coordonnée du cas
 * 
 * @return coord
 */
Coord* Case::getCoord()
{
	return &coord ;
}

////////////
// Setter //
////////////

/**
 * Définit le type de la case
 * 
 * @param type Le type de case.
 */
void Case::setTypeElement (uint8_t type)
{
	this->type = type ;
}

/**
 * Crée une nouvelle case vide
 */
void Case::creerVide()
{
	vide = new Vide() ;
	if (!vide)
	{
		cerr << "Erreur allocation de l'objet vide." << endl ;
		exit (-1) ;
	}
	
}

 /**
  * Si l'objet est un Coord, alors il crée un nouvel objet Curseur et le stock dans le champ curseur. Si
  * l'objet est un Curseur, alors il le stock dans le champ curseur. Si l'objet est nullptr, définissez
  * le champ du curseur sur nullptr. Sinon, imprimez un message d'erreur et quittez le programme
  *
  * @param object l'objet à définir comme nouveau curseur.
  */
void Case::setCurseur(Base* object)
{
	if (instanceof<Coord>(object))
	{
		Coord* coord = (Coord*) object ;
		curseur = new Curseur(coord) ;
		if (!curseur)
		{
			cerr << "Erreur allocation de l'objet curseur." << endl ;
			exit (-1) ;
		}
	}
	else if (instanceof<Curseur>(object))
	{
		curseur = (Curseur*) object ;
		if (!curseur)
		{
			cerr << "Erreur allocation de l'objet curseur." << endl;
			exit(-1);
		}
	}
	else if (object == nullptr) /*--->*/ curseur = nullptr;
	else
	{
		cerr << "Erreur : l'objet n'est pas une coordonnée ou un objet Curseur." << endl ;
		exit (-1) ;
	}
}

/**
 * Crée un nouvel objet Block et l'affecte à la variable de bloc
 * 
 * @param type le type de bloc (1 = terre, 2 = roche, 3 = minerai)
 * @param typeStone le type de pierre qui est utilisé pour construire le bloc.
 */
void Case::setBlock (uint8_t type, uint8_t typeStone)
{
	block = new Block (type, typeStone) ;
	if (!block)
	{
		cerr << "Erreur allocation de l'objet block." << endl ;
		exit (-1) ;
	}
}

/**
 * Il définit le type d'entité de la case.
 * 
 * @param type Le type de l'entité.
 */
void Case::setEntitee (uint8_t type)
{
	switch (type)
	{
		case VAISSEAU        : entitee = new Vaisseau()        ; break ;
		case REACTEUR        : entitee = new Reacteur()        ; break ;
		case MINEUR          : entitee = new Mineur()          ; break ;
		case BOUCLIER        : entitee = new Bouclier()        ; break ;
		case PHARE           : entitee = new Phare()           ; break ;
		case BOMBE           : entitee = new Bombe()           ; break ;
		case CREEPER_EMETTEUR: entitee = new CreeperEmetteur() ; break ;
	}

	entitee->setType(type) ;
	if (!entitee)
	{
		cerr << "Erreur allocation de l'objet entitee." << endl ;
		exit (-1) ;
	}
}

/**
 * Définit les coordonnées de la case
 * 
 * @param x La coordonnée x de la case.
 * @param y La coordonnée y de la case.
 */
void Case::setCoord (double x, double y)
{
	coord = Coord(x, y);
}