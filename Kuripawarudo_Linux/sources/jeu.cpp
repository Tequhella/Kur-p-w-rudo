/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : jeu.cpp                               */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 08/02/2025                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/jeu.h"

Jeu::Jeu(Carte* carte)
    : carte(carte),
      curseur(carte->getElement(LARGEUR / 2, 3)->getCurseur()),
      coord(curseur->getCoord()),
      vaisseau(*(Vaisseau*)carte->getElement(LARGEUR / 2, 2)->getEntitee())
{
}

Jeu::~Jeu()
{
}

void Jeu::afficherCoordonneesCurseur(const Coord& coord) const
{
    std::cout << "Coordonnée curseur : " << coord.x << " " << coord.y << std::endl;
}

void Jeu::verifierTypeElement(const Coord& coord)
{
    if (carte->getElement(coord.x, coord.y)->getBlock())
    {
        carte->getElement(coord.x, coord.y)->setTypeElement(BLOCK);
    }
    else if (carte->getElement(coord.x, coord.y)->getEntitee())
    {
        carte->getElement(coord.x, coord.y)->setTypeElement(ENTITEE);
    }
    else
    {
        carte->getElement(coord.x, coord.y)->setTypeElement(VIDE);
    }
}

void Jeu::deplacerCurseur(char c)
{
    uint8_t verif = curseur->deplacement(&c);
    if (verif == 1)
    {
        carte->getElement(coord.x, coord.y)->setTypeElement(CURSEUR);
    }
    else
    {
        if (curseur->action(&c, carte) == 0)
        {
            std::cout << "Touche invalide !" << std::endl;
        }
    }
}

void Jeu::bouclePrincipale()
{
    BOOST_LOG_TRIVIAL(info) << "Boucle principale du jeu.";

    char c = 0;

    while (c != 'c')
    {
        double energieEff = vaisseau.getEnergieEfficacitee();
        double mineraiEff = vaisseau.getMineraiEfficacitee();

        carte->afficherCarte();
        afficherCoordonneesCurseur(coord);
        verifierTypeElement(coord);

        std::cin >> c;
        deplacerCurseur(c);

        vaisseau.incNRJ(energieEff);
        vaisseau.incMinerai(mineraiEff);

        carte->gestionConstruction();
        carte->gestionCasseBlock();
    }
}

void Jeu::afficherTaille()
{
	std::cout << "Carte : " << sizeof(Carte) << " octets" << std::endl;
	std::cout << "Case : " << sizeof(Case) << " octets" << std::endl;
	std::cout << "Curseur : " << sizeof(Curseur) << " octets" << std::endl;
	std::cout << "Vide : " << sizeof(Vide) << " octets" << std::endl;
	std::cout << "Block : " << sizeof(Block) << " octets" << std::endl;
	std::cout << "Entitee : " << sizeof(Entitee) << " octets" << std::endl;
	std::cout << "Reacteur : " << sizeof(Reacteur) << " octets" << std::endl;
	std::cout << "Mineur : " << sizeof(Mineur) << " octets" << std::endl;
	std::cout << "Bouclier : " << sizeof(Bouclier) << " octets" << std::endl;
	std::cout << "Phare : " << sizeof(Phare) << " octets" << std::endl;
	std::cout << "Bombe : " << sizeof(Bombe) << " octets" << std::endl;
	std::cout << "CreeperEmetteur : " << sizeof(CreeperEmetteur) << " octets" << std::endl;
}