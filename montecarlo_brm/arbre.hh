#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "noeud.hh"
#include "relation.hh"
#include "utilitaire.hh"

class arbre {
    public:
        arbre() = default;
        arbre(std::vector<noeud> const & noeuds, std::vector<relation> relations);

        void decompresserArbre(std::string const & chemin);

        std::vector<noeud> getNoeuds() const;
        void ajouterNoeud(const noeud &noeud);

        std::vector<relation> getRelations() const;
        void ajouterRelation(const relation &relations);

        std::vector<noeud>::iterator getNoeudById(std::string const & id);
        std::vector<noeud>::iterator getNoeudByPlateau(board const & b);

        bool noeudFilsExiste(noeud const & n, board const & board) const;

        std::vector<noeud> getFilsRelationByOrigine (noeud const & n) const;

        bool ajouterFilsSiRelationExiste(noeud const & origine, noeud const & destination);

        bool noeudFilsExisteBrix(noeud const & parent, Brix const & b){
            std::vector<noeud> fils = getFilsRelationByOrigine(parent);

            for(auto & f : fils)
                if(getNoeudById(f.getId())->getBrix().getAo() == b.getAo() && getNoeudById(f.getId())->getBrix().getAx() == b.getAx()
                        && getNoeudById(f.getId())->getBrix().getOo() == b.getOo() && getNoeudById(f.getId())->getBrix().getOx() == b.getOx())
                    return true;
            return false;
        }

        void updateBranche(std::string const & id_noeud , int gain);

        void calculQUBC(std::string const &  noeud_recherche);
        std::string getNoeudParent(std::string const & id_noeud);
        void sauvegarderArbre() const;

private:
        std::vector<noeud> _noeuds;
        std::vector<relation> _relations;
};
