/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : phare.cpp                             */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../../headers/entitee/phare.h"

Phare::Phare()
{
    portee           = 6 ;
    energieQuantitee = 0 ;
    energieMax       = 20 ;
    
    this->vie        = 5 ;
}

Phare::~Phare()
{

}