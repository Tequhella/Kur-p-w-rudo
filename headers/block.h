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

        Block () ;

        Block (unsigned int type, unsigned int typeStone) ;

        ~Block () ;

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        ////////////
        // Getter //
        ////////////
        unsigned int getType () ;

        unsigned int getStoneType () ;

        double getHardness () ;

        int getGold_quantity () ;
    
    private:

        unsigned int type          = 0 ;
        unsigned int stoneType     = 0 ;
        double       hardness      = 0 ;
        int          gold_quantity = 0 ;
} ;

#endif