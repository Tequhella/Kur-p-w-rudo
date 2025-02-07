/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : entitee.cpp                           */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/entitee.h"

/*************************************************************************
*                       Constructeur & Destructeur                       *
*************************************************************************/

Entitee::Entitee(TypeEntitee type, const Coord& coord) 
    : type(type), coord(coord), id(0), constr(0.0), vie(0) {}

Entitee::Entitee() 
    : type(TypeEntitee::NON_ENTITEE), coord(), id(0), constr(0.0), vie(0) {}

Entitee::~Entitee() {}

/*************************************************************************
*                                 Méthode                                *
*************************************************************************/

////////////
// Getter //
////////////

TypeEntitee Entitee::getType() const
{
    return type;
}

double Entitee::getConstr() const
{
    return constr;
}

////////////
// Setter //
////////////

void Entitee::setType(TypeEntitee type)
{
    this->type = type;
}

void Entitee::setId(unsigned int id)
{
    this->id = id;
}

void Entitee::setConstr(double constr)
{
    this->constr = constr;
}

void Entitee::decConstr(double dec)
{
    this->constr -= dec;
}
