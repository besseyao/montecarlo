#include "noeud.hh"

noeud::noeud(const unsigned int &id, const int &aX, const int &oX, const int &aO, const int &oO,const int &idPere)
    :_id(id),_aX(aX),_oX(oX),_aO(aO),_oO(oO),_estOuvert(true),_nbrGainCummule(0),_nbrFoisTraverse(0),_idPere(idPere){}


const int &noeud::getId() const {
    return _id;
}


const bool &noeud::getEstOuvert() const {
    return _estOuvert;
}

const int &noeud::getIdPere() const {
    return _idPere;
}

void noeud::setNbrGainCummule(const int &n){
    _nbrGainCummule+=n;
}

void noeud::setNbrFoisTraverse(){
    _nbrFoisTraverse++;
}

void noeud::setNbrFoisTraverse(const int &v){
    _nbrFoisTraverse=v;
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
