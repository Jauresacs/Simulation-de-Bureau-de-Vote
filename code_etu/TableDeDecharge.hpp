#ifndef TABLEDEDECHARGE_HPP
#define TABLEDEDECHARGE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Action.hpp"
#include "EspaceIsoloirs.hpp"
#include "Electeur.hpp"


using namespace elections;
/**
 * Une table de décharge est un espace où les bulletins de vote sont organisés 
 * et disponibles pour les électeurs, triés par candidat participant à l'élection. 
 * La règle stipulant que cet espace ne peut être occupé que par une seule personne 
 * à la fois est contrôlée par le booléen `occupeDecharge`, qui vérifie si la table 
 * de décharge est actuellement libre. De plus, la durée `dureeDecharge` détermine le temps 
 * maximum qu'un électeur est autorisé à passer dans cet espace pour sélectionner 
 * ses bulletins.
 */

class TableDeDecharge : public Action{
public:
/**
* Constructeur pour initialiser la table avec les bulletins.
* \param duree  Duree que doit passer une électeur dans cet espace.
* \param nombreDeCandidats Nombre de candidats pour l'élection.
* \param nombreDelecteurs  Nombre d'électeur pour le vote électoral.
* \param pb Représente la probabilité de prendre un bulletin blanc sur la 
* table de décharge.
*/
TableDeDecharge(int duree, int nombreDelecteurs, float pb, std::vector<Personne>& candidats);

/**
* Simule la sélection des bulletins par l'électeur.
*/
void prendreBulletins();

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
 * Affiche les bulletins disponibles à la table de décharge.
 */
void affichageBulletin() const;

/**
 * Traite la file d'attente des électeurs en attente de passer à la table de décharge, permettant à chaque électeur d'entrer dès qu'elle est libre.
 */
void traiterFileAttente();

/**
 * Vérifie si la table de décharge est actuellement occupée par un électeur.
 * \return true si la table est occupée, false sinon.
 */
bool estOccupe() const;

/**
 * Obtient une référence à l'électeur actuellement à la table de décharge.
 * \return Une référence à l'électeur présent.
 */
Electeur& obtenirElecteurActuel() const;

/**
 * Obtient la taille de la file d'attente des électeurs attendant pour accéder à la table de décharge.
 * \return Le nombre d'électeurs dans la file d'attente.
 */
int obtenirTailleFile() const;

/**
 * Gère le temps passé par les électeurs à la table de décharge, ajustant la durée de leur présence selon les règles établies.
 */
void gestionTemps() override;

/**
 * Permet à un électeur de passer à la table de décharge, gérant son entrée.
 * \param e Référence à l'électeur qui passe à la table.
 */
void passage(Electeur& e);

/**
 * Obtient la file d'attente des électeurs en attente pour accéder à la table de décharge.
 * \return Une file contenant les références aux électeurs en attente.
 */
std::queue<Electeur*> obtenirFileDattente() const;


private:
std::vector<std::stack<Bulletin>> bulletinsParCandidat;
bool occupeDecharge_; 
int dureeDecharge_;
float probabiliteBulletinBlanc_;
std::queue<Electeur*> fileAttenteDecharge;
Electeur* electeurPresent_;
bool aPrisBulletins_;
};

#endif
