#pragma once
#include "arbre.hh"
#include "../joueurs/joueur_random.hh"
#include <thread>
#include <mutex>

class montecarlo {
    public:
        montecarlo() = default;
        void chargerFichier();
        void apprentissage(unsigned int nbrePartie);
        noeud selectionnerNoeud();
        result const & simulationPartie(Jeu & jeu, Joueur_Random &joueur);
        void rechercherCoup(Jeu & j, Brix &b);
        void enregistrerFichier();
    private:
        arbreNaire _arbre;
};
