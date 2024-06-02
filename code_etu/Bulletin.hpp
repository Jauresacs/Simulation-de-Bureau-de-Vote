#ifndef BULLETIN_HPP
#define BULLETIN_HPP

#include <iostream>
#include <string>

/**
 * La classe Bulletin représente un bulletin de vote.
 * Elle permet de gérer le nom du candidat et la sensibilité politique associée au bulletin.
 */
class Bulletin {
public:
    /**
     * Constructeur pour créer un bulletin avec un nom spécifique et une sensibilité politique donnée.
     * \param nom Le nom du candidat ou du sujet du bulletin.
     * \param sensibilite La sensibilité politique associée au bulletin.
     */
    Bulletin(std::string nom, int sensibilite);

    /**
     * Constructeur pour créer un bulletin avec un type spécifique. Ce constructeur initialise
     * le bulletin avec des valeurs prédéfinies basées sur le type.
     * \param typeBulletin Le type de bulletin, qui pourrait influencer la configuration initiale du bulletin.
     */
    explicit Bulletin(std::string typeBulletin);

    /**
     * Retourne la sensibilité politique du bulletin.
     * \return La sensibilité politique du bulletin.
     */
    int obtenirSensibilitePolitique() const;

    /**
     * Ajoute ou modifie le nom du candidat associé au bulletin.
     * \param nom Le nom du candidat à enregistrer sur le bulletin.
     */
    void ajouterNomCandidat(const std::string& nom);
    
    /**
     * Obtient le nom du candidat enregistré sur le bulletin.
     * \return Le nom du candidat.
     */
    std::string obtenirNomCandidat() const;

private:
    std::string nomCandidat_; 
    int sensibilitePolitique_;
};
#endif