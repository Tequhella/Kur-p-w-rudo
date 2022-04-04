/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : main.c                                */
/* Numéro de version : 0.3.1                                 */
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

/*
 * Fonction permettant d'afficher la taille de toutes les classes.
 */
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

/**
 * Créez une carte avec un nombre aléatoire de grottes et un nombre aléatoire d'ennemis
 *
 * @return Rien.
 */
int main()
{
	/* Création d'un nouvel objet de type Carte. */
	Carte mapHasard = Carte(LARGEUR, HAUTEUR, "test");

	/* Remplit la carte avec des éléments aléatoires. */
	mapHasard.remplirHasard();

	/* Il crée 4 grottes. */
	for (int i = 0; i < 4; i++)
		mapHasard.creerCaverne(rand() % LARGEUR * HAUTEUR + 280, 0);

	/* Créer 3 ennemies */
	mapHasard.creerEnnemie(3);

	Case* element = mapHasard.getElement(LARGEUR * 3 + LARGEUR / 2);

	/* Enregistre les coordonnées du Curseur du tableau de case */
	Coord* coord = (element->getCoord());

	char c = 0;

	afficherTaille();

	/* Boucle en condition la touche C est pressée, réaffiche la carte et demande l'action déplacement au joueur*/
	while (c != 'c')
	{
		/* Affichage de la carte. */
		mapHasard.afficherCarte();

		Curseur* curseur = mapHasard.getElement(LARGEUR * coord->y + coord->x)->getCurseur();
		mapHasard.getElement(LARGEUR * coord->y + coord->x)->setCurseur(nullptr);

		/* Vérifie si l'élément est un bloc ou une entité. S'il s'agit d'un bloc, il définira l'élément de
		type sur "BLOCK". S'il s'agit d'une entitée, il définira l'élément type sur "ENTITEE". Sinon, il
		définira l'élément type sur "VIDE". */
		if (mapHasard.getElement(LARGEUR * coord->y + coord->x)->getBlock())
			mapHasard.getElement(LARGEUR * coord->y + coord->x)->setTypeElement(BLOCK);
		else if (mapHasard.getElement(LARGEUR * coord->y + coord->x)->getEntitee())
			mapHasard.getElement(LARGEUR * coord->y + coord->x)->setTypeElement(ENTITEE);
		else
			mapHasard.getElement(LARGEUR * coord->y + coord->x)->setTypeElement(VIDE);

		/* Déplacement du curseur */
		curseur->deplacement(&c);
		/* Transposition de l'objet curseur dans la prochaine case */
		mapHasard.getElement(LARGEUR * coord->y + coord->x)->setCurseur(curseur);
		mapHasard.getElement(LARGEUR * coord->y + coord->x)->setTypeElement(CURSEUR);
	}
	/* Détruit l'objet `mapHasard`. */
	mapHasard.~Carte();

	return 0;
}