/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : entitee.cpp                           */
/* Numéro de version : 0.3.4                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/entitee.h"

/*************************************************************************
*                       Constructeur & Destructeur                       *
*************************************************************************/

/**
 * Crée un objet Entitee avec un type et des coordonnées donnés
 * 
 * @param type Le type de l'entité. Ceci est utilisé pour identifier l'entité.
 * @param coord Les coordonnées de l'entité.
 */
Entitee::Entitee(uint8_t type, Coord* coord)
{
    this->type   = type;
    this->coord  = *coord;
    this->vie    = 0;
    this->constr = 0;
}

Entitee::Entitee(){}

Entitee::~Entitee(){}

/*************************************************************************
*                                 Méthode                                *
*************************************************************************/

////////////
// Getter //
////////////

/**
 * Renvoie la valeur de la variable de type
 * 
 * @return Le type de l'entité.
 */
uint8_t Entitee::getType()
{
    return type ;
}

/**
 * Renvoie la valeur de la variable constr.
 * 
 * @return La valeur de la variable membre constr.
 */
double Entitee::getConstr()
{
    return constr ;
}


////////////
// Setter //
////////////

/**
 * Définit le type de l'entité
 * 
 * @param type Le type de l'entité.
 */
void Entitee::setType(uint8_t type)
{
    this->type = type ;
}

/**
 * Définit l'identifiant de l'entité
 * 
 * @param id L'identifiant unique de l'entité.
 */
void Entitee::setId(unsigned int id)
{
    this->id = id;
}
