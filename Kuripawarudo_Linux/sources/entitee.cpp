/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : entitee.cpp                           */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/entitee.h"

/*************************************************************************
*                       Constructeur & Destructeur                       *
*************************************************************************/

Entitee::Entitee(unsigned int type, Coord* coord)
{
    this->type  = type ;
    this->coord = *coord;
}

Entitee::Entitee()
{

}

Entitee::~Entitee()
{
    
}

/*************************************************************************
*                                 Méthode                                *
*************************************************************************/

////////////
// Getter //
////////////

unsigned int Entitee::getType()
{
    return type ;
}

double Entitee::getConstr()
{
    return constr ;
}


////////////
// Setter //
////////////

void Entitee::setType(unsigned int type)
{
    this->type = type ;
}

void Entitee::setId(unsigned int id)
{
    this->id = id;
}
