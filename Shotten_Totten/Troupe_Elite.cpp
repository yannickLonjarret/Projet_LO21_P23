#include "Troupe_Elite.h"

void TroupeElite::definir_carte(int v, const string& c) {
	if (v < val_deb || v > val_fin)
		throw Carte_tException("Error : value out of range");
	//Carte_c carte = Carte_c(v, c);
	setCouleur(c);
	setValeur(v);
}