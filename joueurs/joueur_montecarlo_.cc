#include "joueur_montecarlo_.hh"


Joueur_MonteCarlo_::Joueur_MonteCarlo_(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{
    // inititialiser arbre a partir d'un fichier
}



/*char Joueur_MonteCarlo_::nom_abbrege() const
{
    return 'M';
}
*/
void Joueur_MonteCarlo_::recherche_coup(Jeu jeu, Brix &coup)
{
    // verifier si jeu.plataeau exist dans arbre
    // si oui , jouer le brix du fils qui a le plus grand qubc
    // jouer comme random
}
