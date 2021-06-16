/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionAffichage.c                    */
/* Numéro de version : 0.7                                   */
/* Date              : 18/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/gestionAffichage.h"

//---------------------------Affichage Console---------------------------//

void afficherCarte (Map* m)
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
                    if (m->elements[k].visibilitee == 1)
                    {
                        if (m->elements[k].type == VIDE)
                        {
                            if (m->elements[k].vide->creeperQuantity[0] == 0 || m->elements[k].vide->creeperQuantity[1] == 0 || m->elements[k].vide->creeperQuantity[2] == 0 || m->elements[k].vide->creeperQuantity[3] == 0)
                                printf (" ");
                            else
                                printf (".");
                        }
                        else if (m->elements[k].type == BLOCK)
                        {
                            switch (m->elements[k].block->type)
                            {
                                case DIRT: printf ("░"); break;
                                case STONE:
                                    switch (m->elements[k].block->stone->type)
                                    {
                                        case STONE1: printf ("▒"); break;
                                        case STONE2: printf ("▓"); break;
                                        case STONE3: printf ("█"); break;
                                    }
                                    break;
                                case GOLD: printf ("▚"); break;
                            }

                        }
                        else if (m->elements[k].type == ENTITY)
                        {
                            switch (m->elements[k].entitee->type)
                            {
                                case SHIP: printf ("◈"); break;

                                case REACTEUR:  
                                    if (m->elements[k].entitee->reactor->build <= 0) /*--->*/ printf ("◬");
                                    else /*--->*/ printf (" "); 
                                    break;

                                case MINER:     
                                    if (m->elements[k].entitee->miner->build <= 0) /*----->*/ printf ("◭");
                                    else /*--->*/ printf (" "); 
                                    break;

                                case SHIELD:    
                                    if (m->elements[k].entitee->shield->build <= 0) /*---->*/ printf ("◩");
                                    else /*--->*/ printf (" "); 
                                    break;

                                case BEACON:    
                                    if (m->elements[k].entitee->beacon->build <= 0) /*---->*/ printf ("◉");
                                    else /*--->*/ printf (" "); 
                                    break;

                                case BOMBE:     
                                    if (m->elements[k].entitee->bombe->build <= 0) /*----->*/ printf ("◘");
                                    else /*--->*/ printf (" "); 
                                    break;

                                case CREEPERSPAWNER: printf ("◎"); break;
                            }
                        }
                        else if (m->elements[k].type == CURSOR) /*--->*/ printf ("○");
                        
                    }
                    else /*--->*/ printf (" ");
                    
                    k++;

                }
                
            }

        }

        printf ("\n");
        
    }
    
}

void afficherCarteV2 (Map* m)
{
    int k      = 0;
    int l      = 0;
    int p      = 0;
    int cCase  = 0;

    for (unsigned int i = 0; i < HAUTEUR * 2 + 2; i++)
    {
        for (unsigned int j = 0; j < LARGEUR * 2 + 2; j++)
        {
            if (i == 0)
            {
                switch (j)
                {
                    case 0              : printf ("╔"); break;
                    case LARGEUR * 2 + 1: printf ("╗"); break;
                    default             : printf ("═"); break;
                }
                
            }
            else if (i == HAUTEUR * 2 + 1)
            {
                switch (j)
                {
                    case 0              : printf ("╚"); break;
                    case LARGEUR * 2 + 1: printf ("╝"); break;
                    default             : printf ("═"); break;
                }
            }
            else
            {
                if (j == 0 || j == LARGEUR * 2 + 1) /*--->*/ printf ("║");
                else
                {
                    if (m->elements[k].visibilitee == 1)
                    {
                        if (m->elements[k].type == VIDE)
                        {
                            if (l % 2 != 0)
                            {
                                if (cCase == 0)
                                {
                                    if (m->elements[k].vide->creeperQuantity[0] == 0)
                                        printf (" ");
                                    else
                                        printf (".");
                                    
                                    cCase++;
                                }
                                else
                                {
                                    if (m->elements[k].vide->creeperQuantity[1] == 0)
                                        printf (" ");
                                    else
                                        printf (".");
                                    
                                    cCase--;
                                }
                            }
                            else
                            {
                                if (cCase == 0)
                                {
                                    if (m->elements[k].vide->creeperQuantity[2] == 0)
                                        printf (" ");
                                    else
                                        printf (".");
                                    
                                    cCase++;
                                }
                                else
                                {
                                    if (m->elements[k].vide->creeperQuantity[3] == 0)
                                        printf (" ");
                                    else
                                        printf (".");
                                    
                                    cCase--;
                                }

                            }

                        }
                        else if (m->elements[k].type == BLOCK)
                        {
                            switch (m->elements[k].block->type)
                            {
                                case DIRT: printf ("░"); break;
                                case STONE:
                                    switch (m->elements[k].block->stone->type)
                                    {
                                        case STONE1: printf ("▒"); break;
                                        case STONE2: printf ("▓"); break;
                                        case STONE3: printf ("█"); break;
                                    }
                                    break;
                                case GOLD: printf ("▚"); break;
                            }

                        }
                        else if (m->elements[k].type == ENTITY)
                        {
                            switch (m->elements[k].entitee->type)
                            {
                                case SHIP: printf ("◈"); break;

                                case REACTEUR:
                                    if (m->elements[k].entitee->reactor->build <= 0) /*--->*/ printf ("◬");
                                    else /*--->*/ printf (" "); 
                                    break;

                                case MINER:
                                    if (m->elements[k].entitee->miner->build <= 0) /*----->*/ printf ("◭");
                                    else /*--->*/ printf (" "); 
                                    break;

                                case SHIELD:
                                    if (m->elements[k].entitee->shield->build <= 0) /*---->*/ printf ("◩");
                                    else /*--->*/ printf (" "); 
                                    break;

                                case BEACON:
                                    if (m->elements[k].entitee->beacon->build <= 0) /*---->*/ printf ("◉");
                                    else /*--->*/ printf (" "); 
                                    break;

                                case BOMBE:     
                                    if (m->elements[k].entitee->bombe->build <= 0) /*----->*/ printf ("◘");
                                    else /*--->*/ printf (" "); 
                                    break;

                                case CREEPERSPAWNER:
                                    if (l % 2 != 0)
                                    {
                                        if (cCase == 0)
                                        {
                                            printf ("◎");
                                            cCase++;
                                        }
                                        else
                                        {
                                            if (m->elements[k].vide->creeperQuantity[1] == 0)
                                                printf (" ");
                                            else
                                                printf (".");
                                            
                                            cCase--;
                                        }

                                    }
                                    else
                                    {
                                        if (cCase == 0)
                                        {
                                            if (m->elements[k].vide->creeperQuantity[2] == 0)
                                                printf (" ");
                                            else
                                                printf (".");
                                            
                                            cCase++;
                                        }
                                        else
                                        {
                                            if (m->elements[k].vide->creeperQuantity[3] == 0)
                                                printf (" ");
                                            else
                                                printf (".");
                                            
                                            cCase--;
                                        }
                                        
                                    }

                                    break;
                                    
                            }
                        }
                        else if (m->elements[k].type == CURSOR) /*--->*/ printf ("○");
                        
                    }
                    else /*--->*/ printf (" ");
                    
                    k++;
                    p++;

                    if (p % 2 == 1) /*--->*/ k--;
                    else /*-------------->*/ p -= 2;

                }
                
            }

        }

        l++;

        if (l % 2 == 0) /*--->*/ k -= LARGEUR;
        

        printf ("\n");
        
    }
}

void afficherInterface (Map* m, Coord* _tabEntitee, int _nb_Entitee)
{
    if (m)
    {
        printf ("Nom de la carte : %s\n", m->nomDeLaCarte);

        printf ("Reserve d'energy : %.2lf / %.2lf", m->elements[LARGEUR * 2  + LARGEUR / 2].entitee->ship->energy_quantity, m->elements[LARGEUR *2  + LARGEUR / 2].entitee->ship->energy_storage);
        printf ("\tReserve d'or : %.2lf / %.2lf \n", m->elements[LARGEUR * 2  + LARGEUR / 2].entitee->ship->gold_quantity, m->elements[LARGEUR *2  + LARGEUR / 2].entitee->ship->gold_storage);

        printf ("Efficient E : %.2lf", m->elements[LARGEUR * 2  + LARGEUR / 2].entitee->ship->energy_efficient);
        printf ("\t\tEfficient Or : %.2lf \n", m->elements[LARGEUR * 2  + LARGEUR / 2].entitee->ship->gold_efficient);

        if (_tabEntitee)
        {
            int x, y;
            for (unsigned int i = 0; i < _nb_Entitee; i++)
            {
                x = _tabEntitee[i].x;
                y = _tabEntitee[i].y;
                switch (m->elements[LARGEUR * y + x].entitee->type)
                {
                    case 2:
                        printf ("Mineur (%.0lf ; %.0lf) power : %.2lf \n", _tabEntitee[i].x, _tabEntitee[i].y, m->elements[LARGEUR * y + x].entitee->miner->power_quantity);
                        break;
                    
                    case 4:
                        printf ("Beacon (%.0lf ; %.0lf) power : %.2lf \n", _tabEntitee[i].x, _tabEntitee[i].y, m->elements[LARGEUR * y + x].entitee->beacon->power_quantity);
                        break;

                    case 5:
                        printf ("Bombe  (%.0lf ; %.0lf) power : %.2lf \n", _tabEntitee[i].x, _tabEntitee[i].y, m->elements[LARGEUR * y + x].entitee->bombe->power_quantity);
                        break;
                }
            }
            
        }

    }
    
}

void afficherErreur (int* _erreur)
{
    switch (*_erreur)
    {
        case 1:  printf ("Vous ne pouvez rien supprimer sur cette case-là.                   \n");   break;
        case 2:  printf ("Vous ne pouvez pas ajouter ou supprimer d'entitée ici.             \n");   break;
        case 3:  printf ("Vous ne pouvez pas placer cette entitée-la.                        \n");   break;
        case 4:  printf ("Impossible de placer de reacteur ici.                              \n");   break;
        case 5:  printf ("Impossible de placer de mineur ici.                                \n");   break;
        case 6:  printf ("Impossible de placer de beacon ici.                                \n");   break;
        case 7:  printf ("Nombre maximum de cases pouvant être cassé à la suite, atteint.    \n");   break;
        case 8:  printf ("Nombre maximum d'entitée pouvant être ajouter à la suite, atteint. \n");   break;
        case 9:  printf ("Insérez une touche valide.                                         \n");   break;
        case 10: printf ("Vous ne pouvez pas casser ce block-là.                             \n");   break;
    }

    *_erreur = 0;
}

//--------------------------Affichage Graphique--------------------------//