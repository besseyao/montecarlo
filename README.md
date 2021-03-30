# projet_si_MBR

 - Télécharger [le fichier d'apprentissage](https://drive.google.com/file/d/1hJB2_OtO8O_IJSqNFNAFKJXL8v0cObta/view?usp=sharing) et ajouter le a la racine
 - Les fichiers supplémentaire nécessaires au joueur "Joueur_MonteCarlo_MBR" sont dans le dossier "montecarlo".

> IMPORTANT : Avant toute chose, s'assurer que dans le fichier "arbitre.hh" il y ait bien :
 

    include "joueurs/joueur_montecarlo_MBR.hh"

> IMPORTANT : pour charger l'arbre dans le fichier "data.txt" -> dans le main tapper ces 3 lignes :

    montecarlo mc;
    Jeu jeu;
    Joueur_MonteCarlo_MBR::_arbreFichier = mc.chargerFichier();

> pour créer un arbre et le mettre dans le fichier "data.text" -> dans le main tapper ces 3 lignes :

    montecarlo mc;
    Jeu jeu;
    mc.apprentissage(jeu,int nbParties);

> si il faut changer le nom ou l'emplacement du fichier a charger : se placer dans le fichier "montecarlo.cc" puis dans la méthode "chargerFichier()" : modifier la ligne 29 :

    std::ifstream monFlux("path");

> si il faut changer le nom ou l'emplacement du fichier a créer : se placer dans le fichier "montecarlo.cc" puis dans la méthode "enregistrerFichier() " : modifier la ligne 10 : 

    "std::ofstream monFlux("path");"

> Le temps pour un coup a été modifié à 10 ms (temps pour le tournoi) , si il faut le modifier : se placer dans le fichier "arbritre.hh" et modifier la ligne 16 :

    const int TEMPS_POUR_UN_COUP(X);

> de meme pour le temps entre deux parties : dans le fichier arbritre.cc" modifier dans la méthode challenge et modifier la ligne 99 :

    std::this_thread::sleep_for (std::chrono::milliseconds(X))
