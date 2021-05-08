/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : fonction.h                            */
/* Numéro de version : 0.1                                   */
/* Date              : 16/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _FONCTION_H_INCLUDED_
#define _FONCTION_H_INCLUDED_

#include "type.h"

//-----------------------------Gestion Map-----------------------------//

Map* creerMap (double dimX, double dimY, char nomDeLaCarte);

void detruireMap (Map* m);

void afficherMap (Map* m);

//----------------------------Gestion Block----------------------------//

Block* creerBlock (unsigned int type, unsigned int typeStone, double posX, double posY);

void detruireBlock (Block* b);

#endif