#pragma once

#include "../arbre_binaire_naire/montecarlo.hh"
#include "joueur.hh"
#include "joueur_random.hh"

using ligne=std::array<char,MAX_LARGEUR>;
using board=std::array<ligne,MAX_HAUTEUR>;



class Joueur_MonteCarlo_ : public Joueur
{
public:
  Joueur_MonteCarlo_(std::string nom, bool joueur);
  //char nom_abbrege() const override;

  static arbreNaire _arbreFichier;
  void recherche_coup(Jeu, Brix & coup) override;
  void chargerArbre();
  bool premierCoup (const board &b)const;
  bool deuxiemeCoup (const board &b)const;
  void chargerCoupAdverse(const board &b);
  void selectionneMeilleurCoup(Brix &coup);
  int selectionneNoeud(const int &aX, const int &oX, const int &aO, const int &oO);

private:
  bool _joueurX;
  bool _parcourArbreFini;
  int _id;
};
