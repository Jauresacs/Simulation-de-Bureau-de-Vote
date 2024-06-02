#ifndef ISOLOIR_HPP
#define ISOLOIR_HPP

#include <iostream>
#include <string>
#include "Action.hpp"
#include "Electeur.hpp"
#include "TableDeVote.hpp"

using namespace elections;
/**
 * Isoloir représente un isoloir dans un bureau de vote.
 *
 * Cette classe gère le processus de vote d'un électeur dans un isoloir,
 * incluant l'entrée, le choix du bulletin, et la sortie de l'isoloir.
 */
class Isoloir : public Action{
public:
/**
 * Constructeur pour initialiser un isoloir avec une durée spécifiée et
 * une probabilité qu'un bulletin soit nul.
 * 
 * \param duree La durée maximale que l'électeur peut passer dans l'isoloir.
 * \param pn La probabilité qu'un électeur rende son bulletin nul.
 * \param dp distance se sensibilité politique entre le candidat et l'électeur.
 */
Isoloir(float pn, int duree, int dp);

/**
 * Simule le choix d'un bulletin par l'électeur. Cela peut inclure la sélection
 * d'un candidat ou la décision de rendre le bulletin nul selon la probabilité pn.
 */
void choisirBulletin();

/**
* Méthode dérivée permettant l'entrer de lélecteur dans l'espace.
* \param e Electeur présent dans l'espace.
*/
void entrer(Electeur& e) override;

/**
* Méthode dérivée permettant la sortie de lélecteur dans l'espace.
*/
void sortir() override;

/**
 * Méthode permettant la vérification du temps
*/
void gestionTemps() override;

/**
 * Acesseur
 * \return true si l'isoloir est occupé et false si non.
*/
bool estOccupe() const;


private:
bool isoloirOccupe_; 
int idIsoloir_; 
int distance_;
float probabiliteNulle_;
int dureeIsoloir_; 
Electeur* electeurPresent_;
static int compteurId_;
};

#endif
