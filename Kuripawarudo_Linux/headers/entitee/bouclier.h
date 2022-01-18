/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : bouclier.h                            */
/* Numéro de version : 0.3                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_BOUCLIER
#define DEF_BOUCLIER

#include "../entitee.h"

class Bouclier : public Entitee
{
    public:

        /*
        * Constructeur de la classe Bouclier.
        */
        Bouclier() ;

        /*
        * Destructeur de la classe Bouclier.
        */
        ~Bouclier() ;

};

#endif