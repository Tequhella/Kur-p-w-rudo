/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : block.cpp                             */
/* Numéro de version : 0.3.1                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/block.h"

/*************************************************************************
*                       Constructeur & Destructeur                       *
*************************************************************************/

Block::Block (){}

/**
 * Créer un nouveau bloc du type spécifié
 * 
 * @param type Le type de bloc.
 * @param rocheType 1, 2 ou 3
 */
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

Block::~Block (){}

/*************************************************************************
*                                 Méthode                                *
*************************************************************************/

////////////
// Getter //
////////////

/**
 * Renvoie le type du bloc
 * 
 * @return Le type de bloc.
 */
unsigned int Block::getType ()
{
    return type ;
}

/**
 * Renvoie le type Roche du bloc
 * 
 * @return La valeur de la variable rocheType.
 */
unsigned int Block::getRocheType ()
{
    return rocheType ;
}

/**
 * La fonction retourne la valeur de la variable soliditee
 * 
 * @return La valeur de solidité.
 */
double Block::getSoliditee ()
{
    return soliditee ;
}

/**
 * La fonction retourne la valeur de la variable minerai_quantitee
 * 
 * @return La quantité minerale du bloc.
 */
int Block::getMinerai_quantitee ()
{
    return minerai_quantitee ;
}
