#pragma once
#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include "Carte.h"

using namespace std;

class Joueur {
private:
	string nom;
	int nb_cartes;
	int score;
	Carte* main;

public:
	Joueur(string const& n, int nb_c, int s, Carte* m) :nom(n), nb_cartes(nb_c), score(s), main(m) {

	}
};

#endif // !JOUEUR_H

