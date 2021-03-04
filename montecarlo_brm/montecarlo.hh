#pragma once
#include "arbre.hh"
#include "../joueurs/joueur_random.hh"
#include <thread>
#include <mutex>

class montecarlo {
    public:
        montecarlo();
        arbre getArbre () const;
        void chargerFichier();
        void enregistrerFichier();
        void coupRandom (Jeu jeu,Brix &coup)const;
        std::vector<Brix> coupsPossibles (const Jeu &jeu) const;
        resultat simulationPartie(Jeu &jeu, Joueur_Random &joueur);
        // void apprentissage(Jeu &jeu,const int &nbParties);
        void apprentissage(int nbreParties);
private:
        arbre _arbre;
};
