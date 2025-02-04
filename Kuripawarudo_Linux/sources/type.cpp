/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : type.cpp                              */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 03/02/2025                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/type.h"

std::ostream& operator<<(std::ostream& os, TypeElement type)
{
    switch (type)
    {
        case VIDE: os << "VIDE"; break;
        case BLOCK: os << "BLOCK"; break;
        case ENTITEE: os << "ENTITEE"; break;
        default: os << "UNKNOWN"; break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, TypeEntitee type)
{
    switch (type)
    {
        case NON_ENTITEE: os << "NON_ENTITEE"; break;
        case VAISSEAU: os << "VAISSEAU"; break;
        case REACTEUR: os << "REACTEUR"; break;
        case MINEUR: os << "MINEUR"; break;
        case BOUCLIER: os << "BOUCLIER"; break;
        case PHARE: os << "PHARE"; break;
        case BOMBE: os << "BOMBE"; break;
        case CREEPER_EMETTEUR: os << "CREEPER_EMETTEUR"; break;
        default: os << "UNKNOWN"; break;
    }
    return os;
}