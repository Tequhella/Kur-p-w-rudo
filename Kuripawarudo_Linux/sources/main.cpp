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
#include "../headers/type.h"

/**
 * Créez une carte avec un nombre aléatoire de grottes et un nombre aléatoire d'ennemis
 * 
 * @return Rien.
 */
int main ()
{
	/* Création d'un nouvel objet de type Carte. */
	Carte mapHasard = Carte(LARGEUR, HAUTEUR, "test");

	/* Remplit la carte avec des éléments aléatoires. */
	mapHasard.remplirHasard();

	/* Il crée 4 grottes. */
	for (int i = 0; i < 4; i++)
		mapHasard.creerCaverne (rand() % LARGEUR * HAUTEUR + 280, 0);

	/* Créer 3 ennemies */
	mapHasard.creerEnnemie(3);

	/* Appel de la fonction `afficherCarte()` depuis la classe `Carte`. */
	mapHasard.afficherCarte();

	/* Détruit l'objet `mapHasard`. */
	mapHasard.~Carte ();

	return 0;
}