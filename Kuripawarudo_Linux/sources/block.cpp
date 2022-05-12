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
Block::Block (uint8_t type, uint8_t rocheType)
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
uint8_t Block::getType ()
{
    return type ;
}

/**
 * Renvoie le type Roche du bloc
 * 
 * @return La valeur de la variable rocheType.
 */
uint8_t Block::getRocheType ()
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

////////////
// Getter //
////////////

/**
 * @brief Méthode setType, définit l'indicateur du type de block.
 * 
 * @param type Le type de block.
 */
void Block::setType (uint8_t type)
{
	this->type = type ;
}

/**
 * @brief Méthode setRocheType, définit l'indicateur du type de roche.
 * 
 * @param rocheType Le type de roche.
 */
void Block::setRocheType (uint8_t rocheType)
{
	this->rocheType = rocheType ;
}

/**
 * @brief Méthode setSoliditee, définit la soliditée restante avant de se casser.
 * 
 * @param soliditee La nouvelle valeur de solidité.
 */
void Block::setSoliditee (double soliditee)
{
	this->soliditee = soliditee ;
}

/**
 * @brief Méthode decSoliditee, décrémente la soliditée restante avant de se casser.
 * 
 * @param soliditee La valeur de décrémentation.
 */
void Block::decSoliditee (double soliditee)
{
	this->soliditee -= soliditee ;
}

/**
 * @brief Méthode setMinerai_quantitee, définit la quantité de minerai.
 * 
 * @param minerai_quantitee La nouvelle quantité de minerai.
 */
void Block::setMinerai_quantitee (int minerai_quantitee)
{
	this->minerai_quantitee = minerai_quantitee ;
}
