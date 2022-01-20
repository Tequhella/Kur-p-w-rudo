# CMakeList.txt : projet CMake pour Kuripawarudo_Linux, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (Kuripawarudo_Linux "sources/main.cpp"
									"sources/carte.cpp"
									"sources/case.cpp"
									"sources/block.cpp"
									"sources/vide.cpp"
									"sources/entitee.cpp"
									"sources/entitee/vaisseau.cpp"
									"sources/entitee/reacteur.cpp"
									"sources/entitee/mineur.cpp"
									"sources/entitee/bouclier.cpp"
									"sources/entitee/phare.cpp"
									"sources/entitee/bombe.cpp"
									"sources/entitee/creeperEmetteur.cpp"

									"headers/type.h"
									"headers/carte.h"
									"headers/case.h"
									"headers/block.h"
									"headers/vide.h"
									"headers/entitee.h"
									"headers/entitee/vaisseau.h"
									"headers/entitee/reacteur.h"
									"headers/entitee/mineur.h"
									"headers/entitee/bouclier.h"
									"headers/entitee/phare.h"
									"headers/entitee/bombe.h"
									"headers/entitee/creeperEmetteur.h"
)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
