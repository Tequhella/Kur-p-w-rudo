/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : main.c                                */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/carte.h"
#include "../headers/case.h"
#include "../headers/curseur.h"
#include "../headers/vide.h"
#include "../headers/block.h"
#include "../headers/entitee.h"
#include "../headers/type.h"

#include <thread>

/**
 * @brief Fonction afficherTaille, permet d'afficher la taille de toutes les classes.
 */
void afficherTaille();

/**
 * @brief Fonction bouclePrincipale, permet de gérer la boucle principale du jeu.
 * 
 * @param carte, la carte du jeu.
 */
void bouclePrincipale(Carte* carte);

/**
 * @brief Fonction init_logging, permet d'initialiser le logging.
 */
void init_logging();

/**
 * @brief Fonction log_messages, permet de logger des messages.
 */
void log_messages();


int main()
{
    init_logging();
    log_messages();

	/* Création d'un nouvel objet de type Carte. */
	Carte mapHasard = Carte(LARGEUR, HAUTEUR, "test");
    
	/* Remplit la carte avec des éléments aléatoires. */
	mapHasard.remplirHasard();
    

	/* Il crée 4 grottes. */
	for (int i = 0; i < 4; i++)
    {
        mapHasard.creerCaverne(rand() % LARGEUR * HAUTEUR + 280, 0);
        BOOST_LOG_TRIVIAL(debug) << "Grotte " << i << " créée.";
    }

	/* Affiche la taille de toutes les classes. */
    //afficherTaille();
    /* Créer 3 ennemies. */
	mapHasard.creerEnnemie(3);

	/* Boucle principale du jeu. */
	bouclePrincipale(&mapHasard);


	return 0;
}

void init_logging()
{
    // Log vers un fichier
    boost::log::add_file_log(
        boost::log::keywords::file_name = "sample_%N.log",
        boost::log::keywords::rotation_size = 10 * 1024 * 1024,
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
        boost::log::keywords::format = "[%TimeStamp%]: %Message%"
    );

    // Log vers la console
    boost::log::add_console_log(
        std::cout,
        boost::log::keywords::format = "[%TimeStamp%]: %Message%"
    );

    // Ajouter des attributs communs comme le timestamp
    boost::log::add_common_attributes();
}

void log_messages()
{
    BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
    BOOST_LOG_TRIVIAL(info) << "This is an informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
    BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "This is a fatal severity message";
}

void afficherTaille()
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

void bouclePrincipale(Carte* carte)
{
    BOOST_LOG_TRIVIAL(info) << "Boucle principale du jeu.";

	Case* element = carte->getElement(LARGEUR / 2, 3);
	/* Enregistre les coordonnées du Curseur du tableau de case */
	Curseur* curseur = element->getCurseur();
	Coord* coord = curseur->getCoord();

	char c = 0;
	uint8_t	verif = 1;
	
	/* Boucle en condition la touche C est pressée, réaffiche la carte et demande l'action déplacement au joueur*/
	while (c != 'c')
	{
		/* Affichage de la carte. */
		carte->afficherCarte();

		if (verif == 0)
		{
			curseur = carte->getElement(coord->x, coord->y)->getCurseur();
		}

		cout << "Coordonnée curseur : " << coord->x << " " << coord->y << endl;
		carte->afficherAdresse(coord->x, coord->y);

		/* Vérifie si l'élément est un bloc ou une entité. S'il s'agit d'un bloc, il définira l'élément de
		type sur "BLOCK". S'il s'agit d'une entitée, il définira l'élément type sur "ENTITEE". Sinon, il
		définira l'élément type sur "VIDE". */
		if (carte->getElement(coord->x, coord->y)->getBlock())
		{
			carte->getElement(coord->x, coord->y)->setTypeElement(BLOCK);
		}
		else if (carte->getElement(coord->x, coord->y)->getEntitee())
		{
			carte->getElement(coord->x, coord->y)->setTypeElement(ENTITEE);
		}
		else
		{
			carte->getElement(coord->x, coord->y)->setTypeElement(VIDE);
		}

		/* Déplacement du curseur */
		std::cin >> c;
		verif = curseur->deplacement(&c);
		if (verif == 1)
		{
			/* Transposition de l'objet curseur dans la prochaine case */
			element->setCurseur(nullptr);
			carte->getElement(coord->x, coord->y)->setCurseur(curseur);
			carte->getElement(coord->x, coord->y)->setTypeElement(CURSEUR);
			element = carte->getElement(coord->x, coord->y);
		}
		else
		{
			if (curseur->action(&c, carte) == 0) /*--->*/ cout << "Touche invalide !" << endl;
		}

		carte->gestionConstruction();
		carte->gestionCasseBlock();
	}
}