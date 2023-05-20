#include <iostream>
#include <vector>
#include <algorithm>

#include "Combinaison.h"
#include "Tuile.h"
#include <chrono>


int main() {

	vector<Combinaison*> vic;

	vector<Carte_c*> cards;
	vector<Tuile*> tuile;

	Carte_c::getCouleurs().push_back("Vert");
	Carte_c::getCouleurs().push_back("Bleu");
	Carte_c::getCouleurs().push_back("Rouge");
	Carte_c::getCouleurs().push_back("Jaune");
	Carte_c::getCouleurs().push_back("Violet");
	Carte_c::getCouleurs().push_back("Marron");

	vic.push_back(new Combinaison(false, false, false));
	vic.push_back(new Combinaison(true, false, false));
	vic.push_back(new Combinaison(false, true, false));
	vic.push_back(new Combinaison(false, false, true));
	vic.push_back(new Combinaison(true, true, false));

	Tuile* t = new Tuile(3, vic, 2);

	tuile.push_back(t);

	t->ajout_c(new Carte_c(9, "Rouge"), 0);
	t->ajout_c(new Carte_c(8, "Rouge"), 0);
	t->ajout_c(new Carte_c(7, "Rouge"), 0);

	cards = t->getCotes()[0]->getCartesC();
	cout << "Nb cartes J1: " << cards.size() << endl;

	for (int i = 0; i < cards.size(); i++) {
		cout << cards[i]->getValeur() <<" " << cards[i]->getCouleur() << endl;
	}
	cout << "Nb cartes J2: " << t->getCotes()[1]->getCartesC().size() << endl;
	auto startTime = std::chrono::high_resolution_clock::now();

	t->claimTuile(0, tuile);
	auto endTime = std::chrono::high_resolution_clock::now();

	
	std::chrono::duration<double> duration = endTime - startTime;
	double seconds = duration.count();

	t->ajout_c(new Carte_c(9, "Bleu"), 1);
	t->ajout_c(new Carte_c(8, "Bleu"), 1);
	t->ajout_c(new Carte_c(7, "Bleu"), 1);

	cout << "Nb cartes J2: " << t->getCotes()[1]->getCartesC().size() << endl;

	cards = t->getCotes()[1]->getCartesC();

	for (int i = 0; i < cards.size(); i++) {
		cout << cards[i]->getValeur() << " " << cards[i]->getCouleur() << endl;
	}

	t->claimTuile(0, tuile);
	cout << "gagnant: " << t->getClaim() << endl;

	cout << "Temps de preuve: " << seconds << endl;

	return 0;
}