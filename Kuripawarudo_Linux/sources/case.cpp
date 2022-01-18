/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : case.cpp                              */
/* Numéro de version : 0.3                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/case.h"
#include "../headers/entitee.h"
#include "../headers/vide.h"
#include "../headers/block.h"

Case::Case ()
{
    vide    = nullptr ;
    block   = nullptr ;
    entitee = nullptr ;

    type = 0 ;
}

Case::~Case ()
{
    
}

/*************************************************************************
*                                 Méthode                                *
*************************************************************************/

void Case::detruireElement (unsigned int type)
{
    switch (type)
    {
        case VIDE:    if (vide) /*------>*/ delete vide ;  vide      = nullptr ; break ;
        case BLOCK:   if (block) /*----->*/ delete block ; block     = nullptr ; break ;
        case ENTITEE: if (entitee) /*--->*/ delete entitee ; entitee = nullptr ; break ;
    }
}

////////////
// Getter //
////////////

unsigned int Case::getTypeElement()
{
    return type ;
}

Vide* Case::getVide()
{
    return vide ;
}

Block* Case::getBlock()
{
    return block ;
}

Entitee* Case::getEntitee()
{
    return entitee ;
}

Coord Case::getCoord()
{
    return coord ;
}

////////////
// Setter //
////////////

void Case::setTypeElement (unsigned int type)
{
    this->type = type ;
}

void Case::creerVide ()
{
    vide = new Vide() ;
}

void Case::setBlock (unsigned int type, unsigned int typeStone)
{
    block = new Block (type, typeStone) ;
}

void Case::setEntitee (unsigned int type)
{
    switch (type)
    {
        case VAISSEAU        : entitee = new Vaisseau()        ; break ;
        case REACTEUR        : entitee = new Reacteur()        ; break ;
        case MINEUR          : entitee = new Mineur()          ; break ;
        case BOUCLIER        : entitee = new Bouclier()        ; break ;
        case PHARE           : entitee = new Phare()           ; break ;
        case BOMBE           : entitee = new Bombe()           ; break ;
        case CREEPER_EMETTEUR: entitee = new CreeperEmetteur() ; break ;
    }

    entitee->setType(type) ;
}

void Case::setCoord (unsigned int x, unsigned int y)
{
    coord = (Coord) {(double) x, (double) y} ;
}