/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : jeu.h                                 */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 08/02/2025                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_JEU
#define DEF_JEU

#include "carte.h"
#include "vaisseau.h"
#include "curseur.h"
#include "log.h"
#include "vide.h"
#include "block.h"

class Jeu
{
    public:

    /*************************************************************************
     *                      Constructeur & Destructeur                       *
     * ***********************************************************************/

        /**
         * @brief Constructeur de la classe Jeu.
         * 
         * @param carte La carte du jeu.
         */
        Jeu(Carte* carte);

        /**
         * @brief Destructeur de la classe Jeu.
         */
        ~Jeu();

    /*************************************************************************
     *                                Méthode                                *
     * ***********************************************************************/

        /**
         * @brief Méthode bouclePrincipale, permet de gérer la boucle principale du jeu.
         */
        void bouclePrincipale();

        /**
         * @brief Méthode afficherTaille, permet d'afficher la taille de toutes les classes.
         */
        void afficherTaille();

    private:

        /**
         * @brief Méthode afficherCoordonneesCurseur, affiche les coordonnées du curseur.
         * 
         * @param coord Les coordonnées du curseur.
         */
        void afficherCoordonneesCurseur(const Coord& coord) const;

        /**
         * @brief Méthode verifierTypeElement, vérifie le type de l'élément.
         * 
         * @param coord Les coordonnées de l'élément.
         */
        void verifierTypeElement(const Coord& coord);

        /**
         * @brief Méthode deplacerCurseur, déplace le curseur.
         * 
         * @param c La touche pressée.
         */
        void deplacerCurseur(char c);

    /*************************************************************************
     *                               Attribut                                *
     * ***********************************************************************/

    private:
        Carte* carte;
        Curseur* curseur;
        Coord& coord;
        Vaisseau& vaisseau;
};

#endif