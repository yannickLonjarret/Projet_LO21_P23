#include "Joueur.h"


int Joueur::prochain_id = 0; // Initialisation de la variable statique

void Joueur::Poser_carte_c(Carte_c& c, int id, Jeu& jeu) {
	//Logique de pose d'une carte classique sur le plateau
	bool carteTrouvee = false;
	for (auto it = cartes_c.begin(); it != cartes_c.end(); ++it) {
		//surcharger opérateur == pour cartes_c
		/*if (it == c) {
			carteTrouvee = true;
			cartes_c.erase(it);
			setNb_cartes();
			break;
		}*/
	}
	if (carteTrouvee == false) {
		//jeu.Poser_carte_c(c,id);
	}
	else {
		std::cout << "La carte n'appartient pas à la main du joueur !" << std::endl;
	}
}


void Joueur::Poser_carte_t(Carte_t& c, int id, Jeu& jeu) {
	//Logique de pose d'une carte tactique sur le plateau
	bool carteTrouvee = false;
	for (auto it = cartes_t.begin(); it != cartes_t.end(); ++it) {
		/*if (it == c) {
			carteTrouvee = true;
			cartes_t.erase(it);
			setNb_cartes();
			break;
		}*/
	}
	if (carteTrouvee) {
		//jeu.Poser_carte_t(c, id);
	}
	else {
		std::cout << "La carte n'appartient pas à la main du joueur !" << std::endl;
	}
}

Carte_c* Joueur::piocher_c(Jeu& jeu) {
	//Logique de la pioche d'une carte classique
	Carte_c* carte = nullptr;
	/*if (!jeu.getPioche_c().estVide()) {
		carte = jeu.getPioche_c().piocher();
		cartes_c.push_back(carte);
		setNb_cartes();
	}*/
	return carte;
}

Carte_t* Joueur::piocher_t(Jeu& jeu) {
	//Logique de la pioche d'une carte classique
	Carte_t* carte = nullptr;
	/*if (!jeu.getPioche_t().estVide()) {
		carte = jeu.getPioche_t().piocher();
		cartes_t.push_back(carte);
		setNb_cartes();
	}
	*/
	return carte;
}

