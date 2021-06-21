/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : type.h                                */
/* Numéro de version : 0.7                                   */
/* Date              : 27/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _TYPE_H_INCLUDED_
#define _TYPE_H_INCLUDED_

#define NULL (void*) 0
// à remettre uniquement quand l'IDE met une erreur à chaque appelle de NULL

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
//#include <freetype2/ft2build.h>
//#include FT_FREETYPE_H

#define LARGEUR 35
#define HAUTEUR 40
#define SHIPX LARGEUR / 2
#define SHIPY 2
#define NB_CREEPERSPAWNER 3

#define WINDOW_WIDTH  1050
#define WINDOW_HEIGHT 1200

char nomDeLaCarteBis[15];

SDL_Renderer* renderer;

typedef struct
{
    double x;
    double y;
}
Coord;

Coord cPos[3];

//-----------------------------Block-----------------------------//

typedef struct str_dirt
{
    double hardness;
    Coord  pos;
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
    double       quantity;
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

//---------------------------Structure---------------------------//

typedef struct str_Ship
{
    double health;
    double energy_quantity;
    double energy_storage;
    double energy_efficient;
    /*double energy_speed;*/
    double gold_quantity;
    double gold_storage;
    double gold_efficient;
    int    range;

    Coord  pos;
}
Ship;

typedef struct str_Reactor
{
    double build;
    Coord  pos;
}
Reactor;

typedef struct str_Miner
{
    double build;
    double power_quantity;
    double power_max;
    Coord  pos;
}
Miner;

typedef struct str_Shield
{
    double build;
    double health;
    Coord  pos;
}
Shield;

typedef struct str_Beacon
{
    double build;
    int    range;
    double power_quantity;
    double power_max;
    Coord  pos;
}
Beacon;

typedef struct str_Bomb
{
    double build;
    int    range;
    double power_quantity;
    double power_max;
    double damage;
    Coord  pos;
}
Bomb;


typedef struct str_CreeperSpawner
{
    double pulse;
    double power;
    double health;
    Coord  pos;
}
CreeperSpawner;


typedef struct Entity
{
    unsigned int    type;
    Ship*           ship;
    Reactor*        reactor;
    Miner*          miner;
    Shield*         shield;
    Beacon*         beacon;
    Bomb*           bombe;
    CreeperSpawner* creeperSpawner;
}
Entity;

//-------------------------Gestion Creeper-------------------------//

typedef struct Vide
{
    unsigned int* creeperQuantity;
    Coord   pos;
}
Vide;

//-------------------------Gestion Carte------------------------//

typedef struct Case
{
    int     type;
    int     cache;
    int     visibilitee;
    
    Vide*   vide;
    Block*  block;
    Entity* entitee;
}
Case;

typedef struct Map
{
    unsigned int dimX;
    unsigned int dimY;
    Case*        elements;
    char*        nomDeLaCarte;
}
Map;

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