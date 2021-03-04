#include "arbre.hh"
#include <iostream>

arbre::arbre(const std::vector<noeud> &noeuds, std::vector<relation> relations) :_noeuds(noeuds), _relations(relations){}

void arbre::decompresserArbre(const std::string &chemin)
{
    std::string contenuFichier;
    unsigned int nbre_noeud(0), nbre_relation(0), itt(1);

    std::ifstream fichier("apprentissage.txt");

    while (getline (fichier, contenuFichier)) {
        if(itt == 1)
            nbre_noeud = std::stoi(utilitaire::explode(contenuFichier, ' ')[5]);
        else if(itt == 2)
            nbre_relation = std::stoi(utilitaire::explode(contenuFichier, ' ')[5]);
        else if(itt > 2 && itt <= (nbre_noeud + 2)){
            noeud n(contenuFichier);
            ajouterNoeud(n);
        }
        else if(itt > (nbre_noeud + 3) && itt <= (nbre_noeud + nbre_relation + 3)){

            std::vector<std::string> rel = utilitaire::explode(contenuFichier, ' ');

            relation r;
            auto origine = getNoeudById(rel[0]);
            r.setOrigine(*origine);

            for(size_t i(1); i < rel.size(); i++)
                r.ajouterDestination(*getNoeudById(rel[i]));
            ajouterRelation(r);

        }

        itt++;
    }
    noeud::setCpt(_noeuds.size()+1);
    fichier.close();
}

std::vector<noeud> arbre::getNoeuds() const
{
    return _noeuds;
}

void arbre::ajouterNoeud(const noeud &noeud)
{
    _noeuds.push_back(noeud);
}

std::vector<relation> arbre::getRelations() const
{
    return _relations;
}

void arbre::ajouterRelation(const relation &relations)
{
    _relations.push_back(relations);
}

std::vector<noeud>::iterator arbre::getNoeudById(const std::string &id)
{
    for (auto i (_noeuds.begin()); i!=_noeuds.end(); ++i)
        if ((*i).getId() == id)
            return i;
    return _noeuds.end();
}

std::vector<noeud>::iterator arbre::getNoeudByPlateau(const board &b)
{
    for (auto i (_noeuds.begin()); i!=_noeuds.end(); ++i)
        if ((*i).plateau() == b)
            return i;
    return _noeuds.end();
}

bool arbre::noeudFilsExiste(noeud const & n, board const & board) const
{
    std::vector<noeud> fils = getFilsRelationByOrigine(n);

    for(auto & n : fils)
        if(n.plateau() == board)
            return true;
    return false;
}

std::vector<noeud> arbre::getFilsRelationByOrigine(const noeud &n) const {
    std::vector<noeud> vn;
    for(auto &r : _relations)
        if(r.origine().getId() == n.getId())
            return r.destination();
    return vn;
}

bool arbre::ajouterFilsSiRelationExiste(const noeud &origine, const noeud &destination){
    for (auto &r : _relations) {
        if (r.origine().getId() == origine.getId()){
            r.ajouterDestination(destination);
            return  true;
        }
    }
    return false;
}

void arbre::sauvegarderArbre() const
{
    std::ostringstream os;

    os << "C nombre de noeuds : " << _noeuds.size() << "\n";
    os << "C nombre de relations : " << _relations.size() << "\n";

    for (auto & n : _noeuds)
        os << n.showNoeud() << "\n";

    os << "#\n";

    for (auto & r : _relations)
        os << r.showRelation() << "\n";

    std::ofstream fichier("apprentissage.txt");

    // Ecrire l'apprentissage dans le fichier
    fichier << os.str();
    fichier.close();
}
