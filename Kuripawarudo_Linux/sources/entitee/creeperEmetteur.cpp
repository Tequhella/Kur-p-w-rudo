/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : creeperEmetteur.cpp                   */
/* Numéro de version : 0.3.4                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../../headers/entitee/creeperEmetteur.h"

CreeperEmetteur::CreeperEmetteur() : frequence(1), puissance(100)
{
	this->constr = 0 ;
    this->vie = 1 ;
}

CreeperEmetteur::~CreeperEmetteur()
{

}