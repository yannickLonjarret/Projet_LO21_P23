#include "Joueur.h"


int Joueur::prochain_id = 1; // Initialisation de la variable statique



void Joueur::push(const Carte_c& c)
{
	this->cartes_c.push_back(c);
	setNb_cartes();
}

void Joueur::push(const Carte_t& c)
{
	this->cartes_t.push_back(c);
	setNb_cartes();
}

void Joueur::pop(const Carte_c& c) {
	for (auto it = cartes_c.begin(); it != cartes_c.end(); ++it) {
		if (*it == c) {
			cartes_c.erase(it);
			setNb_cartes();
			break;
		}
	}
}

void Joueur::pop(const Carte_t& c) {
	for (auto it = cartes_t.begin(); it != cartes_t.end(); ++it) {
		if (*it == c) {
			cartes_t.erase(it);
			setNb_cartes();
			break;
		}
	}
}

void Joueur::DisplayHand()
{
	std::cout << "Main : ";
	for (const auto& carteC : getCarteC()) {
		std::cout << carteC << " ";
	};
	for (const auto& carteT : getCarteT()) {
		std::cout << carteT << " ";
	};
	std::cout << '\n';
}




