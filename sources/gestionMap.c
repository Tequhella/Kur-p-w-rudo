/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionMap.c                          */
/* Numéro de version : 0.5.1                                 */
/* Date              : 21/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/gestionMap.h"
#include "../headers/gestionMem.h"

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
        
        
        if (relief > 0 && i % LARGEUR == 0) /*--->*/ relief -= 25;

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
                m->elements[i].block = NULL;

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

void remplirStock (Map* m)
{
    if (m)
    {
        if (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity < m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_storage)
        {
            m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity += m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient;

            while (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_storage)
                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity -= 0.05;
        }

        if (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_quantity < m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_storage)
        {
            m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_quantity += m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_efficient;

            while (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_quantity > m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_storage)
                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_quantity -= 0.05;
        }
    }
    
}

//---------------------------Gestion Block---------------------------//

void casserBlock (Map* m, Coord* _bPos, int* _blockAcasser, int* _compte, int* _nb_besoin)
{
    if (m)
    {
        int tempBAC       = *_blockAcasser;
        int temp_nbBesoin = *_nb_besoin;
        if (tempBAC > 0)
        {
            _compte = (int*) realloc (_compte, sizeof(int) * tempBAC);
            if (_compte[tempBAC - 1] != 1) /*--->*/ _compte[tempBAC - 1] = 0;

            for (unsigned int i = 0; i < tempBAC; i++)
            {
                if (_compte[i] == 0)
                {
                    _compte[i] = testAccessibilitee (m, _bPos[i].x, _bPos[i].y);
                    decache (m);
                    if (_compte[i] == 1) /*--->*/temp_nbBesoin++;
                    
                }
                if (m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].block->dirt != NULL && _compte[i] == 1)
                {
                    if (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                    {
                        m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].block->dirt->hardness --;
                        m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                    }
                    else
                    {
                        m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].block->dirt->hardness -= m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / temp_nbBesoin;
                        m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                    }
                    
                    if (m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].block->dirt->hardness <= 0)
                    {
                        detruireBlock (m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].block);

                        m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].block = NULL;
                        m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].type = VIDE;

                        _bPos[i] = _bPos[tempBAC - 1];
                        _bPos[tempBAC - 1] = (Coord){0, 0};

                        _compte[i] = _compte[tempBAC - 1];
                        _compte[tempBAC - 1] = 0;

                        tempBAC--;
                        temp_nbBesoin--;
                        i--;
                    }

                }
                else if (m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].block->stone != NULL && _compte[i] == 1)
                {
                    if (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                    {
                        m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].block->stone->hardness --;
                        m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                    }
                    else
                    {
                        m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].block->stone->hardness -= m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / temp_nbBesoin;
                        m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                    }

                    if (m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].block->stone->hardness <= 0)
                    {
                        detruireBlock (m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].block);

                        m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].block = NULL;
                        m->elements[LARGEUR * (int)_bPos[i].y + (int)_bPos[i].x].type = VIDE;

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
            
        }

        *_blockAcasser = tempBAC;
        *_nb_besoin    = temp_nbBesoin;
    }
    
}

//--------------------------Gestion Entitee--------------------------//

void ajouterStructure (Case* c, int x, int y, unsigned int type, int* erreur)
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

Coord* constructionStructure 
(
    Map* m,
    Coord* _ePos,
    Coord* _tabEntitee,
    int* _entiteeAcreer,
    int* _compteE,
    int* _nb_Entitee,
    int* _nb_besoin,
    int* _sortie
)
{
    if (m)
    {
        int tempEAC         = *_entiteeAcreer;
        int temp_nbEntitee  = *_nb_Entitee;
        int temp_nbBesoin   = *_nb_besoin;
        int temp_sortie     = *_sortie;

        if (tempEAC > 0)
        {
            _compteE = (int*) realloc (_compteE, sizeof(int) * tempEAC);
            if (_compteE[tempEAC - 1] != 1) /*--->*/ _compteE[tempEAC - 1] = 0;
            
            for (unsigned int i = 0; i < tempEAC; i++)
            {
                if (_compteE[i] == 0)
                {
                    _compteE[i] = testAccessibilitee(m, _ePos[i].x, _ePos[i].y);
                    decache (m);
                    if (_compteE[i] == 1) /*--->*/ temp_nbBesoin++;
                    
                }
                if (_compteE[i] == 1)
                {
                    switch (m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->type)
                    {
                        case 1:
                            if (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                            {
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->reactor->build --;
                                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }
                            else
                            {
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->reactor->build -= m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / temp_nbBesoin;
                                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }

                            if (m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->reactor->build <= 0)
                            {
                                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient += 0.15;
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].type = ENTITY;

                                _ePos[i] = _ePos[tempEAC - 1];

                                _compteE[i] = _compteE[tempEAC - 1];
                                _compteE[tempEAC - 1] = 0;

                                tempEAC--;
                                temp_nbBesoin--;
                                i--;
                            }
                            break;
                        
                        case 2:
                            if (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                            {
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->miner->build --;
                                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }
                            else
                            {
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->miner->build -= m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / temp_nbBesoin;
                                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }

                            if (m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->miner->build <= 0)
                            {
                                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_efficient += 0.15;
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].type = ENTITY;



                                temp_nbEntitee++;
                                Coord temp_tabEntitee[temp_nbEntitee];

                                for (unsigned int j = 0; j < temp_nbEntitee; j++)
                                    temp_tabEntitee[j] = _tabEntitee[j];
                                
                                _tabEntitee = (Coord*) realloc (_tabEntitee, sizeof(Coord) * temp_nbEntitee);

                                for (unsigned int j = 0; j < temp_nbEntitee; j++)
                                    _tabEntitee[j] = temp_tabEntitee[j];
                                
                                _tabEntitee[temp_nbEntitee - 1] = _ePos[i];



                                _ePos[i] = _ePos[tempEAC - 1];

                                _compteE[i] = _compteE[tempEAC - 1];
                                _compteE[tempEAC - 1] = 0;

                                tempEAC--;
                                temp_nbBesoin--;
                                i--;
                            }
                            break;

                        case 3:
                            if (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                            {
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->shield->build --;
                                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }
                            else
                            {
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->shield->build -= m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / temp_nbBesoin;
                                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }

                            if (m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->shield->build <= 0)
                            {
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].type = ENTITY;

                                _ePos[i] = _ePos[tempEAC - 1];

                                _compteE[i] = _compteE[tempEAC - 1];
                                _compteE[tempEAC - 1] = 0;

                                tempEAC--;
                                temp_nbBesoin--;
                                i--;
                            }
                            break;
                        
                        case 4:
                            if (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                            {
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->beacon->build --;
                                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }
                            else
                            {
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->beacon->build -= m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / temp_nbBesoin;
                                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }

                            if (m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->beacon->build <= 0)
                            {
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].type = ENTITY;



                                temp_nbEntitee++;
                                Coord temp_tabEntitee[temp_nbEntitee];

                                for (unsigned int j = 0; j < temp_nbEntitee; j++)
                                    temp_tabEntitee[j] = _tabEntitee[j];
                                
                                _tabEntitee = (Coord*) realloc (_tabEntitee, sizeof(Coord) * temp_nbEntitee);
                                for (unsigned int j = 0; j < temp_nbEntitee; j++)
                                    _tabEntitee[j] = temp_tabEntitee[j];
                                
                                _tabEntitee[temp_nbEntitee - 1] = _ePos[i];



                                _ePos[i] = _ePos[tempEAC - 1];

                                _compteE[i] = _compteE[tempEAC - 1];
                                _compteE[tempEAC - 1] = 0;

                                tempEAC--;
                                temp_nbBesoin--;
                                i--;
                            }
                            break;
                        
                        case 5:
                            if (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                            {
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->bombe->build --;
                                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }
                            else
                            {
                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->bombe->build -= m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / temp_nbBesoin;
                                m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }

                            if (m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].entitee->bombe->build <= 0)
                            {
                                if (m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x + 1].type == ENTITY)
                                {
                                    if (m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x + 1].entitee->type == CREEPERSPAWNER)
                                    //--▼------▼--//
                                        temp_sortie--;
                                }
                                if (m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x - 1].type == ENTITY)
                                {
                                    if (m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x - 1].entitee->type == CREEPERSPAWNER)
                                    //--▼------▼--//
                                        temp_sortie--;
                                }
                                if (m->elements[LARGEUR * ((int)_ePos[i].y + 1) + (int)_ePos[i].x].type == ENTITY)
                                {    
                                    if (m->elements[LARGEUR * ((int)_ePos[i].y + 1) + (int)_ePos[i].x].entitee->type == CREEPERSPAWNER)
                                    //--▼------▼--//
                                        temp_sortie--;
                                }
                                if (m->elements[LARGEUR * ((int)_ePos[i].y - 1) + (int)_ePos[i].x].type == ENTITY)
                                {    
                                    if (m->elements[LARGEUR * ((int)_ePos[i].y - 1) + (int)_ePos[i].x].entitee->type == CREEPERSPAWNER)
                                    //--▼------▼--//
                                        temp_sortie--;
                                }

                                m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].type = ENTITY;



                                temp_nbEntitee++;
                                Coord temp_tabEntitee[temp_nbEntitee];

                                for (unsigned int j = 0; j < temp_nbEntitee; j++)
                                    temp_tabEntitee[j] = _tabEntitee[j];
                                
                                _tabEntitee = (Coord*) realloc (_tabEntitee, sizeof(Coord) * temp_nbEntitee);
                                for (unsigned int j = 0; j < temp_nbEntitee; j++)
                                    _tabEntitee[j] = temp_tabEntitee[j];
                                
                                _tabEntitee[temp_nbEntitee - 1] = _ePos[i];



                                _ePos[i] = _ePos[tempEAC - 1];

                                _compteE[i] = _compteE[tempEAC - 1];
                                _compteE[tempEAC - 1] = 0;

                                tempEAC--;
                                temp_nbBesoin--;
                                i--;
                            }
                            break;

                    }
                
                }

            }
            
        }

        *_entiteeAcreer = tempEAC;
        *_nb_Entitee    = temp_nbEntitee;
        *_nb_besoin     = temp_nbBesoin;
        *_sortie        = temp_sortie;

    }

    return _tabEntitee;
    
}

void remplirEnergieStructure (Map* m, Coord* _tabEntitee, int _nb_Entitee, int* _nb_besoin)
{
    if (m)
    {
        int x;
        int y;
        int temp_nbBesoin = *_nb_besoin;
        for (unsigned int i = 0; i < _nb_Entitee; i++)
        {
            x = _tabEntitee[i].x;
            y = _tabEntitee[i].y;

            switch (m->elements[LARGEUR * y + x].entitee->type)
            {
                case 2:
                    if (m->elements[LARGEUR * y + x].entitee->miner->power_quantity <= 19) /*---->*/ temp_nbBesoin++;
                    break;
                
                case 4:
                    if (m->elements[LARGEUR * y + x].entitee->beacon->power_quantity <= 19) /*--->*/ temp_nbBesoin++;
                    break;

                case 5:
                    if (m->elements[LARGEUR * y + x].entitee->bombe->power_quantity <= 19) /*---->*/ temp_nbBesoin++;
                    break;

            }

        }

        for (unsigned int i = 0; i < _nb_Entitee; i++)
        {
            x = _tabEntitee[i].x;
            y = _tabEntitee[i].y;

            switch (m->elements[LARGEUR * y + x].entitee->type)
            {
                case 2:
                    if (m->elements[LARGEUR * y + x].entitee->miner->power_quantity <= 19)
                    {
                        if (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                        {
                            m->elements[LARGEUR * y + x].entitee->miner->power_quantity ++;
                            m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            m->elements[LARGEUR * y + x].entitee->miner->power_quantity += 1 / temp_nbBesoin;
                            m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                        }

                        temp_nbBesoin--;

                    }
                    break;
                
                case 4:
                    if (m->elements[LARGEUR * y + x].entitee->beacon->power_quantity <= 19)
                    {
                        if (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                        {
                            m->elements[LARGEUR * y + x].entitee->beacon->power_quantity ++;
                            m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            m->elements[LARGEUR * y + x].entitee->beacon->power_quantity += 1 / temp_nbBesoin;
                            m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                        }

                        temp_nbBesoin--;
                    }
                    break;
                
                case 5:
                    if (m->elements[LARGEUR * y + x].entitee->bombe->power_quantity <= 19)
                    {
                        if (m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                        {
                            m->elements[LARGEUR * y + x].entitee->bombe->power_quantity ++;
                            m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            m->elements[LARGEUR * y + x].entitee->bombe->power_quantity += 1 / temp_nbBesoin;
                            m->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                        }

                        temp_nbBesoin--;
                    }
                    break;
            }

        }

        *_nb_besoin = temp_nbBesoin;
    
    }

}

void viderEnergieStructure (Map* m, Coord* _tabEntitee, int _nb_Entitee)
{
    if (m)
    {
        for (unsigned int i = 0; i < _nb_Entitee; i++)
        {
            switch (m->elements[LARGEUR * (int)_tabEntitee[i].y + (int)_tabEntitee[i].x].entitee->type)
            {
                case 2:
                    if (m->elements[LARGEUR * (int)_tabEntitee[i].y + (int)_tabEntitee[i].x].entitee->miner->power_quantity > 0)
                    {
                        m->elements[LARGEUR * (int)_tabEntitee[i].y + (int)_tabEntitee[i].x].entitee->miner->power_quantity -= 0.05;
                    }
                    break;
                
                case 4:
                    if (m->elements[LARGEUR * (int)_tabEntitee[i].y + (int)_tabEntitee[i].x].entitee->miner->power_quantity > 0)
                    {
                        m->elements[LARGEUR * (int)_tabEntitee[i].y + (int)_tabEntitee[i].x].entitee->miner->power_quantity -= 0.05;
                    }
                    break;
            }
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