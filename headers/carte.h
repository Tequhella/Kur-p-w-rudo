/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : carte.h                               */
/* Numéro de version : 0.3                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_CARTE
#define DEF_CARTE


using namespace std ;

class Case;

class Carte
{
    public:
    
    /*************************************************************************
    *                       Constructeur & Destructeur                       *
    *************************************************************************/

        /*
        * Constructeur de la classe Carte.
        */
        Carte (int dimX, int dimY, char nomDeLaCarte) ;
        
        /*
        * Destructeur de la classe Carte.
        */
        ~Carte () ;

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        /*
        * Méthode rempliHasard, se contente de remplir une carte de façon aléatoire.
        * Elle place tout type de block et créer des relief à la surface.
        */
        void remplirHasard () ;

        /*
        * Méthode creerCaverne, détruit des blocks dans une carte déjà remplie de façon récursive.
        */
        void creerCaverne (unsigned int pos, int randMoins) ;

        /*
        * Méthode afficherCarte, affiche la carte dans la console.
        */
        void afficherCarte () const ;

        ////////////
        // Getter //
        ////////////

        // Getter getDimX, récupère la largeur de la carte.
        unsigned int getDimX () ;

        // Getter getDimY, récupère la hauteur de la carte.
        unsigned int getDimY () ;
        
        // Getter getElement, récupère le tableau d'éléments.
        Case* getElement () ;

        // Getter getNomDeLaCarte, récupère le nom de la carte.
        char* getNomDeLaCarte () ;

    private:

        /***********************
        * Liste des propriétés *
        ***********************/

        unsigned int dimX, dimY ;
        Case*        elements ; // Propriété elements : tableau des éléments de la carte.
        char         nomDeLaCarte ;
} ;

#endif