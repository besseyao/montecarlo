#include "arbre.hh"


const std::vector<relationBinaire> &arbreBinaire::getArbreBinaire() const
{
    return _arbreBinaire;
}


void arbreBinaire::setFilsG(const std::shared_ptr<noeud> &origine, const std::shared_ptr<noeud> &fg, bool &trouve){
    auto i (_arbreBinaire.begin());
    while ( i!=_arbreBinaire.end() && !trouve){
        if ((*i).getNoeudOrigine()->getId() == origine->getId()){
            (*i).setFilsGauche(fg);
            trouve=true;
        }
        ++i;
    }
}

void arbreBinaire::setFilsD(const std::shared_ptr<noeud> &origine, const std::shared_ptr<noeud> &fd, bool &trouve){
    auto i (_arbreBinaire.begin());
    while ( i!=_arbreBinaire.end() && !trouve){
        if ((*i).getNoeudOrigine()->getId() == origine->getId()){
            (*i).setFilsDroit(fd);
            trouve=true;
        }
        ++i;
    }
}

void arbreBinaire::affichage() const
{
    for(const auto & r : _arbreBinaire){
            std::cout << r.getNoeudOrigine()->getId() << " -- ";
            if(r.getFilsGauche()->getEstUnfils())
                std::cout << r.getFilsGauche()->getId() << " ";
            else std::cout << "x ";
            if(r.getFilsDroit()->getEstUnfils())
                    std::cout << r.getFilsDroit()->getId();
            else std::cout << "x ";
            std::cout << "\n";
    }
}

void arbreBinaire::ajout(const relationBinaire &r) {
    _arbreBinaire.push_back(r);
}


void arbreBinaire::tabToBin(const std::vector<std::shared_ptr<noeud> > &tab)
{
    // les cases contenants comme id -1 sont une indication pour dire que la case represente un fils gauche/droit vide
    // et ainsi restituer un arbre tel qu'il doit etre et non en faisaint un remplissage au fur et a mesure
    for (unsigned int i(0); i < tab.size();i+=3){
        if (tab[i]->getId()!=-1){
            std::shared_ptr<noeud> fg(new noeud(-1,0,0,0,0));
            std::shared_ptr<noeud> fd(new noeud(-1,0,0,0,0));
            relationBinaire r(tab[i],fg,fd);

            if( i+1 < tab.size()){
                if(tab[i+1]->getId()!=-1){
                    r.setFilsGauche(tab[i+1]);
                }

                if(i+2 < tab.size()){
                    if(tab[i+2]->getId()!=-1){
                    r.setFilsDroit(tab[i+2]);
                    }
                }
            _arbreBinaire.push_back(r);
            }
        }
    }
}


std::vector<std::shared_ptr<noeud> > arbreBinaire::binToTab() const
{
    // les cases contenants -1 sont une indication pour dire que la case represente un fils gauche/droit vide
    // et ainsi restituer un arbre tel qu'il etait en faisant un tabToBin apres
    std::vector<std::shared_ptr<noeud>> table;
    for (size_t i(0); i < _arbreBinaire.size(); ++i) {
            table.push_back(_arbreBinaire[i].getNoeudOrigine());

        if(_arbreBinaire[i].getFilsGauche()->getEstUnfils())
            table.push_back(_arbreBinaire[i].getFilsGauche());
        else {
            std::shared_ptr<noeud> null(new noeud(-1,0,0,0,0));
            table.push_back(null);
        }
        if(_arbreBinaire[i].getFilsDroit()->getEstUnfils())
            table.push_back(_arbreBinaire[i].getFilsDroit());
        else{
            std::shared_ptr<noeud> null(new noeud(-1,0,0,0,0));
            table.push_back(null);
        }

    }

    return table;
}

int arbreBinaire::getIndiceParentDroit(const int &id) const{
    int i=0;
    for (const auto &r : _arbreBinaire){
        if (r.getFilsDroit()->getEstUnfils()){
            if (id==r.getFilsDroit()->getId()) return i;
            }
        ++i;
    }
    return -1;
}

int arbreBinaire::getIndiceParentGauche(const int &id) const{
    int i=0;
    for (const auto &r : _arbreBinaire){
        if (r.getFilsGauche()->getEstUnfils()){
            if (id==r.getFilsGauche()->getId()) return i;
            }
        ++i;
    }
    return -1;
}





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


int arbreNaire::getIndNoeudOrigine(const int &id) const{
    int i=0;
    for (const auto & r : _arbreNaire){
        if (id==r.getNoeudOrigine()->getId()) return i;
        ++i;
        }
    return 0;
}

const std::vector<std::shared_ptr<noeud>> &arbreNaire::getNoeudEnfant(noeud const & n) const
{
    for (size_t i(0); i< _arbreNaire.size(); ++i) {
        if(_arbreNaire[i].getNoeudOrigine()->getId() == n.getId())
            return _arbreNaire[i].getNoeudsDest();
    }
}


void arbreNaire::binaireToNaire (const arbreBinaire &arbn){
    if (arbn.getArbreBinaire().size() != 0){
        for (unsigned int i(0); i <arbn.getArbreBinaire().size(); ++i){
            if (i==0){
                std::shared_ptr<noeud> origine = arbn.getArbreBinaire()[i].getNoeudOrigine();
                std::vector<std::shared_ptr<noeud>> fils;
                if(arbn.getArbreBinaire()[i].getFilsGauche()->getEstUnfils()) {
                    std::shared_ptr<noeud> fg = arbn.getArbreBinaire()[i].getFilsGauche();
                    fils.push_back(fg);
                }
                relationNaire r (origine,fils);
                this->ajout(r);
            }
            else {
                if (arbn.getArbreBinaire()[i].getFilsGauche()->getEstUnfils()){
                    std::shared_ptr<noeud> origine = arbn.getArbreBinaire()[i].getNoeudOrigine();
                    std::shared_ptr<noeud> fg = arbn.getArbreBinaire()[i].getFilsGauche();
                    std::vector<std::shared_ptr<noeud>> fils;
                    fils.push_back(fg);
                    relationNaire r (origine,fils);
                    this->ajout(r);
                }
                if(arbn.getArbreBinaire()[i].getFilsDroit()->getEstUnfils()){
                    std::shared_ptr<noeud> fd = arbn.getArbreBinaire()[i].getFilsDroit();
                    //on remonte au parent de ces noeuds fils
                    int x = arbn.getIndiceParentDroit(fd->getId());
                    int y = x;
                    while (x!=-1){
                        y=x;
                        x = arbn.getIndiceParentDroit(arbn.getArbreBinaire()[x].getNoeudOrigine()->getId());
                    }
                    y = arbn.getIndiceParentGauche(arbn.getArbreBinaire()[y].getNoeudOrigine()->getId());
                    int j = this->getIndNoeudOrigine(arbn.getArbreBinaire()[y].getNoeudOrigine()->getId());
                    this->_arbreNaire[j].setNoeudsDest(fd);
                }
                if (!arbn.getArbreBinaire()[i].getFilsGauche()->getEstUnfils()){
                   std::shared_ptr<noeud> origine = arbn.getArbreBinaire()[i].getNoeudOrigine();
                   std::vector<std::shared_ptr<noeud>> fils;
                   relationNaire r (origine,fils);
                   this->ajout(r);
                }
            }
        }
    }
}


bool arbreNaire::isEmpty()
{
    return  (_arbreNaire.size() == 0);
}


void arbreNaire::naireToBinaire(arbreBinaire &arbb) const
{
    if (_arbreNaire.size() != 0){
        for (unsigned int i(0); i < _arbreNaire.size(); ++i){
            for (unsigned int j(0); j < _arbreNaire[i].getNoeudsDest().size(); ++j) {
                if(i == 0 && j == 0) {
                    std::shared_ptr<noeud> origin = _arbreNaire[i].getNoeudOrigine();
                    std::shared_ptr<noeud> fg = _arbreNaire[0].getNoeudsDest()[0];
                    bool trouve = false;
                    arbb.setFilsG(origin,fg,trouve);
                    if (!trouve){
                        std::shared_ptr<noeud> fd(new noeud(-1,0,0,0,0));
                        relationBinaire r(origin,fg,fd);
                        arbb.ajout(r);
                    }
                }else {
                    if (j==0){
                        std::shared_ptr<noeud> origin = _arbreNaire[i].getNoeudOrigine();
                        std::shared_ptr<noeud> fg = _arbreNaire[i].getNoeudsDest()[j];
                        bool trouve = false;
                        arbb.setFilsG(origin,fg,trouve);
                        if (!trouve){
                            std::shared_ptr<noeud> fd(new noeud(-1,0,0,0,0));
                            relationBinaire r(_arbreNaire[i].getNoeudOrigine(),fg,fd);
                            arbb.ajout(r);
                        }
                        //si ce noeud est fils unique c'est une feuille, on le met dans l'arbre
                        if (j==_arbreNaire[i].getNoeudsDest().size()-1){
                            std::shared_ptr<noeud> fd(new noeud(-1,0,0,0,0));
                            std::shared_ptr<noeud> fg(new noeud(-1,0,0,0,0));
                            relationBinaire r(_arbreNaire[i].getNoeudsDest()[j],fg,fd);
                            arbb.ajout(r);
                        }
                    }else {
                        std::shared_ptr<noeud> origin = _arbreNaire[i].getNoeudsDest()[j-1];
                        std::shared_ptr<noeud> fd = _arbreNaire[i].getNoeudsDest()[j];
                        bool trouve = false;
                        arbb.setFilsD(origin,fd,trouve);
                        if (!trouve){
                            std::shared_ptr<noeud> fg(new noeud(-1,0,0,0,0));
                            relationBinaire r(_arbreNaire[i].getNoeudsDest()[j-1],fg,fd);
                            arbb.ajout(r);
                        }
                        //si c'est le dernier noeud fils, c'est une feuille, on l'ajoute dans l'arbre
                        if (j==_arbreNaire[i].getNoeudsDest().size()-1){
                            std::shared_ptr<noeud> fd(new noeud(-1,0,0,0,0));
                            std::shared_ptr<noeud> fg(new noeud(-1,0,0,0,0));
                            relationBinaire r(_arbreNaire[i].getNoeudsDest()[j],fg,fd);
                            arbb.ajout(r);
                        }
                    }
                }
            }
        }
    }
}

void arbreNaire::ajoutfils(const int &origine, std::shared_ptr<noeud> &n){
    _arbreNaire[origine].setNoeudsDest(n);
}

void arbreNaire::completeArbre(const int &result){
    for (auto &r : _arbreNaire){
        if (r.getNoeudOrigine()->getEstOuvert()){
            r.setNoeudOrigine()->setNbrFoisTraverse();
            r.setNoeudOrigine()->setNbrGainCummule(result);
            r.setNoeudOrigine()->setEstOuvert(false);
        }
    }
}

const std::vector<relationNaire> &arbreNaire::getArbreNaire() const{
    return _arbreNaire;
}

std::vector<relationNaire> &arbreNaire::setArbreNaire(){
    return _arbreNaire;
}

bool arbreNaire::appartient(const Brix &coup,const int &indNoeudOrigine) const{
    for (auto & r : _arbreNaire[indNoeudOrigine].getNoeudsDest()){
        if (coup.getAx()==r->getaX() && coup.getOx()==r->getoX() &&
                coup.getAo()==r->getaO() && coup.getOo()==r->getoO())
            return true;
    }
    return false;
}

bool arbreNaire::tousExplores (const std::vector<Brix> &coupsPossibles,const int &indNoeudOrigine) const{
    for (const auto &c : coupsPossibles){
        if (!appartient(c,indNoeudOrigine))
            return false;
    }
    return true;
}

int arbreNaire::rechercheNoeudDescente(const int &indNoeudOrigine) const{
    float max = 0;
    int i = 0;
    int indNoeud;
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
