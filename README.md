----------Kurīpāwārudo_READ_ME----------


Le versionning est un peu chaotic, je ne connais pas encore très bien la méthode. Je corrige donc au fur et mesure.


Pour lancer le programme, il faut être sous un environnement linux et dans la console, taper : ./Jeu-v(le numéro de version) exemple : ./Jeu-v0.5.


Pour intéragir avec le jeu, les touches à utiliser sont :
- Pour les déplacements :
    - a : déplacement gauche.
    - d : déplacement droite.
    - s : déplacement bas.
    - w : déplacement haut.
- Pour choisir une action, entrez z, il vous sera alors demandé de choisir une des 2 actions possible :
    - f : destruction du block ou d'une structure.
    - c : mode développeur
    - 1 : placement d'un réacteur (uniquement sur un sol)
    - 2 : placement d'un mineur (uniquement sur des block d'or '▚')
    - 3 : placement d'un bouclier (fonctionnalité non intégrée)
    - 4 : placement d'un éclaireur (éclaircir les zones dans le brouillards de guerre)
    - 5 : placement d'une bombe



Il y a une notion d'énergie, chaque action coûte de l'énergie, il faut donc un certain temps pour que l'action se finalise.


Si l'énergie se vide et est donc dans le négatif, la vitesse de construction est divisé par le nombre de production.


S'il n'y a pas d'accès au vaisseau '◈', la procédure de construction ne commence pas ou est annulée.


Les réacteurs boost le gains d'énergie par tour.


Pour gagner, il faut placer les bombes à côté des spawner de creepers '◎' et les laisser se charger d'énergie pour qu'elles explosent.
