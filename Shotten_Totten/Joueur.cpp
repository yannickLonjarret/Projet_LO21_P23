#include "Joueur.h"
#include "Tuile.h"


int Joueur::prochain_id = 0; // Initialisation de la variable statique

void Joueur::poser_carte(Carte_c* c, int id, Tuile* t) {
	//Logique de pose d'une carte classique sur le plateau
	bool carteTrouvee = false;
	for (auto it = cartes_c.begin(); it != cartes_c.end(); ++it) {
		/*
		if (it == c) {
			carteTrouvee = true;
			cartes_c.erase(it);
			setNb_cartes();
			break;
		}
		*/
	}
	if (carteTrouvee == false) {
		t->ajout_c(c, id);
	}
	else {
		std::cout << "La carte n'appartient pas à la main du joueur !" << std::endl;
	}
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

