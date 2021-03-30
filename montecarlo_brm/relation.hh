#pragma once
#include "noeud.hh"
#include <vector>
#include <string>

class relation {
    public:
        relation() = default;
        relation(noeud const & origine, std::vector<noeud> const & dest);
        noeud origine() const;
        void setOrigine(const noeud &origine);

        std::vector<noeud> destination() const;
        void setDestination(const std::vector<noeud> &destination);

        void ajouterDestination(noeud const & dest);

        std::string const showRelation() const;

    private:
        noeud _origine;
        std::vector<noeud> _destination;
};

// std::ostream & operator<<(std::ostream & os, relation const & r);
