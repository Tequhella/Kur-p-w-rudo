/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : fonction.c                            */
/* Numéro de version : 0.4.2                                 */
/* Date              : 21/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "fonction.h"

//-----------------------------Gestion Map-----------------------------//

Map* creerCarte (double dimX, double dimY, char* nomDeLaCarte)
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
                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee = creerEntitee (LARGEUR / 2, 2, SHIP);
                m->elements[LARGEUR * 2 + LARGEUR / 2].type = ENTITY;
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

void detruireCarte (Map* m)
{
    if (m)
    {
        if (m->elements)
        {
            for (unsigned int i = 0; i < m->dimX*m->dimY; i++) 
            {
                detruireBlock (m->elements[i].block);
                detruireEntitee (m->elements[i].entitee);
            }
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
                    if (m->elements[k].type == 0) /*--->*/ printf (" ");
                    else if (m->elements[k].type == 1)
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
                    else if (m->elements[k].type == 2)
                    {
                        switch (m->elements[k].entitee->type)
                        {
                            case 0: printf ("◈"); break;
                            case 1: if (m->elements[k].entitee->reactor->build <= 0) /*--->*/ printf ("◬");
                                    else /*--->*/ printf (" "); break;
                            case 2: if (m->elements[k].entitee->miner->build <= 0) /*----->*/ printf ("◭");
                                    else /*--->*/ printf (" "); break;
                            case 3: if (m->elements[k].entitee->shield->build <= 0) /*---->*/ printf ("◩");
                                    else /*--->*/ printf (" "); break;
                            case 4: if (m->elements[k].entitee->beacon->build <= 0) /*---->*/ printf ("◉");
                                    else /*--->*/ printf (" "); break;
                            case 5: if (m->elements[k].entitee->bombe->build <= 0) /*----->*/ printf ("◘");
                                    else /*--->*/ printf (" "); break;
                            case 9: printf ("◎"); break;
                        }
                    }
                    else if (m->elements[k].type == 3) /*--->*/ printf ("○");
                    
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

        if (gold < 3)
        {
            m->elements[i].type  = BLOCK;
            m->elements[i].block = creerBlock (GOLD, 0, i % LARGEUR, i / LARGEUR);
        }
        else if (stone < 21)
        {
            stoneType = (rand() % 100 + 1);

            if (stoneType <= 5) /*---------->*/ stoneType = 3;
            else if (stoneType <= 30) /*---->*/ stoneType = 2;
            else if (stoneType <= 100) /*--->*/ stoneType = 1;

            m->elements[i].type  = BLOCK;
            m->elements[i].block = creerBlock (STONE, stoneType, i % LARGEUR, i / LARGEUR);
        }
        else if (dirt <= 100)
        {
            m->elements[i].type  = BLOCK;
            m->elements[i].block = creerBlock (DIRT, 0, i % LARGEUR, i / LARGEUR);
        } 
        else if (m->elements[i].type == BLOCK);
        else if (m->elements[i].type == ENTITY);
        else /*--->*/ m->elements[i].type = VIDE;
        
        
        if (relief > 0 & i % LARGEUR == 0) /*--->*/ relief -= 25;

        m->elements[i].cache = 0;

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

        detruireBlock (m->elements[pos].block);
        m->elements[pos].block = NULL;
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
                    b->type           = DIRT;
                    b->dirt->hardness = 3;
                    b->dirt->pos      = (Coord) {posX, posY};
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
                    b->type        = STONE;
                    b->stone->type = typeStone;
                    switch (typeStone)
                    {
                        case 1: b->stone->hardness = 7;  break;
                        case 2: b->stone->hardness = 15; break;
                        case 3: b->stone->hardness = 30; break;
                    }
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
                    b->type           = GOLD;
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

//----------------------------Gestion Entité---------------------------//

Entity* creerEntitee (double x, double y, unsigned int type)
{
    Entity* e = malloc (sizeof(Entity));

    if (e)
    {
        switch (type)
        {
            case 0:
                e->type = SHIP;
                e->ship = malloc (sizeof(Ship));

                e->ship->health           = 1000;
                e->ship->energy_quantity  = 0;
                e->ship->energy_storage   = 20;
                e->ship->energy_efficient = 1;
                /* e->ship->energy_speed  = 1;*/
                e->ship->gold_quantity    = 0;
                e->ship->gold_storage     = 20;
                e->ship->gold_efficient   = 0;
                e->ship->range            = 7;
                e->ship->pos              = (Coord){x, y};
                
                e->reactor        = NULL;
                e->miner          = NULL;
                e->shield         = NULL;
                e->beacon         = NULL;
                e->creeperSpawner = NULL;
                break;
            
            case 1:
                e->type    = REACTEUR;
                e->reactor = malloc (sizeof(Reactor));

                e->reactor->build        = 4;
                e->reactor->pos          = (Coord){x, y};

                e->ship           = NULL;
                e->miner          = NULL;
                e->shield         = NULL;
                e->beacon         = NULL;
                e->creeperSpawner = NULL;
                break;
                    
            case 2: 
                e->type  = MINER;
                e->miner = malloc (sizeof(Miner));

                e->miner->build          = 5;
                e->miner->power_quantity = 0;
                e->miner->power_max      = 20;
                e->miner->pos            = (Coord){x, y};

                e->ship           = NULL;
                e->reactor        = NULL;
                e->shield         = NULL;
                e->beacon         = NULL;
                e->creeperSpawner = NULL;
                break;
            
            case 3:
                e->type   = SHIELD;
                e->shield = malloc (sizeof(Shield));

                e->shield->build  = 4;
                e->shield->health = 20;
                e->shield->pos    = (Coord){x, y};

                e->ship           = NULL;
                e->reactor        = NULL;
                e->miner          = NULL;
                e->beacon         = NULL;
                e->creeperSpawner = NULL;
                break;
            
            case 4:
                e->type   = BEACON;
                e->beacon = malloc (sizeof(Beacon));

                e->beacon->build          = 7;
                e->beacon->power_max      = 20;
                e->beacon->power_quantity = 0;
                e->beacon->range          = 7;
                e->beacon->pos            = (Coord){x, y};

                e->ship           = NULL;
                e->reactor        = NULL;
                e->miner          = NULL;
                e->shield         = NULL;
                e->creeperSpawner = NULL;
                break;
            
            case 5:
                e->type  = BOMBE;
                e->bombe = malloc (sizeof(Bomb));

                e->bombe->build          = 20;
                e->bombe->power_max      = 20;
                e->bombe->power_quantity = 0;
                e->bombe->range          = 2;
                e->bombe->damage         = 100;
                e->bombe->pos            = (Coord){x, y};

                e->ship           = NULL;
                e->reactor        = NULL;
                e->miner          = NULL;
                e->shield         = NULL;
                e->beacon         = NULL;
                e->creeperSpawner = NULL;
                break;
            
            case 9:
                e->type = CREEPERSPAWNER;
                e->creeperSpawner = malloc (sizeof(CreeperSpawner));

                e->creeperSpawner->health = 100;
                e->creeperSpawner->pulse  = 0.5;
                e->creeperSpawner->power  = 50;
                e->creeperSpawner->pos    = (Coord){x, y};

                e->ship    = NULL;
                e->reactor = NULL;
                e->miner   = NULL;
                e->shield  = NULL;
                e->beacon  = NULL;
                break;
        }

    }
    else
    {
        perror ("Erreur d'allocation de l'entitee");
        exit (-1);
    }

    return e;
    
}

void detruireEntitee (Entity* e)
{
    if (e)
    {
        if (e->ship)
        {
            free (e->ship);
            e->ship = NULL;
        }
        else if (e->reactor)
        {
            free (e->reactor);
            e->reactor = NULL;
        }
        else if (e->miner)
        {
            free (e->miner);
            e->miner = NULL;
        }
        else if (e->shield)
        {
            free (e->shield);
            e->shield = NULL;
        }
        else if (e->beacon)
        {
            free (e->beacon);
            e->beacon = NULL;
        }
        else if (e->bombe)
        {
            free (e->bombe);
            e->bombe = NULL;
        }
        else if (e->creeperSpawner)
        {
            free (e->creeperSpawner);
            e->creeperSpawner = NULL;
        }
        
        else
        {
            perror ("Erreur d'allocation de l'entitee");
            exit (-1);
        }

        free (e);
        e = NULL;

    }
    
}

void ajouterEntitee (Case* c, int x, int y, unsigned int type, unsigned int* erreur)
{
    if (c)
    {
        switch (type)
        {
            case 48: *erreur = 3; break;
            case 49:
                if (c[LARGEUR * (y + 1) + x].type != VIDE) /*--->*/ c[LARGEUR * y + x].entitee = creerEntitee(x, y, REACTEUR);
                else /*--->*/ *erreur = 4;
                break;

            case 50:
                if (c[LARGEUR * (y + 1) + x].block != NULL)
                    if (c[LARGEUR * (y + 1) + x].block->type == GOLD) /*--->*/ c[LARGEUR * y + x].entitee = creerEntitee(x, y, MINER);
                    else /*--->*/ *erreur = 5;
                else /*--->*/ *erreur = 5;
                break;

            case 51: c[LARGEUR * y + x].entitee = creerEntitee(x, y, SHIELD); break;
            case 52: 
                if (c[LARGEUR * (y + 1) + x].type == BLOCK || c[LARGEUR * (y - 1) + x].type == BLOCK || c[LARGEUR * y + (x + 1)].type == BLOCK || c[LARGEUR * y + (x - 1)].type == BLOCK)
                //--▼-----------------------------------------------------▼--*/
                    c[LARGEUR * y + x].entitee = creerEntitee(x, y, BEACON);
                else /*--->*/ *erreur = 6;
                break;

            case 53: c[LARGEUR * y + x].entitee = creerEntitee(x, y, BOMBE); break;
            
        }

    }
    
}

void ajouterSpawnerHasard (Case* c, unsigned int nb_Spawner)
{
    if (c)
    {
        int i     = LARGEUR * 10;
        int YesNo = 0;

        while (nb_Spawner != 0)
        {
            YesNo = rand() % 10000;
            if (c[i].type == VIDE && YesNo < 1)
            {
                c[i].entitee = creerEntitee(i % LARGEUR, i / LARGEUR, CREEPERSPAWNER);
                c[i].type = ENTITY;
                nb_Spawner--;
            }
            
            if (i != LARGEUR * HAUTEUR) /*--->*/ i++;
            else /*-------------------------->*/ i = LARGEUR * 10;
        }
        
    }
    
}

int testAccessibilitee (Map* m, int x, int y)
{
    if (m)
    {
        m->elements[LARGEUR * y + x].cache = 1;
        
        if ((x == LARGEUR / 2 + 1 && y == 2) || (x == LARGEUR / 2 - 1 && y == 2) || (x == LARGEUR / 2 && y == 1) || (x == LARGEUR / 2 && y == 3))
        {
            m->elements[LARGEUR * y + x].cache = 0;
            return 1;
        }
        

        /*
        if (m->elements[LARGEUR * y + (x + 1)].type == ENTITY)
        {
            if (m->elements[LARGEUR * y + (x + 1)].entitee->type == 0)
            {
                m->elements[LARGEUR * y + x].cache = 0;
                return 1;
            }
        }
        else if (m->elements[LARGEUR * (y - 1) + x].type == ENTITY)
        {
            if (m->elements[LARGEUR * (y - 1) + x].entitee->type == 0)
            {
                m->elements[LARGEUR * y + x].cache = 0;
                return 1;
            }
        }
        else if (m->elements[LARGEUR * y + (x - 1)].type == ENTITY)
        {
            if (m->elements[LARGEUR * y + (x - 1)].entitee->type == 0)
            {
                m->elements[LARGEUR * y + x].cache = 0;
                return 1;
            }
        }
        else if (m->elements[LARGEUR * (y + 1) + x].type == ENTITY)
        {
            if (m->elements[LARGEUR * (y + 1) + x].entitee->type == 0)
            {
                m->elements[LARGEUR * y + x].cache = 0;
                return 1;
            }
        }
        */
        
        else if (y == 2 && x > 17)
        {
            if (m->elements[LARGEUR * y + (x - 1)].type != BLOCK && m->elements[LARGEUR * y + (x - 1)].cache == 0 && (x - 1) >= 0 && testAccessibilitee (m, x - 1, y) == 1)
            {
                m->elements[LARGEUR * y + x].cache = 0;
                return 1;
            }
        }
        else if (y == 2 && x < 17)
        {
            if (m->elements[LARGEUR * y + (x + 1)].type != BLOCK && m->elements[LARGEUR * y + (x + 1)].cache == 0 && (x + 1) < LARGEUR && testAccessibilitee (m, x + 1, y) == 1)
            {
                m->elements[LARGEUR * y + x].cache = 0;
                return 1;
            }
        }

        else if (m->elements[LARGEUR * (y - 1) + x].type != BLOCK && m->elements[LARGEUR * (y - 1) + x].cache == 0 && (y - 1) >= 0 && testAccessibilitee (m, x, y - 1) == 1)
        {
            m->elements[LARGEUR * y + x].cache = 0;
            return 1;
        }
        else if (m->elements[LARGEUR * y + (x + 1)].type != BLOCK && m->elements[LARGEUR * y + (x + 1)].cache == 0 && (x + 1) < LARGEUR && testAccessibilitee (m, x + 1, y) == 1)
        {
            m->elements[LARGEUR * y + x].cache = 0;
            return 1;
        }
        else if (m->elements[LARGEUR * y + (x - 1)].type != BLOCK && m->elements[LARGEUR * y + (x - 1)].cache == 0 && (x - 1) >= 0 && testAccessibilitee (m, x - 1, y) == 1)
        {
            m->elements[LARGEUR * y + x].cache = 0;
            return 1;
        }
        else if (m->elements[LARGEUR * (y + 1) + x].type != BLOCK && m->elements[LARGEUR * (y + 1) + x].cache == 0 && (y + 1) < HAUTEUR && testAccessibilitee (m, x, y + 1) == 1)
        {
            m->elements[LARGEUR * y + x].cache = 0;
            return 1;
        }
        
    }
    
    return 0;
}

void decache (Map* m)
{
    if (m)
    {
        for (unsigned int i = 0; i < HAUTEUR*LARGEUR; i++)
            if (m->elements[i].type == VIDE && m->elements[i].cache == 1) 
                    m->elements[i].cache = 0;
    }
    
}

//---------------------------Gestion Interface-------------------------//

void afficherInterface (Map* m)
{
    if (m)
    {
        printf ("Nom de la carte : %s\n", m->nomDeLaCarte);

        printf ("Reserve d'energy : %.2lf / %.2lf", m->elements[LARGEUR * 2  + LARGEUR / 2].entitee->ship->energy_quantity, m->elements[LARGEUR *2  + LARGEUR / 2].entitee->ship->energy_storage);
        printf ("\tReserve d'or : %.2lf / %.2lf \n", m->elements[LARGEUR * 2  + LARGEUR / 2].entitee->ship->gold_quantity, m->elements[LARGEUR *2  + LARGEUR / 2].entitee->ship->gold_storage);

        printf ("Efficient E : %.2lf", m->elements[LARGEUR * 2  + LARGEUR / 2].entitee->ship->energy_efficient);
        printf ("\t\tEfficient Or : %.2lf \n", m->elements[LARGEUR * 2  + LARGEUR / 2].entitee->ship->gold_efficient);
    }
    
}
