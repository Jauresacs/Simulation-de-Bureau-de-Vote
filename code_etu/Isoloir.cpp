#include "Isoloir.hpp"
#include "Electeur.hpp"
#include "TableDeVote.hpp"

int Isoloir::compteurId_ = 200;

Isoloir::Isoloir(float pn, int duree, int dp)
      : isoloirOccupe_(false), idIsoloir_(compteurId_++), distance_(dp),
      probabiliteNulle_(pn), dureeIsoloir_(duree), electeurPresent_(nullptr)
   {}

void Isoloir::entrer(Electeur& e)
{
   e.assignerDuree(dureeIsoloir_);

   electeurPresent_=&e;

   electeurPresent_->validerEntreeIsoloir();

   isoloirOccupe_=true;

   std::cout<<"   ISOLOIR"<<std::endl;

   std::cout<<"      "<<e.id()+1<<" "<<"entre"<<std::endl;
}

void Isoloir::gestionTemps() 
{
    if (electeurPresent_ != nullptr) {
        if (electeurPresent_->obtenirDuree() > 0) {
            electeurPresent_->modificationDuree();
        }
        if(electeurPresent_->obtenirDuree() == 0)
        {
            choisirBulletin();
            sortir();
        }
    }
}


void Isoloir::sortir()
{
   isoloirOccupe_=false;
   
   std::cout<<"      "<<electeurPresent_->id()+1<<" "<<"sort"<<std::endl;
   
   electeurPresent_->validerChoixDeCandidat();

   electeurPresent_=nullptr;
}

void Isoloir::choisirBulletin()
{
   electeurPresent_->decision(probabiliteNulle_, distance_);
}

bool Isoloir::estOccupe() const
{
   return isoloirOccupe_;
}