#include "joueur_montecarlo_.hh"


Joueur_MonteCarlo_::Joueur_MonteCarlo_(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{}



/*char Joueur_MonteCarlo_::nom_abbrege() const
{
    return 'M';
}
*/
void Joueur_MonteCarlo_::recherche_coup(Jeu jeu, Brix &coup)
{

}

/*
arbreNaire Joueur_MonteCarlo_::fileToArbre (std::vector<unsigned int> &v){
    std::ifstream monFlux("../data.txt");  //Ouverture d'un fichier en lecture

    if(monFlux)
    {
        int val;
        std::vector<unsigned int> v;

        while (monFlux >> val)
            v.push_back(val);

        monFlux.close();

        arbreBinaire a;
        a.tabToBin(v);
        arbreNaire arbre;
        arbre.binaireToNaire(a);
        //arbre.affichage();
        return arbre;
    }
    else
    {
        //c'est le premier coup
        arbreNaire arbre;
        return arbre;
    }
}



void Joueur_MonteCarlo_::recherche_coup(Jeu jeu, Brix &coup)
{

    ofstream monFlux("../data.txt");

    if(monFlux)  //On teste si tout est OK
    {
        //Tout est OK, on peut utiliser le fichier
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}


*/



