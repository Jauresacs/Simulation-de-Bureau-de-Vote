#include "Election.hpp"
#include "Personne.hpp"



Election::Election(std::string nom, std::vector<Personne>& cads)
         : candidats(cads), nomElection_(nom)
         {}

void Election::afficherCandidats() const
{
   std::cout<<"ELECTION"<<" "<<"'"<<nomElection_<<"'"<<std::endl;

   for(size_t i=0; i<candidats.size(); i++)
   {
      std::cout<<"Candidat n°"<<i<<" : "<<candidats[i]<<std::endl;
   }
   std::cout<<std::endl;
}

std::string Election::nom() const
{
   return nomElection_;
}