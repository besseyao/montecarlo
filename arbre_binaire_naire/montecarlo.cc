#include "montecarlo.hh"

void montecarlo::apprentissage(unsigned int nbrePartie)
{
    Jeu jeu;
    Joueur_Random joueur("mc", false);

    while(nbrePartie > 0){
        jeu.reset();

        // Selectionner le noeud //
        // Regarder les coups possibles selectionner un et le mettre dans l'arbre

        simulationPartie(jeu, joueur);

        // enregistrer les info et faire grossir les noeuds concernés (le noeud actuel ses noeud parents)

    }
}

const result &montecarlo::simulationPartie(Jeu &jeu,Joueur_Random &joueur)
{
    bool try_lock = false;
    unsigned int tour(0);
    Brix brix;
    std::mutex coup_mutex;

    while(!jeu.fini()){
        tour++;
        brix.setDefinie(false);

        (tour%2)? joueur.setJoueur(true) : joueur.setJoueur(false);

        coup_mutex.unlock();

        std::thread thread_joueur(&Joueur::jouer, joueur, jeu, std::ref(brix), std::ref(coup_mutex));

        std::this_thread::sleep_for (std::chrono::milliseconds(TEMPS_POUR_UN_COUP));
        //        std::this_thread::sleep_for (std::chrono::seconds(TEMPS_POUR_UN_COUP));



        if (!coup_mutex.try_lock()) {
                std::cerr <<  std::endl << "mutex non rendu " << std::endl;
                try_lock = true;
            }
        else if(brix.getDefinie() == false) {
                std::cerr << "coup invalide Brix non définie" << std::endl;
            }
        else if(!jeu.coup_licite(brix,tour)) {
                std::cerr << "coup invalide " << brix << std::endl;
            }

        thread_joueur.detach();

        if(try_lock ||
                (brix.getDefinie() == false) ||
                !jeu.coup_licite(brix,tour))
            {
                if(jeu.partie_nulle())
                    {
                        std::cout << "partie nulle (" << tour << ")" << std::endl;
                        return result::NULLE;
                    }
                if(tour%2)
                    {
                        // std::cout << joueur->nom() <<" gagne ! Nombre de tours : " << tour << std::endl;
                        return result::O; // joueur jouant en 2eme gagne
                    }
                else
                    {
                        // std::cout << joueur->nom() <<" gagne ! Nombre de tours : " << tour << std::endl;
                        return result::X; // joueur jouant en 1er gagne
                    }
            }
        // On joue le coup, on l'affiche et on affiche le plateau
        jeu.joue(brix);
        // std::cout << ((tour%2) ? joueur1->nom_abbrege() : _joueur2->nom_abbrege())<<" "<< _coups[_numero_partie-1]
           //       << std::endl << _jeu << std::endl;


    }
}
