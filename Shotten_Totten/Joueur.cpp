#include "Joueur.h"

void Poser_carte_c(Carte_c c, int id, Jeu& jeu) {
	//Logique de pose d'une carte classique sur le plateau
	bool carteTrouvee = false;
	for (auto it = cartes_c.begin(); it != cartes_c.end(); ++it) {
		if (it == c) {
			carteTrouvee = true;
			cartes_c.erase(it);
			setNb_cartes();
			break;
		}
	}
	if (carteTrouve) {
		jeu.Poser_carte_c(c, id);
	}
	else {
		std::cout << "La carte n'appartient pas à la main du joueur !" << std::endl;
	}
}

Carte_c Pioche_c(Jeu& jeu) {
	//Logique de la pioche d'une carte classique
	Carte_c carte;
	if (!jeu.getPioche_c().estVide()) {
		carte = jeu.getPioche_c().piocher();
		cartes_c.push_back(carte);
		setNb_cartes();
	}
	return carte;
}

