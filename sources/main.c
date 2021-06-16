/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : main.c                                */
/* Numéro de version : 0.7                                   */
/* Date              : 27/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/gestionMem.h"
#include "../headers/gestionMap.h"
#include "../headers/gestionAffichage.h"
#include "../headers/gestionEntitee.h"
#include "../headers/gestionFichier.h"

/*
#include <SDL2/SDL>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
*/

int main (int argc, char** argv)
{
    srand (time(NULL));

    char yesno;

    Map* carte = NULL;
    
    printf ("Voulez-vous charger une carte déjà enregistrée ? (y/n) ");
    scanf ("%s", &yesno);
    if (yesno == 'y')
    {
        carte = chargerCarte ();
        if (carte) /*--->*/ carte->nomDeLaCarte = nomDeLaCarteBis;
        
    }

    yesno = 0;

    if (carte == NULL)
    {
        printf ("Voulez-vous sauvegarder cette map ? (y/n) ");
        scanf ("%s", &yesno);
        if (yesno == 'y')
        {
            carte = sauvegarderCarte (carte);
            char temp[15];
            for (unsigned int i = 0; i < 15; i++)
                temp[i] = carte->nomDeLaCarte[i];
                
            carte->nomDeLaCarte = temp;
        }
        else
        {
            carte = creerCarte(LARGEUR, HAUTEUR, "newMap");

            remplirHasard (carte);
            creerCaverne  (carte, rand() % LARGEUR * HAUTEUR + 280, 0);
            creerCaverne  (carte, rand() % LARGEUR * HAUTEUR + 280, 0);
            creerCaverne  (carte, rand() % LARGEUR * HAUTEUR + 280, 0);
            creerCaverne  (carte, rand() % LARGEUR * HAUTEUR + 280, 0);
            ajouterSpawnerHasard(carte->elements, NB_CREEPERSPAWNER);
        }

    }

    int sortie        = NB_CREEPERSPAWNER;
    char MvtOrAction  = 0;
    char action       = 0;

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

    carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;
    
    while (sortie != 0)
    {
        afficherInterface (carte, tabEntitee, nb_Entitee);
        afficherCarteV2   (carte);
        afficherErreur    (&erreur);

        scanf (" %c", &MvtOrAction);

        switch (MvtOrAction)
        {
            case 'a':
                if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block == NULL && carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee == NULL)
                    carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 0;
                jPos.x--;
                carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;

                break;
            case 's':
                if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block == NULL && carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee == NULL)
                    carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 0;
                jPos.y++;
                carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;

                break;
            case 'd':
                if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block == NULL && carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee == NULL)
                    carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 0;
                jPos.x++;
                carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;

                break;
            case 'w':
                if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block == NULL && carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee == NULL)
                    carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 0;
                jPos.y--;
                carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;
                break;
            case 'z':
                scanf (" %c", &action);

                switch (action)
                {
                    case 'a':
                        
                        if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block != NULL)
                        {
                            if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block->dirt != NULL || carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block->stone != NULL)
                            {
                                if (blockAcasser < 20)
                                {
                                    bPos[blockAcasser] = jPos;
                                    blockAcasser++;
                                }
                                else /*--->*/ erreur = 7;
                                
                            }
                            
                        }
                        else if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee != NULL && carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee->ship == NULL)
                        {
                            if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee->type == REACTEUR)
                            //--▼----------------------------------------------------------------------------▼--*/
                                carte->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->energy_efficient -= 0.15;

                            else if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee->type == MINER)
                            //--▼--------------------------------------------------------------------------▼--*/
                                carte->elements[LARGEUR * SHIPY + SHIPX].entitee->ship->gold_efficient -= 0.15;
                            
                           

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
                            if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee->type == BEACON)
                            {
                                carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee->beacon->power_quantity = 0;
                                visibilitee (carte, jPos.x, jPos.y);
                            }
                            detruireEntitee (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee);
                            carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee = NULL;
                            carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = VIDE;
                        }
                        else erreur = 1;
                        
                        break;
                    case 'z':
                        if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block != NULL || carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee != NULL) 
                        //--▼--------▼--*/
                            erreur = 2;
                        else
                        {
                            scanf (" %c", &MvtOrAction);
                            if (entiteeAcreer <= 9)
                            {
                                ePos[entiteeAcreer] = jPos;
                                ajouterStructure(carte, ePos[entiteeAcreer].x, ePos[entiteeAcreer].y, (int)MvtOrAction, &erreur);
                                if (erreur == 0) /*--->*/ entiteeAcreer++;
                            }
                            else /*--->*/ erreur = 8;
                        }
                            
                        break;
                    case 'c':
                        for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
                        {
                            carte->elements[i].visibilitee = 1;
                        }
                        break;
                        
                    default: erreur = 9; break;
                }
                break;

            default: erreur = 9; break;
        }
        if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block != NULL) /*----->*/ carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 1;
        if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee != NULL) /*--->*/ carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 2;
        
        if (blockAcasser > 0)
        {
            compte = (int*) realloc (compte, sizeof(int) * blockAcasser);
            if (compte[blockAcasser - 1] != 1) /*--->*/ compte[blockAcasser - 1] = 0;

            casserBlock 
            (
                carte,
                bPos,
                &blockAcasser,
                compte,
                &nb_besoin,
                &erreur
            );
        }
        
        if (entiteeAcreer > 0)
        {
            compteE = (int*) realloc (compteE, sizeof(int) * entiteeAcreer);
            if (compteE[entiteeAcreer - 1] != 1) /*--->*/ compteE[entiteeAcreer - 1] = 0;

            tabEntitee = constructionStructure
            (
                carte,
                ePos,
                tabEntitee,
                &entiteeAcreer,
                compteE,
                &nb_Entitee,
                &nb_besoin
            );
        }
        
        visibilitee (carte, SHIPX, SHIPY);


        remplirStock (carte);
        tabEntitee = remplirEnergieStructure
        (
            carte,
            tabEntitee,
            &nb_Entitee,
            &nb_besoin,
            &sortie
        );
        viderEnergieStructure (carte, tabEntitee, nb_Entitee);
        
        for (unsigned int i = 0; i < 3; i++)
        {
            int x = cPos[i].x;
            int y = cPos[i].y;

            if (carte->elements[LARGEUR * y + x].entitee)
                carte->elements[LARGEUR * y + x].vide->creeperQuantity[0] += carte->elements[LARGEUR * y + x].entitee->creeperSpawner->power;

        }
        
        mouvementCreeper (carte);

        if (sortie == 0)
        {
            afficherInterface (carte, tabEntitee, nb_Entitee);
            afficherCarteV2   (carte);
            printf ("Vous avez gagné ! \n");
        }

    }

    detruireCarte (carte);
    if (compte) /*------->*/ free (compte);
    if (compteE) /*------>*/ free (compteE);
    if (tabEntitee) /*--->*/ free (tabEntitee);
    

    return 0;
}