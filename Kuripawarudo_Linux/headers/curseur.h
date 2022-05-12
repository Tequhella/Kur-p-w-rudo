/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : curseur.h                             */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_CURSEUR
#define DEF_CURSEUR

#include "type.h"
#include "carte.h"
#include "case.h"

using namespace std;

/* La classe Curseur est une classe qui représente un curseur */
class Curseur : public Base
{
	public:
		
	/*************************************************************************
	*                       Constructeur & Destructeur                       *
	*************************************************************************/

		/* Constructeur */
		Curseur();
		
		/*
		* Constructeur de la classe Curseur.
		*/
		Curseur(Coord coord);

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
		uint8_t deplacement(char* touche);

		/*
		* Méthode action, fait une action de construction.
		*/
		uint8_t action(char* touche, Carte* carte);

		////////////
		// Getter //
		////////////

		// Getter getCoord, récupère les coordonnées du curseur.
		Coord* getCoord();

		////////////
		// Setter //
		////////////

		// Setter setCoord, met à jour les coordonnées du curseur.
		void setCoord(Coord coord);

	private:
		
		Coord coord;
};

#endif
