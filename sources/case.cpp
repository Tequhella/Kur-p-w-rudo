/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : case.cpp                              */
/* Numéro de version : 0.2                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 23/10/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/case.h"

Case::Case ()
{

}

Case::~Case ()
{
    
}

/*************************************************************************
*                                 Méthode                                *
*************************************************************************/

////////////
// Getter //
////////////
unsigned int Case::getTypeElement ()
{
    return type ;
}

Block* Case::getBlock ()
{
    return &block ;
}

Case::Coord Case::getCoord ()
{
    return pos ;
}

////////////
// Setter //
////////////
void Case::setTypeElement (unsigned int type)
{
    this->type = type ;
}

void Case::setBlock (unsigned int type, unsigned int typeStone)
{
    block = Block (type, typeStone) ;
}

void Case::setPos (unsigned int x, unsigned int y)
{
    pos = (Coord) {(double) x, (double) y} ;
}