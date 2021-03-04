#include "arbre.hh"


const std::vector<relationBinaire> &arbreBinaire::getArbreBinaire() const
{
    return _arbreBinaire;
}

/*
void arbreBinaire::setFilsG(const noeud &origine, const noeud &fg, bool &trouve){
    auto i (_arbreBinaire.begin());
    while ( i!=_arbreBinaire.end() && !trouve){
        if ((*i).getNoeudOrigine().getId() == origine.getId()){
            (*i).setFilsGauche(fg);
            trouve=true;
        }
        ++i;
    }
}

void arbreBinaire::setFilsD(const noeud &origine,const noeud &fd, bool &trouve){
    auto i (_arbreBinaire.begin());
    while ( i!=_arbreBinaire.end() && !trouve){
        if ((*i).getNoeudOrigine().getId() == origine.getId()){
            (*i).setFilsDroit(fd);
            trouve=true;
        }
        ++i;
    }
}

void arbreBinaire::affichage() const
{
    for(const auto & r : _arbreBinaire){
            std::cout << r.getNoeudOrigine().getId() << " -- ";
            if(r.getFilsGauche().getEstUnfils())
                std::cout << r.getFilsGauche().getId() << " ";
            else std::cout << "x ";
            if(r.getFilsDroit().getEstUnfils())
                    std::cout << r.getFilsDroit().getId();
            else std::cout << "x ";
            std::cout << "\n";
    }
}

void arbreBinaire::ajout(const relationBinaire &r) {
    _arbreBinaire.push_back(r);
}


void arbreBinaire::tabToBin(const std::vector<noeud> &tab)
{
    // les cases contenants 666 sont une indication pour dire que la case represente un fils gauche/droit vide
    // et ainsi restituer un arbre tel qu'il doit etre et non en faisaint un remplissage au fur et a mesure
    unsigned int repere;
    unsigned int j(0);
    for (unsigned int i(0); i < tab.size();++i){
        if (tab[i].getId()!=666){
            noeud n(tab[i].getId(),tab[i].getaX(),tab[i].getoX(),tab[i].getaO(),tab[i].getoO());
            relationBinaire r(n);

            repere = 2*j+1;
            ++j;
            if( repere < tab.size()){
                if(tab[repere].getId()!=666){
                    noeud fg(tab[repere].getId(),tab[repere].getaX(),tab[repere].getoX(),tab[repere].getaO(),tab[repere].getoO());
                    r.setFilsGauche(fg);
                }

                if(repere+1 < tab.size()){
                    if(tab[repere+1].getId()!=666){
                    noeud fd(tab[repere+1].getId(),tab[repere+1].getaX(),tab[repere+1].getoX(),tab[repere+1].getaO(),tab[repere+1].getoO());
                    r.setFilsDroit(fd);
                    }
                }
            _arbreBinaire.push_back(r);
            }
        }
    }
}


std::vector<noeud> arbreBinaire::binToTab() const
{
    // les cases contenants 666 sont une indication pour dire que la case represente un fils gauche/droit vide
    // et ainsi restituer un arbre tel qu'il etait en faisant un tabToBin apres
    std::vector<noeud> table;
    for (size_t i(0); i < _arbreBinaire.size(); ++i) {
        if(i == 0)
            table.push_back(_arbreBinaire[i].getNoeudOrigine());

        if(_arbreBinaire[i].getFilsGauche().getEstUnfils())
            table.push_back(_arbreBinaire[i].getFilsGauche());
        else {
            noeud null(666,0,0,0,0);
            table.push_back(null);
        }
        if(_arbreBinaire[i].getFilsDroit().getEstUnfils())
            table.push_back(_arbreBinaire[i].getFilsDroit());
        else{
            noeud null(666,0,0,0,0);
            table.push_back(null);
        }

    }

    return table;
}

*/






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


int arbreNaire::getIndNoeudOrigine(const int &aX,const int &oX,const int &aO,const int &oO) const{
    int i=0;
    for (const auto & r : _arbreNaire){
        if (aX==r.getNoeudOrigine()->getaX() && oX==r.getNoeudOrigine()->getoX() &&
                aO==r.getNoeudOrigine()->getaO() && oO==r.getNoeudOrigine()->getoO()) return i;
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

/*
void arbreNaire::binaireToNaire (const arbreBinaire &arbn){
    if (arbn.getArbreBinaire().size() != 0){
        for (unsigned int i(0); i <arbn.getArbreBinaire().size(); ++i){
            if (i==0){
                noeud origine = arbn.getArbreBinaire()[i].getNoeudOrigine();
                std::vector<std::shared_ptr<noeud>> fils;
                if(arbn.getArbreBinaire()[i].getFilsGauche().getEstUnfils()) {
                    std::shared_ptr<noeud> fg = arbn.getArbreBinaire()[i].getFilsGauche();
                    fils.push_back(fg);
                }
                relationNaire r (origine,fils);
                this->ajout(r);
            }
            else {
                if(arbn.getArbreBinaire()[i].getFilsDroit().getEstUnfils()){
                    noeud fd = arbn.getArbreBinaire()[i].getFilsDroit();
                    noeud recherche = arbn.getArbreBinaire()[i].getNoeudOrigine();
                    int j = this->getIndNoeudOrigine(recherche.getaX(),recherche.getoX(),recherche.getaO(),recherche.getoO());
                    this->_arbreNaire[j].setNoeudsDest(fd);
                }
                if (arbn.getArbreBinaire()[i].getFilsGauche().getEstUnfils()){
                    noeud origine = arbn.getArbreBinaire()[i].getNoeudOrigine();
                    noeud fg = arbn.getArbreBinaire()[i].getFilsGauche();
                    std::vector<noeud *> fils;
                    fils.push_back(&fg);
                    relationNaire r (origine,fils);
                    this->ajout(r);
                }
            }
        }
    }
}
*/
bool arbreNaire::isEmpty()
{
    return  (_arbreNaire.size() == 0);
}
/*
void arbreNaire::naireToBinaire(arbreBinaire &arbb)
{
    if (_arbreNaire.size() != 0){

        for (unsigned int i(0); i < _arbreNaire.size(); ++i){

            for (unsigned int j(0); j < _arbreNaire[i].getNoeudsDest().size(); ++j) {
                if(i == 0 && j == 0) {
                    noeud origin = _arbreNaire[i].getNoeudOrigine();
                    noeud fg = _arbreNaire[0].getNoeudsDest()[0];
                    bool trouve = false;
                    arbb.setFilsG(origin,fg,trouve);
                    if (!trouve){
                        relationBinaire r(origin);
                        r.setFilsGauche(fg);
                        arbb.ajout(r);
                    }
                }else {
                    if (j==0){
                        noeud origin = _arbreNaire[i].getNoeudOrigine();
                        noeud fg = _arbreNaire[i].getNoeudsDest()[j];
                        bool trouve = false;
                        arbb.setFilsG(origin,fg,trouve);
                        if (!trouve){
                            relationBinaire r(_arbreNaire[i].getNoeudOrigine());
                            r.setFilsGauche(_arbreNaire[i].*getNoeudsDest()[j]);
                            arbb.ajout(r);
                        }
                    }else {
                        noeud origin = _arbreNaire[i].getNoeudsDest()[j-1];
                        noeud fd = _arbreNaire[i].getNoeudsDest()[j];
                        bool trouve = false;
                        arbb.setFilsD(origin,fd,trouve);
                        if (!trouve){
                            relationBinaire r(_arbreNaire[i].getNoeudsDest()[j-1]);
                            r.setFilsDroit(_arbreNaire[i].getNoeudsDest()[j]);
                            arbb.ajout(r);
                        }
                    }
                }
            }
        }
    }
}

*/
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


