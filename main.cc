
#include <iostream>
#include "arbitre.hh"
#include "jeu.hh"
#include "brix.hh"



int main()
{
    //initialise la graine du générateur aléatoire
    std::srand(std::time(nullptr));
    /*
    // création de l'Arbitre (joueur jouant en 1er la premiere partie, joueur jouant en 2eme celle-ci , nombre de parties)
    Arbitre a (player::RAND, player::RAND2,2);
    // commence le challenge
    int r= a.challenge();
   return r;
    */
    montecarlo mc;
    Jeu jeu;
    mc.apprentissage(jeu,0);
    mc.getArbre().affichage();
    return 0;
}
