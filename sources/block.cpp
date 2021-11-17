/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : block.cpp                             */
/* Numéro de version : 0.2                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 23/10/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/block.h"

/*************************************************************************
*                       Constructeur & Destructeur                       *
*************************************************************************/

Block::Block ()
{

}

Block::Block (unsigned int type, unsigned int typeStone)
{
    switch (type)
    {
    case 1:
        // Création bloc de terre.
        this->type = type ;
        hardness   = 3 ;
        
        break ;
    case 2:
        // Création bloc de roche.
        this->type      = type ;
        this->stoneType = typeStone ;
        switch (typeStone)
        {
            case 1: hardness = 6  ; break ;
            case 2: hardness = 12 ; break ;
            case 3: hardness = 24 ; break ;
        }
        
        break ;
    case 3:
        // Création bloc de minerai.
        this->type     = type ;
        gold_quantity = 200 ;
        
    }

}

Block::~Block ()
{
    
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

unsigned int Block::getStoneType ()
{
    return stoneType ;
}

double Block::getHardness ()
{
    return hardness ;
}

int Block::getGold_quantity ()
{
    return gold_quantity ;
}
