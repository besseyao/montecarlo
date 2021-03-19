#include "joueur_montecarlo_.hh"


Joueur_MonteCarlo_::Joueur_MonteCarlo_(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{}



/*char Joueur_MonteCarlo_::nom_abbrege() const
{
    return 'M';
}
*/

montecarlo mc;
arbreNaire Joueur_MonteCarlo_::_arbreFichier = mc.chargerFichier();


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

void Joueur_MonteCarlo_::initPlateau(){
    for (auto & ligne : _plateau)
            for (auto & colonne : ligne)
                colonne = '0';
}

int Joueur_MonteCarlo_::selectionneNoeud(const int &aX,const int &oX,const int &aO,const int &oO){
    int i = _arbreFichier.getIndNoeudOrigine(_id);
    for (const auto &a : _arbreFichier.getArbreNaire()[i].getNoeudsDest()){
        if (a->getaX()==aX && a->getoX()==oX && a->getaO()==aO && a->getoO()==oO)
            return a->getId();
    }
    return 0;
}

void Joueur_MonteCarlo_::chargerCoupAdverse(const board &b){
    int aX;
    int oX;
    int aO;
    int oO;
    for (int i=0;i<8;++i){
        for(int j=0;j<44;++j){
            if (b[i][j]=='x' && _plateau[i][j]=='0') {
                aX=i;
                oX=j;
                _plateau[i][j]='x';
            }
            else if (b[i][j]=='o' && _plateau[i][j]=='0') {
                aO=i;
                oO=j;
                _plateau[i][j]='o';
            }
        }
    }
    _id = this->selectionneNoeud(aX,oX,aO,oO);
    if (_id==0) _parcourArbreFini=true;

}

void Joueur_MonteCarlo_::selectionneMeilleurCoup(){

    int i = _arbreFichier.getIndNoeudOrigine(_id);
    int maxMin = 0;
    int id = 0;
    for (const auto &a : _arbreFichier.getArbreNaire()[i].getNoeudsDest()){
        if (_joueurX){
            //on choisit le coup avec le gain cumule le plus bas
            if (a->getNbrGainCumule()<maxMin) {
                maxMin=a->getNbrGainCumule();
                id=a->getId();
            }
        }
        else {
            //on choisit le coup avec le gain cumule le plus haut
            if (a->getNbrGainCumule()>maxMin) {
                maxMin=a->getNbrGainCumule();
                id=a->getId();
            }
        }
    }
    if (id==0) _parcourArbreFini=true;
    _id=id;

}

void Joueur_MonteCarlo_::recherche_coup(Jeu jeu, Brix &coup)
{
    if (premierCoup(jeu.plateau())){
        //on reinitialise les variables utiles pour la partie
        _joueurX=true;
        _parcourArbreFini=false;
        this->initPlateau();
        _id=0;
        //et on cherche le meilleur coup
        this->selectionneMeilleurCoup();
        int i = _arbreFichier.getIndNoeudOrigine(_id);

        coup.setAx(_arbreFichier.getArbreNaire()[i].getNoeudOrigine()->getaX());
        coup.setOx(_arbreFichier.getArbreNaire()[i].getNoeudOrigine()->getoX());
        coup.setAo(_arbreFichier.getArbreNaire()[i].getNoeudOrigine()->getaO());
        coup.setOo(_arbreFichier.getArbreNaire()[i].getNoeudOrigine()->getoO());

        //on le joue sur notre board
        _plateau[coup.getAx()][coup.getOx()]='x';
        _plateau[coup.getAo()][coup.getOo()]='o';

    }
    else if (deuxiemeCoup(jeu.plateau())){
        //on reinitialise les variables utiles pour la partie
        _joueurX=false;
        _parcourArbreFini=false;
        this->initPlateau();
        _id=0;

        //on charge le premier coup joué par l'adversaire
        this->chargerCoupAdverse(jeu.plateau());

        // on cherche le meilleur coup
        this->selectionneMeilleurCoup();
        int i = _arbreFichier.getIndNoeudOrigine(_id);

        coup.setAx(_arbreFichier.getArbreNaire()[i].getNoeudOrigine()->getaX());
        coup.setOx(_arbreFichier.getArbreNaire()[i].getNoeudOrigine()->getoX());
        coup.setAo(_arbreFichier.getArbreNaire()[i].getNoeudOrigine()->getaO());
        coup.setOo(_arbreFichier.getArbreNaire()[i].getNoeudOrigine()->getoO());

        //on le joue sur notre board
        _plateau[coup.getAx()][coup.getOx()]='x';
        _plateau[coup.getAo()][coup.getOo()]='o';


    }
    else {
        //on charge le dernier coup joué par l'adversaire
        this->chargerCoupAdverse(jeu.plateau());

        // on cherche le meilleur coup
        this->selectionneMeilleurCoup();

        //on selectionne le meilleur coup dans l'arbre si il a encore des solutions
        if (!_parcourArbreFini){
            int i = _arbreFichier.getIndNoeudOrigine(_id);

            coup.setAx(_arbreFichier.getArbreNaire()[i].getNoeudOrigine()->getaX());
            coup.setOx(_arbreFichier.getArbreNaire()[i].getNoeudOrigine()->getoX());
            coup.setAo(_arbreFichier.getArbreNaire()[i].getNoeudOrigine()->getaO());
            coup.setOo(_arbreFichier.getArbreNaire()[i].getNoeudOrigine()->getoO());

            //on le joue sur notre board
            _plateau[coup.getAx()][coup.getOx()]='x';
            _plateau[coup.getAo()][coup.getOo()]='o';
        }

        //si id=0 alors notre arbre de recherche n'a plus de solution, on decide de jouer un coup au hasard
        //methode de coup random copié de joueur_random
        else{
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

            //on le joue sur notre board
            _plateau[coup.getAx()][coup.getOx()]='x';
            _plateau[coup.getAo()][coup.getOo()]='o';
        }
    }
}






