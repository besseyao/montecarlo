#include "joueur_montecarlo_.hh"


Joueur_MonteCarlo_::Joueur_MonteCarlo_(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{}

arbreNaire Joueur_MonteCarlo_::_arbreFichier;

/*char Joueur_MonteCarlo_::nom_abbrege() const
{
    return 'M';
}
*/



bool Joueur_MonteCarlo_::premierCoup(const board &b)const{
    for (const auto & ligne : b)
        for (const auto & colonne : ligne)
            if (colonne != '0') return false;
    return true;
}

bool Joueur_MonteCarlo_::deuxiemeCoup(const board &b)const{
    int casePleine(0);
    for (const auto & ligne : b)
        for (const auto & colonne : ligne){
            if (colonne != '0') ++casePleine;
            if (casePleine >2) return false;
        }
    return true;
}



int Joueur_MonteCarlo_::selectionneNoeud(const int &aX,const int &oX,const int &aO,const int &oO){

    if (_arbreFichier.getArbreNaire()[_id].getNoeudsDest().size()==0)
        return 0;
    for (const auto &a : _arbreFichier.getArbreNaire()[_id].getNoeudsDest()){
        if (a->getaX()==aX && a->getoX()==oX && a->getaO()==aO && a->getoO()==oO)
            return a->getId();
    }
    return 0;
}


void Joueur_MonteCarlo_::selectionneMeilleurCoup(Brix &coup){

    if (_arbreFichier.getArbreNaire()[_id].getNoeudsDest().size()!=0){
        std::shared_ptr<noeud> noeud;
        noeud = _arbreFichier.getArbreNaire()[_id].getNoeudsDest()[0];
        for (const auto &a : _arbreFichier.getArbreNaire()[_id].getNoeudsDest()){
            if (_joueurX){
                //on choisit le coup avec le gain cumule le plus bas
                if (a->getNbrGainCumule()<noeud->getNbrGainCumule())
                    noeud=a;
            }
            else {
                //on choisit le coup avec le gain cumule le plus haut
                if (a->getNbrGainCumule()>noeud->getNbrGainCumule())
                    noeud = a;
            }

        }
        //std::cout << "coup choisi " << noeud->getId() << std::endl;
        _id = noeud->getId();
        coup.setAx(noeud->getaX());
        coup.setOx(noeud->getoX());
        coup.setAo(noeud->getaO());
        coup.setOo(noeud->getoO());
        coup.setDefinie(true);

    }
    else
        _parcourArbreFini=true;
}


void Joueur_MonteCarlo_::recherche_coup(Jeu jeu, Brix &coup)
{
    if (premierCoup(jeu.plateau())){
        //on reinitialise les variables utiles pour la partie
        _joueurX=true;
        _parcourArbreFini=false;
        _id=0;
        //et on cherche le meilleur coup
        this->selectionneMeilleurCoup(coup);


    }
    else if (deuxiemeCoup(jeu.plateau())){
        //on reinitialise les variables utiles pour la partie

        _joueurX=false;
        _parcourArbreFini=false;
        _id=0;

        //on charge le premier coup joué par l'adversaire
        _id=selectionneNoeud(coup.getAx(),coup.getOx(),coup.getAo(),coup.getOo());


        // on cherche le meilleur coup
        this->selectionneMeilleurCoup(coup);



    }
    else {


        //on charge le dernier coup joué par l'adversaire

        if (!_parcourArbreFini){
            _id = selectionneNoeud(coup.getAx(),coup.getOx(),coup.getAo(),coup.getOo());
            //std::cout << "coup choisi de l'IA : " << _id << std::endl;
            if (_id==0)
                _parcourArbreFini=true;
        }
/*
        std::cout << "mon plateau : "<< std::endl;
        int j;
        for(int i=MAX_HAUTEUR -1; i>=0; i--){
                std::cout<<'|';
                auto ligne =_plateau[i];
                for (auto colonne : ligne)
                    if (colonne == '0')
                        std::cout<< " |";
                    else if (colonne == 'x')
                        std::cout<< "x|";
                    else std::cout<< "o|";
                std::cout<<"  "<<i<<std::endl;
            }
        std::cout<<std::endl << '|';
        for (j=0 ; j<MAX_LARGEUR ; j++) {
                std::cout << j << '|';
            }
        std::cout<<std::endl;
*/
        //on selectionne le meilleur coup dans l'arbre si il a encore des solutions


        //on verifie si l arbre a donné une solution
        if (!_parcourArbreFini){
            this->selectionneMeilleurCoup(coup);
        }

        //si id=0 alors notre arbre de recherche n'a plus de solution, on decide de jouer un coup au hasard
        //methode de coup random copié de joueur_random
        if (_parcourArbreFini) {
            //std::cout << "notre arbre est vide on joue maintenant au hasard" << std::endl;
            std::vector<Brix> coupValide;
            Brix b_canditate;
            int tour = jeu.nbCoupJoue()+1;//la b_candidate devra être valide au tour auquel on va la jouer,i.e. au tour suivant
            int place_coup_joue, taille;
            int aX, oX, aO, oO; //coordonnees de la Brix que l'on va joué

            for (int i = 0; i<MAX_LARGEUR;i++) //i abscisse donc numero de colonne
                {
                    int j=0; //j ordonnee donc numero de ligne
                    while(j<MAX_HAUTEUR && jeu.plateau()[j][i]!='0') //dans plateau l'ordonnee en premier
                        {
                            j++;
                        }
                    if (j<MAX_HAUTEUR)//On est tombé sur une case vide, i.e. contenant '0'
                        {
                            //Cherchons des coups valides à partir de cette case vide.
                            b_canditate.setAllCoord(i,j ,i,j+1); //brix verticale dont le bottom est X
                            if (jeu.coup_licite(b_canditate,tour))
                                {
                                    coupValide.push_back(b_canditate);
                                }

                            b_canditate.setAllCoord(i,j+1,i,j); //brix verticale dont le bottom est O
                            if (jeu.coup_licite(b_canditate,tour))
                                {
                                    coupValide.push_back(b_canditate);
                                }

                            b_canditate.setAllCoord(i,j ,i+1,j); //brix horizontale commençant par X
                            if (jeu.coup_licite(b_canditate,tour))
                                {
                                    coupValide.push_back(b_canditate);
                                }

                            b_canditate.setAllCoord(i+1,j,i,j); //brix terminant commençant par X
                            if (jeu.coup_licite(b_canditate,tour))
                                {
                                    coupValide.push_back(b_canditate);
                                }
                            //fin des brix valide à cette abscisse et cette ordonnee
                        }
                }//fin du for.
            //std::cout<<coupValide<<std::endl;
            //On choisit un coup au hazard
            taille =coupValide.size();
            place_coup_joue= taille == 1 ?  0 : rand() % (taille-1);
            aO= coupValide[place_coup_joue].getAo();
            oO= coupValide[place_coup_joue].getOo();
            aX= coupValide[place_coup_joue].getAx();
            oX= coupValide[place_coup_joue].getOx();
            coup.setAllCoord(aX, oX, aO, oO);

        }
    }
}






