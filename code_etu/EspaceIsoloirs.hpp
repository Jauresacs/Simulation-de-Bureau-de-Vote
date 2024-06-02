#ifndef ESPACEISOLOIRS
#define ESPACEISOLOIRS

#include <iostream>
#include <vector>
#include <queue>
#include "Isoloir.hpp"
#include "TableDeVote.hpp"

/**
 * Isoloirs gère un ensemble d'isoloirs dans un bureau de vote.
 *
 * Cette classe représente un ensemble d'isoloirs utilisés lors d'une élection.
 * Elle permet d'ajouter des isoloirs à l'ensemble, de rechercher un isoloir libre pour 
 * un électeur et de gérer l'entrée d'un électeur dans un isoloir libre. 
 */

class EspaceIsoloirs{
public:
/**
 * Constructeur de la classe EspaceIsoloirs. Initialise l'espace avec un nombre donné d'isoloirs et des paramètres spécifiques.
 * @param pn Probabilité associée à l'utilisation des isoloirs (non spécifié mais implicite dans l'utilisation).
 * @param nombresIsoloirs Le nombre total d'isoloirs à créer dans cet espace.
 * @param duree Durée prévue pour l'utilisation de chaque isoloir par un électeur.
 * @param dp Délai ou durée supplémentaire pour des procédures spécifiques dans l'isoloir (non spécifié mais implicite).
 */
EspaceIsoloirs(float pn, int nombresIsoloirs, int duree, int dp);

/**
 * Recherche le premier isoloir libre (non occupé) dans l'ensemble des isoloirs et
 * retourne son identifiant. Si aucun isoloir libre n'est trouvé, retourne -1.
 * \return L'identifiant de l'isoloir libre, ou -1 si aucun isoloir libre n'est trouvé.
 */
int rechercheIsoloirLibre();

/**
 * Vérifie si au moins un isoloir est actuellement libre.
 * \return true si au moins un isoloir est libre, false sinon.
 */
bool etatIsoloir() const;

/**
 * Traite la file d'attente des électeurs en attente d'un isoloir, tentant de les placer dans un isoloir libre dès que possible.
 */
void traiterFileAttente();

/**
 * Obtient la taille de la file d'attente des électeurs qui attendent d'entrer dans un isoloir.
 * \return Le nombre d'électeurs dans la file d'attente.
 */
int obtenirTailleFile() const;

/**
 * Gère la durée d'occupation des isoloirs en ajustant les temps en fonction des électeurs et de leur utilisation actuelle des isoloirs.
 */
void gestionDuree();
/**
 * Permet à un électeur d'entrer dans le premier isoloir libre trouvé.
 */
void entrerIsoloirLibre(Electeur& e);

private:
std::vector<Isoloir> espaceIsoloirs; 
std::queue<Electeur*> fileAttenteIsoloir;
std::queue<int> isoloirsVides;
size_t isoloirsOccupe_;
};

#endif
