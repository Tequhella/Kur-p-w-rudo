/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : carte.cpp                             */
/* Numéro de version : 0.2                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/carte.h"
#include "../headers/type.h"
#include "../headers/case.h"
#include "../headers/block.h"
#include "../headers/entitee.h"

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
            this->dimX = dimX ;
            this->dimY = dimY ;
            
            this->nomDeLaCarte = nomDeLaCarte ;
            
            elements[LARGEUR * 2 + LARGEUR / 2].setTypeElement(ENTITEE) ;
            elements[LARGEUR * 2 + LARGEUR / 2].setCoord(LARGEUR / 2, 2);
            elements[LARGEUR * 2 + LARGEUR / 2].setEntitee(VAISSEAU) ;
        }
        else
        {
            cerr << "Erreur allocation des éléments de la carte." << endl ;
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
        this->elements = nullptr ;
        cout << "Désallocation de la carte reussi." << endl ;
    }
    else
    {
        cerr << "Erreur allocation des éléments de la carte." << endl ;
        exit (-1);
    }

}
    
/*************************************************************************
*                                 Méthode                                *
*************************************************************************/

void Carte::remplirHasard ()
{
    std::srand (std::time(nullptr)) ;

    int terre ;
    int roche ;
    int minerai ;
    int relief = 200; /* variable se démécrantant à chaque ligne pour
                         creer un relief */

    for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
    {
        terre   = (rand() % 100 + 1) + relief ;
        roche   = (rand() % 100 + 1) + relief ;
        minerai = (rand() % 100 + 1) + relief ;

        this->elements[i].setCoord (i % LARGEUR, i / LARGEUR) ;
        
        if (minerai < 3)
        {
            this->elements[i].setTypeElement (BLOCK) ;
            this->elements[i].setBlock (MINERAI, 0) ;
        }
        else if (roche < 21)
        {
            int rocheType = (rand() % 100 + 1) ;

            if (rocheType <= 5) /*---------->*/ rocheType = ROCHE3;
            else if (rocheType <= 30) /*---->*/ rocheType = ROCHE2;
            else if (rocheType <= 100) /*--->*/ rocheType = ROCHE1;

            this->elements[i].setTypeElement (BLOCK) ;
            this->elements[i].setBlock (ROCHE, rocheType) ;
        }
        else if (terre <= 100)
        {
            this->elements[i].setTypeElement (BLOCK) ;
            this->elements[i].setBlock (TERRE, 0) ;
        }
        else if (this->elements[i].getTypeElement() == ENTITEE) ;
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
                    switch (elements[k].getTypeElement())
                    {
                        case VIDE : cout << " " ; break ;
                        case BLOCK:
                            switch (elements[k].getBlock()->getType())
                            {
                                case TERRE: cout << "░"; break ;
                                case ROCHE:
                                    switch (elements[k].getBlock()->getRocheType())
                                    {
                                        case ROCHE1: cout << "▒"; break ;
                                        case ROCHE2: cout << "▓"; break ;
                                        case ROCHE3: cout << "█"; break ;
                                    }
                                    break ;
                                case MINERAI: cout << "▚"; break ;
                            }
                            break ;
                        case ENTITEE:
                            switch (elements[k].getEntitee()->getType())
                            {
                                case VAISSEAU: cout << "◈" ; break ;
                                case REACTEUR:
                                    if (elements[k].getEntitee()->getConstr() <= 0) /*--->*/ cout << "◬" ;
                                    else /*--->*/ cout << " " ;
                                    break ;
                                case MINEUR:
                                    if (elements[k].getEntitee()->getConstr() <= 0) /*--->*/ cout << "◭" ;
                                    else /*--->*/ cout << " " ;
                                    break ;
                                case BOUCLIER:
                                    if (elements[k].getEntitee()->getConstr() <= 0) /*--->*/ cout << "◩" ;
                                    else /*--->*/ cout << " " ;
                                    break ;
                                case PHARE:
                                    if (elements[k].getEntitee()->getConstr() <= 0) /*--->*/ cout << "◉" ;
                                    else /*--->*/ cout << " " ;
                                    break ;
                                case BOMBE:
                                    if (elements[k].getEntitee()->getConstr() <= 0) /*--->*/ cout << "◘" ;
                                    else /*--->*/ cout << " " ;
                                    break ;
                                case CREEPER_EMETTEUR: cout << "◎" ; break ;
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
