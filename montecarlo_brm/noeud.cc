#include "noeud.hh"

unsigned int noeud::_cpt(1);

noeud::noeud()
    :_id("noeud" + std::to_string(_cpt++)),
      _nbrGainCummule(0),
      _nbrFoisTraverse(0)
{
    initPlateau();
}

void noeud::initPlateau()
{
    for (auto & ligne : _plateau)
            for (auto & colonne : ligne)
                colonne = '0';
}

noeud::noeud(std::string &enr){
    std::vector<std::string> n_param (utilitaire::explode(enr, '*'));
    _id = n_param[0];
    _plateau = utilitaire::plateau(n_param[1]);
    // _estUnFils = utilitaire::stob(n_param[2]);
    _nbrGainCummule = std::stoi(n_param[2]);
    _nbrFoisTraverse = std::stoi(n_param[3]);
    // _estOuvert = utilitaire::stob(n_param[4]);

    if(n_param.size() > 4)
        _brix.setAllCoord(std::stoi(n_param[4]), std::stoi(n_param[5]), std::stoi(n_param[6]), std::stoi(n_param[7]));

    // std::string val(n_param[5]);

    /*
    if (val == "-1")
        _valeur = resultat::DEFAITE;
    if (val == "0")
        _valeur = resultat::NUL;
    if(val == "+1")
        _valeur = resultat::VICTOIRE;
    if (val == "nd")
        _valeur = resultat::ND;
    */
}

board noeud::plateau() const
{
    return _plateau;
}


void noeud::setPlateau(const board &plateau)
{
    _plateau = plateau;
}

std::string noeud::getId() const
{
    return _id;
}

void noeud::setId(const std::string &id)
{
    _id = id;
}

/*

bool noeud::getEstUnFils() const
{
    return _estUnFils;
}

void noeud::setEstUnFils(bool estUnFils)
{
    _estUnFils = estUnFils;
}
*/

int noeud::getNbrGainCummule() const
{
    return _nbrGainCummule;
}

void noeud::setNbrGainCummule(int nbrGainCummule)
{
    _nbrGainCummule = nbrGainCummule;
}

int noeud::getNbrFoisTraverse() const
{
    return _nbrFoisTraverse;
}

void noeud::setNbrFoisTraverse(int nbrFoisTraverse)
{
    _nbrFoisTraverse = nbrFoisTraverse;
}
/*
bool noeud::getEstOuvert() const
{
    return _estOuvert;
}

void noeud::setEstOuvert(bool estOuvert)
{
    _estOuvert = estOuvert;
}

resultat noeud::getValeur() const
{
    return _valeur;
}

void noeud::setValeur(const resultat &valeur)
{
    _valeur = valeur;
}
*/
const std::string noeud::showNoeud() const
{
    std::ostringstream os;
    os << _id << "*";

    for (auto & ligne : _plateau)
        for (auto & colonne : ligne)
            os << colonne;

    os << "*";
    // os << _estUnFils << "*";
    os << _nbrGainCummule << "*";
    os << _nbrFoisTraverse ;
    // os << _estOuvert << "*";
    /*
    switch (_valeur) {
        case resultat::DEFAITE: os << "-1" ; break;
        case resultat::NUL: os << "0" ; break;
        case resultat::VICTOIRE: os << "+1"; break;
        case resultat::ND: os << "nd"; break;
    }
    */

    if(_brix.getDefinie()){
        os << "*" << _brix.getAx() << "*" << _brix.getOx() << "*" << _brix.getAo() << "*" << _brix.getOo() ;
    }

    return os.str();
}

noeud &noeud::operator=(const noeud &n)
{
    if (this != &n) {
        _id = n.getId();
        _plateau = n.plateau();
        // _estUnFils = n.getEstUnFils();
        _nbrGainCummule = n.getNbrGainCummule();
        _nbrFoisTraverse = n.getNbrFoisTraverse();
        // _estOuvert = n.getEstOuvert();
        // _valeur = n.getValeur();
        _brix = n.getBrix();
    }
    return *this;
}

void noeud::setCpt(unsigned int cpt){
    _cpt = cpt;
}

Brix noeud::getBrix() const
{
    return _brix;
}

void noeud::setBrix(int aX, int oX, int aO, int oO)
{
    _brix.setAllCoord(aX, oX, aO, oO);
}

