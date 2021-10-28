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
        dirt = new Dirt ;
        if (dirt) 
        {
            cout << sizeof(type) << endl ;
            cout << sizeof(this->type) << endl ;
            this->type = type ;
            gold       = nullptr ;
            stone      = nullptr ;
            *(dirt->hardness) = 3 ;
        }
        else
        {
            perror ("Erreur d'allocation du block type terre. \n") ;
            exit (-1) ;
        }
        
        break ;
    case 2:
        // Création bloc de roche.
        stone = new Stone ;
        if (stone)
        {
            this->type     = type ;
            dirt           = nullptr ;
            gold           = nullptr ;
            *(stone->type) = typeStone ;
            switch (typeStone)
            {
                case 1: *(stone->hardness) = 6  ; break ;
                case 2: *(stone->hardness) = 12 ; break ;
                case 3: *(stone->hardness) = 24 ; break ;
            }
        }
        else
        {
            perror ("Erreur d'allocation du block type roche. \n") ;
            exit (-1) ;
        }
        
        break ;
    case 3:
        // Création bloc de minerai.
        gold = new Gold ;
        if (gold)
        {
            this->type        = type ;
            dirt              = nullptr ;
            stone             = nullptr ;
            *(gold->quantity) = 200 ;
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
        // Destruction bloc de terre.
        delete dirt ;
        dirt = nullptr ;
    }
    else if (stone)
    {
        // Destruction bloc de roche.
        delete stone ;
        stone = nullptr ;
    }
    else if (gold)
    {
        // Destruction bloc de minerai.
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

unsigned int Block::getStoneType ()
{
    return *(stone->type) ;
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