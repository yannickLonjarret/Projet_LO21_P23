#include "Carte_t.h"
#include "Carte_c.h"
using namespace std;

Carte_c& TroupeElite::definir_carte(int v, const string& c){
    if(v < val_deb || v > val_fin)
        throw CarteTactiqueException("Error : value out of range");
    Carte_c carte = Carte_c(v, c);
    return carte; 
}

ostream& operator<<(ostream& f, const TroupeElite& c){
    f << "Nom : " << c.getNom() << "\nDébut : " << c.getDebut() << "\nFin : " << c.getFin();
    return f;
}

//tydfyugh
