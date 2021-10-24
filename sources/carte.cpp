/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : carte.c                               */
/* Numéro de version : 0.1                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 23/10/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/carte.h"
#include "../headers/type.h"

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
        elements = (Case*) calloc (dimX * dimY, sizeof(Case)) ;

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
        for (unsigned int i = 0; i < dimX * dimY; i++) /*--->*/ this->elements[i].block.~Block () ;
        free (elements);
        elements = nullptr;
    }
    else
    {
        perror ("Erreur dans l'allocation des elements de la carte. \n");
        exit (-1);
    }

    cout << "Désallocation de la carte reussi." << endl;
}
    
/*************************************************************************
*                                 Méthode                                *
*************************************************************************/

void Carte::remplirHasard ()
{
    std::srand (1792) ;

    int dirt ;
    int stone ;
    int gold ;

    for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
    {
        dirt  = rand()%40+1 ;
        stone = rand()%40+1 ;
        gold  = rand()%40+1 ;
        
        if (i >= 5 * LARGEUR)
        {
            elements[i].type = BLOCK ;

            if (gold < 2) /*---------->*/ elements[i].block = Block (GOLD, 0, i % LARGEUR, i / LARGEUR) ;
            else if (stone < 10) /*--->*/ elements[i].block = Block (STONE, rand()%3+1, i % LARGEUR, i / LARGEUR) ;
            else if (dirt <= 40) /*--->*/ elements[i].block = Block (DIRT, 0, i % LARGEUR, i / LARGEUR) ;
            
        }
        std::cout << elements[i].type << std::endl ;

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
                if (j == 0 || j == LARGEUR + 1) /*--->*/ cout << "║";
                else
                {
                    if (elements[k].type == 0) /*--->*/ cout << " ";
                    else
                    {
                        switch (elements[k].block.getType())
                        {
                            case 1: cout << "░"; break ;
                            case 2:
                                switch (elements[k].block.getStone()->type)
                                {
                                    case 1: cout << "▒"; break ;
                                    case 2: cout << "▓"; break ;
                                    case 3: cout << "█"; break ;
                                }
                                break ;
                            case 3: cout << "▚"; break ;
                        }
                    }
                    
                    k++;

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

Carte::Case* Carte::getElement ()
{
    return elements ;
}

char* Carte::getNomDeLaCarte ()
{
    return &nomDeLaCarte ;
}
