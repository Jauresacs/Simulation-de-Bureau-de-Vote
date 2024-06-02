/**
 * \file main.cpp
 * \author Laurent Granvilliers
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "Personne.hpp"
#include "Electeur.hpp"
#include "Bulletin.hpp"
#include "Bureau.hpp"
#include "Election.hpp"
#include "Isoloir.hpp"
#include "EspaceIsoloirs.hpp"

using namespace elections;

int main(void)
{
   // initialisation du générateur de nombres aléatoires
   std::srand(std::time(nullptr));

   std::vector<Electeur*> vp = {
      new Electeur("A", "bic", 7),
      new Electeur("B", "gad", 9),
      new Electeur("C", "ann", 2),
      new Electeur("D", "pol", 5),
      new Electeur("E", "lam", 1),
      new Electeur("F", "bul", 10),
      new Electeur("G", "yap", 3),
      new Electeur("X", "nel", 5),
      new Electeur("Y", "rik", 2),
      new Electeur("Z", "pat", 8)
   };
    std::vector<Personne>liste;

   for (size_t i = 7; i < vp.size(); i++) {
      liste.push_back(*vp[i]);
   }

   TableDeVote tableDeVote(4, *vp[2], liste);
   EspaceIsoloirs espaceIsoloir(0.15, 3, 6, 3);
   Election election("Euro 2024", liste);
   TableDeDecharge tableDeDecharge(3, vp.size(), 0.35, liste);
   Bureau bureau(20, tableDeDecharge, election, tableDeVote, espaceIsoloir);

   for(const auto& electeur : vp)
   {
      bureau.ajouterElecteur(electeur); 
   }

   bureau.affichage();
   bureau.miseAJour();

   return 0;
}
