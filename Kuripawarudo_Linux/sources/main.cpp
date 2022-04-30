/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : main.c                                */
/* Numéro de version : 0.3.6                                 */
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


int main()
{
	/* Création d'un nouvel objet de type Carte. */
	Carte mapHasard = Carte(LARGEUR, HAUTEUR, "test");

	/* Remplit la carte avec des éléments aléatoires. */
	mapHasard.remplirHasard();

	/* Il crée 4 grottes. */
	for (int i = 0; i < 4; i++)
		mapHasard.creerCaverne(rand() % LARGEUR * HAUTEUR + 280, 0);

	/* Créer 3 ennemies. */
	mapHasard.creerEnnemie(3);

	/* Boucle principale du jeu. */
	bouclePrincipale(&mapHasard);

	
	/* Détruit l'objet `mapHasard`. */
	mapHasard.~Carte();

	return 0;
}



void afficherTaille()
{
	std::cout << "Carte : " << sizeof(Carte) << std::endl;
	std::cout << "Case : " << sizeof(Case) << std::endl;
	std::cout << "Curseur : " << sizeof(Curseur) << std::endl;
	std::cout << "Vide : " << sizeof(Vide) << std::endl;
	std::cout << "Block : " << sizeof(Block) << std::endl;
	std::cout << "Entitee : " << sizeof(Entitee) << std::endl;
	std::cout << "Reacteur : " << sizeof(Reacteur) << std::endl;
	std::cout << "Mineur : " << sizeof(Mineur) << std::endl;
	std::cout << "Bouclier : " << sizeof(Bouclier) << std::endl;
	std::cout << "Phare : " << sizeof(Phare) << std::endl;
	std::cout << "Bombe : " << sizeof(Bombe) << std::endl;
	std::cout << "CreeperEmetteur : " << sizeof(CreeperEmetteur) << std::endl;
}



void bouclePrincipale(Carte* carte)
{
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
	}
}