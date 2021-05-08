/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : main.c                                */
/* Numéro de version : 0.4                                   */
/* Date              : 21/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "type.h"
#include "fonction.h"

int main ()
{
    srand (time(NULL));
    

    Map* mapHasard = creerCarte(LARGEUR, HAUTEUR, "newMap");

    remplirHasard (mapHasard);
    creerCaverne  (mapHasard, rand() % LARGEUR * HAUTEUR + 280, 0);
    creerCaverne  (mapHasard, rand() % LARGEUR * HAUTEUR + 280, 0);
    creerCaverne  (mapHasard, rand() % LARGEUR * HAUTEUR + 280, 0);
    creerCaverne  (mapHasard, rand() % LARGEUR * HAUTEUR + 280, 0);
    ajouterSpawnerHasard(mapHasard->elements, NB_CREEPERSPAWNER);

    int sortie        = NB_CREEPERSPAWNER;
    char MvtOrAction  = 0;
    char action;

    int blockAcasser  = 0;
    int entiteeAcreer = 0;

    int erreur        = 0;
    int nb_besoin     = 0;
    int compte[20]    = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int compteE[20]   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    Coord* tabEntitee = malloc (sizeof(Coord));
    int nb_Entitee    = 0;

    Coord jPos = (Coord){17, 3};
    Coord bPos[10];
    Coord ePos[10];

    mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;
    
    while (sortie != 0)
    {
        afficherInterface (mapHasard, tabEntitee, nb_Entitee);
        afficherCarte (mapHasard);
        switch (erreur)
        {
            case 1: printf ("Vous ne pouvez rien supprimer sur cette case-là.                   \n");   break;
            case 2: printf ("Vous ne pouvez pas ajouter ou supprimer d'entitée ici.             \n");   break;
            case 3: printf ("Vous ne pouvez pas placer cette entitée-la.                        \n");   break;
            case 4: printf ("Impossible de placer de reacteur ici.                              \n");   break;
            case 5: printf ("Impossible de placer de mineur ici.                                \n");   break;
            case 6: printf ("Impossible de placer de beacon ici.                                \n");   break;
            case 7: printf ("Nombre maximum de cases pouvant être cassé à la suite, atteint.    \n");   break;
            case 8: printf ("Nombre maximum d'entitée pouvant être ajouter à la suite, atteint. \n");   break;
        }
        erreur = 0;

        scanf (" %c", &MvtOrAction);

        switch (MvtOrAction)
        {
            case 'a':
                if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block == NULL && mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee == NULL)
                    mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 0;
                jPos.x--;
                mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;

                break;
            case 's':
                if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block == NULL && mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee == NULL)
                    mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 0;
                jPos.y++;
                mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;

                break;
            case 'd':
                if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block == NULL && mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee == NULL)
                    mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 0;
                jPos.x++;
                mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;

                break;
            case 'w':
                if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block == NULL && mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee == NULL)
                    mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 0;
                jPos.y--;
                mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;
                break;
            case 'z':
                scanf (" %c", &action);

                switch (action)
                {
                    case 'a':
                        
                        if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block != NULL)
                        {
                            if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block->dirt != NULL || mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block->stone != NULL)
                            {
                                if (blockAcasser <= 9)
                                {
                                    bPos[blockAcasser] = jPos;
                                    blockAcasser++;
                                }
                                else /*--->*/ erreur = 7;
                                
                            }
                            
                        }
                        else if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee != NULL && mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee->ship == NULL)
                        {
                            if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee->type == REACTEUR)
                            //--▼----------------------------------------------------------------------------▼--*/
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient -= 0.15;

                            else if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee->type == MINER)
                            //--▼--------------------------------------------------------------------------▼--*/
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_efficient -= 0.15;
                            
                           

                            for (unsigned int i = 0; i < nb_Entitee; i++)
                            {
                                if (tabEntitee[i].x == jPos.x && tabEntitee[i].y == jPos.y)
                                {
                                    for (unsigned int j = i; j < nb_Entitee; j++)
                                    {
                                        if (j == nb_Entitee - 1) /*--->*/ tabEntitee[j] = (Coord) {0, 0};
                                        tabEntitee[j] = tabEntitee[j + 1];
                                    }

                                    nb_Entitee--;
                                    
                                    tabEntitee = (Coord*) realloc (tabEntitee, sizeof(Coord)*nb_Entitee);
                                }
                                
                            }
                            
                            detruireEntitee (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee);
                            mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee = NULL;
                            mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = VIDE;
                        }
                        else erreur = 1;
                        
                        break;
                    case 'z':
                        if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block != NULL || mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee != NULL) 
                        //--▼--------▼--*/
                            erreur = 1;
                        else
                        {
                            scanf (" %c", &MvtOrAction);
                            if (entiteeAcreer <= 9)
                            {
                                ePos[entiteeAcreer] = jPos;
                                ajouterEntitee(mapHasard->elements, ePos[entiteeAcreer].x, ePos[entiteeAcreer].y, (int)MvtOrAction, &erreur);
                                if (erreur == 0) /*--->*/ entiteeAcreer++;
                            }
                            else /*--->*/ erreur = 8;
                        }
                            
                        break;
                }
                break;

            default: sortie = 0; break;
        }
        if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block != NULL) /*----->*/ mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 1;
        if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee != NULL) /*--->*/ mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 2;
        
        if (blockAcasser > 0)
        {
            for (unsigned int i = 0; i < blockAcasser; i++)
            {
                if (compte[i] == 0)
                {
                    compte[i] = testAccessibilitee (mapHasard, bPos[i].x, bPos[i].y);
                    decache (mapHasard);
                    if (compte[i] == 1) /*--->*/ nb_besoin++;
                    
                }
                if (mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block->dirt != NULL && compte[i] == 1)
                {
                    if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                    {
                        mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block->dirt->hardness --;
                        mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                    }
                    else
                    {
                        mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block->dirt->hardness -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
                        mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                    }
                    
                    if (mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block->dirt->hardness <= 0)
                    {
                        detruireBlock (mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block);

                        mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block = NULL;
                        mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].type = VIDE;

                        bPos[i] = bPos[blockAcasser - 1];
                        bPos[blockAcasser - 1] = (Coord){0, 0};

                        compte[i] = compte[blockAcasser - 1];
                        compte[blockAcasser - 1] = 0;

                        blockAcasser--;
                        nb_besoin--;
                        i--;
                    }

                }
                else if (mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block->stone != NULL && compte[i] == 1)
                {
                    if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                    {
                        mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block->stone->hardness --;
                        mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                    }
                    else
                    {
                        mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block->stone->hardness -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
                        mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                    }

                    if (mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block->stone->hardness <= 0)
                    {
                        detruireBlock (mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block);

                        mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block = NULL;
                        mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].type = VIDE;

                        bPos[i] = bPos[blockAcasser - 1];
                        bPos[blockAcasser - 1] = (Coord){0, 0};

                        compte[i] = compte[blockAcasser - 1];
                        compte[blockAcasser - 1] = 0;

                        blockAcasser--;
                        nb_besoin--;
                        i--;
                    }

                }

            }
            
        }
        if (entiteeAcreer > 0)
        {
            for (unsigned int i = 0; i < entiteeAcreer; i++)
            {
                if (compteE[i] == 0)
                {
                    compteE[i] = testAccessibilitee(mapHasard, ePos[i].x, ePos[i].y);
                    decache (mapHasard);
                    if (compteE[i] == 1) /*--->*/ nb_besoin++;
                    
                }
                if (compteE[i] == 1)
                {
                    switch (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->type)
                    {
                        case 1:
                            if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                            {
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->reactor->build --;
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }
                            else
                            {
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->reactor->build -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }

                            if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->reactor->build <= 0)
                            {
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient += 0.15;
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].type = ENTITY;

                                ePos[i] = ePos[entiteeAcreer - 1];

                                compteE[i] = compteE[entiteeAcreer - 1];
                                compteE[entiteeAcreer - 1] = 0;

                                entiteeAcreer--;
                                nb_besoin--;
                                i--;
                            }
                            break;
                        
                        case 2:
                            if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                            {
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->miner->build --;
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }
                            else
                            {
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->miner->build -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }

                            if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->miner->build <= 0)
                            {
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_efficient += 0.15;
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].type = ENTITY;

                                nb_Entitee++;
                                tabEntitee = (Coord*) realloc (tabEntitee, sizeof(Coord)*nb_Entitee);
                                tabEntitee[nb_Entitee - 1] = ePos[i];

                                ePos[i] = ePos[entiteeAcreer - 1];

                                compteE[i] = compteE[entiteeAcreer - 1];
                                compteE[entiteeAcreer - 1] = 0;

                                entiteeAcreer--;
                                nb_besoin--;
                                i--;
                            }
                            break;

                        case 3:
                            if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                            {
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->shield->build --;
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }
                            else
                            {
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->shield->build -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }

                            if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->shield->build <= 0)
                            {
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].type = ENTITY;

                                ePos[i] = ePos[entiteeAcreer - 1];

                                compteE[i] = compteE[entiteeAcreer - 1];
                                compteE[entiteeAcreer - 1] = 0;

                                entiteeAcreer--;
                                nb_besoin--;
                                i--;
                            }
                            break;
                        
                        case 4:
                            if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                            {
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->beacon->build --;
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }
                            else
                            {
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->beacon->build -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }

                            if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->beacon->build <= 0)
                            {
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].type = ENTITY;

                                nb_Entitee++;
                                tabEntitee = (Coord*) realloc (tabEntitee, sizeof(Coord)*nb_Entitee);
                                tabEntitee[nb_Entitee - 1] = ePos[i];

                                ePos[i] = ePos[entiteeAcreer - 1];

                                compteE[i] = compteE[entiteeAcreer - 1];
                                compteE[entiteeAcreer - 1] = 0;

                                entiteeAcreer--;
                                nb_besoin--;
                                i--;
                            }
                            break;
                        
                        case 5:
                            if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                            {
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->bombe->build --;
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }
                            else
                            {
                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->bombe->build -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
                                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                            }

                            if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->bombe->build <= 0)
                            {
                                if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x + 1].type == ENTITY)
                                    if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x + 1].entitee->type == CREEPERSPAWNER)
                                    //--▼------▼--//
                                        sortie--;
                                if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x - 1].type == ENTITY)
                                    if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x - 1].entitee->type == CREEPERSPAWNER)
                                    //--▼------▼--//
                                        sortie--;
                                if (mapHasard->elements[LARGEUR * ((int)ePos[i].y + 1) + (int)ePos[i].x].type == ENTITY)
                                    if (mapHasard->elements[LARGEUR * ((int)ePos[i].y + 1) + (int)ePos[i].x].entitee->type == CREEPERSPAWNER)
                                    //--▼------▼--//
                                        sortie--;
                                if (mapHasard->elements[LARGEUR * ((int)ePos[i].y - 1) + (int)ePos[i].x].type == ENTITY)
                                    if (mapHasard->elements[LARGEUR * ((int)ePos[i].y - 1) + (int)ePos[i].x].entitee->type == CREEPERSPAWNER)
                                    //--▼------▼--//
                                        sortie--;

                                mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].type = ENTITY;

                                tabEntitee = (Coord*) realloc (tabEntitee, sizeof(Coord)*nb_Entitee);
                                tabEntitee[nb_Entitee - 1] = ePos[i];

                                ePos[i] = ePos[entiteeAcreer - 1];

                                compteE[i] = compteE[entiteeAcreer - 1];
                                compteE[entiteeAcreer - 1] = 0;

                                entiteeAcreer--;
                                nb_besoin--;
                                i--;
                            }
                            break;

                    }
                
                }

            }
            
        }
        

        if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity < mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_storage)
        {
            mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity += mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient;

            while (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_storage)
                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity -= 0.05;
        }

        if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_quantity < mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_storage)
        {
            mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_quantity += mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_efficient;

            while (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_quantity > mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_storage)
                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->gold_quantity -= 0.05;
        }

        for (unsigned int i = 0; i < nb_Entitee; i++)
        {
            switch (mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->type)
            {
                case 2:
                    if (mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->miner->power_quantity <= 19) /*---->*/ nb_besoin++;
                    break;
                
                case 4:
                    if (mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->beacon->power_quantity <= 19) /*--->*/ nb_besoin++;
                    break;

                case 5:
                    if (mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->bombe->power_quantity <= 19) /*---->*/ nb_besoin++;
                    break;

            }
        }
        

        for (unsigned int i = 0; i < nb_Entitee; i++)
        {
            switch (mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->type)
            {
                case 2:
                    if (mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->miner->power_quantity <= 19)
                    {
                        if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                        {
                            mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->miner->power_quantity ++;
                            mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->miner->power_quantity += 1 / nb_besoin;
                            mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                        }

                        nb_besoin--;

                    }
                    break;
                
                case 4:
                    if (mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->beacon->power_quantity <= 19)
                    {
                        if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                        {
                            mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->beacon->power_quantity ++;
                            mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->beacon->power_quantity += 1 / nb_besoin;
                            mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                        }

                        nb_besoin--;
                    }
                    break;
                
                case 5:
                    if (mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->bombe->power_quantity <= 19)
                    {
                        if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > 0)
                        {
                            mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->bombe->power_quantity ++;
                            mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                        }
                        else
                        {
                            mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->bombe->power_quantity += 1 / nb_besoin;
                            mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity --;
                        }

                        nb_besoin--;
                    }
                    break;
            }

        }
        
        for (unsigned int i = 0; i < nb_Entitee; i++)
        {
            switch (mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->type)
            {
            case 2:
                if (mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->miner->power_quantity > 0)
                {
                    mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->miner->power_quantity -= 0.05;
                }
                break;
            
            case 4:
                if (mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->miner->power_quantity > 0)
                {
                    mapHasard->elements[LARGEUR * (int)tabEntitee[i].y + (int)tabEntitee[i].x].entitee->miner->power_quantity -= 0.05;
                }
                break;
            }
        }
        
        

        if (sortie == 0)
        {
            afficherInterface (mapHasard, tabEntitee, nb_Entitee);
            afficherCarte (mapHasard);
            printf ("Vous avez gagne ! \n");
        }

    }

    detruireCarte (mapHasard);
    if (tabEntitee) /*--->*/ free (tabEntitee);

    return 0;
}
