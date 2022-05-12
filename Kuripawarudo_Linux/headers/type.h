/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : type.h                                */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _TYPE_H_INCLUDED_
#define _TYPE_H_INCLUDED_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <memory>
#include <vector>

/* Il définit deux constantes, LARGEUR et HAUTEUR, et leur affecte respectivement les valeurs 30 et 45. */
constexpr auto LARGEUR = 30;
constexpr auto HAUTEUR = 45;

class Base
{
    public: virtual ~Base() {}
};

/**
 * Un Coord est une structure qui a deux membres à virgule flottante double précision, x et y.
 * Il est utilisé pour représenter les coordonnées d'une entité.
 * 
 * Coord GetCoord(vide)
 * {
 *     Coord;
 *     coord.x = 3.14 ;
 *     coord.y = 2,71 ;
 *     return coord ;
 * }
 * 
 * int principal (vide)
 * {
 */
typedef struct Coord : public Base
{
	Coord() : x(0), y(0) {}
	Coord(double x, double y) : x(x), y(y) {}
	~Coord(){}
    double x;
    double y;
}
Coord ;

template<typename Base, typename T>
inline bool instanceof(const T* ptr)
{
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

/* Un moyen de définir une valeur constante pour chaque type de case. */
enum
{
    VIDE,
    BLOCK,
    ENTITEE,
    CURSEUR
};

/* Définir une valeur constante pour chaque type de terrain. */
constexpr auto TERRE = 1;
constexpr auto ROCHE = 2;
enum
{
    ROCHE1,
    ROCHE2,
    ROCHE3
};
constexpr auto MINERAI = 3;

/* Une liste de tous les différents types d'entités. */
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