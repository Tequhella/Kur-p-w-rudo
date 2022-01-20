/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : block.h                               */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_BLOCK
#define DEF_BLOCK

#include "type.h"

using namespace std ;

class Block
{
    public:

    /*************************************************************************
    *                       Constructeur & Destructeur                       *
    *************************************************************************/

        /*
        * Constrcuteur de la classe Block.
        */
        Block (unsigned int type, unsigned int typeRoche) ;

        /*
        * Constructeur par défaut de la classe Block.
        */
        Block () ;

        /*
        * Destrcuteur de la classe Block.
        */
        ~Block () ;

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        ////////////
        // Getter //
        ////////////

        // Getter getType, récupère l'indicateur du type block.
        unsigned int getType () ;

        // Getter getRocheType, récupère l'indicateur du type de roche.
        unsigned int getRocheType () ;

        // Getter getSoliditee, récupère la soliditée restante avant de se casser.
        double getSoliditee () ;

        // Getter getMinerai_quantitee, récupère la quantitee de minerai.
        int getMinerai_quantitee () ;
    
    private:

        unsigned int type              = 0 ;
        unsigned int rocheType         = 0 ;
        double       soliditee         = 0 ;
        int          minerai_quantitee = 0 ;
} ;

#endif