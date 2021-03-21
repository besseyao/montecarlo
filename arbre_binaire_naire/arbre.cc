#include "arbre.hh"


void arbreNaire::affichage() const
{
    for(auto & r : _arbreNaire){
            std::cout << r.getNoeudOrigine()->getId() << " -- ";
            for (auto & n : r.getNoeudsDest()){
                std::cout << n->getId() << " ";
            }
            std::cout << "\n";
    }
}

void arbreNaire::ajout(relationNaire &r){
    _arbreNaire.push_back(r);
}


int arbreNaire::getIdPere(const int &id) const{
    for (auto &r : _arbreNaire){
        for (auto &d : r.getNoeudsDest())
            if (d->getId()==id) return r.getNoeudOrigine()->getId();
        }
}

const std::vector<std::shared_ptr<noeud>> &arbreNaire::getNoeudEnfant(noeud const & n) const
{
    for (size_t i(0); i< _arbreNaire.size(); ++i) {
        if(_arbreNaire[i].getNoeudOrigine()->getId() == n.getId())
            return _arbreNaire[i].getNoeudsDest();
    }
}


void arbreNaire::ajoutfils(const int &origine, std::shared_ptr<noeud> &n){
    _arbreNaire[origine].setNoeudsDest(n);
}

void arbreNaire::completeArbre(const int &result, const std::vector<int> &IdNoeudsParcourus){
    for (auto &i : IdNoeudsParcourus){
        _arbreNaire[i].setNoeudOrigine()->setNbrFoisTraverse();
        _arbreNaire[i].setNoeudOrigine()->setNbrGainCummule(result);
    }
}

const std::vector<relationNaire> &arbreNaire::getArbreNaire() const{
    return _arbreNaire;
}

std::vector<relationNaire> &arbreNaire::setArbreNaire(){
    return _arbreNaire;
}


int arbreNaire::rechercheNoeudDescente(const int &indNoeudOrigine) const{
    float max = 0;
    int i = 0;
    int indNoeud = 0;
    for (const auto &r : _arbreNaire[indNoeudOrigine].getNoeudsDest()){
        float val = (r->getNbrGainCumule()/r->getNbrFoisTraverse()) + sqrt(2*(log(_arbreNaire[indNoeudOrigine].getNoeudOrigine()->getNbrFoisTraverse())/r->getNbrFoisTraverse()));
        //std::cout << val << std::endl;
        if (val > max){
            max=val;
            indNoeud=i;
        }
        ++i;
    }
    return indNoeud;
}


//verif pour debugger
bool arbreNaire::sontEgaux(const std::vector<relationNaire> &arbreNaire) const{
    for (const auto &r : _arbreNaire){
        bool trouve=false;
        int i = 0;
        while (!trouve){
            if (r.getNoeudOrigine()->getId()==arbreNaire[i].getNoeudOrigine()->getId())
                trouve=true;
            else
                ++i;
            if (i==arbreNaire.size())
                return false;
        }
        int j=0;
        while(j<r.getNoeudsDest().size()){
            if (r.getNoeudsDest()[j]->getId()!=arbreNaire[i].getNoeudsDest()[j]->getId())
                return false;
            ++j;
        }
    }
    return true;
}
