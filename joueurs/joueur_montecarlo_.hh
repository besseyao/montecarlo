#pragma once


#include "joueur.hh"
#include "../montecarlo_brm/arbre.hh"


class Joueur_MonteCarlo_ : public Joueur
{
public:
  Joueur_MonteCarlo_(std::string nom, bool joueur);
  //char nom_abbrege() const override;

  void recherche_coup(Jeu, Brix & coup) override;
  arbre _arbre; // memoire du joueur montecarlo
};
