#include "Troupe_Elite.h"

Carte_c TroupeElite::definir_carte(int v, const string& c) {
	if (v < val_deb || v > val_fin)
		throw Carte_tException("Error : value out of range");
	//Carte_c carte = Carte_c(v, c);
	return Carte_c(v, c);
}

std::ostream& operator<<(std::ostream& f, const TroupeElite& c) {
	f << "Nom : " << c.getNom() << "\nD�but : " << c.getDebut() << "\nFin : " << c.getFin();
	return f;
}