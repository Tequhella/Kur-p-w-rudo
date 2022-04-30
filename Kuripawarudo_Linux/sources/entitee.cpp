/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : entitee.cpp                           */
/* Numéro de version : 0.3.6                                 */
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
Entitee::Entitee(uint8_t type, Coord* coord) : type(type), coord(*coord), constr(0), vie(0) {}

Entitee::Entitee() : type(0), coord(0, 0), constr(0), vie(0) {}

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

/**
 * @brief Méthode setConstr, définit le nombre de points de construction de l'entité.
 * 
 * @param constr Le nombre de points de construction de l'entité.
 */
void Entitee::setConstr(double constr)
{
	this->constr = constr;
}

/**
 * @brief Méthode decConstr, décrémente les points de construction de l'entitée.
 *
 * @param dec Nombre de points de construction à décrémenter.
 */
void Entitee::decConstr(double dec)
{
	this->constr -= dec;
}
