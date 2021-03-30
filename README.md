# montecarlo

## git clone https://github.com/besseyao/montecarlo.git : pour telecharger
## git checkout tmp pour avoir le contenu de la branche
## executer le programme, vous pouvez apporter une modification sur le nombre de partie a jouer pour apprendre dans le fichier main.cc
## dans votre terminal, faites cd ../build-DISTRIBUTION_CARO-Desktop-Debug pour acceder au repertoire du build du projet
## faites la commande ls, vous retrouverz un fichier apprentissage.txt
## ou acceder tout simplement en utilisant l'utilitaire fichier
## le fichier est sous ce format :

C ................................. // Premier commentaire pour le nombre de noeud
C ................................. // D_euxieme commentaire pour le nombre de relation
id_du_noeud * plateau_du_noeud * nbre_de_gain_cumule * nbre_de_fois_traverse * [ brix_joué (Optionnel)]
# // separateur des noeud et des relation
noeud_origine noeud_fils_1 noeud_fils_2 ... // Liste des relations