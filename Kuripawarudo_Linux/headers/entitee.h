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
        
        /*
        * Constructeur de la classe Entitee.
        */
        Entitee(uint8_t type, Coord* coord) ;


        /*
        * Constructeur par défaut de la classe Entitée.
        */
        Entitee() ;

        /*
        * Destructeur de la classe Entitee.
        */
        ~Entitee() ;

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        ////////////
        // Getter //
        ////////////

        /* Renvoie le type de l'entité. */
        uint8_t getType() ;

        /* Renvoie le nombre de points de construction de l'entité. */
        double getConstr() ;


        ////////////
        // Setter //
        ////////////

		/**
		 * @brief Méthode setType, modifie le type de l'entitée.
		 */
        void setType(uint8_t type) ;

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

        uint8_t      type ;
        Coord        coord ;

    protected:

        unsigned int id;
        double       constr; // Point de construction.
        uint8_t      vie;

};

#endif