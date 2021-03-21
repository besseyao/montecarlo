#include "relation.hh"

const std::shared_ptr<noeud> &relationNaire::getNoeudOrigine() const
{
    return _noeudOrigine;
}

std::shared_ptr<noeud> &relationNaire::setNoeudOrigine(){
    return _noeudOrigine;
}



relationNaire::relationNaire(const std::shared_ptr<noeud> &noeudOrigine, const std::vector<std::shared_ptr<noeud> > &noeudsDest)
    :_noeudOrigine(noeudOrigine), _noeudsDest(noeudsDest){}


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








