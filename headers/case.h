#ifndef DEF_CASE
#define DEF_CASE

#include "type.h"
#include "block.h"

class Case
{
    public:
    
        typedef struct
        {
            double x;
            double y;
        }
        Coord ;

    /*************************************************************************
    *                       Constructeur & Destructeur                       *
    *************************************************************************/
   
        Case () ;

        ~Case () ;

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        ////////////
        // Getter //
        ////////////
        unsigned int getTypeElement () ;

        Block* getBlock () ;

        Coord getCoord () ;


        ////////////
        // Setter //
        ////////////
        void setTypeElement (unsigned int type) ;

        void setBlock (unsigned int type, unsigned int typeStone) ;

        void setPos (unsigned int x, unsigned int y) ;

    private:

        unsigned int type ;
        Block        block ;
        Coord        pos ;
} ;

#endif