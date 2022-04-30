/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : mineur.cpp                            */
/* Numéro de version : 0.3.6                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../../headers/entitee/mineur.h"

Mineur::Mineur() : minageEfficacitee(1), energieQuantitee(0), energieMax(20)
{
	this->constr = 4 ;
    this->vie	 = 10 ;
}

Mineur::~Mineur()
{

}