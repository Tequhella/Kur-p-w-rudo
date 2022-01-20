/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : mineur.cpp                            */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../../headers/entitee/mineur.h"

Mineur::Mineur()
{
    energieMax       = 20 ;
    energieQuantitee = 0 ;

    this->vie = 10 ;
}

Mineur::~Mineur()
{

}