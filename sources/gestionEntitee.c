/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionAffichage.c                    */
/* Numéro de version : 0.6.1                                 */
/* Date              : 18/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/gestionEntitee.h"
#include "../headers/gestionMem.h"
#include "../headers/gestionMap.h"

void ajouterStructure (Map* m, int x, int y, unsigned int type, int* erreur)
{
    if (m)
    {
        switch (type)
        {
            case 48: *erreur = 3; break;
            case 49:
                if (m->elements[LARGEUR * (y + 1) + x].type != VIDE) /*--->*/ m->elements[LARGEUR * y + x].entitee = creerEntitee(x, y, REACTEUR);
                else /*--->*/ *erreur = 4;
                break;

            case 50:
                if (m->elements[LARGEUR * (y + 1) + x].block != NULL)
                    if (m->elements[LARGEUR * (y + 1) + x].block->type == GOLD) /*--->*/ m->elements[LARGEUR * y + x].entitee = creerEntitee(x, y, MINER);
                    else /*--->*/ *erreur = 5;
                else /*--->*/ *erreur = 5;
                break;

            case 51: m->elements[LARGEUR * y + x].entitee = creerEntitee(x, y, SHIELD); break;
            case 52: 
                if (m->elements[LARGEUR * (y + 1) + x].type == BLOCK || m->elements[LARGEUR * (y - 1) + x].type == BLOCK || m->elements[LARGEUR * y + (x + 1)].type == BLOCK || m->elements[LARGEUR * y + (x - 1)].type == BLOCK)
                //--▼-----------------------------------------------------▼--*/
                    m->elements[LARGEUR * y + x].entitee = creerEntitee(x, y, BEACON);
                else /*--->*/ *erreur = 6;
                break;

            case 53: m->elements[LARGEUR * y + x].entitee = creerEntitee(x, y, BOMBE); break;

            default: *erreur = 9; break;
            
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
    int* _nb_besoin
)
{
    if (m)
    {
        int tempEAC         = *_entiteeAcreer;
        int temp_nbEntitee  = *_nb_Entitee;
        int temp_nbBesoin   = *_nb_besoin;
            
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
                            _tabEntitee = (Coord*) realloc (_tabEntitee, sizeof(Coord) * temp_nbEntitee);
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
                            _tabEntitee = (Coord*) realloc (_tabEntitee, sizeof(Coord) * temp_nbEntitee);
                            _tabEntitee[temp_nbEntitee - 1] = _ePos[i];
                            
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
                            m->elements[LARGEUR * (int)_ePos[i].y + (int)_ePos[i].x].type = ENTITY;


                            temp_nbEntitee++;
                            _tabEntitee = (Coord*) realloc (_tabEntitee, sizeof(Coord) * temp_nbEntitee);
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

        *_entiteeAcreer = tempEAC;
        *_nb_Entitee    = temp_nbEntitee;
        *_nb_besoin     = temp_nbBesoin;
    }

    return _tabEntitee;
    
}

Coord* remplirEnergieStructure 
(
    Map* m,
    Coord* _tabEntitee,
    int* _nb_Entitee,
    int* _nb_besoin,
    int* _sortie
)
{
    if (m)
    {
        int x;
        int y;
        int temp_nbBesoin  = *_nb_besoin;
        int temp_nbEntitee = *_nb_Entitee;
        int temp_sortie    = *_sortie;

        for (unsigned int i = 0; i < temp_nbEntitee; i++)
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

        for (unsigned int i = 0; i < temp_nbEntitee; i++)
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

                    if (m->elements[LARGEUR * y + x].entitee->beacon->power_quantity > 0)
                        visibilitee (m, _tabEntitee[i].x, _tabEntitee[i].y);
                    
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
                    else if (m->elements[LARGEUR * y + x].entitee->bombe->power_quantity == 20)
                    {
                        if (m->elements[LARGEUR * y + x + 1].type == ENTITY)
                        {
                            if (m->elements[LARGEUR * y + x + 1].entitee->type == CREEPERSPAWNER)
                            {
                                effetDegats (m->elements, m->elements[LARGEUR * y + x].entitee, m->elements[LARGEUR * y + x + 1].entitee);
                                temp_sortie--;
                                _tabEntitee[i] = _tabEntitee[temp_nbEntitee - 1];
                                _tabEntitee[temp_nbEntitee - 1] = (Coord) {0, 0};
                                temp_nbEntitee--;
                                _tabEntitee = (Coord*) realloc (_tabEntitee, sizeof(Coord) * temp_nbEntitee);
                            }
                        }
                        if (m->elements[LARGEUR * y + x - 1].type == ENTITY)
                        {
                            if (m->elements[LARGEUR * y + x - 1].entitee->type == CREEPERSPAWNER)
                            {
                                effetDegats (m->elements, m->elements[LARGEUR * y + x].entitee, m->elements[LARGEUR * y + x - 1].entitee);
                                temp_sortie--;
                                _tabEntitee[i] = _tabEntitee[temp_nbEntitee - 1];
                                _tabEntitee[temp_nbEntitee - 1] = (Coord) {0, 0};
                                temp_nbEntitee--;
                                _tabEntitee = (Coord*) realloc (_tabEntitee, sizeof(Coord) * temp_nbEntitee);
                            }
                        }
                        if (m->elements[LARGEUR * (y + 1) + x].type == ENTITY)
                        {    
                            if (m->elements[LARGEUR * (y + 1) + x].entitee->type == CREEPERSPAWNER)
                            {
                                effetDegats (m->elements, m->elements[LARGEUR * y + x].entitee, m->elements[LARGEUR * (y + 1) + x].entitee);
                                temp_sortie--;
                                _tabEntitee[i] = _tabEntitee[temp_nbEntitee - 1];
                                _tabEntitee[temp_nbEntitee - 1] = (Coord) {0, 0};
                                temp_nbEntitee--;
                                _tabEntitee = (Coord*) realloc (_tabEntitee, sizeof(Coord) * temp_nbEntitee);
                            }
                        }
                        if (m->elements[LARGEUR * (y - 1) + x].type == ENTITY)
                        {    
                            if (m->elements[LARGEUR * (y - 1) + x].entitee->type == CREEPERSPAWNER)
                            {
                                effetDegats (m->elements, m->elements[LARGEUR * y + x].entitee, m->elements[LARGEUR * (y - 1) + x].entitee);
                                temp_sortie--;
                                _tabEntitee[i] = _tabEntitee[temp_nbEntitee - 1];
                                _tabEntitee[temp_nbEntitee - 1] = (Coord) {0, 0};
                                temp_nbEntitee--;
                                _tabEntitee = (Coord*) realloc (_tabEntitee, sizeof(Coord) * temp_nbEntitee);
                            }

                        }

                    }
                    
                    break;
            }

        }

        *_nb_besoin  = temp_nbBesoin;
        *_nb_Entitee = temp_nbEntitee;
        *_sortie     = temp_sortie;
    
    }
    return _tabEntitee;

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
                    if (m->elements[LARGEUR * (int)_tabEntitee[i].y + (int)_tabEntitee[i].x].entitee->beacon->power_quantity > 0)
                    {
                        m->elements[LARGEUR * (int)_tabEntitee[i].y + (int)_tabEntitee[i].x].entitee->beacon->power_quantity -= 0.05;
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

void effetDegats (Case* c, Entity* attaquant, Entity* victime)
{
    if (attaquant && victime)
    {
        int xA;
        int yA;
        int xV;
        int yV;
        switch (attaquant->type)
        {
            case BOMBE:
                xA = attaquant->bombe->pos.x;
                yA = attaquant->bombe->pos.y;
                switch (victime->type)
                {
                    case CREEPERSPAWNER:
                        xV = victime->creeperSpawner->pos.x;
                        yV = victime->creeperSpawner->pos.y;

                        victime->creeperSpawner->health -= attaquant->bombe->damage;
                        
                        if (victime->creeperSpawner->health <= 0)
                        {
                            detruireEntitee (victime);
                            detruireEntitee (attaquant);
                            
                            victime   = NULL;
                            attaquant = NULL;

                            c[LARGEUR * yV + xV].entitee = NULL;
                            c[LARGEUR * yA + xA].entitee = NULL;

                            c[LARGEUR * yV + xV].type = VIDE;
                            c[LARGEUR * yA + xA].type = VIDE;
                        }
                        break;
                }
                break;
            
        }

    }
    
}
