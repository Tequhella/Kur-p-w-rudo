/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : vaisseau.cpp                          */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../../headers/entitee/vaisseau.h"
#include "vaisseau.h"

Vaisseau::Vaisseau() : energieQuantitee(0),
                       energieReserve(20),
                       energieEfficacitee(1),
                       mineraiQuantitee(0),
                       mineraiReserve(20),
                       mineraiEfficacitee(0),
                       portee(6)
{
    this->id = 0;
    this->vie = 255 ;
}

Vaisseau::~Vaisseau() {}

void Vaisseau::incNRJ(double energie)
{
    if (energieQuantitee + energie > energieReserve)
    {
        energieQuantitee = energieReserve;
    }
    else
    {
        energieQuantitee += energie;
    }
}

void Vaisseau::incMinerai(double minerai)
{
    if (mineraiQuantitee + minerai > mineraiReserve)
    {
        mineraiQuantitee = mineraiReserve;
    }
    else if (mineraiQuantitee + minerai < 0)
    {
        mineraiQuantitee = 0;
    }
    else
    {
        mineraiQuantitee += minerai;
    }
}

void Vaisseau::setEnergieQuantitee(double energieQuantitee)
{
    if (energieQuantitee < 0)
    {
        this->energieQuantitee = 0;
    }
    if (energieQuantitee > energieReserve)
    {
        this->energieQuantitee = this->energieReserve;
    }
    else
    {
        this->energieQuantitee = energieQuantitee;
    }
}

void Vaisseau::setEnergieReserve(double energieReserve)
{
    if (energieReserve < 5)
    {
        this->energieReserve = 5;
    }
    else
    {
        this->energieReserve = energieReserve;
    }
}

void Vaisseau::setEnergieEfficacitee(double energieEfficacitee)
{
    this->energieEfficacitee = energieEfficacitee;
}

void Vaisseau::setMineraiQuantitee(double mineraiQuantitee)
{
    if (mineraiQuantitee < 0)
    {
        this->mineraiQuantitee = 0;
    }
    if (mineraiQuantitee > mineraiReserve)
    {
        this->mineraiQuantitee = this->mineraiReserve;
    }
    else
    {
        this->mineraiQuantitee = mineraiQuantitee;
    }
}

void Vaisseau::setMineraiReserve(double mineraiReserve)
{
    if (mineraiReserve < 5)
    {
        this->mineraiReserve = 5;
    }
    else
    {
        this->mineraiReserve = mineraiReserve;
    }
}

void Vaisseau::setMineraiEfficacitee(double mineraiEfficacitee)
{
    this->mineraiEfficacitee = mineraiEfficacitee;
}

void Vaisseau::setPortee(uint8_t portee)
{
    if (portee < 2)
    {
        this->portee = 2;
    }
    else
    {
        this->portee = portee;
    }
}
