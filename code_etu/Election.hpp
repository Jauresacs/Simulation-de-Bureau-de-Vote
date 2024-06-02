#ifndef ELECTION_HPP
#define ELECTION_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Personne.hpp"

using namespace elections;

/**
 * Election représente une élection avec un ensemble de candidats.
 *
 * Cette classe gère une élection, incluant l'enregistrement des candidats
 * et l'affichage de la liste des candidats. Les candidats sont stockés dans
 * un ensemble pour garantir l'unicité et sont triés automatiquement.
 */
class Election{
public:
/**
 * Constructeur pour créer une nouvelle élection.
 * \param nom Le nom de l'élection.
 * \param cads Représente l'ensemble des candidats participants a l'élection.
 */
Election(std::string nom, std::vector<Personne>& cads);

/**
 * Affiche la liste des candidats participant à l'élection.
 * Les candidats sont listés dans un ordre défini par l'ensemble.
 */
void afficherCandidats() const;

/**
 * Acesseur
 * \return renvoie le nom de l'élection.
*/
std::string nom() const;


private:
std::vector<Personne> candidats; 
std::string nomElection_; 
};

#endif