#include "Bulletin.hpp"

Bulletin::Bulletin(std::string nom, int sensibilite)
      : nomCandidat_(nom), sensibilitePolitique_(sensibilite)
      {}

Bulletin::Bulletin(std::string typeBulletin) 
      : nomCandidat_(typeBulletin), sensibilitePolitique_(0) 
      {}

int Bulletin::obtenirSensibilitePolitique() const {  
        return sensibilitePolitique_; 
    }

void Bulletin::ajouterNomCandidat(const std::string& nom) {
        nomCandidat_ = nom;
    }

std::string Bulletin::obtenirNomCandidat() const
{
   return nomCandidat_;
}