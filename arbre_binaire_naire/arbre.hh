#pragma once
#include <algorithm>
#include "noeud.hh"
#include "relation.hh"
#include "../brix.hh"


class arbreBinaire {

    public:
        arbreBinaire() =default;

        const std::vector<relationBinaire> &getArbreBinaire() const;

        void setFilsG (const std::shared_ptr<noeud> &origine,const std::shared_ptr<noeud> &fg,bool &trouve);
        void setFilsD (const std::shared_ptr<noeud> &origine,const std::shared_ptr<noeud> &fd,bool &trouve);
        void affichage() const;
        void ajout(const relationBinaire & r);

        void tabToBin(const std::vector<std::shared_ptr<noeud>> &tab);
        std::vector<std::shared_ptr<noeud>> binToTab() const;
        int getIndiceParentDroit(const int &id)const;
        int getIndiceParentGauche(const int &id)const;

    private:
        std::vector<relationBinaire> _arbreBinaire;
};


class arbreNaire {
    public:
        arbreNaire() =default;

        void affichage() const;
        void ajout(relationNaire &r);
        int getIndNoeudOrigine(const int &id) const;
        const std::vector<std::shared_ptr<noeud> > &getNoeudEnfant(noeud const & n) const;
        void naireToBinaire(arbreBinaire &arbb) const;
        void binaireToNaire (const arbreBinaire &arbb);
        bool isEmpty();

        //ajout de ces methode
        const std::vector<relationNaire> &getArbreNaire() const;
        std::vector<relationNaire> &setArbreNaire();
        void ajoutfils(const int &origine, std::shared_ptr<noeud> &n);
        void completeArbre(const int &result);
        //savoir si un coup est deja dans un noeud fils du noeud origine donné en parametre
        bool appartient(const Brix &coup, const int &indNoeudOrigine) const;
        //retourne l'indice où mettre le premier coup qui n'est pas encore mis dans l'arbre
        bool tousExplores(const std::vector<Brix> &coupsPossibles, const int &indNoeudOrigine) const;
        //selectione le noeud fils ayant la plus grande valeur UBC
        int rechercheNoeudDescente(const int &indNoeudOrigine) const;

        //fonction de verification
        bool sontEgaux (const std::vector<relationNaire> &arbreNaire)const;


    private:
        std::vector<relationNaire> _arbreNaire;
};
