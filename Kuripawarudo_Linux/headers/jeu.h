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

        /**
         * @brief Méthode getSetCoordCallback, récupère le callback de la méthode setCoordEntiteeConstr.
         * 
         * @return Le callback de la méthode setCoord.
         */
        std::function<void(const Coord&)> getSetCoordEntiteeCallback();

        /**
         * @brief Méthode getSetCoordBlockCasseCallback, récupère le callback de la méthode setCoordBlockCasse.
         * 
         * @return Le callback de la méthode setCoordBlockCasse.
         */
        std::function<void(const Coord&)> getSetCoordBlockCasseCallback();

    /*************************************************************************
     *                              Accesseur                               *
     * ***********************************************************************/

        /**
         * @brief Méthode getCarte, récupère la carte du jeu.
         * 
         * @return La carte du jeu.
         */
        Carte* getCarte() { return carte; }

        /**
         * @brief Méthode getCurseur, récupère le curseur du jeu.
         * 
         * @return Le curseur du jeu.
         */
        Curseur* getCurseur() { return curseur; }

        /**
         * @brief Méthode getCoord, récupère les coordonnées du curseur.
         * 
         * @return Les coordonnées du curseur.
         */
        Coord& getCoord() { return coord; }

        /**
         * @brief Méthode getVaisseau, récupère le vaisseau du jeu.
         * 
         * @return Le vaisseau du jeu.
         */
        Vaisseau& getVaisseau() { return vaisseau; }

        /**
         * @brief Méthode getCoordEntiteeConstr, récupère le tableau de coordonnée d'entitée en construction.
         * 
         * @return Un tableau de coordonnée.
         */
        vector<Coord>* getCoordEntiteeConstr() { return coordEntiteeConstr; }

        /**
         * @brief Méthode getCoordBlockCasse, récupère le tableau de coordonnée de blocks à casser.
         * 
         * @return Un tableau de coordonnée.
         */
        vector<Coord>* getCoordBlockCasse() { return coordBlockCasse; }

        /**
         * @brief Méthode getNbEntiteeConstr, récupère le nombre d'entitées en construction.
         * 
         * @return Le nombre d'entitées en construction.
         */
        uint8_t getNbEntiteeConstr() { return nbEntiteeConstr; }

        /**
         * @brief Méthode getNbBlockCasse, récupère le nombre de blocks à casser.
         * 
         * @return Le nombre de blocks à casser.
         */
        uint8_t getNbBlockCasse() { return nbBlockCasse; }

    /*************************************************************************
     *                              Mutateur                                *
     * ***********************************************************************/

        /**
         * @brief Méthode setCarte, modifie la carte du jeu.
         * 
         * @param carte La nouvelle carte du jeu.
         */
        void setCarte(Carte* carte) { this->carte = carte; }

        /**
         * @brief Méthode setCurseur, modifie le curseur du jeu.
         * 
         * @param curseur Le nouveau curseur du jeu.
         */
        void setCurseur(Curseur* curseur) { this->curseur = curseur; }

        /**
         * @brief Méthode setCoord, modifie les coordonnées du curseur.
         * 
         * @param coord Les nouvelles coordonnées du curseur.
         */
        void setCoord(Coord& coord) { this->coord = coord; }

        /**
         * @brief Méthode setVaisseau, modifie le vaisseau du jeu.
         * 
         * @param vaisseau Le nouveau vaisseau du jeu.
         */
        void setVaisseau(Vaisseau& vaisseau) { this->vaisseau = vaisseau; }

        /**
         * @brief Méthode setCoordEntiteeConstr, modifie le tableau de coordonnée d'entitée en construction.
         * 
         * @param coord La nouvelle coordonnée.
         */
        void setCoordEntiteeConstr(Coord coord);

        /**
         * @brief Méthode setCoordBlockCasse, modifie le tableau de coordonnée de blocks à casser.
         * 
         * @param coord La nouvelle coordonnée.
         */
        void setCoordBlockCasse(Coord coord);

        /**
         * @brief Méthode setNbEntiteeConstr, modifie le nombre d'entitées en construction.
         * 
         * @param nbEntiteeConstr Le nouveau nombre d'entitées en construction.
         */
        void setNbEntiteeConstr(uint8_t nbEntiteeConstr) { this->nbEntiteeConstr = nbEntiteeConstr; }

        /**
         * @brief Méthode setNbBlockCasse, modifie le nombre de blocks à casser.
         * 
         * @param nbBlockCasse Le nouveau nombre de blocks à casser.
         */
        void setNbBlockCasse(uint8_t nbBlockCasse) { this->nbBlockCasse = nbBlockCasse; }

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

        /**
         * @brief Méthode gestionRessources, gère les ressources comme l'énergie et les minerais.
         */
        void gestionRessources();

        /**
         * @brief Méthode gestionConstruction, décrémente les points de construction des entitée.
         */
        void gestionConstruction();

        /**
         * @brief Méthode gestionCasseBlock, décrémente les points de durabilité des blocks.
         */
        void gestionCasseBlock();

    /*************************************************************************
     *                               Attribut                                *
     * ***********************************************************************/

    private:
        Carte* carte;       // Propriété carte : la carte du jeu.
        Curseur* curseur;   // Propriété curseur : le curseur du jeu.
        Coord& coord;       // Propriété coord : les coordonnées du curseur.
        Vaisseau& vaisseau; // Propriété vaisseau : le vaisseau du jeu.

        vector<Coord>* coordEntiteeConstr; // Propriété coordEntiteeConstr : tableau des coordonnées des entitées en construction.
        vector<Coord>* coordBlockCasse;    // Propriété coordBlockCasse : tableau des coordonnées des blocks à casser.
		uint8_t 	   nbEntiteeConstr;    // Propriété nbEntiteeConstr : nombre d'entitées en construction.
		uint8_t 	   nbBlockCasse;       // Propriété nbBlockCasse : nombre de blocks à casser.
};

#endif