/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionAffichage.c                    */
/* Numéro de version : 0.7                                   */
/* Date              : 18/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/gestionEntitee.h"
#include "../headers/gestionMem.h"
#include "../headers/gestionMap.h"
#include "../headers/gestionAffichage.h"

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

        int x, y;
            
        for (unsigned int i = 0; i < tempEAC; i++)
        {
            x = _ePos[i].x;
            y = _ePos[i].y;

            if (_compteE[i] == 0)
            {
                if (testAccessibilitee(m, _ePos[i].x, _ePos[i].y) == 1)
                    _compteE[i] = 1;
                
                decache (m);
                if (_compteE[i] != 0) /*--->*/ temp_nbBesoin++;
                
            }
            if (_compteE[i] != 0)
            {
                switch (m->elements[LARGEUR * y + x].entitee->type)
                {
                    case 1:
                        if (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity > 0)
                        {
                            m->elements[LARGEUR * y + x].entitee->reactor->build --;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            m->elements[LARGEUR * y + x].entitee->reactor->build -= m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient / temp_nbBesoin;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }

                        if (m->elements[LARGEUR * y + x].entitee->reactor->build <= 0)
                        {
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient += 0.15;
                            m->elements[LARGEUR * y + x].type = ENTITY;

                            afficherVide    (m->elements[LARGEUR * y + x].vide);
                            afficherEntitee (m->elements, LARGEUR * y + x);

                            _ePos[i] = _ePos[tempEAC - 1];

                            _compteE[i] = _compteE[tempEAC - 1];
                            _compteE[tempEAC - 1] = 0;

                            tempEAC--;
                            temp_nbBesoin--;
                            i--;
                        }
                        break;
                    
                    case 2:
                        if (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity > 0)
                        {
                            m->elements[LARGEUR * y + x].entitee->miner->build --;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            m->elements[LARGEUR * y + x].entitee->miner->build -= m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient / temp_nbBesoin;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }

                        if (m->elements[LARGEUR * y + x].entitee->miner->build <= 0)
                        {
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->gold_efficient += 0.15;
                            m->elements[LARGEUR * y + x].type = ENTITY;
                            
                            afficherVide    (m->elements[LARGEUR * y + x].vide);
                            afficherEntitee (m->elements, LARGEUR * y + x);
                            
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
                        if (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity > 0)
                        {
                            m->elements[LARGEUR * y + x].entitee->shield->build --;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            m->elements[LARGEUR * y + x].entitee->shield->build -= m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient / temp_nbBesoin;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }

                        if (m->elements[LARGEUR * y + x].entitee->shield->build <= 0)
                        {
                            m->elements[LARGEUR * y + x].type = ENTITY;

                            afficherVide    (m->elements[LARGEUR * y + x].vide);
                            afficherEntitee (m->elements, LARGEUR * y + x);

                            _ePos[i] = _ePos[tempEAC - 1];

                            _compteE[i] = _compteE[tempEAC - 1];
                            _compteE[tempEAC - 1] = 0;

                            tempEAC--;
                        
                            temp_nbBesoin--;
                            i--;
                        }
                        break;
                    
                    case 4:
                        if (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity > 0)
                        {
                            m->elements[LARGEUR * y + x].entitee->beacon->build --;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            m->elements[LARGEUR * y + x].entitee->beacon->build -= m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient / temp_nbBesoin;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }

                        if (m->elements[LARGEUR * y + x].entitee->beacon->build <= 0)
                        {
                            m->elements[LARGEUR * y + x].type = ENTITY;

                            afficherVide    (m->elements[LARGEUR * y + x].vide);
                            afficherEntitee (m->elements, LARGEUR * y + x);

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
                        if (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity > 0)
                        {
                            m->elements[LARGEUR * y + x].entitee->bombe->build --;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            m->elements[LARGEUR * y + x].entitee->bombe->build -= m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient / temp_nbBesoin;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }

                        if (m->elements[LARGEUR * y + x].entitee->bombe->build <= 0)
                        {
                            m->elements[LARGEUR * y + x].type = ENTITY;

                            afficherVide    (m->elements[LARGEUR * y + x].vide);
                            afficherEntitee (m->elements, LARGEUR * y + x);

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
                        if (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity > 0)
                        {
                            m->elements[LARGEUR * y + x].entitee->miner->power_quantity ++;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            m->elements[LARGEUR * y + x].entitee->miner->power_quantity += m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient / temp_nbBesoin;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }

                        temp_nbBesoin--;

                    }
                    break;
                
                case 4:
                    if (m->elements[LARGEUR * y + x].entitee->beacon->power_quantity <= 19)
                    {
                        if (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity > 0)
                        {
                            m->elements[LARGEUR * y + x].entitee->beacon->power_quantity ++;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            m->elements[LARGEUR * y + x].entitee->beacon->power_quantity += m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient / temp_nbBesoin;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }

                        temp_nbBesoin--;
                    }

                    if (m->elements[LARGEUR * y + x].entitee->beacon->power_quantity > 0 && m->elements[LARGEUR * y + x].entitee->beacon->power_quantity < 2)
                    {
                        printf ("test\n");
                        visibilitee (m, _tabEntitee[i].x, _tabEntitee[i].y);
                    }
                    break;
                
                case 5:
                    if (m->elements[LARGEUR * y + x].entitee->bombe->power_quantity <= 19)
                    {
                        if (m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity > 0)
                        {
                            m->elements[LARGEUR * y + x].entitee->bombe->power_quantity ++;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            m->elements[LARGEUR * y + x].entitee->bombe->power_quantity += m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient / temp_nbBesoin;
                            m->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_quantity --;
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
    if (m && _tabEntitee)
    {
        int x, y;
        for (unsigned int i = 0; i < _nb_Entitee; i++)
        {
            x = _tabEntitee[i].x;
            y = _tabEntitee[i].y;
            switch (m->elements[LARGEUR * y + x].entitee->type)
            {
                case 2:
                    if (m->elements[LARGEUR * y + x].entitee->miner->power_quantity > 0)
                    {
                        m->elements[LARGEUR * y + x].entitee->miner->power_quantity -= 0.05;
                    }
                    break;
                
                case 4:
                    if (m->elements[LARGEUR * y + x].entitee->beacon->power_quantity > 0)
                    {
                        m->elements[LARGEUR * y + x].entitee->beacon->power_quantity -= 0.05;
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

                cPos[nb_Spawner - 1] = (Coord) {i % LARGEUR, i / LARGEUR};
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

void mouvementCreeper (Map* m, int* _sortie)
{
    if (m)
    {
        for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
        {
            int x = i % LARGEUR;
            int y = i / LARGEUR;
            /*
            if (m->elements[LARGEUR * y + x].type == ENTITY)
            { 
                if (m->elements[LARGEUR * y + x].entitee->ship && (m->elements[LARGEUR * y + x].vide->creeperQuantity[0] != 0 ||
                                                                   m->elements[LARGEUR * y + x].vide->creeperQuantity[1] != 0 || 
                                                                   m->elements[LARGEUR * y + x].vide->creeperQuantity[2] != 0 || 
                                                                   m->elements[LARGEUR * y + x].vide->creeperQuantity[3] != 0))
                {
                    m->elements[LARGEUR * y + x].entitee->ship->health -= 10;
                        if (m->elements[LARGEUR * y + x].entitee->ship->health == 0)
                            *_sortie = -1;
                }
                else if ((m->elements[LARGEUR * y + x].entitee->reactor || m->elements[LARGEUR * y + x].entitee->miner || m->elements[LARGEUR * y + x].entitee->beacon || m->elements[LARGEUR * y + x].entitee->bombe) && 
                                                                  (m->elements[LARGEUR * y + x].vide->creeperQuantity[0] != 0 ||
                                                                   m->elements[LARGEUR * y + x].vide->creeperQuantity[1] != 0 || 
                                                                   m->elements[LARGEUR * y + x].vide->creeperQuantity[2] != 0 || 
                                                                   m->elements[LARGEUR * y + x].vide->creeperQuantity[3] != 0))
                    detruireEntitee (m->elements[LARGEUR * y + x].entitee);
                        
            }
            */ 
            

        

            if (m->elements[LARGEUR * y + x].vide)
            {

        //-------------------------------Transfert Bas--------------------------------//

                if (m->elements[LARGEUR * (y + 1) + x].vide && (y + 1) < HAUTEUR)
                {
                    if (m->elements[LARGEUR * y + x].vide->creeperQuantity[2] >= 1 && m->elements[LARGEUR * (y + 1) + x].vide->creeperQuantity[0] < m->elements[LARGEUR * y + x].vide->creeperQuantity[2] * 1.2)
                    {
                        m->elements[LARGEUR * (y + 1) + x].vide->creeperQuantity[0] += m->elements[LARGEUR * y + x].vide->creeperQuantity[2] / 4;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[2]       -= m->elements[LARGEUR * y + x].vide->creeperQuantity[2] / 4;
                    }
                    if (m->elements[LARGEUR * y + x].vide->creeperQuantity[3] >= 1 && m->elements[LARGEUR * (y + 1) + x].vide->creeperQuantity[1] < m->elements[LARGEUR * y + x].vide->creeperQuantity[3] * 1.2)
                    {
                        m->elements[LARGEUR * (y + 1) + x].vide->creeperQuantity[1] += m->elements[LARGEUR * y + x].vide->creeperQuantity[3] / 4;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[3]       -= m->elements[LARGEUR * y + x].vide->creeperQuantity[3] / 4;
                    }
                    
                }
                if (m->elements[LARGEUR * y + x].vide->creeperQuantity[0] >= 1 && m->elements[LARGEUR * y + x].vide->creeperQuantity[2] < m->elements[LARGEUR * y + x].vide->creeperQuantity[0] * 1.2)
                {
                    m->elements[LARGEUR * y + x].vide->creeperQuantity[2] += m->elements[LARGEUR * y + x].vide->creeperQuantity[0] / 4;
                    m->elements[LARGEUR * y + x].vide->creeperQuantity[0] -= m->elements[LARGEUR * y + x].vide->creeperQuantity[0] / 4;
                }
                if (m->elements[LARGEUR * y + x].vide->creeperQuantity[1] >= 1 && m->elements[LARGEUR * y + x].vide->creeperQuantity[3] < m->elements[LARGEUR * y + x].vide->creeperQuantity[1] * 1.2)
                {
                    m->elements[LARGEUR * y + x].vide->creeperQuantity[3] += m->elements[LARGEUR * y + x].vide->creeperQuantity[1] / 4;
                    m->elements[LARGEUR * y + x].vide->creeperQuantity[1] -= m->elements[LARGEUR * y + x].vide->creeperQuantity[1] / 4;
                }


        //------------------------------Transfert Gauche------------------------------//


                int nb_Creep[4] = {0};

                if (m->elements[LARGEUR * y + x - 1].vide && (x - 1) >= 0)
                {
                    if (m->elements[LARGEUR * y + x].vide->creeperQuantity[0] >= 10 && m->elements[LARGEUR * y + x - 1].vide->creeperQuantity[1] < m->elements[LARGEUR * y + x].vide->creeperQuantity[0])
                    {
                        nb_Creep[0] += m->elements[LARGEUR * y + x].vide->creeperQuantity[0] / 5;
                        m->elements[LARGEUR * y + x - 1].vide->creeperQuantity[1] += nb_Creep[0] / 2;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[0]     -= nb_Creep[0] / 2;
                    }
                    if (m->elements[LARGEUR * y + x].vide->creeperQuantity[2] >= 10 && m->elements[LARGEUR * y + x - 1].vide->creeperQuantity[3] < m->elements[LARGEUR * y + x].vide->creeperQuantity[2])
                    {
                        nb_Creep[2] += m->elements[LARGEUR * y + x].vide->creeperQuantity[2] / 5;
                        m->elements[LARGEUR * y + x - 1].vide->creeperQuantity[3] += nb_Creep[2] / 2;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[2]     -= nb_Creep[2] / 2;
                    }
                    
                }
                if (m->elements[LARGEUR * y + x].vide->creeperQuantity[1] >= 10 && m->elements[LARGEUR * y + x].vide->creeperQuantity[0] < m->elements[LARGEUR * y + x].vide->creeperQuantity[1])
                {
                    if (m->elements[LARGEUR * y + x + 1].vide && (x + 1) < LARGEUR)
                    {
                        nb_Creep[1] += m->elements[LARGEUR * y + x].vide->creeperQuantity[1] / 5;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[0] += nb_Creep[1] / 2;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[1] -= nb_Creep[1] / 2;
                        
                    }
                    else
                    {
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[0] += m->elements[LARGEUR * y + x].vide->creeperQuantity[1] / 5;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[1] -= m->elements[LARGEUR * y + x].vide->creeperQuantity[1] / 5;
                    }
                    
                }
                if (m->elements[LARGEUR * y + x].vide->creeperQuantity[3] >= 10 && m->elements[LARGEUR * y + x].vide->creeperQuantity[2] < m->elements[LARGEUR * y + x].vide->creeperQuantity[3])
                {
                    if (m->elements[LARGEUR * y + x + 1].vide && (x + 1) < LARGEUR)
                    {
                        nb_Creep[3] += m->elements[LARGEUR * y + x].vide->creeperQuantity[3] / 5;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[2] += nb_Creep[3] / 2;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[3] -= nb_Creep[3] / 2;
                    }
                    else
                    {
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[2] += m->elements[LARGEUR * y + x].vide->creeperQuantity[3] / 5;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[3] -= m->elements[LARGEUR * y + x].vide->creeperQuantity[3] / 5;
                    }
                    
                }

        //------------------------------Transfert Droite------------------------------//

                if (m->elements[LARGEUR * y + x + 1].vide && (x + 1) < LARGEUR)
                {
                    if (m->elements[LARGEUR * y + x].vide->creeperQuantity[1] >= 10 && m->elements[LARGEUR * y + x + 1].vide->creeperQuantity[0] < m->elements[LARGEUR * y + x].vide->creeperQuantity[1] && nb_Creep[1] > 0)
                    {
                        m->elements[LARGEUR * y + x + 1].vide->creeperQuantity[0] += nb_Creep[1] / 2;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[1]     -= nb_Creep[1] / 2;
                    }
                    if (m->elements[LARGEUR * y + x].vide->creeperQuantity[3] >= 10 && m->elements[LARGEUR * y + x + 1].vide->creeperQuantity[2] < m->elements[LARGEUR * y + x].vide->creeperQuantity[3] && nb_Creep[3] > 0)
                    {
                        m->elements[LARGEUR * y + x + 1].vide->creeperQuantity[2] += nb_Creep[3] / 2;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[3]     -= nb_Creep[3] / 2;
                    }
                    
                }
                if (m->elements[LARGEUR * y + x].vide->creeperQuantity[0] >= 10 && m->elements[LARGEUR * y + x].vide->creeperQuantity[1] < m->elements[LARGEUR * y + x].vide->creeperQuantity[0])
                {
                    if (nb_Creep[0] > 0)
                    {
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[1] += nb_Creep[0] / 2;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[0] -= nb_Creep[0] / 2;
                    }
                    else
                    {
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[1] += m->elements[LARGEUR * y + x].vide->creeperQuantity[0] / 5;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[0] -= m->elements[LARGEUR * y + x].vide->creeperQuantity[0] / 5;
                    }

                }
                if (m->elements[LARGEUR * y + x].vide->creeperQuantity[2] >= 10 && m->elements[LARGEUR * y + x].vide->creeperQuantity[3] < m->elements[LARGEUR * y + x].vide->creeperQuantity[2])
                {
                    if (nb_Creep[2] > 0)
                    {
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[3] += nb_Creep[2] / 2;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[2] -= nb_Creep[2] / 2;
                    }
                    else
                    {
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[3] += m->elements[LARGEUR * y + x].vide->creeperQuantity[2] / 5;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[2] -= m->elements[LARGEUR * y + x].vide->creeperQuantity[2] / 5;
                    }
                    
                }


        //-------------------------------Transfert Haut-------------------------------//


                if (m->elements[LARGEUR * (y - 1) + x].vide && (y - 1) >= 0)
                {
                    if (m->elements[LARGEUR * y + x].vide->creeperQuantity[0] >= 300 && m->elements[LARGEUR * (y - 1) + x].vide->creeperQuantity[2] < m->elements[LARGEUR * y + x].vide->creeperQuantity[0] * 0.6)
                    {
                        m->elements[LARGEUR * (y - 1) + x].vide->creeperQuantity[2] += m->elements[LARGEUR * y + x].vide->creeperQuantity[0] / 6;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[0]       -= m->elements[LARGEUR * y + x].vide->creeperQuantity[0] / 6;
                    }
                    if (m->elements[LARGEUR * y + x].vide->creeperQuantity[1] >= 300 && m->elements[LARGEUR * (y - 1) + x].vide->creeperQuantity[3] < m->elements[LARGEUR * y + x].vide->creeperQuantity[1] * 0.6)
                    {
                        m->elements[LARGEUR * (y - 1) + x].vide->creeperQuantity[3] += m->elements[LARGEUR * y + x].vide->creeperQuantity[1] / 6;
                        m->elements[LARGEUR * y + x].vide->creeperQuantity[1]       -= m->elements[LARGEUR * y + x].vide->creeperQuantity[1] / 6;
                    }
                    
                }
                if (m->elements[LARGEUR * y + x].vide->creeperQuantity[2] >= 300 && m->elements[LARGEUR * y + x].vide->creeperQuantity[0] < m->elements[LARGEUR * y + x].vide->creeperQuantity[2] * 0.6)
                {
                    m->elements[LARGEUR * y + x].vide->creeperQuantity[0] += m->elements[LARGEUR * y + x].vide->creeperQuantity[2] / 6;
                    m->elements[LARGEUR * y + x].vide->creeperQuantity[2] -= m->elements[LARGEUR * y + x].vide->creeperQuantity[2] / 6;
                }
                if (m->elements[LARGEUR * y + x].vide->creeperQuantity[3] >= 300 && m->elements[LARGEUR * y + x].vide->creeperQuantity[1] < m->elements[LARGEUR * y + x].vide->creeperQuantity[3] * 0.6)
                {
                    m->elements[LARGEUR * y + x].vide->creeperQuantity[1] += m->elements[LARGEUR * y + x].vide->creeperQuantity[3] / 6;
                    m->elements[LARGEUR * y + x].vide->creeperQuantity[3] -= m->elements[LARGEUR * y + x].vide->creeperQuantity[3] / 6;
                }

            }

        }

    }
    
}