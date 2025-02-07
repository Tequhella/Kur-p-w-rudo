/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : vaisseau.h                            */
/* Numéro de version : 0.3.7                                 */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef DEF_VAISSEAU
#define DEF_VAISSEAU

#include "../entitee.h"

class Vaisseau : public Entitee
{
    public:

        /*
        * Constructeur de la classe Vaisseau.
        */
        Vaisseau();

        /*
        * Destructeur de la classe Vaisseau.
        */
        ~Vaisseau();

    /*************************************************************************
    *                                 Méthode                                *
    *************************************************************************/

        /**
         * @brief Méthode incNRJ, incrémente la quantité d'énergie du vaisseau.
         * 
         * @param energie La quantité d'énergie à ajouter.
         */
        void incNRJ(double energie);

        /**
         * @brief Méthode incMinerai, incrémente la quantité de minerai du vaisseau.
         * 
         * @param minerai La quantité de minerai à ajouter.
         */
        void incMinerai(double minerai);

        /**
         * @brief Surcharge de l'opérateur << pour afficher les informations du vaisseau.
         * 
         * @param strm Le flux de sortie.
         * @param vaisseau Le vaisseau à afficher.
         * @return std::ostream& Le flux de sortie modifié.
         */
        friend std::ostream& operator<< (std::ostream& strm, const Vaisseau& vaisseau)
        {
            strm << "Energie : " << vaisseau.getEnergieQuantitee() << "/" << vaisseau.getEnergieReserve() << " | " << "Efficacitée : " << vaisseau.getEnergieEfficacitee() << std::endl;
            strm << "Minerai : " << vaisseau.getMineraiQuantitee() << "/" << vaisseau.getMineraiReserve() << " | " << "Efficacitée : " << vaisseau.getMineraiEfficacitee() << std::endl;

            return strm;
        }

        ////////////
        // Getter //
        ////////////

        /**
         * @brief Méthode getEnergieQuantitee, récupère la quantité d'énergie du vaisseau.
         * 
         * @return double La quantité d'énergie du vaisseau.
         */
        double getEnergieQuantitee() const { return energieQuantitee; }

        /**
         * @brief Méthode getEnergieReserve, récupère la réserve d'énergie du vaisseau.
         * 
         * @return double La réserve d'énergie du vaisseau.
         */
        double getEnergieReserve() const { return energieReserve; }
        
        /**
         * @brief Méthode getEnergieEfficacitee, récupère l'efficacité énergétique du vaisseau.
         * 
         * @return double L'efficacité énergétique du vaisseau.
         */
        double getEnergieEfficacitee() const { return energieEfficacitee; }

        /**
         * @brief Méthode getEnergieVitesse, récupère la vitesse d'énergie du vaisseau.
         * 
         * @return double La vitesse d'énergie du vaisseau.
         */
        /*double getEnergieVitesse() const { return energieVitesse; }*/ // A voir si on garde cette méthode

        /**
         * @brief Méthode getMineraiQuantitee, récupère la quantité de minerai du vaisseau.
         * 
         * @return double La quantité de minerai du vaisseau.
         */
        double getMineraiQuantitee() const { return mineraiQuantitee; }

        /**
         * @brief Méthode getMineraiReserve, récupère la réserve de minerai du vaisseau.
         * 
         * @return double La réserve de minerai du vaisseau.
         */
        double getMineraiReserve() const { return mineraiReserve; }

        /**
         * @brief Méthode getMineraiEfficacitee, récupère l'efficacité du minerai du vaisseau.
         * 
         * @return double L'efficacité du minerai du vaisseau.
         */
        double getMineraiEfficacitee() const { return mineraiEfficacitee; }

        /**
         * @brief Méthode getPortee, récupère la portée du vaisseau.
         * 
         * @return uint8_t La portée du vaisseau.
         */
        uint8_t getPortee() const { return portee; }

        ////////////
        // Setter //
        ////////////

        /**
         * @brief Méthode setEnergieQuantitee, modifie la quantité d'énergie du vaisseau.
         * 
         * @param energieQuantitee La quantité d'énergie du vaisseau.
         */
        void setEnergieQuantitee(double energieQuantitee);

        /**
         * @brief Méthode setEnergieReserve, modifie la réserve d'énergie du vaisseau.
         * 
         * @param energieReserve La réserve d'énergie du vaisseau.
         */
        void setEnergieReserve(double energieReserve);

        /**
         * @brief Méthode setEnergieEfficacitee, modifie l'efficacité énergétique du vaisseau.
         * 
         * @param energieEfficacitee L'efficacité énergétique du vaisseau.
         */
        void setEnergieEfficacitee(double energieEfficacitee);

        /**
         * @brief Méthode setEnergieVitesse, modifie la vitesse d'énergie du vaisseau.
         * 
         * @param energieVitesse La vitesse d'énergie du vaisseau.
         */
        /*void setEnergieVitesse(double energieVitesse);*/

        /**
         * @brief Méthode setMineraiQuantitee, modifie la quantité de minerai du vaisseau.
         * 
         * @param mineraiQuantitee La quantité de minerai du vaisseau.
         */
        void setMineraiQuantitee(double mineraiQuantitee);

        /**
         * @brief Méthode setMineraiReserve, modifie la réserve de minerai du vaisseau.
         * 
         * @param mineraiReserve La réserve de minerai du vaisseau.
         */
        void setMineraiReserve(double mineraiReserve);

        /**
         * @brief Méthode setMineraiEfficacitee, modifie l'efficacité du minerai du vaisseau.
         * 
         * @param mineraiEfficacitee L'efficacité du minerai du vaisseau.
         */
        void setMineraiEfficacitee(double mineraiEfficacitee);

        /**
         * @brief Méthode setPortee, modifie la portée du vaisseau.
         * 
         * @param portee La portée du vaisseau.
         */
        void setPortee(uint8_t portee);



    private:

        double  energieQuantitee;
        double  energieReserve;
        double  energieEfficacitee;
        /*double energieVitesse;*/
        double  mineraiQuantitee;
        double  mineraiReserve;
        double  mineraiEfficacitee;
        uint8_t portee;

};

#endif