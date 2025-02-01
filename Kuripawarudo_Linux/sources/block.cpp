/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : block.cpp                             */
/* Numéro de version : 0.3.7                                 */
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
Block::Block (uint8_t type, RocheType rocheType)
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
                case NON_ROCHE:
                    BOOST_LOG_TRIVIAL(error) << "Erreur : le type de roche n'est pas défini.";
                    break ;
                case ROCHE1: soliditee = 6  ; break ;
                case ROCHE2: soliditee = 12 ; break ;
                case ROCHE3: soliditee = 24 ; break ;
            }
            
            break ;
        case MINERAI:
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

uint8_t Block::getType ()
{
    return type ;
}

RocheType Block::getRocheType ()
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

////////////
// Getter //
////////////

void Block::setType (uint8_t type)
{
	this->type = type ;
}

void Block::setRocheType (RocheType rocheType)
{
	this->rocheType = rocheType ;
}

void Block::setSoliditee (double soliditee)
{
	this->soliditee = soliditee ;
}

void Block::decSoliditee (double soliditee)
{
	this->soliditee -= soliditee ;
}

void Block::setMinerai_quantitee (int quantitee)
{
	this->minerai_quantitee = quantitee ;
}
