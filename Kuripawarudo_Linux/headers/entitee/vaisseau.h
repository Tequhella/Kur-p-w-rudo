/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : vaisseau.h                            */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_VAISSEAU
#define DEF_VAISSEAU

#include "../entitee.h"

class Vaisseau : public Entitee
{
    public:

        /*
        * Constructeur de la classe Vaisseau.
        */
        Vaisseau() ;

        /*
        * Destructeur de la classe Vaisseau.
        */
        ~Vaisseau() ;

    private:

        double energieQuantitee ;
        double energieReserve ;
        double energieEfficacitee ;
        /*double energieVitesse ;*/
        double mineraiQuantitee ;
        double mineraiReserve ;
        double mineraiEfficacitee ;
        int    portee ;

};

#endif