#pragma once
#include "../jeu.hh"
#include "arbre.hh"
#include <fstream>
#include <sstream>
#include <utility>

class montecarlo {
    public:
        montecarlo() = default;
        arbreNaire getArbre () const;
        arbreNaire chargerFichier();
        void enregistrerFichier()const;
        void coupRandom (Jeu jeu,Brix &coup)const;
        std::vector<Brix> coupsPossibles (const Jeu &jeu) const;
        void simulePartie (Jeu &jeu);
        bool etatFusionnable (const int &indNoeudOrigine,const Jeu & jeu,const Brix &coup);
        void apprentissage(Jeu &jeu,const int &nbParties);

    private:
        arbreNaire _arbre;
};
