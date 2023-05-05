#pragma once
#ifndef TUILE_H
#define TUILE_H
#include "Carte.h"
#include "Carte_c.h"
#include "Carte_t.h"
#include <vector>
#include <list>
#include "Combinaison.h"

using namespace std;

class Tuile
{
private:
	int nbCarteMax;

	vector<Carte_c> carteC_j1;
	vector<Carte_t> carteT_j1;
	int nbCarteJoue_J1;

	vector<Carte_c> carteC_j2;
	vector<Carte_t> carteT_j2;
	int nbCarteJoue_J2;

	vector<int* []> hist; //pas sur pour le tableau de pointeur sur des int pour l'historique mais à changer

	vector<Combinaison> victoirePossible;

	int claim;

public:
	Tuile() {
	};

};

#endif // !TUILE_H



