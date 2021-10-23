/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionEntitee.h                      */
/* Numéro de version : 0.8.2                                 */
/* Date              : 27/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _GESTIONENTITEE_H_INCLUDED_
#define _GESTIONENTITEE_H_INCLUDED_

#include "type.h"

void ajouterStructure (Map* m, int x, int y, unsigned int type, int* erreur);

Coord* constructionStructure
(
    Map* m,
    Coord* _ePos,
    Coord* _tabEntitee,
    int* _entiteeAcreer,
    int* _compteE,
    int* _nb_Entitee,
    int* _nb_besoin
);

Coord* remplirEnergieStructure
(
    Map* m,
    Coord* _tabEntitee,
    int* _nb_Entitee,
    int* _nb_besoin,
    int* _sortie
);

void viderEnergieStructure (Map* m, Coord* _tabEntitee, int _nb_Entitee);

void ajouterSpawnerHasard (Case* c, unsigned int nb_Spawner);

void effetDegats (Case* c, Entity* attaquant, Entity* victime);

void mouvementCreeper (Map* m, int* _sortie);

#endif