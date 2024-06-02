#ifndef ELECTEUR_HPP
#define ELECTEUR_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Personne.hpp"
#include "Bulletin.hpp"
#include "Personne.hpp"

namespace elections {

/*
 * Electeur représente un électeur dans le contexte d'une élection.
 *
 * Cette classe dérive de `Personne` pour ajouter des fonctionnalités spécifiques aux électeurs,
 * telles que la gestion des bulletins de vote et la sauvegarde de leur choix de vote.
 */
class Electeur : public Personne {
public:
/**
 * Constructeur pour initialiser un électeur avec son nom, prénom et sensibilité politique.
 * \param nom Le nom de l'électeur.
 * \param prenom Le prénom de l'électeur.
 * \param spol La sensibilité politique de l'électeur, représentée par un entier.
 */
Electeur(const std::string& nom, const std::string& prenom, int spol);


/**
 * Ajoute un bulletin à la liste des bulletins que l'électeur a pris.
 * \param bulletin Le nom du candidat ou l'option représentée sur le bulletin.
 */
void ajouterBulletin(const Bulletin& bulletin);

/**
 * Sauvegarde le choix final de l'électeur.
 * \param choix Le nom du candidat comme son vote final.
 */
void sauvegarderChoix(const std::string& choix);

/**
 * Accesseur
 * \return la liste des bulletins choisit par l'électeur.
*/
std::vector<Bulletin> obtenirBulletins() const;

/**
 * Méthode permettant d'attribuer la durée dans chaque espace du bureau.
*/
void assignerDuree(int temps);

/**
 * Méthode pour supprimer la liste de bulletin de choix après que 
 * l'électeur ait voté.
*/
void jeterBulletins();

/**
 * Acesseur permettant de retouner le choix de l'électeur.
 * \return choix de l'électeur.
*/
std::string obtenirChoix() const;

/**
 * Méthode permettant de renvoyer la durée d'un electeur
 * \return duree 
*/
int obtenirDuree() const;

/**
 * Méthode permettant à l'électeur de faire le choix de son candidat
 * dans un isoloir.
*/
void decision(float pn, int dmax);

/**
 * Méthode permettant de modifier la durée d'un électeur
*/
void modificationDuree();

/**
 * Valide l'entrée de l'électeur dans la zone de décharge.
 */
void validerEntreeDecharge();

/**
 * Valide l'entrée de l'électeur dans l'isoloir.
 */
void validerEntreeIsoloir();

/**
 * Valide l'entrée générale de l'électeur dans le bureau de vote.
 */
void validerEntrer();

/**
 * Valide l'entrée de l'électeur dans la zone de vote.
 */
void validerEntreeVote();

/**
 * Obtient l'état d'entrée de l'électeur dans le bureau de vote.
 * \return true si l'électeur a validé son entrée, false sinon.
 */
bool obtenirEtatEntree() const;

/**
 * Obtient l'état d'entrée de l'électeur dans la zone de décharge.
 * \return true si l'électeur a validé son entrée en décharge, false sinon.
 */
bool obtenirEtatDecharge() const;

/**
 * Obtient l'état d'entrée de l'électeur dans l'isoloir.
 * \return true si l'électeur est  ou est déjà passé dans l'isoloir, false sinon.
 */
bool obtenirEtatIsoloir() const;

/**
 * Obtient l'état d'entrée de l'électeur dans la zone de vote.
 * @return true si l'électeur a validé son entrée en zone de vote, false sinon.
 */
bool obtenirEtatVote() const;

/**
 * Valide la prise des bulletins par l'électeur.
 */
void validerPriseBulletin();

/**
 * Valide le choix final du candidat par l'électeur.
 */
void validerChoixDeCandidat();

/**
 * Obtient l'état de prise de bulletins par l'électeur.
 * \return true si l'électeur a pris ses bulletins, false sinon.
 */
bool obtenirEtatPriseDeBulletin() const;

/**
 * Obtient l'état de choix final du candidat par l'électeur.
 * \return true si l'électeur a fait son choix final, false sinon.
 */
bool obtenirEtatChoix() const;

/**
 * Valide la présence de l'électeur dans l'espace isoloir.
 */
void validerPresenceEspaceIsoloir();

/**
 * Obtient l'état de présence de l'électeur dans l'espace isoloir.
 * \return true si l'électeur est présent dans l'espace isoloir, false sinon.
 */
bool obtenirPresenceIsoloir() const;

/**
 * Méthode permettant l'affchage des choix de bulletins par l'électeur
*/
void affichageChoix() const;

private:
int duree_; 
std::vector<Bulletin> bulletins;
std::string choix_;
bool estEntree_, estEntreeDecharge_,estDansEspaceIsoloir_, estEntreeIsoloir_, estEntreeTableDeVote_, 
aPrisSesBulletins, aFaitSonChoix;
};

struct CompareElecteur {
    bool operator()(Electeur* e1, Electeur* e2) const {
        if (e1->nom() < e2->nom()) return true;
        if (e1->nom() > e2->nom()) return false;
        if (e1->prenom() < e2->prenom()) return true;
        if (e1->prenom() > e2->prenom()) return false;
        return false;
    }
};



}
#endif