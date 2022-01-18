/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : bombe.h                               */
/* Numéro de version : 0.3                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_BOMBE
#define DEF_BOMBE

#include "../entitee.h"

class Bombe : public Entitee
{
    public:

        /*
        * Constructeur de la classe Bombe.
        */
        Bombe() ;

        /*
        * Destructeur de la classe Bombe.
        */
        ~Bombe() ;

    private:

        int    portee ;
        double energieQuantitee ;
        double energieMax ;
        double degat ;

};

#endif