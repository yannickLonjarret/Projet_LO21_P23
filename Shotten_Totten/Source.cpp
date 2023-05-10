#include <iostream>
#include <vector>
#include <algorithm>

#include "Combinaison.h"
#include "Tuile.h"

int main() {

	vector<Combinaison*> vic;

	vector<Carte_c*> cards;

	vic.push_back(new Combinaison(false, false, false));
	vic.push_back(new Combinaison(true, false, false));
	vic.push_back(new Combinaison(false, true, false));
	vic.push_back(new Combinaison(false, false, true));
	vic.push_back(new Combinaison(true, true, false));

	Tuile* t = new Tuile(3, vic);

	t->ajout_c(new Carte_c(1, Couleur::Rouge), 1);
	t->ajout_c(new Carte_c(2, Couleur::Bleu), 1);
	t->ajout_c(new Carte_c(4, Couleur::Rouge), 1);

	t->claimTuile(1);
	
	t->ajout_c(new Carte_c(1, Couleur::Rouge), 2);
	t->ajout_c(new Carte_c(2, Couleur::Rouge), 2);
	t->ajout_c(new Carte_c(3, Couleur::Rouge), 2);

	t->claimTuile(1);

	t->claimTuile(2);

	cout << "gagnant: " << t->getClaim() << endl;

	
}