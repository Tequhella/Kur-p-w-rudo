/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : entitee.h                             */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_ENTITEE
#define DEF_ENTITEE

#include "type.h"

/* La classe Entitee est une classe qui représente une entité dans le jeu */
class Entitee
{
    public:

    /*************************************************************************
    *                       Constructeur & Destructeur                       *
    *************************************************************************/
        
        /*
        * Constructeur de la classe Entitee.
        */
        Entitee(unsigned int type, Coord* coord) ;


        /*
        * Constructeur par défaut de la classe Entitée.
        */
        Entitee() ;

        /*
        * Destructeur de la classe Entitee.
        */
        ~Entitee() ;

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        ////////////
        // Getter //
        ////////////

        /* Renvoie le type de l'entité. */
        unsigned int getType() ;

        /* Renvoie le nombre de points de construction de l'entité. */
        double getConstr() ;


        ////////////
        // Setter //
        ////////////

        /* Mise à jour du type de l'entité. */
        void setType(unsigned int type) ;

        /* Une méthode setter qui définit l'identifiant de l'entité. */
        void setId(unsigned int id);

    private:

        unsigned int type ;
        double       constr ; // Point de construction.
        Coord        coord ;

    protected:

        unsigned int id;
        int vie;

};

#endif