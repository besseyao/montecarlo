#pragma once
#include <string>
#include <iostream>
#include <memory>

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

        const int &getId() const ;
        const bool &getEstUnfils() const ;
        void setEstUnfils(const bool &rep);

        const bool &getEstOuvert() const;
        const int &getNbrGainCumule() const;
        const int &getNbrFoisTraverse() const;
        void setNbrGainCummule (const int &n);
        void setNbrFoisTraverse ();
        void setNbrFoisTraverse (const int &v);
        void setEstOuvert (const bool &b);
        void setBrix (const int aX, const int oX, const int aO, const int oO);
        const int &getaX() const;
        const int &getoX() const;
        const int &getaO() const;
        const int &getoO() const;
    private:
        int _id;
        //les 4 données pour un brix
        int _aX;
        int _oX;
        int _aO;
        int _oO;
        bool _estUnFils;
        int _nbrGainCummule;
        int _nbrFoisTraverse;
        bool _estOuvert;
};
