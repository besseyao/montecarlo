#include "montecarlo.hh"

arbreNaire montecarlo::getArbre() const{
    return _arbre;
}

void montecarlo::enregistrerFichier() const{
    std::ofstream monFlux("../data.txt");  //On essaye d'ouvrir le fichier

    if(monFlux)  //On teste si tout est OK
    {
        arbreBinaire arbb;
        _arbre.naireToBinaire(arbb);
        std::vector<std::shared_ptr<noeud>> tab = arbb.binToTab();
        for (const auto &i : tab){
            monFlux << i->getId() << " " << i->getaX() << " " << i->getoX() << " " << i->getaO() << " " << i->getoO() << " "
                    << i->getEstOuvert() << " " << i->getEstUnfils() << " " << i->getNbrFoisTraverse() << " " << i->getNbrGainCumule() << std::endl;
        }
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
}

//nécessaire pour lire les données du fichier
std::vector<int> montecarlo::explode( const std::string &delimiter, const std::string &str)const {
    std::vector<std::string> arr;
    std::vector<int> exp;

    int strleng = str.length();
    int delleng = delimiter.length();
    if (delleng==0){
        return exp;
    }
    int i=0;
    int k=0;
    while( i<strleng )
    {
        int j=0;
        while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
            j++;
        if (j==delleng)
        {
            arr.push_back(  str.substr(k, i-k) );
            i+=delleng;
            k=i;
        }
        else
        {
            i++;
        }
    }
    arr.push_back(  str.substr(k, i-k) );

    for (const auto & v : arr){
        exp.push_back(std::stoi(v));
    }

    return exp;
}


arbreNaire montecarlo::chargerFichier()const{
    std::ifstream monFlux("../data.txt");  //Ouverture d'un fichier en lecture

    if(monFlux)
    {
        std::vector<std::shared_ptr<noeud>> v;
        std::string ligne;
        while (std::getline(monFlux,ligne)){
            std::vector<int> e = this->explode(" ",ligne);
            std::shared_ptr<noeud> val(new noeud(e[0],e[1],e[2],e[3],e[4]));
            val->setEstOuvert(e[5]);
            val->setEstUnfils(e[6]);
            val->setNbrFoisTraverse(e[7]);
            val->setNbrGainCummule(e[8]);
            v.push_back(val);
        }

        monFlux.close();

        arbreBinaire a;
        a.tabToBin(v);
        arbreNaire arbre;
        arbre.binaireToNaire(a);
        return arbre;
    }
    else
    {
        //c'est le premier coup
        arbreNaire arbre;
        return arbre;
    }
}


//methode copié collé de Joueur_Random::recherche_coup
void montecarlo::coupRandom (Jeu jeu,Brix &coup) const{
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

void montecarlo::simulePartie (Jeu &jeu){
    Brix coup;
    while (!jeu.fini()){
        coupRandom(jeu,coup);
        jeu.joue(coup);
    }
    if (jeu.partie_O()) {
        //std::cout << "les O ont gg ! " << std::endl;
        _arbre.completeArbre(1);
    }
    else if (jeu.partie_X()) {
        //std::cout << "les X ont gg ! " << std::endl;
        _arbre.completeArbre(-1);
    }
    else if (jeu.partie_nulle()){
        //std::cout << "match nul! " << std::endl;
        _arbre.completeArbre(0);
    }
}

std::vector<Brix> montecarlo::coupsPossibles (const Jeu &jeu)const{
    std::vector<Brix> coupValide;
    Brix b_canditate;
    int tour = jeu.nbCoupJoue()+1;//la b_candidate devra être valide au tour auquel on va la jouer,i.e. au tour suivant

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
        }
    return coupValide;
}


void montecarlo::apprentissage (Jeu &jeu, const int &nbParties) {
    // construction de la racine de l'arbre
    int id = 0;
    auto racine = std::make_shared<noeud>(0,0,0,0,0);
    id++;
    std::vector<std::shared_ptr<noeud>> vide;
    relationNaire r(racine,vide);
    _arbre.ajout(r);
    int NbSimulation=0;
    //premier acroissement pas de descente, on roll out directement
    simulePartie(jeu);
    int i;
    int j;
    //ensuite on deroule l'algorithme avec descente/growth/roll out
    while (NbSimulation<nbParties){
        _arbre.setArbreNaire()[0].setNoeudOrigine()->setEstOuvert(true);
        i=0;
        jeu.reset();
        //1ere et deuxieme etape, la descente et le growth
        bool growth = false;
        while (!growth)
        {
            //on regarde le nombre de coup possibles a cette etape
            std::vector<Brix> cp = coupsPossibles(jeu);
            //si les noeuds de l'arbre n'ont pas deja tous les coups possibles a cette etape alors on peut growth
            if (!_arbre.tousExplores(cp,i)){
                j=0;
                //on selectionne un coup qui n'est pas dans l'arbre
                while (_arbre.appartient(cp[j],i))
                    ++j;
                //growth
                auto fils = std::make_shared<noeud>(id,cp[j].getAx(),cp[j].getOx(),cp[j].getAo(),cp[j].getOo());
                id++;
                //ajout en tant que noeud dans l'arbre
                std::vector<std::shared_ptr<noeud>> vide;
                relationNaire r(fils,vide);
                _arbre.ajout(r);
                //ajout en tant que fils
                _arbre.ajoutfils(i,fils);
                //on joue le coup dans le plateau
                jeu.joue(cp[j]);
                //std::cout << jeu;
                growth=true;
            }
            //sinon on fait la selection exploration/enfoncement selon le calcul de l'UBC
            else {
                //on selectionne le coup ayant l' UBC le plus haut
                int indNoeud = _arbre.rechercheNoeudDescente(i);
                //on se place donc au niveau du nouveau noeud choisi, donc on joue le coup
                int aX=_arbre.getArbreNaire()[i].getNoeudsDest()[indNoeud]->getaX();
                int oX=_arbre.getArbreNaire()[i].getNoeudsDest()[indNoeud]->getoX();
                int aO=_arbre.getArbreNaire()[i].getNoeudsDest()[indNoeud]->getaO();
                int oO=_arbre.getArbreNaire()[i].getNoeudsDest()[indNoeud]->getoO();
                _arbre.setArbreNaire()[i].setNoeudsDest()[indNoeud]->setEstOuvert(true);
                //on joue le coup dans le plateau
                Brix coup (aX,oX,aO,oO);
                jeu.joue(coup);
                //on se place dans l'arbre au niveaux du coup choisit pour la prochaine itération
                i = _arbre.getArbreNaire()[i].getNoeudsDest()[indNoeud]->getId();
            }
        }
        //rollout
        simulePartie(jeu);
        NbSimulation++;
        //on remonte l'information ce qui est fait avec la methode simule partie
     }

}

