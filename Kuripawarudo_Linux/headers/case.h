/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : case.h                                */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_CASE
#define DEF_CASE

#include "type.h"
#include "entitee/vaisseau.h"
#include "entitee/reacteur.h"
#include "entitee/mineur.h"
#include "entitee/bouclier.h"
#include "entitee/phare.h"
#include "entitee/bombe.h"
#include "entitee/creeperEmetteur.h"


class Block ;
class Vide ;
class Entitee ;
class Curseur;

/* La classe Case est utilisée pour créer une case dans la carte */
class Case
{
	public:

	/*************************************************************************
	*                       Constructeur & Destructeur                       *
	*************************************************************************/

		/*
		* Constructeur de la classe Case.
		*/
		Case () ;

		/*
		* Destructeur de la classe Case.
		*/
		~Case () ;

	/*************************************************************************
	*                                 Méthode                                *
	*************************************************************************/

		/*
		* Méthode detruireElement, permet de détruire l'élément selon le type que c'est.
		*/
		void detruireElement (uint8_t type) ;

		/*
		* Méthode creerVide, crée une case de vide.
		*/
		void creerVide() ;

		/*
		* Méthode creerCurseur, crée un curseur.
		*/
		void creerCurseur(Coord* coord) ;

		////////////
		// Getter //
		////////////

		// Getter getTypeElement, permet de récupérer l'indicateur du type de l'élément.
		uint8_t getTypeElement() ;

		// Getter getVide, récupère la case de vide (ainsi sa quantité de creeper).
		Vide* getVide() ;

		// Getter getBlock, récupère le block de la case.
		Block* getBlock() ;

		// Getter getEntitee, récupère l'entitée de la case.
		Entitee* getEntitee() ;

		// Getter getEntitee, récupère le curseur.
		Curseur* getCurseur() ;

		// Getter getCoord, récupère les coordonnées de la case (x, y) ;
		Coord* getCoord() ;


		////////////
		// Setter //
		////////////

		// Setter setTypeElement, met à jour l'indicateur de type.
		void setTypeElement (uint8_t type) ;

		// Setter setBlock, met à jour un block.
		void setBlock (uint8_t type, uint8_t typeStone) ;

		// Setter setEntitee, met à jour une entitée.
		void setEntitee (uint8_t type) ;

		// Setter setCoord, met à jour les coordonnées.
		void setCoord (double x, double y) ;

	private:

		uint8_t		type ;
		Vide*       vide ;
		Block*      block ;
		Curseur*	curseur;
		Coord       coord ;

		uint8_t*	entiteeType ;
		Entitee*    entitee ;
} ;

#endif