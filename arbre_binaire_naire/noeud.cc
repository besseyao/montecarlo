#include "noeud.hh"

noeud::noeud(const unsigned int &id, const int aX, const int oX, const int aO, const int oO)
    :_id(id), _estUnFils(false),_aX(aX),_oX(oX),_aO(aO),_oO(oO),_nbrGainCummule(0),_nbrFoisTraverse(0){}

noeud::noeud(const noeud &n)
    :_id(n._id), _estUnFils(n._estUnFils),_aX(n._aX),_oX(n._oX),_aO(n._aO),_oO(n._oO),_nbrGainCummule(n._nbrGainCummule),_nbrFoisTraverse(n._nbrGainCummule){}



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

bool noeud::getEstOuvert() const {
    return _estOuvert;
}

void  noeud::setNbrGainCummule(const int &n){
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

int noeud::getaX()const{
    return _aX;
}

int noeud::getoX()const{
    return _oX;
}

int noeud::getaO()const{
    return _aO;
}

int noeud::getoO()const{
    return _oO;
}

int noeud::getNbrGainCumule()const {
    return _nbrGainCummule;
}

int noeud::getNbrFoisTraverse()const {
    return _nbrFoisTraverse;
}
