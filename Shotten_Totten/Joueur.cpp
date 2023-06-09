#include "Joueur.h"
#include "Tuile.h"


int Joueur::prochain_id = 1; // Initialisation de la variable statique

void Joueur::poser_carte(Carte* c, int id, Tuile* t) {
	//Logique de pose d'une carte classique sur le plateau
	t->ajout_carte(c, id);
	cout << "AJOUT TERMINE" << endl;
	for (auto it = 0; it < cartes_c.size(); it++) {
		if ((Carte*)cartes_c[it] == c) {
			cartes_c.erase(cartes_c.begin() + it);

		}
		cout << "Boucle classique" << endl;
	}

	for (auto it = 0; it < cartes_t.size(); it++) {
		if ((Carte*)cartes_t[it] == c) {
			cartes_t.erase(cartes_t.begin() + it);
		}
		cout << "Boucle tactique" << endl;
	}

	setNb_cartes();
}

Carte_c* Joueur::piocher_c(Pioche_c& pc) {
	//Logique de la pioche d'une carte classique
	Carte_c* carte = nullptr;
	if (pc.getSize() != 0) {
		carte = pc.pop();
		cartes_c.push_back(carte);
		setNb_cartes();
	}
	return carte;
}

Carte_t* Joueur::piocher_t(Pioche_t& pt) {
	//Logique de la pioche d'une carte classique
	Carte_t* carte = nullptr;
	if (pt.getSize() != 0) {
		carte = pt.pop();
		cartes_t.push_back(carte);
		setNb_cartes();
	}

	return carte;
}


