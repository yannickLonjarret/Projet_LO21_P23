#include <iostream>
#include <vector>
#include <algorithm>

#include "Combinaison.h"
#include "Tuile.h"

int main() {

	vector<Combinaison*> vic;

	vector<Carte_c*> cards;
	vector<Tuile*> tuile;


	vic.push_back(new Combinaison(false, false, false));
	vic.push_back(new Combinaison(true, false, false));
	vic.push_back(new Combinaison(false, true, false));
	vic.push_back(new Combinaison(false, false, true));
	vic.push_back(new Combinaison(true, true, false));

	Tuile* t = new Tuile(3, vic);

	tuile.push_back(t);

	t->ajout_c(new Carte_c(9, Couleur::Rouge), 2);
	t->ajout_c(new Carte_c(8, Couleur::Rouge), 2);
	t->ajout_c(new Carte_c(7, Couleur::Rouge), 2);
	
	cards = t->getCartesJ1();
	cout << "Nb cartes J1: " << t->getCartesJ1().size() << endl;

	for (int i = 0; i < cards.size(); i++) {
		cout << cards[i]->getValeur() << endl;
	}
	cout << "Nb cartes J2: "<<t->getCartesJ2().size() << endl;
	//t->claimTuile(1);
	
	t->ajout_c(new Carte_c(9, Couleur::Bleu), 1);
	t->ajout_c(new Carte_c(8, Couleur::Bleu), 1);
	//t->ajout_c(new Carte_c(7, Couleur::Bleu), 1);
	
	cout << "Nb cartes J2: " << t->getCartesJ2().size() << endl;
	
	cards = t->getCartesJ2();

	for (int i = 0; i < cards.size(); i++) {
		cout << cards[i]->getValeur() << endl;
	}

	t->claimTuile(2, tuile);

	cout << "gagnant: " << t->getClaim() << endl;

	
}