/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : block.cpp                             */
/* Numéro de version : 0.3                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/block.h"

/*************************************************************************
*                       Constructeur & Destructeur                       *
*************************************************************************/

Block::Block ()
{

}

Block::Block (unsigned int type, unsigned int rocheType)
{
    switch (type)
    {
    case TERRE:
        // Création bloc de terre.
        this->type = type ;
        soliditee   = 3 ;
        
        break ;
    case ROCHE:
        // Création bloc de roche.
        this->type      = type ;
        this->rocheType = rocheType ;
        switch (rocheType)
        {
            case 1: soliditee = 6  ; break ;
            case 2: soliditee = 12 ; break ;
            case 3: soliditee = 24 ; break ;
        }
        
        break ;
    case 3:
        // Création bloc de minerai.
        this->type        = type ;
        minerai_quantitee = rand() % 500 + 1 ;
        break ;
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

unsigned int Block::getRocheType ()
{
    return rocheType ;
}

double Block::getSoliditee ()
{
    return soliditee ;
}

int Block::getMinerai_quantitee ()
{
    return minerai_quantitee ;
}
