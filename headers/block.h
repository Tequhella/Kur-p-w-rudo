#ifndef DEF_BLOCK
#define DEF_BLOCK

#include "type.h"

using namespace std ;

class Block
{
    public:

        typedef struct
        {
            double x;
            double y;
        }
        Coord ;
        
        typedef struct str_dirt
        {
            Coord pos ;
        }
        Dirt ;

        typedef struct str_stone
        {
            unsigned int type ;
            double       hardness ;
            Coord        pos ;
        }
        Stone ;

        typedef struct str_gold
        {
            unsigned int type ;
            unsigned int quantity ;
            Coord pos ;
        }
        Gold ;
    /*************************************************************************
    *                       Constructeur & Destructeur                       *
    *************************************************************************/

        Block (unsigned int type, unsigned int typeStone, double posX, double posY) ;

        ~Block () ;

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        ////////////
        // Getter //
        ////////////
        unsigned int getType () ;

        Dirt* getDirt () ;

        Stone* getStone () ;

        Gold* getGold () ;
    
    private:

        unsigned int type ;
        Dirt*        dirt ;
        Stone*       stone ;
        Gold*        gold ;
} ;

#endif