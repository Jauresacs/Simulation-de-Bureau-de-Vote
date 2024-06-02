#ifndef BUREAU_HPP
#define BUREAU_HPP

#include <queue>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Action.hpp"
#include "TableDeDecharge.hpp"
#include "TableDeVote.hpp"
#include "EspaceIsoloirs.hpp"
#include "Election.hpp"
#include "Electeur.hpp"

using namespace elections;

/**
 * Bureau gère les opérations d'un bureau de vote, incluant la gestion des candidats, des électeurs, et le processus électoral.
 */
class Bureau {
public:
/**
 * Constructeur pour le Bureau. Initialise les composants essentiels pour gérer un bureau de vote.
 * \param tmax Temps maximum pour le processus électoral.
 * \param decharge Référence à la table de décharge utilisée pour gérer les bulletins.
 * \param el Référence à l'objet Election pour gérer l'ensemble du processus électoral.
 * \param tb Référence à la table de vote où les électeurs déposent leurs votes.
 * \param esp Référence à l'espace des isoloirs où les électeurs peuvent voter en privé.
 */
Bureau(int tmax, TableDeDecharge& decharge, Election& el, TableDeVote& tb, EspaceIsoloirs& esp);

/**
 * Ajoute un électeur à la liste électorale du bureau.
 * \param e L'électeur à ajouter.
 */
void ajouterElecteur(Electeur* e);

/**
 * Affiche la liste électorale, montrant tous les électeurs inscrits.
 */
void afficherListeElectorale() const;

/**
 * Ouvre l'entrée du bureau pour permettre aux électeurs d'entrer.
 */
void ouvertureEntree();

/**
 * Ouvre officiellement le bureau de vote, permettant le début des opérations électorales.
 */
void ouvertureBureau();

/**
 * Ferme l'entrée du bureau, empêchant les électeurs d'entrer.
 */
void fermerEntree();

/**
 * Ouvre officiellement le bureau de vote, permettant le début des opérations électorales.
 */
bool verifierOccupation() const;

/**
 * Recherche un électeur spécifique dans la liste électorale.
 * \param e L'électeur à rechercher.
 * \return true si l'électeur est trouvé dans la liste électorale, false sinon.
 */
bool rechercherElecteur(Electeur* e);

/**
 * Ferme le bureau de vote, marquant la fin du processus électoral.
 */
void fermerBureau();

/**
* Méthode dérivée permettant l'entrer de lélecteur dans l'espace.
*/
void entrer(Electeur& e);

/**
 * Méthode pour simuler le processus électoral. Inclut l'entrée des électeurs, le vote et le dépouillement des votes.
 */
void simulerElection();

/**
 * Met à jour le temps du processus électoral, avançant du temps T au temps T+1, utile dans la simulation des activités de vote.
 */
void miseAJour();

/**
 * Obtient la liste des candidats participant à l'élection.
 * \return Un vecteur contenant tous les candidats.
 */
std::vector<Personne> obtenirCandidats() const;

/**
 * Obtient un ensemble de tous les électeurs inscrits au bureau de vote.
* \return Un ensemble (set) de pointeurs vers des objets Electeur, triés selon les critères définis par CompareElecteur.
 */
std::set<Electeur*, CompareElecteur> obtenirElecteurs() const;

/**
 * Affiche le bureau et la liste electorale pour le déroulement de l'élection.
*/
void affichage() const;

/**
 * Affiche des statistiques sur l'élection après la fin du vote, incluant les résultats et le taux de participation.
 */
void affichageStatistiquesElection() const;

/**
 * Destructeur de la classe Bureau. Nettoie toutes les ressources et ferme le bureau de manière appropriée à la fin du processus électoral.
 */
~Bureau();

private:
bool entreeOuverte_;
bool bureauOuvert_;
std::set<Electeur*, CompareElecteur> listeElectorale;
std::vector<Personne> candidats;
int bureauId_;
static int comptId_;
int dureeMax;
std::queue<Electeur> fileAttenteBureau;
TableDeDecharge tab_;
Election election_;
TableDeVote tableVote_;
EspaceIsoloirs espace_;
int t_;

};

#endif
