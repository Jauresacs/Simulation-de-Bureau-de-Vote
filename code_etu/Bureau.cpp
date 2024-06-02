#include "Bureau.hpp"
#include "Electeur.hpp"
#include "Personne.hpp"
#include "TableDeDecharge.hpp"
#include "Election.hpp"
#include <cmath>

using namespace elections;

int Bureau::comptId_ = 310;

//Constructeur du bureau de vote 
Bureau::Bureau(int tmax, TableDeDecharge& decharge, Election& el, TableDeVote& tb, EspaceIsoloirs& esp)
      : entreeOuverte_(false), bureauOuvert_(false), bureauId_(comptId_++),
      dureeMax(tmax), tab_(decharge), election_(el),  tableVote_(tb), espace_(esp), t_(1)
{}

float calculerProbaEntree(int t, int dureeMax)
{
    return static_cast<float>(t) / dureeMax;
}

void Bureau::entrer(Electeur& e) {
    // Calcule la probabilité basée sur le temps restant
    float probaEntree = calculerProbaEntree(t_, dureeMax);

    // Génère un nombre aléatoire entre 0 et 1
    float randValue = static_cast<float>(rand()) / RAND_MAX;

    // Compare la valeur aléatoire à la probabilité d'entrée
    if (randValue < probaEntree && entreeOuverte_ && tab_.obtenirTailleFile()<2) {
        std::cout << "   ENTREE" << std::endl;
        std::cout << "      " << e.id()+1 << " " << "entre" << std::endl;
        e.validerEntrer();
    }

    if (t_ == dureeMax) {
        fermerEntree();
    }
}

void Bureau::afficherListeElectorale() const
{
   for(const auto& electeur : listeElectorale)
   {
      std::cout<<electeur->nom()<<" "<<electeur->prenom()<<" "<<"("<<electeur->id()<<")"<<std::endl;
   }
    std::cout<<std::endl;
}

std::set<Electeur*, CompareElecteur> Bureau::obtenirElecteurs() const
{
   return listeElectorale;
} 

void Bureau::ouvertureBureau()
{
   std::cout<<std::endl;
   std::cout<<"OUVERTURE BUREAU n°"<<bureauId_<<std::endl;
   std::cout<<"TMAX = "<<dureeMax<<std::endl;
   std::cout<<std::endl;
}

void Bureau::ouvertureEntree()
{
   if(entreeOuverte_==false && t_>2)
   {
      entreeOuverte_=true;
   }
}

void Bureau::fermerEntree()
{
   if(entreeOuverte_==true)
   {
      std::cout<<std::endl;
      std::cout<<"FERMETURE ENTREE"<<std::endl;
      entreeOuverte_=false;
      std::cout<<std::endl;
   }
}

void Bureau::fermerBureau()
{
   std::cout<<std::endl;
   bureauOuvert_=false;
   std::cout<<"FERMETURE BUREAU n°"<<bureauId_<<std::endl;
   std::cout<<std::endl;
}

bool Bureau::rechercherElecteur(Electeur* e)
{
   return (listeElectorale.find(e)!=listeElectorale.end()) ;
}

void Bureau::simulerElection() {
    for(auto& electeur : listeElectorale)
    {
      if(!electeur->obtenirEtatEntree())
      {
         entrer(*electeur);
      }

      if(electeur->obtenirEtatEntree() && !electeur->obtenirEtatDecharge())
      {
         tab_.entrer(*electeur);
      }

      if(!electeur->obtenirPresenceIsoloir() &&electeur->obtenirEtatPriseDeBulletin() && !electeur->obtenirEtatIsoloir())
      {
         espace_.entrerIsoloirLibre(*electeur);
      }

      if (electeur->obtenirEtatChoix() && !electeur->obtenirEtatVote())
      {
         tableVote_.entrer(*electeur);
      }
    }
    

}

void Bureau::affichageStatistiquesElection() const
{
   std::unordered_map<std::string, int> stats = tableVote_.obtenirNombreDeVote();

   int nbVotes = 0;
   int nbElecteurs = listeElectorale.size();
   for(const auto& pair : stats)
   {
      nbVotes+=pair.second;
   }
   double tauxParticipation = static_cast<double>(nbVotes) / nbElecteurs * 100;
   double tauxAbstention = 100 - tauxParticipation;

   std::cout << std::endl;
   std::cout<<"Bureau n°"<<bureauId_<<" : "<<" RESULTATS "<<election_.nom()<<std::endl;

   std::cout<<"PRESIDENT : "<<tableVote_.obtenirPresident().nom()<<" "<<tableVote_.obtenirPresident().prenom()<<std::endl;

   std::cout<<"    nb electeurs : "<<nbElecteurs<<std::endl;
   std::cout<<"    nb votes : "<<nbVotes<<std::endl;

   std::cout<<"    partitipation : "<<tauxParticipation<<"%"<<std::endl;

   std::cout<<"    abstention : "<<tauxAbstention<<"%"<<std::endl;

   for(const auto& pair : stats)
   {
      double pourcentage = (static_cast<double>(pair.second) / nbVotes) * 100.0;
      int pourcentageArrondi = static_cast<int>(round(pourcentage));
      std::cout << "    " << pair.first << " : " << pair.second << " (" << pourcentageArrondi << "%)" << std::endl;
   }

}


void Bureau::miseAJour() {

   bool entreDejaOuverteUneFois = false; 
    bool affichage = false;
    ouvertureBureau();
    while (t_ <= dureeMax || verifierOccupation()) {

      simulerElection();
      std::cout << "T = " << t_ << std::endl;
      if (tab_.estOccupe() || !tab_.obtenirFileDattente().empty()) 
      {
         tab_.gestionTemps();
      }

      if (espace_.etatIsoloir() || espace_.obtenirTailleFile()!=0) 
      {
        espace_.gestionDuree();
      }

      if(!tab_.estOccupe() && tab_.obtenirFileDattente().empty() && !espace_.etatIsoloir() && espace_.obtenirTailleFile()==0 && !affichage && t_>dureeMax)
      {
         std::cout<<"   DECHARGE"<<std::endl;
         std::cout<<"   ISOLOIR"<<std::endl;
         affichage = true;
      } 
      
      if (tableVote_.estOccupe() || tableVote_.obtenirTailleFile() !=0)
      {
        tableVote_.gestionTemps();
      }

      t_++;

      if(!entreDejaOuverteUneFois && t_>2)
      {
         ouvertureEntree();
         entreDejaOuverteUneFois=true;
      }
   }
   simulerElection();
   while(tableVote_.estOccupe())
   {
      std::cout << "T = " << t_ << std::endl;
      tableVote_.gestionTemps();
   }
    
    fermerBureau();
    affichageStatistiquesElection();
}


bool Bureau::verifierOccupation() const
{
   if (tab_.estOccupe() || tab_.obtenirTailleFile() > 0)
   {
      return true;
   }
   if (tableVote_.estOccupe() || tableVote_.obtenirTailleFile() > 0)
   {
      return true;
   }
   if (espace_.etatIsoloir() || espace_.obtenirTailleFile() > 0)
   { 
      return true;
   }

   return false;
}

void Bureau::ajouterElecteur(Electeur* e)
{
   listeElectorale.insert(e);
}

std::vector<Personne> Bureau::obtenirCandidats() const
{
   return candidats;
 }

void Bureau::affichage() const
{
   election_.afficherCandidats();
   std::cout<<"BUREAU n°"<<bureauId_<<std::endl;
   std::cout<<"LISTE ELECTORALE"<<std::endl;
   afficherListeElectorale();
   
   std::cout<<"PREPARATION DECHARGE"<<std::endl;
   tab_.affichageBulletin();

}

Bureau::~Bureau() {
    for (auto electeur : listeElectorale) {
        delete electeur;
    }
}
