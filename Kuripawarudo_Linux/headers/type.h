/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : type.h                                */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _TYPE_H_INCLUDED_
#define _TYPE_H_INCLUDED_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>

#define LARGEUR 30
#define HAUTEUR 45

typedef struct
{
    double x;
    double y;
}
Coord ;

enum
{
    VIDE,
    BLOCK,
    ENTITEE,
    CURSEUR
};

#define TERRE  1
#define ROCHE 2
enum
{
    ROCHE1,
    ROCHE2,
    ROCHE3
};
#define MINERAI  3

enum
{
    VAISSEAU,
    REACTEUR,
    MINEUR,
    BOUCLIER,
    PHARE,
    BOMBE,
    CREEPER_EMETTEUR
};


#endif