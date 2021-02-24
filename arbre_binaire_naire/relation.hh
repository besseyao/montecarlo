#pragma once
#include "noeud.hh"
#include <vector>

class relation {
    public:
        relation() = default;
        relation(noeud const & noeudOrigine);

        noeud getNoeudOrigine() const;
        noeud setNoeudOrigine();

    private:
        noeud _noeudOrigine;
};


class relationBinaire : public relation {
    public:
        relationBinaire(noeud const & noeudOrigine);

        noeud getFilsGauche() const;
        noeud getFilsDroit() const;

        void setFilsGauche(const noeud & n);
        void setFilsDroit(const noeud & n);

    private:
        noeud _filsGauche;
        noeud _filsDroit;
};


class relationNaire : public relation {
    public:
        relationNaire(noeud const & noeudOrigine, std::vector<noeud> const & noeudsDest);

        std::vector<noeud> getNoeudsDest() const;
        void setNoeudsDest(const noeud &n);
        void setNoeudOrigin (const int &result);

    private:
        std::vector<noeud> _noeudsDest;
};
