/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionAffichage.c                    */
/* Numéro de version : 0.8.2                                 */
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

void afficherImage (int x, int y, char* nomFichier)
{
    SDL_Surface* surface_image = SDL_LoadBMP (nomFichier);

    if (surface_image)
    {
        SDL_Texture* image = SDL_CreateTextureFromSurface (renderer, surface_image);

        if (image)
        {
            SDL_SetRenderTarget (renderer, image);

            SDL_Rect r = (SDL_Rect){x, y};

            SDL_QueryTexture (image, NULL, NULL, &(r.w), &(r.h));

            SDL_RenderCopy (renderer, image, NULL, &r);
            SDL_SetRenderTarget (renderer, NULL);
            SDL_DestroyTexture (image);
        }
        else fprintf (stderr, "Erreur de création de la texture \n");

        SDL_FreeSurface (surface_image);
    }
    else fprintf (stderr, "Erreur de chargement de l'image %s \n", nomFichier);
    
}

void afficherMouvementCurseur (int Key, Map* m, Coord* _jPos)
{
    if (m)
    {
        int x = _jPos->x;
        int y = _jPos->y;

        if (m->elements[LARGEUR * y + x].block == NULL && m->elements[LARGEUR * y + x].entitee == NULL && m->elements[LARGEUR * y + x].visibilitee == 1)
        {
            m->elements[LARGEUR * y + x].type = VIDE;
            afficherImage (x * 30, y * 30, "img/sol.bmp");
        }
        else if (m->elements[LARGEUR * y + x].block != NULL && m->elements[LARGEUR * y + x].visibilitee == 1)
            afficherBlock (m->elements[LARGEUR * y + x].block);

        else if (m->elements[LARGEUR * y + x].entitee != NULL && m->elements[LARGEUR * y + x].visibilitee == 1)
            afficherEntitee (m->elements, LARGEUR * y + x);
        
        else
            afficherImage (x * 30, y * 30, "img/brouillard.bmp");

        switch (Key)
        {
            case SDLK_a:
                x--;
                afficherImage (x * 30, y * 30, "img/curseur.bmp");

                m->elements[LARGEUR * y + x].type = 3;

                break;
            case SDLK_s:
                y++;
                afficherImage (x * 30, y * 30, "img/curseur.bmp");

                m->elements[LARGEUR * y + x].type = 3;

                break;
            case SDLK_d:
                x++;
                afficherImage (x * 30, y * 30, "img/curseur.bmp");

                m->elements[LARGEUR * y + x].type = 3;

                break;
            case SDLK_w:
                y--;
                afficherImage (x * 30, y * 30, "img/curseur.bmp");

                m->elements[LARGEUR * y + x].type = 3;
        }

        _jPos->x = x;
        _jPos->y = y;
    }
    
}

void afficherBlock (Block* b)
{
    switch (b->type)
    {
        case DIRT : afficherImage (b->dirt->pos.x * 30, b->dirt->pos.y * 30, "img/dirt.bmp"); break;
        
        case STONE:
            switch (b->stone->type)
            {
                case STONE1: afficherImage (b->stone->pos.x * 30, b->stone->pos.y * 30, "img/stone1.bmp"); break;
                case STONE2: afficherImage (b->stone->pos.x * 30, b->stone->pos.y * 30, "img/stone2.bmp"); break;
                case STONE3: afficherImage (b->stone->pos.x * 30, b->stone->pos.y * 30, "img/stone3.bmp"); break;
            }
            break;
        
        case GOLD : afficherImage (b->gold->pos.x * 30, b->gold->pos.y * 30, "img/gold.bmp"); break;
    }
}

void afficherEntitee (Case* c, int pos)
{
    switch (c[pos].entitee->type)
    {
        case SHIP : afficherImage (c[pos].entitee->ship->pos.x * 30, c[pos].entitee->ship->pos.y * 30,   "img/ship.bmp"); break;
        case REACTEUR :
            if (c[pos].entitee->reactor->build <= 0)
            {
                afficherVide  (c[pos].vide);
                afficherImage (c[pos].entitee->reactor->pos.x * 30, c[pos].entitee->reactor->pos.y * 30,               "img/reactor.bmp");
            }
            else /*--->*/ afficherVide  (c[pos].vide);
            break;
        case MINER :
            if (c[pos].entitee->miner->build <= 0)
            {
                afficherVide  (c[pos].vide);
                afficherImage (c[pos].entitee->miner->pos.x * 30, c[pos].entitee->miner->pos.y * 30,                   "img/miner.bmp");
            }
            else /*--->*/ afficherVide  (c[pos].vide);
            break;
        case SHIELD :
            if (c[pos].entitee->shield->build <= 0)
            {
                afficherVide  (c[pos].vide);
                afficherImage (c[pos].entitee->shield->pos.x * 30, c[pos].entitee->shield->pos.y * 30,                 "img/shield.bmp");
            }
            else /*--->*/ afficherVide  (c[pos].vide);
            break;
        case BEACON :
            if (c[pos].entitee->beacon->build <= 0)
            {
                afficherVide  (c[pos].vide);
                afficherImage (c[pos].entitee->beacon->pos.x * 30, c[pos].entitee->beacon->pos.y * 30,                 "img/beacon.bmp");
            }
            else /*--->*/ afficherVide  (c[pos].vide);
            break;
        case BOMBE:
            if (c[pos].entitee->bombe->build <= 0)
            {
                afficherVide  (c[pos].vide);
                afficherImage (c[pos].entitee->bombe->pos.x * 30, c[pos].entitee->bombe->pos.y * 30,                   "img/Bombe.bmp");
            }
            else /*--->*/ afficherVide  (c[pos].vide);
            break;
        case CREEPERSPAWNER :
            afficherVide  (c[pos].vide);
            afficherImage (c[pos].entitee->creeperSpawner->pos.x * 30, c[pos].entitee->creeperSpawner->pos.y * 30, "img/Creeper_Spawner.bmp");
            break;
    }
}

void afficherVide (Vide* v)
{
//-----------------------Case 0-----------------------//

    if (v->creeperQuantity[0] > 0 && v->creeperQuantity[0] < 1000)
        afficherImage (v->pos.x * 30, v->pos.y * 30, "img/Creeper1.bmp");

    else if (v->creeperQuantity[0] >= 1000 && v->creeperQuantity[0] < 6000)
        afficherImage (v->pos.x * 30, v->pos.y * 30, "img/Creeper2.bmp");

    else if (v->creeperQuantity[0] >= 6000 && v->creeperQuantity[0] < 10000)
        afficherImage (v->pos.x * 30, v->pos.y * 30, "img/Creeper3.bmp");

    else if (v->creeperQuantity[0] >= 10000 && v->creeperQuantity[0] < 70000)
        afficherImage (v->pos.x * 30, v->pos.y * 30, "img/Creeper4.bmp");

    else if (v->creeperQuantity[0] >= 70000 && v->creeperQuantity[0] < 200000)
        afficherImage (v->pos.x * 30, v->pos.y * 30, "img/Creeper5.bmp");

    else if (v->creeperQuantity[0] >= 200000 && v->creeperQuantity[0] < 1000000)
        afficherImage (v->pos.x * 30, v->pos.y * 30, "img/Creeper6.bmp");

    else if (v->creeperQuantity[0] >= 1000000 && v->creeperQuantity[0] < 5000000)
        afficherImage (v->pos.x * 30, v->pos.y * 30, "img/Creeper7.bmp");

    else if (v->creeperQuantity[0] >= 5000000)
        afficherImage (v->pos.x * 30, v->pos.y * 30, "img/Creeper8.bmp");
    else
        afficherImage (v->pos.x * 30, v->pos.y * 30, "img/solMini.bmp");

    
//-----------------------Case 1-----------------------//

    if (v->creeperQuantity[1] > 0 && v->creeperQuantity[1] < 1000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30, "img/Creeper1.bmp");

    else if (v->creeperQuantity[1] >= 1000 && v->creeperQuantity[1] < 6000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30, "img/Creeper2.bmp");

    else if (v->creeperQuantity[1] >= 6000 && v->creeperQuantity[1] < 10000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30, "img/Creeper3.bmp");

    else if (v->creeperQuantity[1] >= 10000 && v->creeperQuantity[1] < 70000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30, "img/Creeper4.bmp");

    else if (v->creeperQuantity[1] >= 70000 && v->creeperQuantity[1] < 200000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30, "img/Creeper5.bmp");

    else if (v->creeperQuantity[1] >= 200000 && v->creeperQuantity[1] < 1000000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30, "img/Creeper6.bmp");

    else if (v->creeperQuantity[1] >= 1000000 && v->creeperQuantity[1] < 5000000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30, "img/Creeper7.bmp");

    else if (v->creeperQuantity[1] >= 5000000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30, "img/Creeper8.bmp");
    else
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30, "img/solMini.bmp");


//-----------------------Case 2-----------------------//

    if (v->creeperQuantity[2] > 0 && v->creeperQuantity[2] < 1000)
        afficherImage (v->pos.x * 30, v->pos.y * 30 + 15, "img/Creeper1.bmp");

    else if (v->creeperQuantity[2] >= 1000 && v->creeperQuantity[2] < 6000)
        afficherImage (v->pos.x * 30, v->pos.y * 30 + 15, "img/Creeper2.bmp");

    else if (v->creeperQuantity[2] >= 6000 && v->creeperQuantity[2] < 10000)
        afficherImage (v->pos.x * 30, v->pos.y * 30 + 15, "img/Creeper3.bmp");

    else if (v->creeperQuantity[2] >= 10000 && v->creeperQuantity[2] < 70000)
        afficherImage (v->pos.x * 30, v->pos.y * 30 + 15, "img/Creeper4.bmp");

    else if (v->creeperQuantity[2] >= 70000 && v->creeperQuantity[2] < 200000)
        afficherImage (v->pos.x * 30, v->pos.y * 30 + 15, "img/Creeper5.bmp");

    else if (v->creeperQuantity[2] >= 200000 && v->creeperQuantity[2] < 1000000)
        afficherImage (v->pos.x * 30, v->pos.y * 30 + 15, "img/Creeper6.bmp");

    else if (v->creeperQuantity[2] >= 1000000  && v->creeperQuantity[2] < 5000000)
        afficherImage (v->pos.x * 30, v->pos.y * 30 + 15, "img/Creeper7.bmp");

    else if (v->creeperQuantity[2] >= 5000000)
        afficherImage (v->pos.x * 30, v->pos.y * 30 + 15, "img/Creeper8.bmp");
    else
        afficherImage (v->pos.x * 30, v->pos.y * 30 + 15, "img/solMini.bmp");


//-----------------------Case 3-----------------------//

    if (v->creeperQuantity[3] > 0 && v->creeperQuantity[3] < 1000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30 + 15, "img/Creeper1.bmp");

    else if (v->creeperQuantity[3] >= 1000 && v->creeperQuantity[3] < 6000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30 + 15, "img/Creeper2.bmp");

    else if (v->creeperQuantity[3] >= 6000 && v->creeperQuantity[3] < 10000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30 + 15, "img/Creeper3.bmp");

    else if (v->creeperQuantity[3] >= 10000 && v->creeperQuantity[3] < 70000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30 + 15, "img/Creeper4.bmp");

    else if (v->creeperQuantity[3] >= 70000 && v->creeperQuantity[3] < 200000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30 + 15, "img/Creeper5.bmp");

    else if (v->creeperQuantity[3] >= 200000 && v->creeperQuantity[3] < 1000000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30 + 15, "img/Creeper6.bmp");

    else if (v->creeperQuantity[3] >= 1000000  && v->creeperQuantity[3] < 5000000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30 + 15, "img/Creeper7.bmp");

    else if (v->creeperQuantity[3] >= 5000000)
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30 + 15, "img/Creeper8.bmp");
    else
        afficherImage (v->pos.x * 30 + 15, v->pos.y * 30 + 15, "img/solMini.bmp");

}