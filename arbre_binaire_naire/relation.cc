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


relationBinaire::relationBinaire(const std::shared_ptr<noeud> &noeudOrigine, const std::shared_ptr<noeud> &noeudGauche, const std::shared_ptr<noeud> &noeudDroit)
    :relation (noeudOrigine),_filsGauche(noeudGauche),_filsDroit(noeudDroit){
    if (_filsGauche->getId()!=-1)
        _filsGauche->setEstUnfils(true);
    if (_filsDroit->getId()!=-1)
        _filsDroit->setEstUnfils(true);
}

const std::shared_ptr<noeud> &relationBinaire::getFilsGauche() const
{
    return _filsGauche;
}

const std::shared_ptr<noeud> &relationBinaire::getFilsDroit() const
{
    return  _filsDroit;
}

void relationBinaire::setFilsGauche(const std::shared_ptr<noeud> &n)
{
    _filsGauche = std::move(n);
    _filsGauche->setEstUnfils(true);
}

void relationBinaire::setFilsDroit(const std::shared_ptr<noeud> &n)
{
    _filsDroit = std::move(n) ;
    _filsDroit->setEstUnfils(true);
}




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









