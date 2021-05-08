/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : fonction.c                            */
/* Numéro de version : 0.1                                   */
/* Date              : 16/03/2021                            */
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
        printf ("Desallocation de la carte reussi. \n");
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