#include "montecarlo.hh"

montecarlo::montecarlo()
{
    std::fstream fichier;

    fichier.open("apprentissage.txt");

    if (!fichier.fail()) {
        _arbre.decompresserArbre("apprentissage.txt");
    }
}

resultat montecarlo::simulationPartie(Jeu &jeu,Joueur_Random &joueur)
{
    unsigned int tour(0);
    Brix brix;
    std::mutex coup_mutex;
    bool n_noeud(false);

    std::string old;

    while(!jeu.fini()){

        if(tour == 0  && _arbre.getNoeuds().size() == 0){
            noeud n;
            n.setPlateau(jeu.plateau());
            _arbre.ajouterNoeud(n);
            n_noeud = true;
        }
        else if(tour == 0  && _arbre.getNoeuds().size() > 0){

            old = _arbre.getNoeudByPlateau(jeu.plateau())->getId();
            std::cout << "le nouveau old est : " << old ;
        }
        else if(_arbre.noeudFilsExiste(*_arbre.getNoeudById(old), jeu.plateau())){
            old = _arbre.getNoeudByPlateau(jeu.plateau())->getId();
            std::cout << "le nouveau old est : " << old ;
        }
        /*
        * On verifie si nous avons ajouté un nouveau noeud
        * Si non, on verifie si le noeud actuel exist parmi les enfants du noeud precedent
        * Si non, on l'ajoute
        */

        else if(!n_noeud && !_arbre.noeudFilsExiste(*_arbre.getNoeudById(old), jeu.plateau())){
            noeud n;
            n.setPlateau(jeu.plateau());

            // On enregistre le nouveau brix if est defini
            if(brix.getDefinie()) n.setBrix(brix.getAx(), brix.getOx(), brix.getAo(), brix.getOo());

            _arbre.ajouterNoeud(n);
            n_noeud = true;

            /*
            * Si oui on cré une realtion
            */

            if (!_arbre.ajouterFilsSiRelationExiste(*_arbre.getNoeudById(old), n)){
                relation r;
                r.setOrigine(*_arbre.getNoeudById(old));
                r.ajouterDestination(*_arbre.getNoeudById(n.getId()));
                _arbre.ajouterRelation(r);
            }

        }

        bool try_lock = false;
        tour++;
        brix.setDefinie(false);

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
                        return resultat::NUL;
                    }
                if(tour%2)
                    {
                        std::cout << joueur.nom() <<" gagne ! Nombre de tours : " << tour << std::endl;
                        return resultat::DEFAITE; // joueur jouant en 2eme gagne
                    }
                else
                    {
                        std::cout << joueur.nom() <<" gagne ! Nombre de tours : " << tour << std::endl;
                        return resultat::VICTOIRE; // joueur jouant en 1er gagne
                    }
            }

        // On joue le coup, on l'affiche et on affiche le plateau
        jeu.joue(brix);

        std::cout << ((tour%2) ? "joueur1" : "joueur2")<<" "<< brix
                  << std::endl << jeu << std::endl;

    }

    if (jeu.partie_nulle())
        {
            std::cout << std::endl << "Partie nulle" << std::endl;
            return resultat::NUL;
        }
    else if (jeu.partie_X())
        {
            std::cout << std::endl << "Victoire. Nombre de tours : " << tour << std::endl;
            return resultat::VICTOIRE;
        }
    else if (jeu.partie_O())
        {
            std::cout << std::endl << "Defaite. Nombre de tours : " << tour << std::endl;
            return resultat::DEFAITE;
        }

    return resultat::ND;
}

void montecarlo::apprentissage(int nbreParties)
{
    Jeu jeu;
    Joueur_Random joueur("apprentit", false);

    while(nbreParties > 0){
        jeu.reset();
        std::cout << nbreParties << "\n";
        // Selectionner le noeud //
        // Regarder les coups possibles selectionner un et le mettre dans l'arbre
        resultat res = simulationPartie(jeu, joueur);

        if (res == resultat::ND) {
            std::cerr << "Alerte bug. Sauvez votre terminal et prévenez Me Devred. Merci. " << std::endl;
            // return 1;
        }
        else if (res == resultat::DEFAITE) { // Nous considerons ce cas comme etant une defaite
            _arbre.updateBranche(_arbre.getNoeuds().back().getId(), -1);
            std::cout << "- 1 sur dernier coup enregistre : " << _arbre.getNoeuds().back().getId();
        }
        else if (res == resultat::VICTOIRE) { // Nous considerons ce cas comme etant une victoire
            _arbre.updateBranche(_arbre.getNoeuds().back().getId(), 1);
            std::cout << "+ 1 sur dernier coup enregistre : " << _arbre.getNoeuds().back().getId();
        }
        else if (res == resultat::NUL){ // Nous considerons ce cas comme etant un null
            _arbre.updateBranche(_arbre.getNoeuds().back().getId(), 0);
            std::cout << "Rien sur dernier coup enregistre : " << _arbre.getNoeuds().back().getId();
        }

        nbreParties--;

        // enregistrer les info et faire grossir les noeuds concernés (le noeud actuel ses noeud parents)

    }
    std::this_thread::sleep_for (std::chrono::milliseconds(2500)); // temps de latence entre deux parties
    _arbre.sauvegarderArbre();

}
