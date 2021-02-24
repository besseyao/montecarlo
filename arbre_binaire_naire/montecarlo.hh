#pragma once
#include "../jeu.hh"
#include "arbre.hh"

class montecarlo {
    public:
        montecarlo() = default;
        arbreNaire getArbre () const;
        void chargerFichier();
        void enregistrerFichier();
        void coupRandom (Jeu jeu,Brix &coup)const;
        std::vector<Brix> coupsPossibles (const Jeu &jeu) const;
        void simulePartie (Jeu &jeu);
        void apprentissage(Jeu &jeu,const int &nbParties);
    private:
        arbreNaire _arbre;
};
