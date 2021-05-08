/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : type.h                                */
/* Numéro de version : 0.2                                   */
/* Date              : 17/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _TYPE_H_INCLUDED_
#define _TYPE_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LARGEUR 35
#define HAUTEUR 50

typedef struct
{
    double x;
    double y;
}
Coord;

//-----------------------------Block-----------------------------//

typedef struct str_dirt
{
    Coord pos;
}
Dirt;

typedef struct str_stone
{
    unsigned int type;
    double       hardness;
    Coord        pos;
}
Stone;

typedef struct str_gold
{
    unsigned int type;
    unsigned int quantity;
    Coord        pos;
}
Gold;

typedef struct str_Block
{
    unsigned int type;
    Dirt*        dirt;
    Stone*       stone;
    Gold*        gold;
}
Block;

//-------------------------Gestion Carte------------------------//

typedef struct Case
{
    int type;
    Block*       block;
}
Case;

typedef struct Map
{
    unsigned int dimX;
    unsigned int dimY;
    Case*        elements;
    char         nomDeLaCarte;
}
Map;

#define VIDE  0
#define BLOCK 1

#define DIRT  1
#define STONE 2
    #define STONE1 1
    #define STONE2 2
    #define STONE3 3
#define GOLD  3

#endif