/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : case.cpp                              */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/case.h"
#include "../headers/entitee.h"
#include "../headers/vide.h"
#include "../headers/block.h"
#include "../headers/curseur.h"
#include "case.h"

Case::Case () : vide(nullptr), block(nullptr), curseur(nullptr), entitee(nullptr) {}

Case::~Case(){}

/*************************************************************************
*                                 Méthode                                *
*************************************************************************/


void Case::detruireElement (TypeElement type)
{
	switch (type)
	{
		case VIDE:
			if (curseur)
			{
				delete curseur;
				curseur = nullptr;
			}
			if (vide)
			{
				delete vide;
				vide  = nullptr;
			}
			else /*--------->*/ BOOST_LOG_TRIVIAL(error) << "Erreur : l'élément vide n'existe pas.";
			break;
		case BLOCK:
			if (curseur)
			{
				delete curseur;
				curseur = nullptr;
			}
			if (block)
			{
				delete block;
				block = nullptr;
			}
			else /*--------->*/ BOOST_LOG_TRIVIAL(error) << "Erreur : l'élément block n'existe pas.";
			break;
		case ENTITEE:
			if (curseur)
			{
				delete curseur;
				curseur = nullptr;
			}
			if (entitee)
			{
                BOOST_LOG_TRIVIAL(info) << "Entitée " << entitee->getType() << " détruite.";
                delete entitee;
				entitee = nullptr;
			}
			else /*--->*/ BOOST_LOG_TRIVIAL(error) << "Erreur : l'entité n'existe pas.";

			if (vide)
			{
				delete vide;
				vide = nullptr;
			}
			else /*--->*/ BOOST_LOG_TRIVIAL(error) << "Erreur : l'entité n'a pas d'élément vide associé.";
			break;
		case CURSEUR:
			if (entitee)
			{
				delete entitee;
				entitee = nullptr;
			}
			if (curseur)
			{
				delete curseur;
				curseur = nullptr;
			}
			else /*--->*/ BOOST_LOG_TRIVIAL(error) << "Erreur : le curseur n'existe pas.";

			if (vide)
			{
				delete vide;
				vide = nullptr;
			}
			else /*--->*/ BOOST_LOG_TRIVIAL(error) << "Erreur : le curseur n'a pas d'élément vide associé.";
			break;
	}
}

std::ostream &operator<<(std::ostream &os, const Case &c)
{
    if (c.vide) /*--->*/ os << "VIDE";
    else if (c.block) /*--->*/ os << "BLOCK";
    else if (c.entitee) /*--->*/ os << "ENTITEE";
    else if (c.curseur) /*--->*/ os << "CURSEUR";
    else /*--->*/ os << "UNKNOWN";
    return os;
}

////////////
// Getter //
////////////

TypeElement Case::getTypeElement()
{
	return type;
}

Vide* Case::getVide()
{
	return vide;
}

Block* Case::getBlock()
{
	return block;
}

Entitee* Case::getEntitee()
{
	return entitee;
}

Curseur* Case::getCurseur()
{
	return curseur;
}

Coord* Case::getCoord()
{
	return &coord;
}

////////////
// Setter //
////////////

void Case::setTypeElement (TypeElement type)
{
	this->type = type;
}

void Case::creerVide()
{
	if (!vide)
    {
        vide = new Vide();
        if (!vide)
        {
            BOOST_LOG_TRIVIAL(error) << "Erreur allocation de l'objet vide.";
            exit (-1);
        }
    }
}

void Case::setCurseur(Base* object)
{
	if (instanceof<Coord>(object))
	{
		Coord* coord = (Coord*) object;
		curseur = new Curseur(*coord);
		if (!curseur)
		{
			BOOST_LOG_TRIVIAL(error) << "Erreur allocation de l'objet curseur.";
			exit (-1);
		}
	}
	else if (instanceof<Curseur>(object))
	{
		curseur = (Curseur*) object;
		if (!curseur)
		{
			BOOST_LOG_TRIVIAL(error) << "Erreur allocation de l'objet curseur.";
			exit(-1);
		}
	}
	else if (object == nullptr) /*--->*/ curseur = nullptr;
	else
	{
		BOOST_LOG_TRIVIAL(error) << "Erreur : l'objet n'est pas une coordonnée ou un objet Curseur.";
		exit (-1);
	}
}

void Case::setBlock (uint8_t type, RocheType typeStone)
{
	block = new Block (type, typeStone);
	if (!block)
	{
		BOOST_LOG_TRIVIAL(error) << "Erreur allocation de l'objet block.";
		exit (-1);
	}
}

void Case::setEntitee (TypeEntitee type, Carte* carte)
{
	switch (type)
	{
        case NON_ENTITEE:
            entitee = nullptr;
            BOOST_LOG_TRIVIAL(error) << "Erreur : le type d'entitée n'est pas défini." ;
            break;
		case VAISSEAU        : entitee = new Vaisseau()       ; break;
		case REACTEUR		 : entitee = new Reacteur()		  ; carte->setCoordEntiteeConstr(coord); break;
		case MINEUR			 : entitee = new Mineur()		  ; carte->setCoordEntiteeConstr(coord); break;
		case BOUCLIER		 : entitee = new Bouclier()		  ; carte->setCoordEntiteeConstr(coord); break;
		case PHARE			 : entitee = new Phare()		  ; carte->setCoordEntiteeConstr(coord); break;
		case BOMBE			 : entitee = new Bombe()		  ; carte->setCoordEntiteeConstr(coord); break;
		case CREEPER_EMETTEUR: entitee = new CreeperEmetteur(); break;
	}

	entitee->setType(type);
	if (!entitee)
	{
		BOOST_LOG_TRIVIAL(error) << "Erreur allocation de l'objet entitee.";
		exit (-1);
	}

    BOOST_LOG_TRIVIAL(info) << "Entitée " << type << " créée.";
}

void Case::setCoord (double x, double y)
{
	coord = Coord(x, y);
}