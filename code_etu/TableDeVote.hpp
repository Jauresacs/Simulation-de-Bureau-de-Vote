#ifndef TABLEDEVOTE_HPP
#define TABLEDEVOTE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
#include "Action.hpp"
#include "Electeur.hpp"


using namespace elections;

/**
 * La table de vote est l'endroit où se trouve le président de l'élection. 
 * La règle stipulant qu'un seul électeur peut occuper cet espace à la fois 
 * est régulée par la variable `occupeVote`. L'espace dispose également d'une 
 * liste d'émargement, utilisée pour signer après avoir voté. Au sein de cet 
 * espace, chaque électeur dépose son bulletin dans l'urne, et le temps passé 
 * dans cet espace pour le déroulement du vote est également pris en compte.
 */

class TableDeVote : public Action{
public:
/**
* Constructeur pour initialiser la table de vote.
* \param duree  La duree que doit passer une electeur dans cet espace.
* \param p   Le president de l'élection en cours.
*/
TableDeVote(int duree, const Personne& p, std::vector<Personne>& candidats);

/**
* Simule le dépôt du bulletin choisi par l'électeur.
*/
void voter(); 

/**
* Simule l'émargement de l'électeur après son vote.
*/
void emarger();

/**
 * Méthode permettant la recherche d'un électeur dans une liste d'émargement.
 * \return renvoie true si l'électeur a voté et false sinon.
*/
bool rechercheVote(int id);

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
 * Obtient la taille de la file d'attente des électeurs attendant pour voter à la table de vote.
 * \return Le nombre d'électeurs dans la file d'attente.
 */
int obtenirTailleFile() const;

/**
 * Traite la file d'attente des électeurs en attente de voter, permettant à chaque électeur de voter dès que l'espace est libre.
 */
void traiterFileAttente();

/**
 * Obtient le nombre de votes reçus par chaque candidat jusqu'à présent.
 * \return Un dictionnaire contenant les noms des candidats et le nombre de votes qu'ils ont reçus.
 */
std::unordered_map<std::string, int> obtenirNombreDeVote() const;

/**
 * Gère le temps passé par les électeurs à la table de vote, ajustant la durée de leur présence selon les règles établies.
 */
void gestionTemps() override;

/**
 * Permet à un électeur de passer à la table de vote, gérant son entrée.
 * \param e Référence à l'électeur qui passe à la table.
 */
void passage(Electeur& e);

/**
 * Vérifie si la table de vote est actuellement occupée par un électeur.
 * \return true si la table est occupée, false sinon.
 */
bool estOccupe() const;

/**
 * Obtient le président de l'élection qui supervise le processus de vote à cette table.
 * \return Une référence au président de l'élection.
 */
Personne obtenirPresident() const;


/**
* Retourne le résultat de l'ensemble des votes à la fin des votes.
* \return Les résultats de chaque vote par les électeurs pour chaque candidat.
*/
std::unordered_map<std::string, int> resultats() const;   
 
private:
bool occupeVote_; 
Personne president_;
std::unordered_set<int> listeEmargement; 
int dureeVote_;
std::unordered_map<std::string, int> nombreDeVotes;
std::queue<Electeur*> fileAttenteVote;
Electeur* electeurPresent_;
};

#endif
