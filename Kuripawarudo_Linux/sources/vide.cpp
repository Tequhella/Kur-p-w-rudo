/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : vide.cpp                              */
/* Numéro de version : 0.3.6                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/vide.h"

/**
 * Le constructeur crée un nouvel objet de type Vide et initialise le tableau creeperQuantity à 0
 */
Vide::Vide() : creeperQuantity{0}
{

}

Vide::~Vide(){}

/**
 * Renvoie le nombre de creepers dans la case
 * 
 * @return Le nombre de creepers dans la case.
 */
int Vide::getCreeperQuantity(uint8_t placement)
{
    return creeperQuantity[placement];
}

/**
 * Définit le nombre de creepers dans la case.
 * 
 * @param creeperQuantity Le nombre de creepers dans la case.
 */
void Vide::setCreeperQuantity(int creeperQuantity, uint8_t placement)
{
    this->creeperQuantity[placement] = creeperQuantity;
}

/**
 * Ajoute un creeper dans la case.
 */
void Vide::addCreeper(int creeperQuantity, uint8_t placement)
{
    this->creeperQuantity[placement] += creeperQuantity;
}