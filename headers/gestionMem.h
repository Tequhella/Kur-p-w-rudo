/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionMem.h                          */
/* Numéro de version : 0.7                                   */
/* Date              : 27/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _GESTIONMEM_H_INCLUDED_
#define _GESTIONMEM_H_INCLUDED_

#include "type.h"

//-----------------------------Gestion Map-----------------------------//

Map* creerCarte (int dimX, int dimY, char* nomDeLaCarte);

void detruireCarte (Map* m);

//----------------------------Gestion Block----------------------------//

Block* creerBlock (unsigned int type, unsigned int typeStone, double posX, double posY);

void detruireBlock (Block* b);

//----------------------------Gestion Entité---------------------------//

Entity* creerEntitee (double x, double y, unsigned int type);

void detruireEntitee (Entity* e);

//---------------------------Gestion Mem Vide--------------------------//

Vide* creerVide (int pos);

void detruireVide (Vide* v);

#endif