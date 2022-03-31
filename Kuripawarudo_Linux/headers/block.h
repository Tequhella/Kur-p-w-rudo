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

/* La classe Block est utilisée pour représenter un bloc dans la carte */
class Block
{
    public:

    /*************************************************************************
    *                       Constructeur & Destructeur                       *
    *************************************************************************/

        /*
        * Constrcuteur de la classe Block.
        */
        Block (uint8_t type, uint8_t typeRoche) ;

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
        uint8_t getType () ;

        // Getter getRocheType, récupère l'indicateur du type de roche.
        uint8_t getRocheType () ;

        // Getter getSoliditee, récupère la soliditée restante avant de se casser.
        double getSoliditee () ;

        // Getter getMinerai_quantitee, récupère la quantitee de minerai.
        int getMinerai_quantitee () ;
    
    private:

        uint8_t type              = 0 ;
        uint8_t rocheType         = 0 ;
        double  soliditee         = 0 ;
        int     minerai_quantitee = 0 ;
} ;

#endif