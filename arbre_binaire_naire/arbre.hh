#pragma once
#include <algorithm>
#include "noeud.hh"
#include "relation.hh"
#include "../brix.hh"


class arbreBinaire {

    public:
        arbreBinaire() =default;

        const std::vector<relationBinaire> &getArbreBinaire() const;

        void setFilsG (const noeud &origine,const noeud &fg,bool &trouve);
        void setFilsD (const noeud &origine,const noeud &fd,bool &trouve);
        void affichage() const;
        void ajout(const relationBinaire & r);

        void tabToBin(const std::vector<noeud> &tab);
        std::vector<noeud> binToTab() const;

    private:
        std::vector<relationBinaire> _arbreBinaire;
};


class arbreNaire {
    public:
        arbreNaire() =default;

        void affichage() const;
        void ajout(const relationNaire  &r);
        int getIndNoeudOrigine(const noeud &n) const;
        std::vector<noeud> getNoeudEnfant(noeud const & n);
        void naireToBinaire(arbreBinaire & arbb);
        void binaireToNaire (const arbreBinaire &arbb);
        bool isEmpty();

        //ajout de ces methode
        const std::vector<relationNaire> &getArbreNaire() const;
        void ajoutfils(const noeud &origine,const noeud &n);
        void completeArbre(const int &result);
        //savoir si un coup est deja dans un noeud fils du noeud origine donné en parametre
        bool appartient (const Brix &coup, const int &indNoeudOrigine) const;
        //retourne l'indice où mettre le premier coup qui n'est pas encore mis dans l'arbre
        bool tousExplores (const std::vector<Brix> &coupsPossibles, const int &indNoeudOrigine) const;
        //selectione le noeud fils ayant la plus grande valeur UBC
        int rechercheNoeudDescente(const int &indNoeudOrigine) const;

    private:
        std::vector<relationNaire> _arbreNaire;
};
