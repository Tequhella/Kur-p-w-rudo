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

Jeu::Jeu(Carte *carte)
    : carte(carte),
      curseur(carte->getElement(LARGEUR / 2, 3)->getCurseur()),
      coord(curseur->getCoord()),
      vaisseau(*(Vaisseau *)carte->getElement(LARGEUR / 2, 2)->getEntitee()),
      coordEntiteeConstr(nullptr),
      coordBlockCasse(nullptr),
      nbEntiteeConstr(0),
      nbBlockCasse(0)
{
    BOOST_LOG_TRIVIAL(info) << "Création du jeu.";

    // Initialisation des callbacks
    carte->setSetCoordEntiteeCallback([this](const Coord &coord)
                                      { this->setCoordEntiteeConstr(coord); });
    carte->setSetCoordBlockCasseCallback([this](const Coord &coord)
                                         { this->setCoordBlockCasse(coord); });
}

Jeu::~Jeu()
{
    if (coordEntiteeConstr)
    {
        delete coordEntiteeConstr;
        coordEntiteeConstr = nullptr;
    }
    if (coordBlockCasse)
    {
        delete coordBlockCasse;
        coordBlockCasse = nullptr;
    }
}

void Jeu::afficherCoordonneesCurseur(const Coord &coord) const
{
    std::cout << "Coordonnée curseur : " << coord.x << " " << coord.y << std::endl;
}

void Jeu::verifierTypeElement(const Coord &coord)
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
        carte->afficherCarte();
        afficherCoordonneesCurseur(coord);
        verifierTypeElement(coord);

        std::cin >> c;
        deplacerCurseur(c);

        gestionRessources();
        gestionConstruction();
        gestionCasseBlock();
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

void Jeu::gestionRessources()
{
    double energieEff = vaisseau.getEnergieEfficacitee();
    double mineraiEff = vaisseau.getMineraiEfficacitee();

    vaisseau.incNRJ(energieEff);
    vaisseau.incMinerai(mineraiEff);
}

/**
 * Méthode gestionConstruction, décrémente les points de construction des entitée.
 */
void Jeu::gestionConstruction()
{
    if (coordEntiteeConstr)
    {
        for (uint8_t i = 0; i < nbEntiteeConstr; i++)
        {
            BOOST_LOG_TRIVIAL(debug) << "Coordonnée dans coordEntiteeConstr[i] : " << coordEntiteeConstr->at(i).x << " " << coordEntiteeConstr->at(i).y;
            Entitee *entitee = carte->getElement(coordEntiteeConstr->at(i).x, coordEntiteeConstr->at(i).y)->getEntitee();
            switch (entitee->getType())
            {
            case VAISSEAU:
                break;
            case CREEPER_EMETTEUR:
                break;
            default:
                if (entitee->getConstr() > 0)
                {
                    entitee->decConstr(1);
                }
                else
                {
                    /*
                     * Enlève l'entitée du tableau d'entitée et realloue la mémoire du tableau en fonction de la taille.
                     */
                    for (uint8_t j = i; j < nbEntiteeConstr - 1; j++)
                    {
                        coordEntiteeConstr->at(j) = coordEntiteeConstr->at(j + 1);
                    }
                    coordEntiteeConstr->resize(nbEntiteeConstr - 1);
                    nbEntiteeConstr--;
                    i--;
                    if (nbEntiteeConstr == 0)
                    {
                        delete coordEntiteeConstr;
                        coordEntiteeConstr = nullptr;
                    }

                    if (entitee->getType() == REACTEUR)
                    {
                        vaisseau.setEnergieEfficacitee(vaisseau.getEnergieEfficacitee() + 0.4);
                    }
                    else if (entitee->getType() == MINEUR)
                    {
                        vaisseau.setMineraiEfficacitee(vaisseau.getMineraiEfficacitee() + 0.5);
                    }
                }
                break;
            }
        }
    }
}

/**
 * @brief Méthode gestionCasseBlock, décrémente les points de durabilité des blocks.
 */
void Jeu::gestionCasseBlock()
{
    if (coordBlockCasse)
    {
        for (uint8_t i = 0; i < nbBlockCasse; i++)
        {
            BOOST_LOG_TRIVIAL(debug) << "Coordonnée dans coordBlockCasse[i] : " << coordBlockCasse->at(i).x << " " << coordBlockCasse->at(i).y;
            Block *block = carte->getElement(coordBlockCasse->at(i).x, coordBlockCasse->at(i).y)->getBlock();
            if (block->getSoliditee() > 0) /*--->*/
                block->decSoliditee(1);
            else
            {
                carte->getElement(coordBlockCasse->at(i).x, coordBlockCasse->at(i).y)->detruireElement(BLOCK);
                carte->getElement(coordBlockCasse->at(i).x, coordBlockCasse->at(i).y)->creerVide();
                carte->getElement(coordBlockCasse->at(i).x, coordBlockCasse->at(i).y)->setTypeElement(VIDE);
                /*
                 * Enlève le block du tableau de coordonnées des blocks à casser et realloue la mémoire
                 * du tableau en fonction de la taille.
                 *	*/
                for (uint8_t j = i; j < nbBlockCasse - 1; j++)
                {
                    coordBlockCasse->at(j) = coordBlockCasse->at(j + 1);
                }
                coordBlockCasse->resize(nbBlockCasse - 1);
                nbBlockCasse--;
                i--;
                if (nbBlockCasse == 0)
                {
                    delete coordBlockCasse;
                    coordBlockCasse = nullptr;
                }
            }
        }
    }
}

void Jeu::setCoordEntiteeConstr(Coord coord)
{
    if (coordEntiteeConstr)
    {
        coordEntiteeConstr->resize(nbEntiteeConstr + 1);
        coordEntiteeConstr->at(nbEntiteeConstr) = coord;
        nbEntiteeConstr++;
    }
    else
    {
        coordEntiteeConstr = new vector<Coord>(1);
        if (coordEntiteeConstr)
        {
            coordEntiteeConstr->at(0) = coord;
            nbEntiteeConstr++;
        }
        else
        {
            BOOST_LOG_TRIVIAL(error) << "Erreur : impossible de créer le tableau de coordonnée d'entitée en construction.";
        }
    }
}

void Jeu::setCoordBlockCasse(Coord coord)
{
    if (coordBlockCasse)
    {
        // check if coord is already in the vector
        for (uint8_t i = 0; i < nbBlockCasse; i++)
        {
            if (coordBlockCasse->at(i).x == coord.x && coordBlockCasse->at(i).y == coord.y)
            {
                BOOST_LOG_TRIVIAL(info) << "Coordonnée déjà présente dans le tableau de coordonnée de block à casser.";
                return;
            }
        }

        coordBlockCasse->resize(nbBlockCasse + 1);
        coordBlockCasse->at(nbBlockCasse) = coord;
        nbBlockCasse++;
    }
    else
    {
        coordBlockCasse = new vector<Coord>(1);
        if (coordBlockCasse)
        {
            coordBlockCasse->at(0) = coord;
            nbBlockCasse++;
        }
        else
        {
            BOOST_LOG_TRIVIAL(error) << "Erreur : impossible de créer le tableau de coordonnée de block à casser.";
        }
    }
}

std::function<void(const Coord &)> Jeu::getSetCoordEntiteeCallback()
{
    return [this](const Coord &coord)
    { this->setCoordEntiteeConstr(coord); };
}

std::function<void(const Coord &)> Jeu::getSetCoordBlockCasseCallback()
{
    return [this](const Coord &coord)
    { this->setCoordBlockCasse(coord); };
}