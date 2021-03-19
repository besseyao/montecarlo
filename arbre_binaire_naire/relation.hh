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
        relationBinaire(const std::shared_ptr<noeud> &noeudOrigine, const std::shared_ptr<noeud> &noeudGauche, const std::shared_ptr<noeud> &noeudDroit);

        const std::shared_ptr<noeud> &getFilsGauche() const;
        const std::shared_ptr<noeud> &getFilsDroit() const;

        void setFilsGauche(const std::shared_ptr<noeud> &n);
        void setFilsDroit(const std::shared_ptr<noeud> &n);

    private:
        std::shared_ptr<noeud> _filsGauche;
        std::shared_ptr<noeud> _filsDroit;
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
