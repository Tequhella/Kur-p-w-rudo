/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : reacteur.cpp                          */
/* Numéro de version : 0.3.4                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../../headers/entitee/reacteur.h"

Reacteur::Reacteur() : emissionEnergie(0.15)
{
    this->constr = 4;
    this->vie = 1 ;
}

Reacteur::~Reacteur()
{

}