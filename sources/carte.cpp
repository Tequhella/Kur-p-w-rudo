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
        for (unsigned int i = 0; i < dimX * dimY; i++) /*--->*/ this->elements[i].detruireElement(this->elements[i].getTypeElement()) ;
        delete[] this->elements ;
        elements = nullptr;
        cout << "Désallocation de la carte reussi." << endl;
    }
    else
    {
        std::cerr << "Erreur allocation des éléments de la carte." << std::endl;
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
    int relief = 200; /* variable se démécrantant à chaque ligne pour
                         creer un relief */

    for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
    {
        dirt  = (rand() % 100 + 1) + relief ;
        stone = (rand() % 100 + 1) + relief ;
        gold  = (rand() % 100 + 1) + relief ;

        this->elements[i].setPos (i % LARGEUR, i / LARGEUR) ;
        
        if (gold < 3)
        {
            this->elements[i].setTypeElement (BLOCK) ;
            this->elements[i].setBlock (GOLD, 0) ;
        }
        else if (stone < 21)
        {
            int stoneType = (rand() % 100 + 1) ;

            if (stoneType <= 5) /*---------->*/ stoneType = STONE3;
            else if (stoneType <= 30) /*---->*/ stoneType = STONE2;
            else if (stoneType <= 100) /*--->*/ stoneType = STONE1;

            this->elements[i].setTypeElement (BLOCK) ;
            this->elements[i].setBlock (STONE, stoneType) ;
        }
        else if (dirt <= 100)
        {
            this->elements[i].setTypeElement (BLOCK) ;
            this->elements[i].setBlock (DIRT, 0) ;
        }
        else if (this->elements[i].getTypeElement() == BLOCK);
        else if (this->elements[i].getTypeElement() == ENTITY);
        else
        {
            this->elements[i].setTypeElement(VIDE) ;
            this->elements[i].creerVide() ;
        }

        if (relief > 0 && i % LARGEUR == 0) /*--->*/ relief -= 25;

    }
}

void Carte::creerCaverne (unsigned int pos, int randMoins)
{
    
    while (pos > LARGEUR * HAUTEUR || this->elements[pos].getTypeElement() != BLOCK) /*--->*/ pos = rand() % LARGEUR * HAUTEUR + 280;
    
    if (this->elements[pos].getTypeElement() == BLOCK)
    {
        int droite = rand() % 100 - randMoins;
        while (droite < 0) /*--->*/ droite = rand() % 100 - randMoins;
        
        int bas    = rand() % 100 - randMoins;
        while (bas < 0) /*------>*/ bas = rand() % 100 - randMoins;

        int gauche = rand() % 100 - randMoins;
        while (gauche < 0) /*--->*/ gauche = rand() % 100 - randMoins;

        int haut   = rand() % 100 - randMoins;
        while (haut < 0) /*----->*/ haut = rand() % 100 - randMoins;

        this->elements[pos].detruireElement (BLOCK) ;
        this->elements[pos].setTypeElement (VIDE) ;
        this->elements[pos].creerVide() ;

        randMoins += 5;

        if (droite > 30 && this->elements[pos + 1].getTypeElement() == BLOCK) /*--------->*/ creerCaverne (pos + 1, randMoins);
        if (bas > 30 && this->elements[pos + LARGEUR].getTypeElement() == BLOCK) /*------>*/ creerCaverne (pos + LARGEUR, randMoins);
        if (gauche > 30 && this->elements[pos - 1].getTypeElement() == BLOCK) /*--------->*/ creerCaverne (pos - 1, randMoins);
        if (bas > 30 && this->elements[pos - LARGEUR].getTypeElement() == BLOCK) /*------>*/ creerCaverne (pos - LARGEUR, randMoins);
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
                    if (elements[k].getTypeElement() == VIDE) /*---->*/ cout << " " ;
                    else
                    {
                        switch (elements[k].getBlock()->getType())
                        {
                            case DIRT: cout << "░"; break ;
                            case STONE:
                                switch (elements[k].getBlock()->getStoneType())
                                {
                                    case STONE1: cout << "▒"; break ;
                                    case STONE2: cout << "▓"; break ;
                                    case STONE3: cout << "█"; break ;
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