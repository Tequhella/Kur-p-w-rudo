/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : block.c                               */
/* Numéro de version : 0.1                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 23/10/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/block.h"
#include "../headers/type.h"

/*************************************************************************
*                       Constructeur & Destructeur                       *
*************************************************************************/

Block::Block (unsigned int type, unsigned int typeStone, double posX, double posY)
{
    switch (type)
    {
    case 1:
        dirt = new Dirt ;
        if (dirt) 
        {
            type      = type ;
            dirt->pos = (Coord) {posX, posY} ;
        }
        else
        {
            perror ("Erreur d'allocation du block type terre. \n") ;
            exit (-1) ;
        }
        
        break ;
    case 2:
        stone = new Stone ;
        if (stone)
        {
            type        = type ;
            stone->type = typeStone ;
            stone->pos  = (Coord) {posX, posY} ;
        }
        else
        {
            perror ("Erreur d'allocation du block type roche. \n") ;
            exit (-1) ;
        }
        
        break ;
    case 3:
        gold = new Gold ;
        if (gold)
        {
            type           = type ;
            gold->quantity = 200 ;
            gold->pos      = (Coord) {posX, posY} ;
        }
        else
        {
            perror ("Erreur d'allocation du block type ressource d'or. \n") ;
            exit (-1) ;
        }
        
    }

}

Block::~Block ()
{
    if (dirt)
    {
        delete dirt ;
        dirt = nullptr ;
    }
    else if (stone)
    {
        delete stone ;
        stone = nullptr ;
    }
    else if (gold)
    {
        delete gold ;
        gold = nullptr ;
    }
    else
    {
        perror ("Erreur d'allocation du block. \n") ;
        exit (-1) ;
    }
    
}

/*************************************************************************
*                                 Méthode                                *
*************************************************************************/

////////////
// Getter //
////////////
unsigned int Block::getType ()
{
    return type ;
}

Block::Dirt* Block::getDirt ()
{
    return dirt ;
}

Block::Stone* Block::getStone ()
{
    return stone ;
}

Block::Gold* Block::getGold ()
{
    return gold ;
}