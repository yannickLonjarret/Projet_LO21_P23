#include "Joueur.h"
#include "Tuile.h"


int Joueur::prochain_id = 0; // Initialisation de la variable statique

void Joueur::poser_carte(Carte* c, int id, Tuile* t) {
	//Logique de pose d'une carte classique sur le plateau
	
	t->ajout_carte(c, id);

	for (auto it = 0; it < cartes_c.size(); it++) {
		if ((Carte*)cartes_c[it] == c) {
			cartes_c.erase(cartes_c.begin() + it);

		}

	}

	for (auto it = 0; it < cartes_t.size(); it++) {
		if ((Carte*)cartes_t[it] == c) {
			cartes_t.erase(cartes_t.begin() + it);
		}
	}

	setNb_cartes();
}

void Joueur::piocher_c(Carte_c* pc) {
	//Logique de la pioche d'une carte classique
	if (pc != nullptr) {
		cartes_c.push_back(pc);
		setNb_cartes();
	}
}

void Joueur::piocher_t(Carte_t* pt) {
	//Logique de la pioche d'une carte classique
	if (pt != nullptr) {
		cartes_t.push_back(pt);
		setNb_cartes();
	}
}


