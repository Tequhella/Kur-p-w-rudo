/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : entitee.h                             */
/* Numéro de version : 0.3                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_ENTITEE
#define DEF_ENTITEE

#include "type.h"

class Entitee
{
    public:

        int vie ;

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

        // Getter getType, récupère l'indicateur du type de l'entitée.
        unsigned int getType() ;

        // Getter getConstr, récupère le nombre de point de construction de l'entitee.
        double getConstr() ;


        ////////////
        // Setter //
        ////////////

        // Getter getType, récupère l'indicateur du type de l'entitée.
        void setType(unsigned int type) ;

    private:

        unsigned int type ;
        double       constr ; // Point de construction.
        Coord        coord ;


};

#endif