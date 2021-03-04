
#include <iostream>
#include "arbitre.hh"
#include "jeu.hh"
#include "brix.hh"
#include "montecarlo_brm/montecarlo.hh"


int main()
{
    /*
    //initialise la graine du générateur aléatoire
    std::srand(std::time(nullptr));

    // création de l'Arbitre (joueur jouant en 1er la premiere partie, joueur jouant en 2eme celle-ci , nombre de parties)
    Arbitre a (player::RAND, player::RAND2,2);
    // commence le challenge
    int r= a.challenge();
    return r;

    */

    montecarlo mtc;
    mtc.apprentissage(1);

}
