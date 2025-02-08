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
#include "../headers/log.h"
#include "../headers/jeu.h"

#include <thread>


int main()
{
    init_logging();
    log_messages();

    Carte mapHasard = Carte(LARGEUR, HAUTEUR, "test");
    mapHasard.remplirHasard();

    for (int i = 0; i < 4; i++)
    {
        mapHasard.creerCaverne(rand() % LARGEUR * HAUTEUR + 280, 0);
        BOOST_LOG_TRIVIAL(debug) << "Grotte " << i << " créée.";
    }

    mapHasard.creerEnnemie(3);

    Jeu jeu(&mapHasard);
    jeu.bouclePrincipale();

    return 0;
}