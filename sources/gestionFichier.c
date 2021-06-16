/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionFichier.c                      */
/* Numéro de version : 0.7                                   */
/* Date              : 27/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/gestionFichier.h"
#include "../headers/gestionMem.h"
#include "../headers/gestionMap.h"
#include "../headers/gestionEntitee.h"

Map* sauvegarderCarte (Map* m)
{
    char* sauvegarde = "sauvegardeMap.txt";

    FILE* fichier = fopen (sauvegarde, "rb");

    if (fichier == NULL)
    {
        fichier = fopen (sauvegarde, "w");
        fprintf (fichier, "------------------Sauvegarde de map------------------\n\n");
        fclose  (fichier);
    }
    else /*--->*/ fclose (fichier);
        
    fichier = fopen (sauvegarde, "a+");

    if (fichier)
    {
        char nomDeLaMap[15];
        
        printf ("Donnez un nom à la map : ");
        scanf ("%s", nomDeLaMap);

        m = creerCarte(LARGEUR, HAUTEUR, nomDeLaMap);

        remplirHasard (m);
        creerCaverne  (m, rand() % LARGEUR * HAUTEUR + 280, 0);
        creerCaverne  (m, rand() % LARGEUR * HAUTEUR + 280, 0);
        creerCaverne  (m, rand() % LARGEUR * HAUTEUR + 280, 0);
        creerCaverne  (m, rand() % LARGEUR * HAUTEUR + 280, 0);
        ajouterSpawnerHasard(m->elements, NB_CREEPERSPAWNER);

        printf ("Le fichier %s a pu être ouvert en écriture. \n", sauvegarde);
        fprintf (fichier, "\nNom : %s\n{\n", m->nomDeLaCarte);
        fprintf (fichier, "\tDimension :\n\t\tLargeur : %d\n\t\tHauteur : %d\n", m->dimX, m->dimY);
        fprintf (fichier, "\tÉléments : \n\t\t");

        for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
        {
            switch (m->elements[i].type)
            {
                case VIDE   : fprintf (fichier, "0 "); break;

                case BLOCK  : 
                    fprintf (fichier, "1(");
                    switch (m->elements[i].block->type)
                    {
                        case DIRT : fprintf (fichier, "1) ");   break;

                        case STONE: 
                            fprintf (fichier, "2(");
                            switch (m->elements[i].block->stone->type)
                            {
                                case STONE1: fprintf (fichier, "0)) "); break;
                                case STONE2: fprintf (fichier, "1)) "); break;
                                case STONE3: fprintf (fichier, "2)) "); break;
                            }
                            break;

                        case GOLD : fprintf (fichier, "3) ");
                    }
                    break;

                case ENTITY :
                    fprintf (fichier, "2(");
                    switch (m->elements[i].entitee->type)
                    {
                        case SHIP           : fprintf (fichier, "0) "); break;
                        case REACTEUR       : fprintf (fichier, "1) "); break;
                        case MINER          : fprintf (fichier, "2) "); break;
                        case SHIELD         : fprintf (fichier, "3) "); break;
                        case BEACON         : fprintf (fichier, "4) "); break;
                        case BOMBE          : fprintf (fichier, "5) "); break;
                        case CREEPERSPAWNER : fprintf (fichier, "9) "); break;
                    }
                    break;
            }

            if (i == LARGEUR * HAUTEUR - 1)
                fprintf (fichier, ";");

        }

        fprintf (fichier, "\n};");
        

        fclose (fichier);
    }
    else
    {
        printf ("Le fichier %s n'a pas pu être ouvert. \n", sauvegarde);
    }

    return m;
}

Map* chargerCarte ()
{
    Map* m;

    char* sauvegarde = "sauvegardeMap.txt";
    char caractere = 't';
    char nomDeLaCarte[15];
    char cdimX[2], cdimY[2];
    
    FILE* fichier = fopen (sauvegarde, "r");

    if (fichier)
    {
        printf ("\nListes des cartes :\n\n");

        while (caractere != 0)
        {
            while (caractere != 'N')
            {
                fgets (&caractere, 2, fichier);
                if (caractere == '}')
                {
                    fseek (fichier, 1, SEEK_CUR);
                    fgets (&caractere, 2, fichier);
                    if (caractere != 'N')
                    {
                        caractere = 0;
                        break;
                    }
                    
                }
                
            }

            if (caractere != 0)
            {
                fseek (fichier, 4, SEEK_CUR);
                printf (" - %s\n", fgets (nomDeLaCarte, 15, fichier));
                caractere = 't';
            }
            
        }
        caractere = 't';
        printf ("Choisissez une carte : ");
        scanf  ("%s", nomDeLaCarteBis);

        int nbCar = strlen(nomDeLaCarteBis);

        fseek (fichier, 1, SEEK_SET);

        while (caractere != 0)
        {
            int check = 0;
            while (caractere != 'N' && check == 0)
            {
                fgets (&caractere, 2, fichier);
                if (caractere == 'N')
                {
                    fseek (fichier, 5, SEEK_CUR);
                    fgets (nomDeLaCarte, strlen(nomDeLaCarteBis) + 1, fichier);
                }
                
            }
            caractere = 't';
            for (unsigned int i = 0; i < nbCar; i++)
                if (nomDeLaCarte[i] == nomDeLaCarteBis[i])
                    check++;
            
            if (check == nbCar)
            {
                int i = 0;
                int c = 0;
                int  dimX = 10, dimY = 10;

                while (i < dimX * dimY)
                {
                    fgets (&caractere, 2, fichier);
                    switch (caractere)
                    {
                        case 'L' :
                            fseek  (fichier, 9, SEEK_CUR);
                            fgets (cdimX, 3, fichier);
                            dimX = atoi (cdimX);
                            break;
                        
                        case 'H' :
                            fseek (fichier, 9, SEEK_CUR);
                            fgets (cdimY, 3, fichier);
                            dimY = atoi (cdimY);
                            m = creerCarte  (dimX, dimY, nomDeLaCarteBis);
                            break;
                        
                        case '0' : 
                            m->elements[i].type    = VIDE;
                            m->elements[i].vide    = creerVide (i);
                            m->elements[i].entitee = NULL;
                            m->elements[i].block   = NULL;
                            i++;
                            break;
                        
                        case '1' :
                            m->elements[i].type  = BLOCK;

                            printf ("Crétaion block\n");

                            fseek (fichier, 1, SEEK_CUR);
                            fgets (&caractere, 2, fichier);

                            switch (caractere)
                            {
                                case '3' : m->elements[i].block = creerBlock (GOLD, 0, i % dimX, i / dimX); break;

                                case '2' :
                                    fseek (fichier, 1, SEEK_CUR);
                                    fgets (&caractere, 2, fichier);
                                    m->elements[i].block = creerBlock (STONE, atoi(&caractere),  i % dimX, i / dimX);
                                    break;
                                
                                case '1' : m->elements[i].block = creerBlock (DIRT, 0, i % dimX, i / dimX); break;
                            }

                            m->elements[i].entitee = NULL;
                            m->elements[i].vide    = NULL;

                            i++;
                            break;

                        case '2' :
                            m->elements[i].type  = ENTITY;
                            m->elements[i].block = NULL;
                            m->elements[i].vide  = creerVide (i);

                            fseek (fichier, 1, SEEK_CUR);
                            fgets (&caractere, 2, fichier);

                            printf ("Création entitee\n");

                            switch (caractere)
                            {
                                case '0' : m->elements[i].entitee = creerEntitee (i % dimX, i / dimX, SHIP);           break;
                                case '1' : m->elements[i].entitee = creerEntitee (i % dimX, i / dimX, REACTEUR);       break;
                                case '2' : m->elements[i].entitee = creerEntitee (i % dimX, i / dimX, MINER);          break;
                                case '3' : m->elements[i].entitee = creerEntitee (i % dimX, i / dimX, SHIELD);         break;
                                case '4' : m->elements[i].entitee = creerEntitee (i % dimX, i / dimX, BEACON);         break;
                                case '5' : m->elements[i].entitee = creerEntitee (i % dimX, i / dimX, BOMBE);          break;
                                case '9' : 
                                    m->elements[i].entitee = creerEntitee (i % dimX, i / dimX, CREEPERSPAWNER);
                                    cPos[c] = m->elements[i].entitee->creeperSpawner->pos;
                                    c++;
                                    break;
                            }

                            i++;
                            break;
                            
                    }

                }

                caractere = 0;
                
            }
            else /*--->*/ check = 0;
            
        }
    
        fclose (fichier);
    }
    else
    {
        printf ("\nLe fichier de sauvegarde n'existe pas encore, veuillez jouer une 1ère fois.\n");
    }
    
        

    return m;
}