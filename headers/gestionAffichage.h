/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionAffichage.h                    */
/* Numéro de version : 0.5                                   */
/* Date              : 21/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _GESTIONAFFICHAGE_H_INCLUDED_
#define _GESTIONAFFICHAGE_H_INCLUDED_

#include "../headers/type.h"

//---------------------------Affichage Console---------------------------//

void afficherCarte (Map* m);

void afficherInterface (Map* m, Coord* _tabEntitee, int _nb_Entitee);

void afficherErreur (int* _erreur);

//--------------------------Affichage Graphique--------------------------//

#endif
