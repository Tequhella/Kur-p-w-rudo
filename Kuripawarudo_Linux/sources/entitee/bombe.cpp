/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : bombe.cpp                             */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../../headers/entitee/bombe.h"

Bombe::Bombe() : energieQuantitee(0), energieMax(20), degat(100), portee(2)
{
    this->constr = 20 ;
    this->vie = 1 ;
}

Bombe::~Bombe() {}