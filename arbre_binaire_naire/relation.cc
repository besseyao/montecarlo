#include "relation.hh"

relation::relation(const noeud &noeudOrigine)
    :_noeudOrigine(noeudOrigine){}

relationBinaire::relationBinaire(const noeud &noeudOrigine)
    :relation (noeudOrigine){
    _filsGauche.setEstUnfils(false);
    _filsDroit.setEstUnfils(false);
}

noeud relation::getNoeudOrigine() const
{
    return _noeudOrigine;
}

noeud relationBinaire::getFilsGauche() const
{
    return _filsGauche;
}

noeud relationBinaire::getFilsDroit() const
{
    return  _filsDroit;
}

void relationBinaire::setFilsGauche(const noeud &n)
{
    _filsGauche = n;
    _filsGauche.setEstUnfils(true);
}

void relationBinaire::setFilsDroit(const noeud &n)
{
    _filsDroit = n ;
    _filsDroit.setEstUnfils(true);
}




relationNaire::relationNaire(const noeud &noeudOrigine, const std::vector<noeud> &noeudsDest)
    :relation (noeudOrigine), _noeudsDest(noeudsDest){
    for (auto &r : _noeudsDest)
        r.setEstUnfils(true);
    }

std::vector<noeud> relationNaire::getNoeudsDest() const
{
    return _noeudsDest;
}


void relationNaire::setNoeudsDest(const noeud &n)
{
    _noeudsDest.push_back(n);
}












