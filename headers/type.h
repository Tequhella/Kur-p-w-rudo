/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : type.h                                */
/* Numéro de version : 0.1                                   */
/* Date              : 16/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _TYPE_H_INCLUDED_
#define _TYPE_H_INCLUDED_

#include <iostream>
#include <cstdlib>
#include <ctime>

#define LARGEUR 30
#define HAUTEUR 45

enum
{
    VIDE,
    BLOCK,
    ENTITY,
    CURSOR
};

#define DIRT  1
#define STONE 2
enum
{
    STONE1,
    STONE2,
    STONE3
};
#define GOLD  3

#define SHIP           0
#define REACTEUR       1
#define MINER          2
#define SHIELD         3
#define BEACON         4
#define BOMBE          5
#define CREEPERSPAWNER 9

#endif