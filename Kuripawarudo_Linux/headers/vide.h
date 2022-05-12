/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : vide.h                                */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_VIDE
#define DEF_VIDE

#include "type.h"
#include "case.h"

class Vide
{
    public:
    /*************************************************************************
    *                       Constructeur & Destructeur                       *
    *************************************************************************/

        Vide () ;

        ~Vide () ;

    /*************************************************************************
     *                                Méthode                                *
     * ***********************************************************************/
        
        int getCreeperQuantity(uint8_t placement);

        void setCreeperQuantity(int creeperQuantity, uint8_t placement);

        void addCreeper(int creeperQuantity, uint8_t placement);
        
    private:
        int creeperQuantity[4] ;
};

#endif