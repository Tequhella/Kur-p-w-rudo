/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : case.h                                */
/* Numéro de version : 0.3.7                                 */
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

#include <memory>


class Block;
class Vide;
class Entitee;
class Curseur;
class Carte;

/* La classe Case est utilisée pour créer une case dans la carte */
class Case
{
	public:

	/*************************************************************************
	*                       Constructeur & Destructeur                       *
	*************************************************************************/

		/**
		 * @brief Constructeur de la classe Case.
		 * 
		 */
		Case ();

		/**
		 * @brief Destructeur de la classe Case.
		 * 
		 */
		~Case ();

	/*************************************************************************
	*                                 Méthode                                *
	*************************************************************************/

		/**
		 * @brief detruireElement, détruit un élément de la case.
		 * 
         * Si l'élément est un bloc, le supprime.
         * Si l'élément est une entitée, le supprime ainsi que son élément vide associé.
         * Si l'élément est un curseur, le supprime ainsi que son élément vide associé.
         * Si l'élément est un élément vide, le supprime
         * 
		 * @param type Le type de l'élément à détruire.
		 */
		void detruireElement (TypeElement type);

		/**
		 * @brief creerVide, crée un objet vide.
		 * 
		 */
		void creerVide();

		/**
		 * @brief Définit le curseur de la case.
		 * 
         * @param curseur Le curseur à définir.
		 */
		void setCurseur(std::shared_ptr<Curseur> curseur);

        /**
         * @brief Surcharge de l'opérateur de flux de sortie.
         *
         * @param os Le flux de sortie. 
         * @param c La case à afficher.
         * @return std::ostream& Le flux de sortie.
         */
        friend std::ostream& operator<< (std::ostream& os, const Case& c);

		////////////
		// Getter //
		////////////

		/**
		 * @brief getTypeElement, récupère le type de l'élément.
		 * 
		 * @return TypeElement Le type de l'élément.
		 */
		TypeElement getTypeElement();

		/**
		 * @brief getVide, récupère l'objet vide.
		 * 
		 * @return Vide* L'objet vide.
		 */
		Vide* getVide();

		/**
		 * @brief getBlock, récupère l'objet block.
		 * 
		 * @return Block* L'objet block.
		 */
		Block* getBlock();

		/**
		 * @brief getEntitee, récupère l'entitée.
		 * 
		 * @return Entitee* L'entitée.
		 */
		Entitee* getEntitee();

		/**
		 * @brief getCurseur, récupère le curseur.
		 * 
		 * @return Curseur* Le curseur.
		 */
		Curseur* getCurseur();

		/**
		 * @brief getCoord, récupère la coordonnée de la case.
		 * 
		 * @return Coord* La coordonnée de la case.
		 */
		Coord* getCoord();


		////////////
		// Setter //
		////////////

		// Setter setTypeElement, met à jour l'indicateur de type.
		void setTypeElement (TypeElement type);

		// Setter setBlock, met à jour un block.
		void setBlock (uint8_t type, RocheType typeStone);

		/**
		 * Il définit le type d'entité de la case.
		 *
		 * @param type Le type d'entité.
         * @param setCoordCallback Le callback de coordonnée.
		 */
		void setEntitee(TypeEntitee type, std::function<void(const Coord&)> setCoordCallback);

		// Setter setCoord, met à jour les coordonnées.
		void setCoord (double x, double y);

	private:

		TypeElement                 type;
		Vide*                       vide;
		Block*                      block;
		std::shared_ptr<Curseur>	curseur;
		Coord                       coord;

		TypeEntitee*                entiteeType;
		Entitee*                    entitee;
};

#endif