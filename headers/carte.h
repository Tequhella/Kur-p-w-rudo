#ifndef DEF_CARTE
#define DEF_CARTE

#include "block.h"
#include "case.h"

using namespace std ;

class Carte
{
    public:
    
    /*************************************************************************
    *                       Constructeur & Destructeur                       *
    *************************************************************************/
        Carte (int dimX, int dimY, char nomDeLaCarte) ;
        
        ~Carte () ;

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        void remplirHasard () ;

        void afficherCarte () const ;

        ////////////
        // Getter //
        ////////////
        unsigned int getDimX () ;

        unsigned int getDimY () ;

        Case* getElement () ;

        char* getNomDeLaCarte () ;
    
    private:

        /***********************
        * Liste des propriétés *
        ***********************/
        unsigned int dimX, dimY ;
        Case*        elements ;
        char         nomDeLaCarte ;
} ;

#endif