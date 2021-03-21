
#include <iostream>
#include "arbitre.hh"
#include "jeu.hh"
#include "brix.hh"
#include "joueurs/joueur_montecarlo_.hh"


int main()
{
    //initialise la graine du générateur aléatoire
    std::srand(std::time(nullptr));

    montecarlo mc;
    Jeu jeu;
    //mc.apprentissage(jeu,300000);
    //mc.enregistrerFichier();
    Joueur_MonteCarlo_::_arbreFichier = mc.chargerFichier();

    //Joueur_MonteCarlo_ m1("lol",false);
    /*Joueur_Random r1("connard",true);
    jeu.reset();
    Brix coup;
    std::cout << "la partie commence" << std::endl;
    while (!jeu.fini()){
        m1.recherche_coup(jeu,coup);
        jeu.joue(coup);
        std::cout << jeu << std::endl;
        r1.recherche_coup(jeu,coup);
        jeu.joue(coup);
    }
    if (jeu.partie_O()) std::cout << "GG" << std::endl;
    else std::cout << "LOOSER" << std::endl;
*/
    //if (mc.getArbre().sontEgaux(m1._arbreFichier.getArbreNaire())) std::cout << "OUIIII";
    //else std::cout << "NOOON";


    // création de l'Arbitre (joueur jouant en 1er la premiere partie, joueur jouant en 2eme celle-ci , nombre de parties)
    Arbitre a (player::RAND,player::M_1,100);
    // commence le challenge
    int r= a.challenge();
   return r;

    return 0;

}
