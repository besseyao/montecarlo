#include "noeud.hh"

noeud::noeud(const unsigned int &id, const int aX, const int oX, const int aO, const int oO)
    :_id(id),_aX(aX),_oX(oX),_aO(aO),_oO(oO), _estUnFils(false),_estOuvert(true),_nbrGainCummule(0),_nbrFoisTraverse(0){}


const unsigned int &noeud::getId() const {
    return _id;
}

const bool &noeud::getEstUnfils() const
{
    return _estUnFils;
}


void noeud::setEstUnfils(const bool &rep)
{
    _estUnFils = rep;
}

const bool &noeud::getEstOuvert() const {
    return _estOuvert;
}

void noeud::setNbrGainCummule(const int &n){
    _nbrGainCummule+=n;
}

void noeud::setNbrFoisTraverse(){
    _nbrFoisTraverse++;
}

void noeud::setEstOuvert(const bool &b){
    _estOuvert=b;
}

void noeud::setBrix(const int aX, const int oX, const int aO, const int oO){
    _aX=aX;
    _oX=oX;
    _aO=aO;
    _oO=oO;
}

const int &noeud::getaX()const{
    return _aX;
}

const int &noeud::getoX()const{
    return _oX;
}

const int &noeud::getaO()const{
    return _aO;
}

const int &noeud::getoO()const{
    return _oO;
}

const int &noeud::getNbrGainCumule()const {
    return _nbrGainCummule;
}

const int &noeud::getNbrFoisTraverse()const {
    return _nbrFoisTraverse;
}
