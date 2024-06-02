#include "TableDeVote.hpp"
#include "Personne.hpp"
#include "Electeur.hpp"
#include "Bureau.hpp"

TableDeVote::TableDeVote(int duree, const Personne& p, std::vector<Personne>& candidats)
      : occupeVote_(false), president_(p), dureeVote_(duree), electeurPresent_(nullptr)
   {   
      for(size_t i=0; i<candidats.size(); i++)
      {
         nombreDeVotes.insert({candidats[i].nom()+" "+candidats[i].prenom(), 0});
      }
      nombreDeVotes.insert({"blanc", 0});
      nombreDeVotes.insert({"nul", 0});
   }

void TableDeVote::passage(Electeur& e)
{
   std::cout<<"   VOTE"<<std::endl;

   occupeVote_=true;

   electeurPresent_=&e;

   e.assignerDuree(dureeVote_);
   
   std::cout<<"      "<<e.id()+1<<" "<<"entre"<<std::endl;
}

void TableDeVote::traiterFileAttente()
{
   if(!occupeVote_ && !fileAttenteVote.empty())
   {
      Electeur* prochain = fileAttenteVote.front();
      fileAttenteVote.pop();
      passage(*prochain);
   }
}

void TableDeVote::entrer(Electeur &e){
   e.validerEntreeVote();
   if(occupeVote_)
   {
      fileAttenteVote.push(&e);
   }else
   {
      if(!fileAttenteVote.empty())
      {
         fileAttenteVote.push(&e);
         traiterFileAttente();
      }else
      {
         passage(e);
      }
   }
}

std::unordered_map<std::string, int> TableDeVote::obtenirNombreDeVote() const
{
   return nombreDeVotes;
}

void TableDeVote::gestionTemps() {
    if (electeurPresent_ != nullptr) {
        if (electeurPresent_->obtenirDuree() > 0) {
            electeurPresent_->modificationDuree();
            if (electeurPresent_->obtenirDuree() <= dureeVote_ / 2) {
                if (!rechercheVote(electeurPresent_->id())) {
                    voter();
                }
            }
        } else {
            sortir();
        }
    }
    traiterFileAttente();
    if(electeurPresent_==nullptr)
    {
      occupeVote_=false;
    }
}



void TableDeVote::sortir()
{
   std::cout<<"   VOTE"<<std::endl;

   std::cout<<"      "<<electeurPresent_->id()+1<<" "<<"sort"<<std::endl;

   std::cout<<"   SORTIE"<<std::endl;

   std::cout<<"      "<<electeurPresent_->id()+1<<" "<<"sort"<<std::endl;

   electeurPresent_=nullptr;
}

Personne TableDeVote::obtenirPresident() const
{
   return president_;
}

bool TableDeVote::estOccupe() const
{
   return occupeVote_;
}

int TableDeVote::obtenirTailleFile() const
{
   return fileAttenteVote.size();
}


void TableDeVote::voter()
{
   std::cout<<"   VOTE"<<std::endl;

   nombreDeVotes[electeurPresent_->obtenirChoix()]++;

   electeurPresent_->jeterBulletins();

   std::cout<<"      "<<electeurPresent_->id()+1<<" "<<"vote"<<std::endl;

   emarger();
}

void TableDeVote::emarger()
{
   listeEmargement.insert(electeurPresent_->id());
}

std::unordered_map<std::string, int> TableDeVote::resultats() const
{
   return nombreDeVotes;
}

bool TableDeVote::rechercheVote(int id)
{
   return(listeEmargement.find(id)!=listeEmargement.end());
}
