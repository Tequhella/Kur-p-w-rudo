/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionAffichage.h                    */
/* Numéro de version : 0.7                                   */
/* Date              : 27/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _GESTIONAFFICHAGE_H_INCLUDED_
#define _GESTIONAFFICHAGE_H_INCLUDED_

#include "type.h"

//---------------------------Affichage Console---------------------------//

void afficherCarte (Map* m);

void afficherCarteV2 (Map* m);

void afficherInterface (Map* m, Coord* _tabEntitee, int _nb_Entitee);

void afficherErreur (int* _erreur);

//--------------------------Affichage Graphique--------------------------//

void afficherImage (int x, int y, char* nomFichier);

void afficherBlock (Block* b);

void afficherMouvementCurseur (int Key, Map* m, Coord* _jPos);

void afficherEntitee (Case* c, int pos);

void afficherVide (Vide* v);

#endif
