#pragma once
#include <string>
#include <iostream>

enum class resultat
{
    ND,
    DEFAITE,
    VICTOIRE,
    NUL
};

class noeud
{
    public:
        noeud() =default;
        noeud(const unsigned int &id);
        noeud(noeud const & n);

        unsigned int getId() const ;
        bool getEstUnfils() const ;
        void setEstUnfils(const bool &rep);

    private:
        unsigned int _id;
        bool _estUnFils;
        float _qubc;
        unsigned int _nbreFoisTraverse;
        unsigned int _nbreGainCummule;
        bool _estOuvert;
        resultat _valeur;

        //  -- Prevue pour la suite

        /*
         *  std::string _nom;
         * int _nbreGainCummule;
         * int _nbreFoisTraverse;
         * bool _estOuvert;
         */
};
