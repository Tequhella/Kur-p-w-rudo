/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : creeperEmetteur.h                     */
/* Numéro de version : 0.3                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_CREEPEREMETTEUR
#define DEF_CREEPEREMETTEUR

#include "../entitee.h"

class CreeperEmetteur : public Entitee
{
    public:

        /*
        * Constructeur de la classe CreeperEmetteur.
        */
        CreeperEmetteur() ;

        /*
        * Destructeur de la classe CreeperEmetteur.
        */
        ~CreeperEmetteur() ;

    private:

        double frequence ;
        double puissance ;

};

#endif