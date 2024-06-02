#include "TableDeDecharge.hpp"
#include "Electeur.hpp"
#include "EspaceIsoloirs.hpp"
#include <ctime>

TableDeDecharge::TableDeDecharge(int duree, int nombreDelecteurs, float pb, std::vector<Personne>& candidats)
      : occupeDecharge_(false), dureeDecharge_(duree), probabiliteBulletinBlanc_(pb), electeurPresent_(nullptr), aPrisBulletins_(false)
      {
         for (size_t i = 0; i < candidats.size(); i++) 
         {
            std::stack<Bulletin> pile;
            for (int j = 0; j < nombreDelecteurs; j++) 
            {
               pile.push(Bulletin(candidats[i].nom() + " " + candidats[i].prenom(), candidats[i].spol()));
            }
         bulletinsParCandidat.push_back(pile);
      }
   }

void TableDeDecharge::affichageBulletin() const
{
   for(const auto& bulletin: bulletinsParCandidat)
   {
      if(!bulletin.empty())
      {
         std::string nomCandidat = bulletin.top().obtenirNomCandidat();
         std::cout << nomCandidat << " : " << bulletin.size() <<" bulletins" <<std::endl;
      }
   }
}

void TableDeDecharge::prendreBulletins()
{

   int randomNumber = std::rand() % 3 + 2;//Renvoie un nombre entre 2 et 4.
 
   double probability = static_cast<double>(std::rand()) / RAND_MAX; //Renvoie une probabilité entre 0 et 1.

    std::set<int> candidatsChoisis;

   if(probability < probabiliteBulletinBlanc_)
   {

      electeurPresent_->ajouterBulletin(Bulletin("blanc"));

      randomNumber--;
   }


   for(int i=0; i<randomNumber; i++)
   {

      int indice_selection = std::rand() % bulletinsParCandidat.size();


      if(candidatsChoisis.find(indice_selection)==candidatsChoisis.end()){

         electeurPresent_->ajouterBulletin(bulletinsParCandidat[indice_selection].top());

         bulletinsParCandidat[indice_selection].pop();

         candidatsChoisis.insert(indice_selection);
      }
   }
   std::cout<<"   DECHARGE"<<std::endl;

   electeurPresent_->affichageChoix();

   candidatsChoisis.clear();
}

void TableDeDecharge::passage(Electeur& e)
{
   std::cout<<"   DECHARGE"<<std::endl;

   electeurPresent_=&e;

   occupeDecharge_=true;

   e.assignerDuree(dureeDecharge_);

   std::cout<<"      "<<e.id()+1<<" "<<"entre"<<std::endl;

}

void TableDeDecharge::entrer(Electeur &e){

   e.validerEntreeDecharge();

   if(occupeDecharge_)
   {
      fileAttenteDecharge.push(&e);
   }else
   {
      if(!fileAttenteDecharge.empty())
      {
         fileAttenteDecharge.push(&e);
         traiterFileAttente();

      }else
      {
         passage(e);
      }
   }
}

void TableDeDecharge::traiterFileAttente()
{
   if(!occupeDecharge_ && !fileAttenteDecharge.empty())
   {
      Electeur* prochain = fileAttenteDecharge.front();
      fileAttenteDecharge.pop();
      passage(*prochain);
   }
}

int TableDeDecharge::obtenirTailleFile() const
{
   return fileAttenteDecharge.size();
}

std::queue<Electeur*> TableDeDecharge::obtenirFileDattente() const
{
   return fileAttenteDecharge;
}

Electeur& TableDeDecharge::obtenirElecteurActuel() const {
    return *electeurPresent_;
}


void TableDeDecharge::gestionTemps() {
    
    if (electeurPresent_!= nullptr && electeurPresent_->obtenirDuree() > 0) {
        
        electeurPresent_->modificationDuree();

        if (electeurPresent_->obtenirDuree() <= dureeDecharge_ / 2) {
            
            if (!aPrisBulletins_) {
                prendreBulletins();
                aPrisBulletins_ = true;
            }
        }

        
        if (electeurPresent_->obtenirDuree() == 0) {
            sortir();
        }
    }
    traiterFileAttente();
    if(electeurPresent_==nullptr)
    {
      occupeDecharge_=false;
    }
}


bool TableDeDecharge::estOccupe() const
{
   return occupeDecharge_;
}

void TableDeDecharge::sortir()
{

   std::cout<<"   DECHARGE"<<std::endl;

   electeurPresent_->validerPriseBulletin();

   std::cout<<"      "<<electeurPresent_->id()+1<<" "<<"sort"<<std::endl;

   electeurPresent_=nullptr;

   aPrisBulletins_=false;
   

}
