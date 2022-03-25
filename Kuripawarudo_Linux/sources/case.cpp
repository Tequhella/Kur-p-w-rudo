/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : case.cpp                              */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/case.h"
#include "../headers/entitee.h"
#include "../headers/vide.h"
#include "../headers/block.h"
#include "../headers/curseur.h"

/**
 * Le constructeur initialise l'objet Case
 */
Case::Case ()
{
    vide    = nullptr ;
    block   = nullptr ;
    entitee = nullptr ;
    curseur = nullptr ;

    type = 0 ;
}

Case::~Case(){}

/*************************************************************************
*                                 Méthode                                *
*************************************************************************/


/**
 * * Si l'élément est un bloc, le supprime.
 * * Si l'élément est une entitée, le supprime ainsi que son élément vide associé.
 * * Si l'élément est un curseur, le supprime.
 * * Si l'élément est un élément vide, le supprime
 * 
 * @param type le type d'élément à supprimer.
 */
void Case::detruireElement (unsigned int type)
{
    switch (type)
    {
        case VIDE:  if (vide) /*---->*/ delete vide ;  vide  = nullptr ; break ;
        case BLOCK: if (block) /*--->*/ delete block ; block = nullptr ; break ;
        case ENTITEE:
            if (entitee)
            {
                delete entitee ;
                entitee = nullptr ;
            }
            if (vide)
            {
                delete vide ;
                vide = nullptr ;
            }
            break ;
        case CURSEUR: if (curseur) /*--->*/ delete curseur; curseur = nullptr ; break ;
    }
}

////////////
// Getter //
////////////

/**
 * Renvoyer le type de case
 * 
 * @return Le type de l'élément.
 */
unsigned int Case::getTypeElement()
{
    return type ;
}

/**
 * Renvoie la valeur du membre privée vide
 * 
 * @return La valeur de la variable vide.
 */
Vide* Case::getVide()
{
    return vide ;
}

/**
 * Retourne le bloc de la case
 * 
 * @return Le bloc de la case actuelle.
 */
Block* Case::getBlock()
{
    return block ;
}

Entitee* Case::getEntitee()
{
    return entitee ;
}

/**
 * Renvoie la coordonnée du cas
 * 
 * @return coord
 */
Coord Case::getCoord()
{
    return coord ;
}

////////////
// Setter //
////////////

/**
 * Définit le type de la case
 * 
 * @param type Le type de case.
 */
void Case::setTypeElement (unsigned int type)
{
    this->type = type ;
}

/**
 * Crée une nouvelle case vide
 */
void Case::creerVide()
{
    vide = new Vide() ;
}

/**
 * Crée un nouveau curseur
 */
void Case::creerCurseur()
{
    curseur = new Curseur();
}

/**
 * Crée un nouvel objet Block et l'affecte à la variable de bloc
 * 
 * @param type le type de bloc (1 = terre, 2 = roche, 3 = minerai)
 * @param typeStone le type de pierre qui est utilisé pour construire le bloc.
 */
void Case::setBlock (unsigned int type, unsigned int typeStone)
{
    block = new Block (type, typeStone) ;
}

/**
 * Il définit le type d'entité de la case.
 * 
 * @param type Le type de l'entité.
 */
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

/**
 * Définit les coordonnées de la case
 * 
 * @param x La coordonnée x de la case.
 * @param y La coordonnée y de la case.
 */
void Case::setCoord (unsigned int x, unsigned int y)
{
    coord = (Coord) {(double) x, (double) y} ;
}