#ifndef ACTION_HPP
#define ACTION_HPP

#include "Electeur.hpp"

#include <iostream>

using namespace elections;

/**
 * Cette classe représente une classe abstraite qui se charge
 * des méthodes en commun avec la Table de decharge, la table de
 * vote, Bureau, isoloir
*/
class Action {
public:
    /**
     * Méthode virtuelle pure pour l'entrée d'un électeur dans un espace.
     * 
     * \param e Référence à l'électeur qui entre dans l'espace.
     */
    virtual void entrer(Electeur& e) = 0;

    /**
     * Méthode virtuelle pure pour la sortie d'un électeur d'un espace.
     * 
     * \param e Référence à l'électeur qui sort de l'espace.
     */
    virtual void sortir() = 0;

    /**
     * Méthode virtuelle pure pour gérer le temps de l'électeur dans un espace.
    */
    virtual void gestionTemps() = 0;

    /**
     * Destructeur virtuel.
     */
    virtual ~Action() {};
};
#endif