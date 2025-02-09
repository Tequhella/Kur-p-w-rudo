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
#include <functional>

class Case;
class Entitee;

/* La classe Carte est une classe qui contient une grille d'objets Case */
class Carte
{
    public:
    
    /*************************************************************************
    *                       Constructeur & Destructeur                       *
    *************************************************************************/

        /**
         * Créer un nouvel objet Carte
         * 
         * @param dimX La largeur de la carte.
         * @param dimY La hauteur de la carte.
         * @param nomDeLaCarte Le nom de la carte.
         */
        Carte (int dimX, int dimY, const char* nomDeLaCarte);
        
        /*
        * Destructeur de la classe Carte.
        */
        ~Carte ();

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        /*
        * Méthode rempliHasard, se contente de remplir une carte de façon aléatoire.
        * Elle place tout type de block et créer des relief à la surface.
        */
        void remplirHasard ();

        /*
        * Méthode creerCaverne, détruit des blocks dans une carte déjà remplie de façon récursive.
        */
        void creerCaverne (int pos, int randMoins);

        /*
        * Méthode creerEnnemie, ajoute des émetteurs de creeper dans les cavernes.
        */
        void creerEnnemie (int nbEnnemie);

        /*
        * Méthode afficherCarte, affiche la carte dans la console.
        */
        void afficherCarte () const;

		/**
         * @brief Méthode afficherAdresse, affiche l'adresse de l'élément de la carte.
         * 
         * @param pos
         */
		void afficherAdresse (unsigned int x, unsigned int y) const;

        ////////////
        // Getter //
        ////////////

        /**
         * @brief Méthode getDimX, récupère la dimenion X de la carte.
         */
        unsigned int getDimX ();

        /**
         * @brief Méthode getDimY, récupère la dimenion Y de la carte.
         */
        unsigned int getDimY ();
        
        /**
         * @brief Méthode getElement, récupère l'élément de la carte à la position donnée.
         */
        Case* getElement (unsigned int x, unsigned int y);

        /**
         * @brief Méthode getNomDeLaCarte, récupère le nom de la carte.
         */
        const char* getNomDeLaCarte ();

        ////////////
        // Setter //
        ////////////

		/**
		 * @brief Méthode setNomDeLaCarte, modifie le nom de la carte.
		 * 
		 * @param nomDeLaCarte le nouveau nom de la carte.
		 */
		void setNomDeLaCarte (const char* nomDeLaCarte);

        /**
         * @brief Méthode setCoordEntiteeCallback, modifie la fonction de callback pour les coordonnées.
         * 
         * @param setCoordEntiteeCallback la nouvelle fonction de callback pour les coordonnées.
         */
        void setSetCoordEntiteeCallback (std::function<void(const Coord&)> setCoordEntiteeCallback);

        /**
         * @brief Méthode setCoordBlockCasseCallback, modifie la fonction de callback pour les coordonnées.
         * 
         * @param setCoordBlockCasseCallback la nouvelle fonction de callback pour les coordonnées.
         */
        void setSetCoordBlockCasseCallback (std::function<void(const Coord&)> setCoordBlockCasseCallback);
		
		////////////
		// Thread //
		////////////

    private:

        /***********************
        * Liste des propriétés *
        ***********************/

        unsigned int   dimX, dimY;
        Case*          elements;          // Propriété elements : tableau des éléments de la carte.
        const char*    nomDeLaCarte;
        std::function<void(const Coord&)> setCoordEntiteeCallback; // Propriété setCoordEntiteeCallback : fonction de callback pour les coordonnées.
        std::function<void(const Coord&)> setCoordBlockCasseCallback; // Propriété setCoordBlockCasseCallback : fonction de callback pour les coordonnées.
};

#endif