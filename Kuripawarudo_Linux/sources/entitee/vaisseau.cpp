/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : vaisseau.cpp                          */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../../headers/entitee/vaisseau.h"

Vaisseau::Vaisseau() : energieQuantitee(0),
                       energieReserve(20),
                       energieEfficacitee(1),
                       mineraiQuantitee(0),
                       mineraiReserve(20),
                       mineraiEfficacitee(0),
                       portee(6)
{
    this->id = 0;
    this->vie = 255 ;
}

Vaisseau::~Vaisseau()
{

}