/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : vaisseau.cpp                          */
/* Numéro de version : 0.3                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../../headers/entitee/vaisseau.h"

Vaisseau::Vaisseau()
{
    this->id = 0;
    energieReserve     = 20 ;
    energieQuantitee   = energieReserve ;
    energieEfficacitee = 1 ;
    
    mineraiEfficacitee = 0 ;
    mineraiReserve     = 20 ;
    mineraiQuantitee   = 0 ;

    portee = 6 ;

    this->vie = 200 ;
}

Vaisseau::~Vaisseau()
{

}