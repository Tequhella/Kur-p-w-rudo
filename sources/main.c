/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : main.c                                */
/* Numéro de version : 0.6                                   */
/* Date              : 18/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/type.h"
#include "../headers/gestionMem.h"
#include "../headers/gestionMap.h"
#include "../headers/gestionAffichage.h"

/*
#include <SDL2/SDL>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
*/

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
    int* compte       = malloc (sizeof(int));
    int* compteE      = malloc (sizeof(int));

    Coord* tabEntitee = malloc (sizeof(Coord));
    int nb_Entitee    = 0;

    Coord jPos  = (Coord){17, 3};
    Coord bPos[20];
    Coord ePos[20];

    mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;
    
    while (sortie != 0)
    {
        afficherInterface (mapHasard, tabEntitee, nb_Entitee);
        afficherCarte     (mapHasard);
        afficherErreur    (&erreur);

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
                                if (blockAcasser < 20)
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
                                    
                                    tabEntitee = (Coord*) realloc (tabEntitee, sizeof(Coord) * nb_Entitee);
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
                            erreur = 2;
                        else
                        {
                            scanf (" %c", &MvtOrAction);
                            if (entiteeAcreer <= 9)
                            {
                                ePos[entiteeAcreer] = jPos;
                                ajouterStructure(mapHasard, ePos[entiteeAcreer].x, ePos[entiteeAcreer].y, (int)MvtOrAction, &erreur);
                                if (erreur == 0) /*--->*/ entiteeAcreer++;
                            }
                            else /*--->*/ erreur = 8;
                        }
                            
                        break;
                    case 'c':
                        for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
                        {
                            mapHasard->elements[i].visibilitee = 1;
                        }
                        break;
                        
                    default: erreur = 9; break;
                }
                break;

            default: erreur = 9; break;
        }
        if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block != NULL) /*----->*/ mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 1;
        if (mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee != NULL) /*--->*/ mapHasard->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 2;
        
        if (blockAcasser > 0)
        {
            compte = (int*) realloc (compte, sizeof(int) * blockAcasser);
            if (compte[blockAcasser - 1] != 1) /*--->*/ compte[blockAcasser - 1] = 0;

            casserBlock 
            (
                mapHasard,
                bPos,
                &blockAcasser,
                compte,
                &nb_besoin
            );
        }
        
        if (entiteeAcreer > 0)
        {
            compteE = (int*) realloc (compteE, sizeof(int) * entiteeAcreer);
            if (compteE[entiteeAcreer - 1] != 1) /*--->*/ compteE[entiteeAcreer - 1] = 0;

            tabEntitee = constructionStructure
            (
                mapHasard,
                ePos,
                tabEntitee,
                &entiteeAcreer,
                compteE,
                &nb_Entitee,
                &nb_besoin
            );
        }
        


        remplirStock (mapHasard);
        tabEntitee = remplirEnergieStructure
        (
            mapHasard,
            tabEntitee,
            &nb_Entitee,
            &nb_besoin,
            &sortie
        );
        viderEnergieStructure (mapHasard, tabEntitee, nb_Entitee);


        if (sortie == 0)
        {
            afficherInterface (mapHasard, tabEntitee, nb_Entitee);
            afficherCarte (mapHasard);
            printf ("Vous avez gagné ! \n");
        }

    }

    detruireCarte (mapHasard);
    if (compte) /*------->*/ free (compte);
    if (compteE) /*------>*/ free (compteE);
    if (tabEntitee) /*--->*/ free (tabEntitee);

    return 0;
}