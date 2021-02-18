#pragma once
#include <algorithm>
#include "noeud.hh"
#include "relation.hh"


class arbreBinaire {

    public:
        arbreBinaire() =default;

        const std::vector<relationBinaire> &getArbreBinaire() const;

        void setFilsG (const noeud &origine,const noeud &fg,bool &trouve);
        void setFilsD (const noeud &origine,const noeud &fd,bool &trouve);
        void affichage() const;
        void ajout(const relationBinaire & r);

        void tabToBin(const std::vector<unsigned int> &tab);
        std::vector<unsigned int> binToTab() const;

    private:
        std::vector<relationBinaire> _arbreBinaire;
};


class arbreNaire {
    public:
        arbreNaire() =default;

        void affichage() const;
        void ajout(const relationNaire  & r);
        int getIndNoeudOrigine(const noeud &n) const;
        std::vector<noeud> getNoeudEnfant(noeud const & n);
        void naireToBinaire(arbreBinaire & arbb);
        void binaireToNaire (const arbreBinaire &arbb);
        bool isEmpty();

    private:
        std::vector<relationNaire> _arbreNaire;
};
