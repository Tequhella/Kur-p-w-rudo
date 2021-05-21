/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionMem.c                          */
/* Numéro de version : 0.6.1                                 */
/* Date              : 18/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/gestionMem.h"
#include "../headers/gestionMap.h"

//-----------------------------Gestion Mem Map-----------------------------//

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

                for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
                    m->elements[i].visibilitee = 0;
                
                visibilitee (m, m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->pos.x, m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->pos.y);

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

//----------------------------Gestion Mem Block----------------------------//

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

//----------------------------Gestion Mem Entité---------------------------//

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
                e->bombe          = NULL;
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
                e->bombe          = NULL;
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
                e->bombe          = NULL;
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
                e->bombe          = NULL;
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
                e->bombe          = NULL;
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
                e->bombe   = NULL;
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
