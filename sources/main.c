/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : main.c                                */
/* Numéro de version : 0.8.2                                 */
/* Date              : 27/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/gestionMem.h"
#include "../headers/gestionMap.h"
#include "../headers/gestionAffichage.h"
#include "../headers/gestionEntitee.h"
#include "../headers/gestionFichier.h"


int main (int argc, char** argv)
{
    srand (time(NULL));

    char yesno;         // écoute l'utilisateur pour choisir une action.
    Map* carte = NULL;  // la carte sur laquelle on joue (pas encore créé pour l'instant).
    
    /*
    * On demande à l'utilisateur s'il veut charger une carte prédéfinie.
    */
    printf ("Voulez-vous charger une carte déjà enregistrée ? (y/n) ");
    scanf ("%s", &yesno);
    if (yesno == 'y')
    {
        carte = chargerCarte ();
        if (carte) /*--->*/ carte->nomDeLaCarte = nomDeLaCarteBis;
        
    }

    yesno = 0;  // valorisation à 0 pour vider l'ancienne réponse.


    /*
    * Si la carte n'a pas été chargé, on la créé à partir de rien.
    */
    if (carte == NULL)
    {
        // On demande à l'utilsateur s'il veut sauvegarder la carte.
        printf ("Voulez-vous sauvegarder cette map ? (y/n) ");
        scanf ("%s", &yesno);
        if (yesno == 'y')
        {
            carte = sauvegarderCarte (carte);
            char temp[15];
            for (unsigned int i = 0; i < 15; i++)   // Le nom de la carte ne se charge pas correctement,
                temp[i] = carte->nomDeLaCarte[i];   // on le sauvegarde dans un tempon pour le récupérer ensuite.
                
            carte->nomDeLaCarte = temp;
        }
        else
        {
            // On créé la carte normalement, avec les dimensions le nom de la carte choisie.
            carte = creerCarte(LARGEUR, HAUTEUR, "newMap");

            // On rempli la carte des blocks de manière aléatoirement.
            remplirHasard (carte);

            // On créé plusieurs cavernes aléatoires.
            for (unsigned int i = 0; i < 4; i++)
                creerCaverne  (carte, rand() % LARGEUR * HAUTEUR + 280, 0);

            // On ajoute les producteurs de creeper.
            ajouterSpawnerHasard(carte->elements, NB_CREEPERSPAWNER);
        }

    }

    int sortie           = NB_CREEPERSPAWNER,
        affichageActu    = 0,
        affichageActuPre = 0;

    int blockActu       = 0,
        blockActuPre    = 0,
        blockAcasser    = 0;

    int entitActu       = 0,
        entitActuPre    = 0,
        entiteeAcreer   = 0;

    int stockActu       = 0,
        stockActuPre    = 0,
        structActu      = 0,
        structActuPre   = 0;

    int energieActu     = 0,
        energieActuPre  = 0;

    int creepActu       = 0,
        creepActuPre    = 0,
        creepMove       = 0,
        creepMovePre    = 0;

    int spawnActu       = 0,
        spawnActuPre[3] = {0};

    
    

    int erreur        = 0;
    int nb_besoin     = 0;
    int* compte       = malloc (4);
    int* compteE      = malloc (4);

    Coord* tabEntitee = malloc (sizeof(Coord));
    int nb_Entitee    = 0;

    Coord jPos  = (Coord){17, 3};
    Coord bPos[20];
    Coord ePos[20];

    carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = 3;

    //-----------------affichage graphique-----------------//

    if (SDL_Init (SDL_INIT_VIDEO) != 0)
    {
        fprintf (stderr, "Erreur d'inititalisation du mécanisme SDL : %s \n", SDL_GetError());

        return EXIT_FAILURE;
    }

    SDL_Window* fenetre = SDL_CreateWindow (
                                            "Exemple 1"             ,
                                            SDL_WINDOWPOS_UNDEFINED ,
                                            SDL_WINDOWPOS_UNDEFINED ,
                                            WINDOW_WIDTH            ,
                                            WINDOW_HEIGHT           ,
                                            SDL_WINDOW_SHOWN
                                            );
    if (fenetre == NULL)
    {
        fprintf (stderr, "Erreur de création de la fenêtre : %s \n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    renderer = SDL_CreateRenderer (fenetre, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event1;

    for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
    {
        if (carte->elements[i].visibilitee == 1)
        {
            switch (carte->elements[i].type)
            {
                case VIDE : afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/sol.bmp"); break;

                case BLOCK:
                    switch (carte->elements[i].block->type)
                    {
                        case DIRT : afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/dirt.bmp"); break;
                        
                        case STONE:
                            switch (carte->elements[i].block->stone->type)
                            {
                                case STONE1: afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/stone1.bmp"); break;
                                case STONE2: afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/stone2.bmp"); break;
                                case STONE3: afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/stone3.bmp"); break;
                            }
                            break;
                        
                        case GOLD : afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/gold.bmp"); break;
                    }
                    break;
                    
                
                case ENTITY:
                    afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/sol.bmp");
                    switch (carte->elements[i].entitee->type)
                    {
                        case SHIP           : afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/ship.bmp");            break;
                        case REACTEUR       : afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/reacteur.bmp");        break;
                        case MINER          : afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/miner.bmp");           break;
                        case BEACON         : afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/beacon.bmp");          break;
                        case BOMBE          : afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/Bombe.bmp");           break;
                        case CREEPERSPAWNER : afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/Creeper_Spawner.bmp"); break;
                    }
                    break;
                
                case CURSOR: 
                    afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/sol.bmp");
                    afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/curseur.bmp");
                    break;
            }

        }
        else /*--->*/ afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/brouillard.bmp");
        
    }

    //-----------------------------------------------------//
    
    while (sortie != 0)
    {
        affichageActu = SDL_GetTicks ();
        if (affichageActu - affichageActuPre >= 1000)
        {
            //afficherInterface (carte, tabEntitee, nb_Entitee);
            affichageActuPre = SDL_GetTicks ();
        }
        
        afficherErreur    (&erreur);
        SDL_RenderPresent (renderer);
        

        while (SDL_PollEvent(&event1))
        {
            if (event1.type == SDL_KEYDOWN)
            {
                if (event1.key.keysym.sym == SDLK_c)
                {
                    for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
                    {
                        carte->elements[i].visibilitee = 1;
                        switch (carte->elements[i].type)
                        {
                            case VIDE  : afficherVide    (carte->elements[i].vide);    break;
                            case BLOCK : afficherBlock   (carte->elements[i].block);   break;
                            case ENTITY: afficherEntitee (carte->elements, i);         break;
                        }
                    }
                }
                else if (event1.key.keysym.sym == SDLK_f)
                {
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

                            for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
                            {
                                if (carte->elements[i].visibilitee == 0)
                                    afficherImage (i % LARGEUR * 30, i / LARGEUR * 30, "img/brouillard.bmp");
                                
                            }
                            
                        }

                        detruireEntitee (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee);
                        carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee = NULL;
                        carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = VIDE;
                        afficherImage (jPos.x * 40, jPos.y * 40, "img/sol.bmp");

                    }
                    else erreur = 1;

                }
                else if (event1.key.keysym.sym == SDLK_a ||
                         event1.key.keysym.sym == SDLK_s || 
                         event1.key.keysym.sym == SDLK_d || 
                         event1.key.keysym.sym == SDLK_w) /*--->*/ afficherMouvementCurseur (event1.key.keysym.sym, carte, &jPos);
                
                else if (event1.key.keysym.sym == SDLK_1 ||
                         event1.key.keysym.sym == SDLK_2 ||
                         event1.key.keysym.sym == SDLK_3 ||
                         event1.key.keysym.sym == SDLK_4 ||
                         event1.key.keysym.sym == SDLK_5)
                {
                    if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block != NULL || carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee != NULL) 
                    //--▼--------▼--*/
                        erreur = 2;
                    else
                    {
                        if (entiteeAcreer <= 19)
                        {
                            ePos[entiteeAcreer] = jPos;
                            ajouterStructure(carte, ePos[entiteeAcreer].x, ePos[entiteeAcreer].y, event1.key.keysym.sym, &erreur);
                            if (erreur == 0)
                            {
                                entiteeAcreer++;
                            }
                        }
                        else /*--->*/ erreur = 8;

                    }
                }
                
                else erreur = 9;

            }
            else if (event1.type == SDL_WINDOWEVENT)
            {
                if (event1.window.event == SDL_WINDOWEVENT_CLOSE) /*--->*/ sortie = -2;
            }
            
        
        }
        if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].block != NULL) /*----->*/ carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = BLOCK;
        if (carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].entitee != NULL) /*--->*/ carte->elements[LARGEUR * (int)jPos.y + (int)jPos.x].type = ENTITY;
        
        if (blockAcasser > 0)
        {
            compte = (int*) realloc (compte, 4 * blockAcasser);
            if (compte[blockAcasser - 1] != 1) /*--->*/ compte[blockAcasser - 1] = 0;

            blockActu = SDL_GetTicks ();

            if (blockActu - blockActuPre >= 1000)
            {
                casserBlock
                (
                    carte,
                    bPos,
                    &blockAcasser,
                    compte,
                    &nb_besoin,
                    &erreur
                );
                blockActuPre = SDL_GetTicks ();
            }
            
            
        }
        
        if (entiteeAcreer > 0)
        {
            compteE = (int*) realloc (compteE, 4 * entiteeAcreer);
            if (compteE[entiteeAcreer - 1] == 0) /*--->*/ compteE[entiteeAcreer - 1] = 0;

            entitActu = SDL_GetTicks ();

            if (entitActu - entitActuPre >= 1000)
            {
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
                entitActuPre = SDL_GetTicks ();
            }
            
        }
        
        visibilitee (carte, SHIPX, SHIPY);


        stockActu = SDL_GetTicks ();

        if (stockActu - stockActuPre >= 1000)
        {
            remplirStock (carte);
            stockActuPre = SDL_GetTicks ();
        }


        structActu = SDL_GetTicks ();
        
        if (structActu - structActuPre >= 1000)
        {
            tabEntitee = remplirEnergieStructure
            (
                carte,
                tabEntitee,
                &nb_Entitee,
                &nb_besoin,
                &sortie
            );
            structActuPre = SDL_GetTicks ();
        }


        energieActu = SDL_GetTicks ();
        
        if (energieActu - energieActuPre >= 1000)
        {
            viderEnergieStructure (carte, tabEntitee, nb_Entitee);
            energieActuPre = SDL_GetTicks ();
        }
        
        

        
        spawnActu = SDL_GetTicks ();
        
        for (unsigned int i = 0; i < 3; i++)
        {
            int x = cPos[i].x;
            int y = cPos[i].y;

            if (carte->elements[LARGEUR * y + x].entitee && spawnActu - spawnActuPre[i] >= 1000 * carte->elements[LARGEUR * y + x].entitee->creeperSpawner->pulse)
            {
                carte->elements[LARGEUR * y + x].vide->creeperQuantity[0] += carte->elements[LARGEUR * y + x].entitee->creeperSpawner->power / 4;
                carte->elements[LARGEUR * y + x].vide->creeperQuantity[1] += carte->elements[LARGEUR * y + x].entitee->creeperSpawner->power / 4;
                carte->elements[LARGEUR * y + x].vide->creeperQuantity[2] += carte->elements[LARGEUR * y + x].entitee->creeperSpawner->power / 4;
                carte->elements[LARGEUR * y + x].vide->creeperQuantity[3] += carte->elements[LARGEUR * y + x].entitee->creeperSpawner->power / 4;
                spawnActuPre[i] = SDL_GetTicks ();
            }
            
        }
        
        creepMove = SDL_GetTicks ();

        if (creepMove - creepMovePre >= 200)
        {
            mouvementCreeper (carte, &sortie);
            creepMovePre = SDL_GetTicks ();
        }
        
        if (sortie == 0)
        {
            afficherInterface (carte, tabEntitee, nb_Entitee);
            printf ("Vous avez gagné ! \n");
        }
        else if (sortie == -1)
        {
            afficherInterface (carte, tabEntitee, nb_Entitee);
            printf ("Vous avez perdu ! \n");
            sortie++;
        }
        else if (sortie == -2)
            sortie += 2;

        creepActu = SDL_GetTicks ();
        
        if (creepActu - creepActuPre >= 200)
        {
            for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
            {
                if ((carte->elements[i].type == VIDE || carte->elements[i].type == ENTITY) && carte->elements[i].visibilitee == 1 && (carte->elements[i].vide->creeperQuantity[0] > 0 ||
                                                                                               carte->elements[i].vide->creeperQuantity[1] > 0 ||
                                                                                               carte->elements[i].vide->creeperQuantity[2] > 0 ||
                                                                                               carte->elements[i].vide->creeperQuantity[3] > 0))
                {
                    afficherVide (carte->elements[i].vide);
                    if (carte->elements[i].entitee)
                        afficherEntitee (carte->elements, i);
                    
                }
            }
            creepActuPre = SDL_GetTicks ();
        }

    }

    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow   (fenetre);

    SDL_Quit ();

    detruireCarte (carte);
    if (compte) /*------->*/ free (compte);
    if (compteE) /*------>*/ free (compteE);
    if (tabEntitee) /*--->*/ free (tabEntitee);
    

    return 0;
}

/*
                
*/