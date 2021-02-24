#pragma once

#include "../arbre_binaire_naire/montecarlo.hh"
#include "joueur.hh"
#include "joueur_random.hh"


class Joueur_MonteCarlo_ : public Joueur
{
public:
  Joueur_MonteCarlo_(std::string nom, bool joueur);
  //char nom_abbrege() const override;

  void recherche_coup(Jeu, Brix & coup) override;

  //arbreNaire fileToArbre (std::vector<unsigned int> &v)
};
