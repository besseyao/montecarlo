#include "relation.hh"

relation::relation(const noeud &origine, const std::vector<noeud> &dest) :_origine(origine), _destination(dest){}

noeud relation::origine() const
{
    return _origine;
}

void relation::setOrigine(const noeud &origine)
{
    _origine = origine;
}

std::vector<noeud> relation::destination() const
{
    return _destination;
}

void relation::setDestination(const std::vector<noeud> &destination)
{
    _destination = destination;
}

void relation::ajouterDestination(const noeud &dest) {
    _destination.push_back(dest);
}

const std::string relation::showRelation() const
{
    std::ostringstream os;
    os << _origine.getId() << ' ';
    for(auto &d : _destination)
        os << d.getId() << ' ';
    return os.str();
}

