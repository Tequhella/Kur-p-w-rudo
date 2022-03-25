﻿/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : curseur.cpp                           */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/curseur.h"

/**
 * Le constructeur de la classe Curseur crée un nouvel objet Curseur et initialise sa variable membre
 * coord à la valeur de l'objet Coord {LARGEUR / 2, 3}
 */
Curseur::Curseur()
{
	coord((Coord) { LARGEUR / 2, 3 });
}

Curseur::~Curseur(){}

/**
 * Renvoie les coordonnées du curseur
 * 
 * @return Les coordonnées du curseur.
 */
Coord Curseur::getCoord()
{
	return coord;
}

/**
 * Définit la coordonnée du curseur sur la coordonnée donnée.
 * 
 * @param coord La coordonnée du curseur.
 */
void Curseur::setCoord(Coord coord)
{
	this->coord = coord;
}
