#include "EspaceIsoloirs.hpp"
#include "Isoloir.hpp"
#include "Electeur.hpp"

EspaceIsoloirs::EspaceIsoloirs(float pn, int nombresIsoloirs, int duree, int dp)

    : isoloirsOccupe_(0)      
{
   for(int i=0; i<nombresIsoloirs; i++)
   {
      espaceIsoloirs.push_back(Isoloir(pn, duree,dp));
      isoloirsVides.push(i);
   }
}

bool EspaceIsoloirs::etatIsoloir() const
{
    return isoloirsOccupe_> 0;
}

int EspaceIsoloirs::obtenirTailleFile() const
{
   return fileAttenteIsoloir.size();
}

void EspaceIsoloirs::entrerIsoloirLibre(Electeur& e) {
    e.validerPresenceEspaceIsoloir();
    int indice = rechercheIsoloirLibre();
    if (indice != -1) {
        espaceIsoloirs[indice].entrer(e);
        isoloirsOccupe_++;
    } else {
        fileAttenteIsoloir.push(&e);
    }
    traiterFileAttente();
}

void EspaceIsoloirs::traiterFileAttente() 
{
    while (!fileAttenteIsoloir.empty() && isoloirsOccupe_< espaceIsoloirs.size()) 
    {
        int indice = rechercheIsoloirLibre();
        if (indice != -1) {
            Electeur* prochain = fileAttenteIsoloir.front();
            fileAttenteIsoloir.pop();
            espaceIsoloirs[indice].entrer(*prochain);
            isoloirsOccupe_++;
        }
    }
}

void EspaceIsoloirs::gestionDuree() 
{
    for (size_t i = 0; i < espaceIsoloirs.size(); i++) 
    {
        if (espaceIsoloirs[i].estOccupe()) 
        {
            espaceIsoloirs[i].gestionTemps();

            if (!espaceIsoloirs[i].estOccupe()) 
            {
                isoloirsVides.push(i);
                isoloirsOccupe_--;
            }
        }
    }
    traiterFileAttente();
}


int EspaceIsoloirs::rechercheIsoloirLibre(){
        if (!isoloirsVides.empty()) {
            int indice = isoloirsVides.front();
            isoloirsVides.pop();
            return indice;
        }
        return -1;
    }
