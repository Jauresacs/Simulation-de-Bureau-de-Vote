#include "Electeur.hpp"
#include <ctime>
#include <cstdlib>

using namespace elections;

Electeur::Electeur(const std::string& nom, const std::string& prenom, int spol)
    : Personne(nom, prenom, spol), duree_(0), choix_(" "), estEntree_(false), estEntreeDecharge_(false),
      estDansEspaceIsoloir_(false) ,estEntreeIsoloir_(false), estEntreeTableDeVote_(false), aPrisSesBulletins(false), aFaitSonChoix(false)
      {}


void Electeur::ajouterBulletin(const Bulletin& bulletin)
{
   bulletins.push_back(bulletin);
}

void Electeur::assignerDuree(int temps)
{
   duree_=temps;
}

void Electeur::jeterBulletins()
{ 
   bulletins.clear();
}

std::vector<Bulletin> Electeur::obtenirBulletins() const
{
   return bulletins;
}

std::string Electeur::obtenirChoix() const
{
   return choix_;
}

int Electeur::obtenirDuree() const
{
   return duree_;
}

void Electeur::decision(float pn, int dmax)
{
    double probability = static_cast<double>(std::rand()) / RAND_MAX;

    if (probability < pn)
    {
        choix_ = "nul";
    }
    else
    {
        std::string meilleurChoix = "";
        std::string blanc ="";
        int meilleureDistance = dmax + 1;  // Initialisation à une distance hors de portée

        for (size_t i = 0; i < bulletins.size(); i++)
        {
            if(bulletins[i].obtenirNomCandidat()=="blanc" && blanc.empty()){
               blanc = bulletins[i].obtenirNomCandidat();
            }
            int distance = std::abs(spol() - bulletins[i].obtenirSensibilitePolitique());
            if (distance <= dmax && (meilleurChoix.empty() || distance < meilleureDistance))
            {
                meilleurChoix = bulletins[i].obtenirNomCandidat();
                meilleureDistance = distance;
            }
        }

        // S'assurer qu'un bulletin "blanc" n'est choisi que si aucun autre choix n'est disponible
        if (meilleurChoix.empty())
        {
            if(!blanc.empty()){
               meilleurChoix = blanc;
            }
        }

        // Finaliser le choix
        choix_ = meilleurChoix.empty() ? "nul" : meilleurChoix;
    }

    // Affichage du résultat
    std::cout << "   ISOLOIR" << std::endl;
    std::cout << "      " << id()+1 << " choisit " << choix_ << std::endl;
}



void Electeur::validerPriseBulletin()
{
   aPrisSesBulletins = true;
}

void Electeur::validerChoixDeCandidat()
{
   aFaitSonChoix = true;
}

bool Electeur::obtenirEtatPriseDeBulletin() const
{
   return aPrisSesBulletins;
}

bool Electeur::obtenirEtatChoix() const
{
   return aFaitSonChoix;
}


void Electeur::modificationDuree()
{
   duree_--;
}

bool Electeur::obtenirEtatEntree() const
{
   return estEntree_;
}

void Electeur::validerEntreeVote()
{
   estEntreeTableDeVote_ = true;
}

bool Electeur::obtenirEtatVote() const
{
   return estEntreeTableDeVote_;
}

bool Electeur::obtenirEtatDecharge() const
{
   return estEntreeDecharge_;
}

bool Electeur::obtenirEtatIsoloir() const
{
   return estEntreeIsoloir_;
}

void Electeur::validerEntreeIsoloir()
{
   estEntreeIsoloir_ = true;
}

void Electeur::validerEntrer()
{
   estEntree_ = true;
}

void Electeur::validerPresenceEspaceIsoloir()
{
   estDansEspaceIsoloir_ = true;
}

bool Electeur::obtenirPresenceIsoloir() const
{
   return estDansEspaceIsoloir_;
}

void Electeur::validerEntreeDecharge()
{
   estEntreeDecharge_ = true;
}

void Electeur::affichageChoix() const
{
   for(size_t i=0; i<bulletins.size(); i++){
      std::cout<<"      "<<id()+1<<" "<<"prend"<<" "<<bulletins[i].obtenirNomCandidat()<<std::endl;
   }
}
