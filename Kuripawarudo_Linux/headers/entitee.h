/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : entitee.h                             */
/* Numéro de version : 0.3.4                                 */
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
        Entitee(uint8_t type, Coord* coord) ;


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
        uint8_t getType() ;

        /* Renvoie le nombre de points de construction de l'entité. */
        double getConstr() ;


        ////////////
        // Setter //
        ////////////

        /* Mise à jour du type de l'entité. */
        void setType(uint8_t type) ;

        /* Une méthode setter qui définit l'identifiant de l'entité. */
        void setId(unsigned int id);

    private:

        uint8_t      type ;
        double       constr ; // Point de construction.
        Coord        coord ;

    protected:

        unsigned int id;
        uint8_t      vie;

};

#endif