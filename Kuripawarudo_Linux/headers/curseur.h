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

		/**
		 * @brief Constructeur de la classe Curseur.
		 * 
		 */
		Curseur();
		
		/**
		 * @brief Constructeur de la classe Curseur.
		 * 
		 * @param coord Les coordonnées du curseur.
		 */
		Curseur(Coord coord);

		/**
		 * @brief Destructeur de la classe Curseur.
		 * 
		 */
		~Curseur();

	/*************************************************************************
	*                                 Méthode                                *
	*************************************************************************/

		/**
		 * @brief deplacement, déplace le curseur.
		 * 
		 * @param touche La touche appuyée.
		 * @return bool true si le curseur a été déplacé, false sinon.
		 */
		bool deplacement(char* touche);

		/**
		 * @brief action, effectue une action.
		 * 
		 * @param touche La touche appuyée.
		 * @param carte La carte où se trouve le curseur.
		 * @return true si l'action a été effectuée, false sinon.
         */
        bool action(char* touche, Carte* carte);

		////////////
		// Getter //
		////////////

		/**
		 * @brief getCoord, récupère les coordonnées du curseur.
		 * 
		 * @return Coord* Les coordonnées du curseur.
		 */
		Coord& getCoord();

		////////////
		// Setter //
		////////////

		/**
		 * @brief setCoord, modifie les coordonnées du curseur.
		 * 
		 * @param coord Les nouvelles coordonnées du curseur.
		 */
		void setCoord(Coord coord);

	private:
		
		Coord coord;
};

#endif
