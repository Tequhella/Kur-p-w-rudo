/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionMap.c                          */
/* Numéro de version : 0.8.2                                 */
/* Date              : 18/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/gestionMap.h"
#include "../headers/gestionMem.h"
#include "../headers/gestionAffichage.h"

//----------------------------Gestion Map----------------------------//

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
            detruireVide (m->elements[i].vide);
            m->elements[i].vide = NULL;

            m->elements[i].type  = BLOCK;
            m->elements[i].block = creerBlock (GOLD, 0, i % LARGEUR, i / LARGEUR);
        }
        else if (stone < 21)
        {
            stoneType = (rand() % 100 + 1);

            if (stoneType <= 5) /*---------->*/ stoneType = STONE3;
            else if (stoneType <= 30) /*---->*/ stoneType = STONE2;
            else if (stoneType <= 100) /*--->*/ stoneType = STONE1;

            detruireVide (m->elements[i].vide);
            m->elements[i].vide = NULL;

            m->elements[i].type  = BLOCK;
            m->elements[i].block = creerBlock (STONE, stoneType, i % LARGEUR, i / LARGEUR);
        }
        else if (dirt <= 100)
        {
            detruireVide (m->elements[i].vide);
            m->elements[i].vide = NULL;

            m->elements[i].type  = BLOCK;
            m->elements[i].block = creerBlock (DIRT, 0, i % LARGEUR, i / LARGEUR);
        } 
        else if (m->elements[i].type == BLOCK);
        else if (m->elements[i].type == ENTITY);
        else /*--->*/ m->elements[i].type = VIDE;
        
        
        if (relief > 0 && i % LARGEUR == 0) /*--->*/ relief -= 25;

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
                detruireBlock (m->elements[i].block);
                m->elements[i].block = NULL;

                m->elements[i].type = VIDE;
                m->elements[i].vide = creerVide (i);
            }
        }
        
    }
    
}

void creerCaverne (Map* m, unsigned int pos, int randMoins)
{
    
    while (pos > LARGEUR * HAUTEUR || m->elements[pos].type != BLOCK) /*--->*/ pos = rand() % LARGEUR * HAUTEUR + 280;
    
    if (m && m->elements[pos].type == BLOCK)
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
        m->elements[pos].vide = creerVide (pos);

        randMoins += 5;

        if (droite > 30 && m->elements[pos + 1].type == BLOCK) /*--------->*/ creerCaverne (m, pos + 1, randMoins);
        if (bas > 30 && m->elements[pos + LARGEUR].type == BLOCK) /*------>*/ creerCaverne (m, pos + LARGEUR, randMoins);
        if (gauche > 30 && m->elements[pos - 1].type == BLOCK) /*--------->*/ creerCaverne (m, pos - 1, randMoins);
        if (bas > 30 && m->elements[pos - LARGEUR].type == BLOCK) /*------>*/ creerCaverne (m, pos - LARGEUR, randMoins);
    }
    
}

int testAccessibilitee (Map* m, int x, int y)
{
    if (m)
    {
        m->elements[LARGEUR * y + x].cache = 1;
        
        if ((x == SHIPX + 1 && y == 2) || (x == SHIPX - 1 && y == 2) || (x == SHIPX && y == 1) || (x == SHIPX && y == 3))
        {
            m->elements[LARGEUR * SHIPY + x].cache = 0;
            return 1;
        }
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

void remplirStock (Map* m)
{
    if (m)
    {
        if (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity < m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_storage)
        {
            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity += m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient;

            while (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity > m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_storage)
                m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity -= 0.05;
        }

        if (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->gold_quantity < m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->gold_storage)
        {
            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->gold_quantity += m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->gold_efficient;

            while (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->gold_quantity > m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->gold_storage)
                m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->gold_quantity -= 0.05;
        }
    }
    
}

void visibilitee (Map* m, int x, int y)
{
    if (m)
    {
        switch (m->elements[LARGEUR * y + x].entitee->type)
        {
            case SHIP:
                    for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
                    {
                        if (i % LARGEUR < x)
                        {
                            if (i / LARGEUR < y)
                            {
                                if (x - i % LARGEUR <= 7 && y - i / LARGEUR <= 7 && (x - i % LARGEUR) + (y - i / LARGEUR) < 12)
                                    m->elements[i].visibilitee = 1;
                            }
                            else
                            {
                                if (x - i % LARGEUR <= 7 && i / LARGEUR - y <= 7 && (x - i % LARGEUR) + (i / LARGEUR - y) < 12)
                                    m->elements[i].visibilitee = 1;
                            }
                        }
                        else
                        {
                            if (i / LARGEUR < y)
                            {
                                if (i % LARGEUR - x <= 7 && y - i / LARGEUR <= 7 && (i % LARGEUR - x) + (y - i / LARGEUR) < 12)
                                    m->elements[i].visibilitee = 1;
                            }
                            else
                            {
                                if (i % LARGEUR - x <= 7 && i / LARGEUR - y <= 7 && (i % LARGEUR - x) + (i / LARGEUR - y) < 12)
                                    m->elements[i].visibilitee = 1;
                            }

                        }

                    }
                
                break;
            
            case BEACON:
                if (m->elements[LARGEUR * y + x].entitee->beacon->power_quantity > 0)
                {
                    for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
                    {
                        if (i % LARGEUR < x)
                        {
                            if (i / LARGEUR < y)
                            {
                                if (x - i % LARGEUR <= 7 && y - i / LARGEUR <= 7 && (x - i % LARGEUR) + (y - i / LARGEUR) < 12)
                                {
                                    m->elements[i].visibilitee = 1;
                                    if (m->elements[i].visibilitee == 1)
                                    {
                                        switch (m->elements[i].type)
                                        {
                                            case VIDE  : afficherVide    (m->elements[i].vide);    break;
                                            case BLOCK : afficherBlock   (m->elements[i].block);   break;
                                            case ENTITY: afficherEntitee (m->elements, i);         break;
                                        }

                                    }

                                }

                            }
                            else
                            {
                                if (x - i % LARGEUR <= 7 && i / LARGEUR - y <= 7 && (x - i % LARGEUR) + (i / LARGEUR - y) < 12)
                                {
                                    m->elements[i].visibilitee = 1;
                                    if (m->elements[i].visibilitee == 1)
                                    {
                                        switch (m->elements[i].type)
                                        {
                                            case VIDE  : afficherVide    (m->elements[i].vide);    break;
                                            case BLOCK : afficherBlock   (m->elements[i].block);   break;
                                            case ENTITY: afficherEntitee (m->elements, i);         break;
                                        }

                                    }

                                }
                            }
                        }
                        else
                        {
                            if (i / LARGEUR < y)
                            {
                                if (i % LARGEUR - x <= 7 && y - i / LARGEUR <= 7 && (i % LARGEUR - x) + (y - i / LARGEUR) < 12)
                                {
                                    m->elements[i].visibilitee = 1;
                                    if (m->elements[i].visibilitee == 1)
                                    {
                                        switch (m->elements[i].type)
                                        {
                                            case VIDE  : afficherVide    (m->elements[i].vide);    break;
                                            case BLOCK : afficherBlock   (m->elements[i].block);   break;
                                            case ENTITY: afficherEntitee (m->elements, i);         break;
                                        }

                                    }

                                }
                            }
                            else
                            {
                                if (i % LARGEUR - x <= 7 && i / LARGEUR - y <= 7 && (i % LARGEUR - x) + (i / LARGEUR - y) < 12)
                                {
                                    m->elements[i].visibilitee = 1;
                                    if (m->elements[i].visibilitee == 1)
                                    {
                                        switch (m->elements[i].type)
                                        {
                                            case VIDE  : afficherVide    (m->elements[i].vide);    break;
                                            case BLOCK : afficherBlock   (m->elements[i].block);   break;
                                            case ENTITY: afficherEntitee (m->elements, i);         break;
                                        }

                                    }

                                }
                            }

                        }

                    }

                }
                else
                {
                    for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
                    {
                        if (i % LARGEUR < x)
                        {
                            if (i / LARGEUR < y)
                            {
                                if (x - i % LARGEUR <= 7 && y - i / LARGEUR <= 7 && (x - i % LARGEUR) + (y - i / LARGEUR) < 12)
                                    m->elements[i].visibilitee = 0;
                            }
                            else
                            {
                                if (x - i % LARGEUR <= 7 && i / LARGEUR - y <= 7 && (x - i % LARGEUR) + (i / LARGEUR - y) < 12)
                                    m->elements[i].visibilitee = 0;
                            }
                        }
                        else
                        {
                            if (i / LARGEUR < y)
                            {
                                if (i % LARGEUR - x <= 7 && y - i / LARGEUR <= 7 && (i % LARGEUR - x) + (y - i / LARGEUR) < 12)
                                    m->elements[i].visibilitee = 0;
                            }
                            else
                            {
                                if (i % LARGEUR - x <= 7 && i / LARGEUR - y <= 7 && (i % LARGEUR - x) + (i / LARGEUR - y) < 12)
                                    m->elements[i].visibilitee = 0;
                            }

                        }

                    }
                }
                
                break;
        }

    }
    
}


//---------------------------Gestion Block---------------------------//

void casserBlock 
(
    Map* m, 
    Coord* _bPos, 
    int* _blockAcasser, 
    int* _compte, 
    int* _nb_besoin, 
    int* _erreur
)
{
    if (m)
    {
        int tempBAC       = *_blockAcasser;
        int temp_nbBesoin = *_nb_besoin;

        int x, y;

        for (unsigned int i = 0; i < tempBAC; i++)
        {
            x = _bPos[i].x;
            y = _bPos[i].y;
            if (_compte[i] == 0)
            {
                _compte[i] = testAccessibilitee (m, x, y);
                decache (m);
                if (_compte[i] == 1) /*--->*/temp_nbBesoin++;
                
            }
            if (m->elements[LARGEUR * y + x].block->dirt != NULL && _compte[i] == 1)
            {
                if (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity > 0)
                {
                    m->elements[LARGEUR * y + x].block->dirt->hardness --;
                    m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                }
                else
                {
                    m->elements[LARGEUR * y + x].block->dirt->hardness -= m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient / temp_nbBesoin;
                    m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                }
                
                if (m->elements[LARGEUR * y + x].block->dirt->hardness <= 0)
                {
                    if (m->elements[LARGEUR * (y - 1) + x].type == ENTITY)
                    {
                        if (m->elements[LARGEUR * (y - 1) + x].entitee->type == BEACON)
                        {
                            if ((m->elements[LARGEUR * (y - 2) + x].type == VIDE     || m->elements[LARGEUR * (y - 2) + x].type == CURSOR)     && 
                                (m->elements[LARGEUR * (y - 1) + x - 1].type == VIDE || m->elements[LARGEUR * (y - 1) + x - 1].type == CURSOR) && 
                                (m->elements[LARGEUR * (y - 1) + x + 1].type == VIDE || m->elements[LARGEUR * (y - 1) + x + 1].type == CURSOR))
                            {
                                *_erreur = 10;
                            }
                                
                        }
                        else if (m->elements[LARGEUR * (y - 1) + x].entitee->type == REACTEUR || m->elements[LARGEUR * (y - 1) + x].entitee->type == MINER)
                            *_erreur = 10;
                        
                    }
                    if (m->elements[LARGEUR * (y + 1) + x].type == ENTITY)
                        if (m->elements[LARGEUR * (y + 1) + x].entitee->type == BEACON)
                            if ((m->elements[LARGEUR * (y + 2) + x].type == VIDE     || m->elements[LARGEUR * (y + 2) + x].type == CURSOR)     &&
                                (m->elements[LARGEUR * (y + 1) + x - 1].type == VIDE || m->elements[LARGEUR * (y + 1) + x - 1].type == CURSOR) &&
                                (m->elements[LARGEUR * (y + 1) + x + 1].type == VIDE || m->elements[LARGEUR * (y + 1) + x + 1].type == CURSOR))
                            {
                                *_erreur = 10;
                            }
                    
                    if (m->elements[LARGEUR * y + x - 1].type == ENTITY)
                        if (m->elements[LARGEUR * y + x - 1].entitee->type == BEACON)
                            if ((m->elements[LARGEUR * (y - 1) + x - 1].type == VIDE || m->elements[LARGEUR * (y - 1) + x - 1].type == CURSOR) &&
                                (m->elements[LARGEUR * (y + 1) + x - 1].type == VIDE || m->elements[LARGEUR * (y + 1) + x - 1].type == CURSOR) &&
                                (m->elements[LARGEUR * y + x - 2].type == VIDE       || m->elements[LARGEUR * y + x - 2].type == CURSOR))
                            {
                                *_erreur = 10;
                            }
                            
                    if (m->elements[LARGEUR * y + x + 1].type == ENTITY)
                        if (m->elements[LARGEUR * y + x + 1].entitee->type == BEACON)
                            if ((m->elements[LARGEUR * (y - 1) + x + 1].type == VIDE || m->elements[LARGEUR * (y - 1) + x + 1].type == CURSOR) && 
                                (m->elements[LARGEUR * (y + 1) + x + 1].type == VIDE || m->elements[LARGEUR * (y + 1) + x + 1].type == CURSOR) &&
                                (m->elements[LARGEUR * y + x + 2].type == VIDE       || m->elements[LARGEUR * y + x + 2].type == CURSOR))
                            {
                                *_erreur = 10;
                            }
                            
                    
                    if (*_erreur != 10)
                    {
                        afficherImage (m->elements[LARGEUR * y + x].block->dirt->pos.x, m->elements[LARGEUR * y + x].block->dirt->pos.y, "img/sol.bmp");
                        
                        detruireBlock (m->elements[LARGEUR * y + x].block);
                        m->elements   [LARGEUR * y + x].block = NULL;

                        m->elements[LARGEUR * y + x].type = VIDE;
                        m->elements[LARGEUR * y + x].vide = creerVide (LARGEUR * y + x);
                    }
                    else /*--->*/ m->elements[LARGEUR * y + x].block->dirt->hardness += 3;

                    _bPos[i] = _bPos[tempBAC - 1];
                    _bPos[tempBAC - 1] = (Coord){0, 0};

                    _compte[i] = _compte[tempBAC - 1];
                    _compte[tempBAC - 1] = 0;

                    tempBAC--;
                    temp_nbBesoin--;
                    i--;
                    
                }

            }
            else if (m->elements[LARGEUR * y + x].block->stone != NULL && _compte[i] == 1)
            {
                if (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity > 0)
                {
                    m->elements[LARGEUR * y + x].block->stone->hardness --;
                    m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                }
                else
                {
                    m->elements[LARGEUR * y + x].block->stone->hardness -= m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient / temp_nbBesoin;
                    m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                }

                if (m->elements[LARGEUR * y + x].block->stone->hardness <= 0)
                {
                    if (m->elements[LARGEUR * (y - 1) + x].type == ENTITY)
                    {
                        if (m->elements[LARGEUR * (y - 1) + x].entitee->type == BEACON)
                        {
                            if ((m->elements[LARGEUR * (y - 2) + x].type == VIDE     || m->elements[LARGEUR * (y - 2) + x].type == CURSOR)     && 
                                (m->elements[LARGEUR * (y - 1) + x - 1].type == VIDE || m->elements[LARGEUR * (y - 1) + x - 1].type == CURSOR) && 
                                (m->elements[LARGEUR * (y - 1) + x + 1].type == VIDE || m->elements[LARGEUR * (y - 1) + x + 1].type == CURSOR))
                            {
                                *_erreur = 10;
                            }
                                
                        }
                        else if (m->elements[LARGEUR * (y - 1) + x].entitee->type == REACTEUR || m->elements[LARGEUR * (y - 1) + x].entitee->type == MINER)
                            *_erreur = 10;
                        
                    }
                    if (m->elements[LARGEUR * (y + 1) + x].type == ENTITY)
                        if (m->elements[LARGEUR * (y + 1) + x].entitee->type == BEACON)
                            if ((m->elements[LARGEUR * (y + 2) + x].type == VIDE     || m->elements[LARGEUR * (y + 2) + x].type == CURSOR)     &&
                                (m->elements[LARGEUR * (y + 1) + x - 1].type == VIDE || m->elements[LARGEUR * (y + 1) + x - 1].type == CURSOR) &&
                                (m->elements[LARGEUR * (y + 1) + x + 1].type == VIDE || m->elements[LARGEUR * (y + 1) + x + 1].type == CURSOR))
                            {
                                *_erreur = 10;
                            }
                    
                    if (m->elements[LARGEUR * y + x - 1].type == ENTITY)
                        if (m->elements[LARGEUR * y + x - 1].entitee->type == BEACON)
                            if ((m->elements[LARGEUR * (y - 1) + x - 1].type == VIDE || m->elements[LARGEUR * (y - 1) + x - 1].type == CURSOR) &&
                                (m->elements[LARGEUR * (y + 1) + x - 1].type == VIDE || m->elements[LARGEUR * (y + 1) + x - 1].type == CURSOR) &&
                                (m->elements[LARGEUR * y + x - 2].type == VIDE       || m->elements[LARGEUR * y + x - 2].type == CURSOR))
                            {
                                *_erreur = 10;
                            }
                            
                    if (m->elements[LARGEUR * y + x + 1].type == ENTITY)
                        if (m->elements[LARGEUR * y + x + 1].entitee->type == BEACON)
                            if ((m->elements[LARGEUR * (y - 1) + x + 1].type == VIDE || m->elements[LARGEUR * (y - 1) + x + 1].type == CURSOR) && 
                                (m->elements[LARGEUR * (y + 1) + x + 1].type == VIDE || m->elements[LARGEUR * (y + 1) + x + 1].type == CURSOR) &&
                                (m->elements[LARGEUR * y + x + 2].type == VIDE       || m->elements[LARGEUR * y + x + 2].type == CURSOR))
                            {
                                *_erreur = 10;
                            }
                        
                    
                    if (*_erreur != 10)
                    {
                        afficherImage (m->elements[LARGEUR * y + x].block->stone->pos.x, m->elements[LARGEUR * y + x].block->stone->pos.y, "img/sol.bmp");

                        detruireBlock (m->elements[LARGEUR * y + x].block);
                        m->elements   [LARGEUR * y + x].block = NULL;

                        m->elements[LARGEUR * y + x].type = VIDE;
                        m->elements[LARGEUR * y + x].vide = creerVide (LARGEUR * y + x);
                    }
                    else
                    {
                        switch (m->elements[LARGEUR * y + x].block->stone->type)
                        {
                            case STONE1: m->elements[LARGEUR * y + x].block->stone->hardness += 7;  break;
                            case STONE2: m->elements[LARGEUR * y + x].block->stone->hardness += 15; break;
                            case STONE3: m->elements[LARGEUR * y + x].block->stone->hardness += 30; break;
                        }
                    }

                    _bPos[i] = _bPos[tempBAC - 1];
                    _bPos[tempBAC - 1] = (Coord){0, 0};

                    _compte[i] = _compte[tempBAC - 1];
                    _compte[tempBAC - 1] = 0;

                    tempBAC--;
                    temp_nbBesoin--;
                    i--;
                    
                }

            }

        }

        *_blockAcasser = tempBAC;
        *_nb_besoin    = temp_nbBesoin;
    }
    
}
