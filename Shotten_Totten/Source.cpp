#include <iostream>
#include <vector>
#include <algorithm>

#include "Combinaison.h"
#include "Tuile.h"
#include <chrono>
#include "Jeu.h"
#include "Troupe_Elite.h"

int main() {
	/*
	vector<Combinaison*> vic; //vic

	vector<Carte_c*> cards;
	vector<Tuile*> tuile; //plateau

	Carte_c::getCouleurs().push_back("Vert");
	Carte_c::getCouleurs().push_back("Bleu");
	Carte_c::getCouleurs().push_back("Rouge");
	Carte_c::getCouleurs().push_back("Jaune");
	Carte_c::getCouleurs().push_back("Violet");
	Carte_c::getCouleurs().push_back("Marron");


	TroupeElite* joker = new TroupeElite((types)0, "Joker", "Le putain de joker", -1, Carte_c::getCouleurs()[0], 1, 9);
	TroupeElite* joker2 = new TroupeElite((types)0, "Joker", "Le putain de joker", -1, Carte_c::getCouleurs()[0], 1, 9);
	TroupeElite* joker3 = new TroupeElite((types)0, "Joker", "Le putain de joker", -1, Carte_c::getCouleurs()[0], 1, 9);

	vic.push_back(new Combinaison(false, false, false));
	vic.push_back(new Combinaison(true, false, false));
	vic.push_back(new Combinaison(false, true, false));
	vic.push_back(new Combinaison(false, false, true));
	vic.push_back(new Combinaison(true, true, false));

	Tuile* t = new Tuile(3, vic, 2);

	tuile.push_back(t);

	t->ajout_c(new Carte_c(3, "Rouge"), 0);
	t->ajout_c(new Carte_c(2, "Rouge"), 0);
	t->ajout_c(new Carte_c(1, "Rouge"), 0);

	cards = t->getCotes()[0]->getCartesC();
	cout << "Nb cartes J1: " << cards.size() << endl;

	for (int i = 0; i < cards.size(); i++) {
		cout << cards[i]->getValeur() << " " << cards[i]->getCouleur() << endl;
	}
	cout << "Nb cartes J2: " << t->getCotes()[1]->getCartesC().size() << endl;
	for (int i = 0; i < t->getCotes()[1]->getCartesC().size(); i++) {
		cout << t->getCotes()[1]->getCartesC()[i]->getValeur() << " " << t->getCotes()[1]->getCartesC()[i]->getCouleur() << endl;
	}

	t->ajout_c(joker, 1);
	t->ajout_c(joker2, 1);
	t->ajout_c(joker3, 1);


	auto startTime = std::chrono::high_resolution_clock::now();

	//t->claimTuile(0, tuile);
	auto endTime = std::chrono::high_resolution_clock::now();
	cout << "gagnant: " << t->getClaim() << endl;

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
	cout << *t;
	*/

	Jeu* j = new Jeu();

	j->printTitles();
	j->menu_selection();

	return 0;
}