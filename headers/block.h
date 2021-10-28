#ifndef DEF_BLOCK
#define DEF_BLOCK

#include "type.h"

using namespace std ;

class Block
{
    public:
  
        typedef struct str_dirt
        {
            double* hardness ;
        }
        Dirt ;

        typedef struct str_stone
        {
            unsigned int* type ;
            double*       hardness ;
        }
        Stone ;

        typedef struct str_gold
        {
            unsigned int* quantity ;
        }
        Gold ;

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

        Dirt* getDirt () ;

        Stone* getStone () ;

        Gold* getGold () ;
    
    private:

        unsigned int type  = 0 ;
        Dirt*        dirt  = nullptr ;
        Stone*       stone = nullptr ;
        Gold*        gold  = nullptr ;
} ;

#endif