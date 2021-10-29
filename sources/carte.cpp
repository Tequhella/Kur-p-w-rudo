/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : carte.cpp                             */
/* Numéro de version : 0.2                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 23/10/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/carte.h"

/*************************************************************************
*                       Constructeur & Destructeur                       *
*************************************************************************/

Carte::Carte (int dimX, int dimY, char nomDeLaCarte)
{
    if (dimX == 0 || dimY == 0)
    {
        elements           = nullptr ;
        this->dimX         = 0 ;
        this->dimY         = 0 ;
        this->nomDeLaCarte = nomDeLaCarte ;
    }
    else
    {
        elements = new Case [sizeof(Case) * dimX * dimY] ;
        
        if (elements)
        {
            this->dimX         = dimX ;
            this->dimY         = dimY ;
            this->nomDeLaCarte = nomDeLaCarte ;
        }
        else
        {
            perror ("Erreur d'allocation du tableau d'elements. \n") ;
            exit (-1) ;
        }
        
    }

}

Carte::~Carte ()
{
    if (elements)
    {
        for (unsigned int i = 0; i < dimX * dimY; i++) /*--->*/ this->elements[i].detruireBlock() ;
        delete[] this->elements ;
        elements = nullptr;
        cout << "Désallocation de la carte reussi." << endl;
    }
    else
    {
        perror ("Erreur dans l'allocation des elements de la carte. \n");
        exit (-1);
    }

}
    
/*************************************************************************
*                                 Méthode                                *
*************************************************************************/

void Carte::remplirHasard ()
{
    std::srand (std::time(nullptr)) ;

    int dirt ;
    int stone ;
    int gold ;

    for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
    {
        dirt  = rand()%40+1 ;
        stone = rand()%40+1 ;
        gold  = rand()%40+1 ;

        this->elements[i].setPos (i % LARGEUR, i / LARGEUR) ;
        
        if (i >= 5 * LARGEUR)
        {
            this->elements[i].setTypeElement (BLOCK) ;
            
            if (gold < 2) /*---------->*/ this->elements[i].setBlock (GOLD, 0) ;
            else if (stone < 10) /*--->*/ this->elements[i].setBlock (STONE, rand()%3+1) ;
            else if (dirt <= 40) /*--->*/ this->elements[i].setBlock (DIRT, 0) ;
            
        }

    }
}

void Carte::afficherCarte () const
{
    unsigned int k = 0;

    for (unsigned int i = 0; i < HAUTEUR + 2; i++)
    {
        for (unsigned int j = 0; j < LARGEUR + 2; j++)
        {
            if (i == 0)
            {
                switch (j)
                {
                    case 0          : cout << "╔" ; break ;
                    case LARGEUR + 1: cout << "╗" ; break ;
                    default         : cout << "═"; break ;
                }
                
            }
            else if (i == HAUTEUR + 1)
            {
                switch (j)
                {
                    case 0          : cout << "╚"; break ;
                    case LARGEUR + 1: cout << "╝"; break ;
                    default         : cout << "═"; break ;
                }
            }
            else
            {
                if (j == 0 || j == LARGEUR + 1) /*--->*/ cout << "║" ;
                else
                {
                    if (elements[k].getTypeElement() == 0) /*---->*/ cout << " " ;
                    else
                    {
                        switch (elements[k].getBlock()->getType())
                        {
                            case 1: cout << "░"; break ;
                            case 2:
                                switch (elements[k].getBlock()->getStoneType())
                                {
                                    case 1: cout << "▒"; break ;
                                    case 2: cout << "▓"; break ;
                                    case 3: cout << "█"; break ;
                                }
                                break ;
                            case 3: cout << "▚"; break ;
                        }
                    }
                    
                    k++ ;

                }
                
            }

        }

        cout << endl;
        
    }
    
}

////////////
// Getter //
////////////
unsigned int Carte::getDimX ()
{
    return dimX ;
}

unsigned int Carte::getDimY ()
{
    return dimY ;
}

Case* Carte::getElement ()
{
    return elements ;
}

char* Carte::getNomDeLaCarte ()
{
    return &nomDeLaCarte ;
}
