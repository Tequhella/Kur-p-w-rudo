/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : carte.h                               */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_CARTE
#define DEF_CARTE

#include "type.h"
#include <thread>

using namespace std ;

class Case;
class Entitee;

/* La classe Carte est une classe qui contient une grille d'objets Case */
class Carte
{
    public:
    
    /*************************************************************************
    *                       Constructeur & Destructeur                       *
    *************************************************************************/

        /*
        * Constructeur de la classe Carte.
        */
        Carte (int dimX, int dimY, const char* nomDeLaCarte) ;
        
        /*
        * Destructeur de la classe Carte.
        */
        ~Carte () ;

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        /*
        * Méthode rempliHasard, se contente de remplir une carte de façon aléatoire.
        * Elle place tout type de block et créer des relief à la surface.
        */
        void remplirHasard () ;

        /*
        * Méthode creerCaverne, détruit des blocks dans une carte déjà remplie de façon récursive.
        */
        void creerCaverne (int pos, int randMoins) ;

        /*
        * Méthode creerEnnemie, ajoute des émetteurs de creeper dans les cavernes.
        */
        void creerEnnemie (int nbEnnemie) ;

        /*
        * Méthode afficherCarte, affiche la carte dans la console.
        */
        void afficherCarte () const ;

		/**
         * @brief Méthode afficherAdresse, affiche l'adresse de l'élément de la carte.
         * 
         * @param pos
         */
		void afficherAdresse (unsigned int x, unsigned int y) const;
		
        /**
         * @brief Méthode gestionConstruction, décrémente les points de construction des entitée.
         */
        void gestionConstruction();

		/**
		 * @brief Méthode gestionCasseBlock, décrémente les points de durabilité des blocks.
		 */
		void gestionCasseBlock();

        ////////////
        // Getter //
        ////////////

        /**
         * @brief Méthode getDimX, récupère la dimenion X de la carte.
         */
        unsigned int getDimX () ;

        /**
         * @brief Méthode getDimY, récupère la dimenion Y de la carte.
         */
        unsigned int getDimY () ;
        
        /**
         * @brief Méthode getElement, récupère l'élément de la carte à la position donnée.
         */
        Case* getElement (unsigned int x, unsigned int y) ;
		
		/**
		 * @Méthode getCoordEntiteeConstr, récupère le tableau de coordonnée d'entitée en construction.
		 * 
		 * @return un tableau de coordonnée.
		 */
		vector<Coord>* getCoordEntiteeConstr() ;

		/**
		 * @brief getCoordBlockCasse, récupère le tableau de coordonnée de blocks à casser.
		 * 
		 * @return un tableau de coordonnée.
		 */
		vector<Coord>* getCoordBlockCasse() ;

        /**
         * @brief Méthode getNomDeLaCarte, récupère le nom de la carte.
         */
        const char* getNomDeLaCarte () ;

        ////////////
        // Setter //
        ////////////

		/**
		 * @brief Méthode setNomDeLaCarte, modifie le nom de la carte.
		 * 
		 * @param nomDeLaCarte le nouveau nom de la carte.
		 */
		void setNomDeLaCarte (const char* nomDeLaCarte) ;
		
		/**
		 * @brief Méthode setCoordEntiteeConstr, modifie le tableau de coordonnée d'entitée en construction.
		 * 
		 * @param coord la nouvelle coordonnée.
		 */
		void setCoordEntiteeConstr(Coord coord) ;

		/**
		 * @brief Méthode setCoordBlockCasse, modifie le tableau de coordonnée de block à casser.
		 * 
		 * @param coord la nouvelle coordonnée.
		 */
		void setCoordBlockCasse(Coord coord) ;
		
		////////////
		// Thread //
		////////////

		/**
		 * @brief Méthode threadConstruction, crée un thread pour la gestion de la construction.
		 */
		void threadConstruction() ;

    private:

        /***********************
        * Liste des propriétés *
        ***********************/

        unsigned int   dimX, dimY ;
        Case*          elements ;          // Propriété elements : tableau des éléments de la carte.
        vector<Coord>* coordEntiteeConstr; // Propriété coordEntiteeConstr : tableau des coordonnées des entitées en construction.
        vector<Coord>* coordBlockCasse;    // Propriété coordBlockCasse : tableau des coordonnées des blocks à casser.
		uint8_t 	   nbEntiteeConstr;    // Propriété nbEntiteeConstr : nombre d'entitées en construction.
		uint8_t 	   nbBlockCasse;       // Propriété nbBlockCasse : nombre de blocks à casser.
        const char*    nomDeLaCarte ;
} ;

#endif