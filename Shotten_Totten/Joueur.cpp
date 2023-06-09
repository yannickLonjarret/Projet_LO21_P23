#include "Joueur.h"
#include "Tuile.h"


int Joueur::prochain_id = 1; // Initialisation de la variable statique

void Joueur::poser_carte(Carte_c* c, int id, Tuile* t) {
	//Logique de pose d'une carte classique sur le plateau
	cout << "## POSER CARTE";
	t->ajout_c(c, id);

	//std::vector<Carte_c*>::iterator position = std::find(getCarteC().begin(), getCarteC().end()-1, c);
	//cout << "pass";
	//if (position != getCarteC().end()) // == m	yVector.end() means the element was not found
	//	getCarteC().erase(position);

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


