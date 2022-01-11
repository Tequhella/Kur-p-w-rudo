/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : phare.h                               */
/* Numéro de version : 0.3                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_PHARE
#define DEF_PHARE

#include "../entitee.h"

class Phare : public Entitee
{
    public:

        /*
        * Constructeur de la classe Phare.
        */
        Phare() ;

        /*
        * Destructeur de la classe Phare.
        */
        ~Phare() ;

    private:

        int    portee;
        double energieQuantitee ;
        double energieMax ;

};

#endif