#pragma once
#include "noeud.hh"
#include <vector>

class relation {
    public:
        relation() = default;
        relation(const std::shared_ptr<noeud> &noeudOrigine);

        const std::shared_ptr<noeud> &getNoeudOrigine() const;
        std::shared_ptr<noeud> &setNoeudOrigine();

    protected:
        std::shared_ptr<noeud> _noeudOrigine;
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

        relationNaire(const std::shared_ptr<noeud> &noeudOrigine, const std::vector<std::shared_ptr<noeud> > &noeudsDest);

        const std::vector<std::shared_ptr<noeud> > &getNoeudsDest() const;
        std::vector<std::shared_ptr<noeud>> &setNoeudsDest();
        void setNoeudsDest(std::shared_ptr<noeud> &n);
        void setNoeudOrigin (const int &result);

    private:
        std::vector<std::shared_ptr<noeud>> _noeudsDest;
};
