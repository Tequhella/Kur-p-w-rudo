/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : main.c                                */
/* Numéro de version : 0.3                                   */
/* Date              : 19/03/2021                            */
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

    int sortie        = 1;
    int MvtOrAction   = 0;
    int blockAcasser  = 0;
    int entiteeAcreer = 0;
    int erreur        = 0;
    int nb_besoin     = 0;
    int compte[20]    = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char action;
    Coord jPos = (Coord){17, 3};
    Coord bPos[10];
    Coord ePos[10];

    mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;
    
    while (sortie != 0)
    {
        afficherInterface (mapHasard);
        afficherCarte (mapHasard);
        switch (erreur)
        {
            case 1: printf ("Vous ne pouvez rien supprimer sur cette case-là. \n"); break;
            case 2: printf ("Vous ne pouvez pas ajouter ou supprimer d'entitee ici. \n"); break;
            case 3: printf ("Vous ne pouvez pas placer cette entitee-la. \n"); break;
            case 4: printf ("Impossible de placer de reacteur ici. \n"); break;
            case 5: printf ("Impossible de placer de mineur ici. \n"); break;
            case 6: printf ("Impossible de placer de beacon ici. \n"); break;
            case 7: printf ("Nombre maximum de cases pouvant être cassé à la suite, atteint. \n"); break;
            case 8: printf ("Nombre maximum d'entitee pouvant être ajouter à la suite, atteint. \n"); break;
        }
        erreur = 0;

        scanf ("%d", &MvtOrAction);

        switch (MvtOrAction)
        {
            case 1:
                if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block == NULL && mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee == NULL)
                    mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 0;
                jPos.x--;
                mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;

                break;
            case 2:
                if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block == NULL && mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee == NULL)
                    mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 0;
                jPos.y++;
                mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;

                break;
            case 3:
                if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block == NULL && mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee == NULL)
                    mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 0;
                jPos.x++;
                mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;


                break;
            case 5:
                if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block == NULL && mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee == NULL)
                    mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 0;
                jPos.y--;
                mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;
                break;
            case 6:
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
                            detruireEntitee(mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee);
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
                            scanf ("%d", &MvtOrAction);
                            if (entiteeAcreer <= 9)
                            {
                                ePos[entiteeAcreer] = jPos;
                                ajouterEntitee(mapHasard->elements, ePos[entiteeAcreer].x, ePos[entiteeAcreer].y, MvtOrAction, &erreur);
                                if (erreur == 0)
                                {
                                    entiteeAcreer++;
                                    nb_besoin++;
                                }
                                
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
                    compte[i] = testAccessibilitee(mapHasard, bPos[i].x, bPos[i].y);
                    if (compte[i] == 1) /*--->*/ nb_besoin++;
                    
                }
                if (mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block->dirt != NULL && compte[i] == 1)
                {
                    mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block->dirt->hardness -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
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
                    mapHasard->elements[LARGEUR * (int)bPos[i].y + (int)bPos[i].x].block->stone->hardness -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
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
                switch (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->type)
                {
                case 1:
                    mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->reactor->construction -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
                    if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->reactor->construction <= 0)
                    {
                        mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].type = ENTITY;
                        ePos[i] = ePos[entiteeAcreer - 1];
                        entiteeAcreer--;
                        nb_besoin--;
                        i--;
                    }
                    break;
                
                case 2:
                    mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->miner->construction -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
                    if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->miner->construction <= 0)
                    {
                        mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].type = ENTITY;
                        ePos[i] = ePos[entiteeAcreer - 1];
                        entiteeAcreer--;
                        nb_besoin--;
                        i--;
                    }
                    break;

                case 3:
                    mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->shield->construction -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
                    if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->shield->construction <= 0)
                    {
                        mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].type = ENTITY;
                        ePos[i] = ePos[entiteeAcreer - 1];
                        entiteeAcreer--;
                        nb_besoin--;
                        i--;
                    }
                    break;
                
                case 4:
                    mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->beacon->construction -= mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient / nb_besoin;
                    if (mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].entitee->beacon->construction <= 0)
                    {
                        mapHasard->elements[LARGEUR * (int)ePos[i].y + (int)ePos[i].x].type = ENTITY;
                        ePos[i] = ePos[entiteeAcreer - 1];
                        entiteeAcreer--;
                        nb_besoin--;
                        i--;
                    }
                    break;
                }

            }
            
        }
        

        if (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity < mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_storage)
        {
            mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity += mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_efficient;

            while (mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity > mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_storage)
            {
                mapHasard->elements[LARGEUR * 2 + LARGEUR / 2].entitee->ship->energy_quantity -= 0.25;
            }
            
        }

    }

    detruireCarte (mapHasard);

    return 0;
}
