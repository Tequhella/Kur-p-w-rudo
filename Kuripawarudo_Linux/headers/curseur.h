/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : curseur.h                             */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_CURSEUR
#define DEF_CURSEUR

#include "type.h"

/* La classe Curseur est une classe qui représente un curseur */
class Curseur
{
	public:
		
	/*************************************************************************
	*                       Constructeur & Destructeur                       *
	*************************************************************************/

		/*
		* Constructeur de la classe Curseur.
		*/
		Curseur();

		/*
		* Destructeur de la classe Curseur.
		*/
		~Curseur();

	/*************************************************************************
	*                                 Méthode                                *
	*************************************************************************/

		/*
		* Méthode deplacement, déplace le curseur.
		*/
		void deplacement();

		////////////
		// Getter //
		////////////

		// Getter getCoord, récupère les coordonnées du curseur.
		Coord getCoord();

		////////////
		// Setter //
		////////////

		// Setter setCoord, met à jour les coordonnées du curseur.
		void setCoord(Coord coord);

	private:
		
		Coord coord;
};

#endif
