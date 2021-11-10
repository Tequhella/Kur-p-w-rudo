#ifndef DEF_CASE
#define DEF_CASE

#include "type.h"
#include "block.h"
#include "vide.h"

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

        void detruireElement (unsigned int type) ;

        void creerVide () ;

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

        unsigned int type = 0;
        Block        block ;
        Vide         vide ;
        Coord        pos ;
} ;

#endif