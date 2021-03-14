#pragma once
#include<array>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "utilitaire.hh"
enum class resultat
{
    ND,
    DEFAITE,
    VICTOIRE,
    NUL
};

class noeud {
    public:
        noeud();
        void initPlateau();

        noeud(std::string & enr);

        board plateau() const;
        void setPlateau(board const & plateau);

        std::string getId() const;
        void setId(const std::string &id);

        // bool getEstUnFils() const;
        // void setEstUnFils(bool estUnFils);

        int getNbrGainCummule() const;
        void setNbrGainCummule(int nbrGainCummule);

        int getNbrFoisTraverse() const;
        void setNbrFoisTraverse(int nbrFoisTraverse);

        // bool getEstOuvert() const;
        // void setEstOuvert(bool estOuvert);

        // resultat getValeur() const;
        // void setValeur(const resultat &valeur);

        std::string const showNoeud() const;
        noeud &operator=(noeud const & n);
        static void setCpt(unsigned int cpt);

        Brix getBrix() const;
        void setBrix(int aX, int oX, int aO, int oO);

        double getQubc() const;
        void setQubc(double qubc);

private:
        std::string _id;

        board _plateau;

        // bool _estUnFils;
        int _nbrGainCummule;
        unsigned int _nbrFoisTraverse;
        // bool _estOuvert;
        // resultat _valeur;
        Brix _brix;
        double _qubc;
        static unsigned int _cpt;

};


