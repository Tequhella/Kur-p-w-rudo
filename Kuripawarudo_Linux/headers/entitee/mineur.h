/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : mineur.h                              */
/* Numéro de version : 0.3.4                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_MINEUR
#define DEF_MINEUR

#include "../entitee.h"

class Mineur : public Entitee
{
    public:

        /*
        * Constructeur de la classe Mineur.
        */
        Mineur() ;

        /*
        * Destructeur de la classe Mineur.
        */
        ~Mineur() ;

    private:

        double energieQuantitee ;
        double energieMax ;

};

#endif