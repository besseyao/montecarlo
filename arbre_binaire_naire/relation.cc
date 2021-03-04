#include "relation.hh"

relation::relation(const std::shared_ptr<noeud> &noeudOrigine)
    :_noeudOrigine(noeudOrigine){}

const std::shared_ptr<noeud> &relation::getNoeudOrigine() const
{
    return _noeudOrigine;
}

std::shared_ptr<noeud> &relation::setNoeudOrigine(){
    return _noeudOrigine;
}

/*
relationBinaire::relationBinaire(const noeud &noeudOrigine)
    :relation (noeudOrigine){
    _filsGauche.setEstUnfils(false);
    _filsDroit.setEstUnfils(false);
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
*/



relationNaire::relationNaire(const std::shared_ptr<noeud> &noeudOrigine, const std::vector<std::shared_ptr<noeud> > &noeudsDest)
    :relation (noeudOrigine), _noeudsDest(noeudsDest){
    for (auto &r : _noeudsDest)
        r->setEstUnfils(true);
    }


const std::vector<std::shared_ptr<noeud> > &relationNaire::getNoeudsDest() const
{
    return _noeudsDest;
}

std::vector<std::shared_ptr<noeud> > &relationNaire::setNoeudsDest()
{
    return _noeudsDest;
}



void relationNaire::setNoeudsDest(std::shared_ptr<noeud> &n)
{
    _noeudsDest.push_back(n);
}

void relationNaire::setNoeudOrigin(const int &result){
    _noeudOrigine->setNbrFoisTraverse();
    _noeudOrigine->setNbrGainCummule(result);
    _noeudOrigine->setEstOuvert(false);
}









