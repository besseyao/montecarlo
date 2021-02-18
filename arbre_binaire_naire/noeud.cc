#include "noeud.hh"

noeud::noeud(const unsigned int &id)
    :_id(id), _estUnFils(false){}

noeud::noeud(const noeud &n)
    :_id(n._id), _estUnFils(n._estUnFils), _qubc(NULL), _nbreFoisTraverse(0), _nbreGainCummule(0), _estOuvert(false), _valeur(resultat::ND){}


unsigned int noeud::getId() const {
    return _id;
}

bool noeud::getEstUnfils() const
{
    return _estUnFils;
}


void noeud::setEstUnfils(const bool &rep)
{
    _estUnFils = rep;
}
