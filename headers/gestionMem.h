/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionMem.h                          */
/* Numéro de version : 0.5                                   */
/* Date              : 21/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _GESTIONMEM_H_INCLUDED_
#define _GESTIONMEM_H_INCLUDED_

#include "../headers/type.h"

//-----------------------------Gestion Map-----------------------------//

Map* creerCarte (double dimX, double dimY, char* nomDeLaCarte);

void detruireCarte (Map* m);

//----------------------------Gestion Block----------------------------//

Block* creerBlock (unsigned int type, unsigned int typeStone, double posX, double posY);

void detruireBlock (Block* b);

//----------------------------Gestion Entité---------------------------//

Entity* creerEntitee (double x, double y, unsigned int type);

void detruireEntitee (Entity* e);







#endif
