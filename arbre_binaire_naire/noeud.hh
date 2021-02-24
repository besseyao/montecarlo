#pragma once
#include <string>
#include <iostream>

enum class resultat
{
    ND,
    DEFAITE,
    VICTOIRE,
    NUL
};

class noeud
{
    public:
        noeud() =default;
        noeud(const unsigned int &id,const int aX, const int oX, const int aO, const int oO);
        noeud(noeud const & n);

        unsigned int getId() const ;
        bool getEstUnfils() const ;
        void setEstUnfils(const bool &rep);

        bool getEstOuvert() const;
        int getNbrGainCumule() const;
        int getNbrFoisTraverse() const;
        void setNbrGainCummule (const int &n);
        void setNbrFoisTraverse ();
        void setEstOuvert (const bool &b);
        void setBrix (const int aX, const int oX, const int aO, const int oO);
        int getaX() const;
        int getoX() const;
        int getaO() const;
        int getoO() const;
    private:
        unsigned int _id;
        //les 4 données pour un brix
        int _aX;
        int _oX;
        int _aO;
        int _oO;
        bool _estUnFils;
        int _nbrGainCummule;
        int _nbrFoisTraverse;
        bool _estOuvert;
        resultat _valeur;

        //  -- Prevue pour la suite

        /*
         *  std::string _nom;
         * int _nbreGainCummule;
         * int _nbreFoisTraverse;
         * bool _estOuvert;
         */
};
