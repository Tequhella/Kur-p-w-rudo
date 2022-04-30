/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : reacteur.h                            */
/* Numéro de version : 0.3.6                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_REACTEUR
#define DEF_REACTEUR

#include "../entitee.h"

class Reacteur : public Entitee
{
    public:

        /*
        * Constructeur de la classe Reacteur.
        */
        Reacteur() ;

        /*
        * Destructeur de la classe Reacteur.
        */
        ~Reacteur() ;

    private:

        double emissionEnergie ;

};

#endif