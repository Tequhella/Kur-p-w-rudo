/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : block.h                               */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_BLOCK
#define DEF_BLOCK

#include "type.h"

using namespace std;

/* La classe Block est utilisée pour représenter un bloc dans la carte */
class Block
{
    public:

    /*************************************************************************
    *                       Constructeur & Destructeur                       *
    *************************************************************************/

        /*
        * Constrcuteur de la classe Block.
        */
        Block (uint8_t type, RocheType typeRoche);

        /*
        * Constructeur par défaut de la classe Block.
        */
        Block ();

        /*
        * Destrcuteur de la classe Block.
        */
        ~Block ();

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        ////////////
        // Getter //
        ////////////

        /**
         * @brief getType, récupère le type de block.
         * 
         * @return uint8_t
         */
        uint8_t getType ();

        /**
         * @brief getRocheType, récupère le type de roche.
         * 
         * @return RocheType
         */
        RocheType getRocheType ();

        /**
         * @brief getSoliditee, récupère la solidité restante avant de se casser.
         * 
         * @return double 
         */
        double getSoliditee ();

        /**
         * @brief getMinerai_quantitee, récupère la quantité de minerai.
         * 
         * @return int 
         */
        int getMinerai_quantitee ();

        ////////////
        // Setter //
        ////////////
        
		/**
		 * @brief setType, définit l'indicateur du type de block.
		 * 
		 * @param type Le type de block.
		 */
		void setType (uint8_t type);
		
		/**
		 * @brief setRocheType, définit l'indicateur du type de roche.
		 * 
		 * @param typeRoche Le type de roche.
		 */
		void setRocheType (RocheType typeRoche);
		
		/**
		 * @brief setSoliditee, définit la solidité restante avant de se casser.
		 * 
		 * @param soliditee La solidité restante avant de se casser.
		 */
		void setSoliditee (double soliditee);

		/**
		 * @brief setMinerai_quantitee, définit la quantité de minerai.
		 * 
		 * @param soliditee La quantité de minerai.
		 */
		void decSoliditee (double soliditee);
		
		/**
		 * @brief setMinerai_quantitee, définit la quantité de minerai.
		 * 
		 * @param quantitee La quantité de minerai.
		 */
		void setMinerai_quantitee (int quantitee);
    
    private:

        uint8_t type              = 0;
        RocheType rocheType       = NON_ROCHE;
        double  soliditee         = 0;
        int     minerai_quantitee = 0;
};

#endif