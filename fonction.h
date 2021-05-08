/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : fonction.h                            */
/* Numéro de version : *0.3*                                 */
/* Date              : 21/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _FONCTION_H_INCLUDED_
#define _FONCTION_H_INCLUDED_

#include "type.h"

//-----------------------------Gestion Map-----------------------------//

Map* creerCarte (double dimX, double dimY, char* nomDeLaCarte);

void detruireCarte (Map* m);

void afficherCarte (Map* m);

void remplirHasard (Map* m);

void creerCaverne (Map* m, unsigned int pos, int randMoins);

//----------------------------Gestion Block----------------------------//

Block* creerBlock (unsigned int type, unsigned int typeStone, double posX, double posY);

void detruireBlock (Block* b);

//----------------------------Gestion Entité---------------------------//

Entity* creerEntitee (double x, double y, unsigned int type);

void detruireEntitee (Entity* e);

void ajouterEntitee (Case* c, int x, int y, unsigned int type, unsigned int* erreur);

void ajouterSpawnerHasard (Case* c, unsigned int nb_Spawner);

int testAccessibilitee (Map* m, int x, int y);

void decache (Map* m);

//---------------------------Gestion Interface-------------------------//

void afficherInterface (Map* m);

#endif
