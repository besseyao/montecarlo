#pragma once
#include <algorithm>
#include "noeud.hh"
#include "relation.hh"
#include "../brix.hh"


class arbreNaire {
    public:
        arbreNaire() =default;

        void affichage() const;
        void ajout(relationNaire &r);
        const std::vector<std::shared_ptr<noeud> > &getNoeudEnfant(noeud const & n) const;

        //ajout de ces methode
        const std::vector<relationNaire> &getArbreNaire() const;
        std::vector<relationNaire> &setArbreNaire();
        void ajoutfils(const int &origine, std::shared_ptr<noeud> &n);
        void completeArbre(const int &result,const std::vector<int> &IdNoeudsParcourus);
        //selectione le noeud fils ayant la plus grande valeur UBC
        int rechercheNoeudDescente(const int &indNoeudOrigine) const;
        int getIdPere (const int & id) const;

        //fonction de verification
        bool sontEgaux (const std::vector<relationNaire> &arbreNaire)const;


    private:
        std::vector<relationNaire> _arbreNaire;
};
