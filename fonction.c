/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : fonction.c                            */
/* Numéro de version : 0.2                                   */
/* Date              : 17/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "fonction.h"

//-----------------------------Gestion Map-----------------------------//

Map* creerMap (double dimX, double dimY, char nomDeLaCarte)
{
    Map* m = malloc (sizeof(Map));

    if (m)
    {
        if (dimX == 0 || dimY == 0)
        {
            m->elements     = NULL;
            m->dimX         = 0;
            m->dimY         = 0;
            m->nomDeLaCarte = nomDeLaCarte;
        }
        else
        {
            m->elements = (Case*) calloc (dimX * dimY, sizeof(Case));

            if (m->elements)
            {
                m->dimX         = dimX;
                m->dimY         = dimY;
                m->nomDeLaCarte = nomDeLaCarte;
            }
            else
            {
                perror ("Erreur d'allocation du tableau d'elements. \n");
                free (m);
                m = NULL;
            }
            
        }
        
    }
    else
    {
        perror ("Erreur d'allocation. \n");
        exit (-1);
    }
    
    return m;
}

void detruireMap (Map* m)
{
    if (m)
    {
        if (m->elements)
        {
            for (unsigned int i = 0; i < m->dimX*m->dimY; i++) /*--->*/ detruireBlock (m->elements[i].block);
            free (m->elements);
            m->elements = NULL;
        }
        else
        {
            perror ("Erreur dans l'allocation des elements de la carte. \n");
            exit (-1);
        }

        free (m);
        m = NULL;
    }
    else
    {
        perror ("Erreur dans l'allocation de la carte. \n");
        exit (-1);
    }
    
}

void afficherMap (Map* m)
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
                    case 0          : printf ("╔"); break;
                    case LARGEUR + 1: printf ("╗"); break;
                    default         : printf ("═"); break;
                }
                
            }
            else if (i == HAUTEUR + 1)
            {
                switch (j)
                {
                    case 0          : printf ("╚"); break;
                    case LARGEUR + 1: printf ("╝"); break;
                    default         : printf ("═"); break;
                }
            }
            else
            {
                if (j == 0 || j == LARGEUR + 1) /*--->*/ printf ("║");
                else
                {
                    if (m->elements[k].type == 0) /*--->*/ printf (" "); 
                    else
                    {
                        switch (m->elements[k].block->type)
                        {
                            case 1: printf ("░"); break;
                            case 2:
                                switch (m->elements[k].block->stone->type)
                                {
                                    case 1: printf ("▒"); break;
                                    case 2: printf ("▓"); break;
                                    case 3: printf ("█"); break;
                                }
                                break;
                            case 3: printf ("▚"); break;
                        }
                    }
                    
                    k++;

                }
                
            }

        }

        printf ("\n");
        
    }
    
}

void remplirHasard (Map* m)
{
    int dirt  = 0;
    int stone = 0;
    int gold  = 0;
    int stoneType = 0;
    int relief = 200; /* variable se démécrantant à chaque ligne pour
                                  creer un relief */

    for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
    {
        dirt  = (rand() % 100 + 1) + relief;
        stone = (rand() % 100 + 1) + relief;
        gold  = (rand() % 100 + 1) + relief;

        if (gold < 2)
        {
            m->elements[i].type  = BLOCK;
            m->elements[i].block = creerBlock (GOLD, 0, i % LARGEUR, i / LARGEUR);
        }
        else if (stone < 20)
        {
            stoneType = (rand() % 100 + 1);

            if (stoneType <= 5) /*--->*/ stoneType = 3;
            else if (stoneType <= 50) /*--->*/ stoneType = 2;
            else if (stoneType <= 100) /*------->*/ stoneType = 1;

            m->elements[i].type  = BLOCK;
            m->elements[i].block = creerBlock (STONE, stoneType, i % LARGEUR, i / LARGEUR);
        }
        else if (dirt <= 100)
        {
            m->elements[i].type  = BLOCK;
            m->elements[i].block = creerBlock (DIRT, 0, i % LARGEUR, i / LARGEUR);
        } 
        else /*--->*/ m->elements[i].type = VIDE;
        
        
        if (relief > 0 && i % LARGEUR == 0) /*--->*/ relief -= 20;

    }

    for (unsigned int i = 0; i < LARGEUR * 5; i++)
    {
        if (m->elements[i].type == BLOCK)
        {
            int stackVoid;
            (m->elements[i + 1].type == VIDE) ? stackVoid++ : 0;
            (m->elements[i - 1].type == VIDE) ? stackVoid++ : 0;
            (m->elements[i + LARGEUR].type == VIDE) ? stackVoid++ : 0;
            (m->elements[i + LARGEUR + 1].type == VIDE) ? stackVoid++ : 0;
            (m->elements[i + LARGEUR - 1].type == VIDE) ? stackVoid++ : 0;

            if (stackVoid > 3)
            {
                m->elements[i].type = VIDE;
                detruireBlock (m->elements[i].block);
            }
        }
        
        
        
    }
    
}

void creerCaverne (Map* m, unsigned int pos, int randMoins)
{
    if (m && pos <= LARGEUR * HAUTEUR && m->elements[pos].type == BLOCK)
    {
        int droite = rand() % 100 - randMoins;
        while (droite < 0) /*--->*/ droite = rand() % 100 - randMoins;
        
        int bas    = rand() % 100 - randMoins;
        while (bas < 0) /*------>*/ bas = rand() % 100 - randMoins;

        int gauche = rand() % 100 - randMoins;
        while (gauche < 0) /*--->*/ gauche = rand() % 100 - randMoins;

        int haut   = rand() % 100 - randMoins;
        while (haut < 0) /*----->*/ haut = rand() % 100 - randMoins;

        
        m->elements[pos].type = VIDE;

        randMoins += 5;

        if (droite > 30 && m->elements[pos + 1].type == BLOCK) /*--------->*/ creerCaverne (m, pos + 1, randMoins);
        if (bas > 30 && m->elements[pos + LARGEUR].type == BLOCK) /*------>*/ creerCaverne (m, pos + LARGEUR, randMoins);
        if (gauche > 30 && m->elements[pos - 1].type == BLOCK) /*--------->*/ creerCaverne (m, pos - 1, randMoins);
        if (bas > 30 && m->elements[pos - LARGEUR].type == BLOCK) /*------>*/ creerCaverne (m, pos - LARGEUR, randMoins);
    }
    
}

//----------------------------Gestion Block----------------------------//

Block* creerBlock (unsigned int type, unsigned int typeStone, double posX, double posY)
{
    Block* b = (Block*) calloc (1, sizeof(Block));

    if (b)
    {
        switch (type)
        {
        case 1:
            b->dirt = malloc (sizeof(Dirt));
            if (b->dirt) 
            {
                b->type      = type;
                b->dirt->pos = (Coord) {posX, posY};
            }
            else
            {
                perror ("Erreur d'allocation du block type terre. \n");
                exit (-1);
                free (b);
                b = NULL;
            }
            
            break;
        case 2:
            b->stone = malloc (sizeof(Stone));
            if (b->stone)
            {
                b->type        = type;
                b->stone->type = typeStone;
                b->stone->pos  = (Coord) {posX, posY};
            }
            else
            {
                perror ("Erreur d'allocation du block type roche. \n");
                exit (-1);
                free (b);
                b = NULL;
            }
            
            break;
        case 3:
            b->gold = malloc (sizeof(Gold));
            if (b->gold)
            {
                b->type           = type;
                b->gold->quantity = 200;
                b->gold->pos      = (Coord) {posX, posY};
            }
            else
            {
                perror ("Erreur d'allocation du block type ressource d'or. \n");
                exit (-1);
                free (b);
                b = NULL;
            }
            
        }
        
    }
    else
    {
        perror ("Erreur d'allocation du block. \n");
        exit (-1);
    }

    return b;
    
}

void detruireBlock (Block* b)
{
    if (b)
    {
        if (b->dirt)
        {
            free (b->dirt);
            b->dirt = NULL;
        }
        else if (b->stone)
        {
            free (b->stone);
            b->stone = NULL;
        }
        else if (b->gold)
        {
            free (b->gold);
            b->gold = NULL;
        }
        else
        {
            perror ("Erreur d'allocation du block. \n");
            exit (-1);
        }

        free (b);
        b = NULL;
        
    }
    
}

