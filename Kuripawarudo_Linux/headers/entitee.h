/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : entitee.h                             */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_ENTITEE
#define DEF_ENTITEE

#include "type.h"

/* La classe Entitee est une classe qui représente une entité dans le jeu */
class Entitee
{
    public:

    /*************************************************************************
    *                       Constructeur & Destructeur                       *
    *************************************************************************/
        
        /**
         * @brief Constructeur de la classe Entitee.
         * 
         * @param type Le type de l'entitée. Ceci est utilisé pour identifier l'entitée.
         * @param coord Les coordonnées de l'entitée.
         */
        Entitee(TypeEntitee type, Coord* coord) ;


        /**
         * @brief Constructeur par défaut de la classe Entitee.
         */
        Entitee() ;

        /**
         * @brief Destructeur de la classe Entitee.
         */
        ~Entitee() ;

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        ////////////
        // Getter //
        ////////////

        /**
         * @brief Méthode getType, récupère le type de l'entitée.
         * 
         * @return TypeEntitee Le type de l'entitée.
         */
        TypeEntitee getType() ;

        /**
         * @brief Méthode getId, récupère l'id de l'entitée.
         * 
         * @return double L'id de l'entitée.
         */
        double getConstr() ;


        ////////////
        // Setter //
        ////////////

		/**
		 * @brief Méthode setType, modifie le type de l'entitée.
		 */
        void setType(TypeEntitee type) ;

        /**
         * @brief Méthode setId, modifie l'id de l'entitée.
		 */
        void setId(unsigned int id);
		
        /**
         * @brief Méthode setConstr, modifie le nombre de points de construction de l'entitée.
         * 
         * @param constr Le nombre de points de construction de l'entité.
		 */
        void setConstr(double constr);

		/**
		 * @brief Méthode decConstr, décrémente les points de construction de l'entitée.
		 * 
		 * @param dec Nombre de points de construction à décrémenter.
		 */
		void decConstr(double dec);
		

    private:

        TypeEntitee      type ;
        Coord            coord ;

    protected:

        unsigned int id;
        double       constr; // Point de construction.
        uint8_t      vie;

};

#endif