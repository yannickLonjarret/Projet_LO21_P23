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

	vector<Carte_c> cartesC_j1;
	vector<Carte_t> cartesT_j1;
	int nbCartesJoue_J1;

	vector<Carte_c> cartesC_j2;
	vector<Carte_t> cartesT_j2;
	int nbCarteJoues_J2;

	vector<int* []> hist; //pas sur pour le tableau de pointeur sur des int pour l'historique mais à changer

	vector<Combinaison> victoirePossible;

	int claim;

public:
	Tuile(int nb_cartes, vector<Combinaison> vicPoss) {
		this->nbCarteMax = nb_cartes;
		this->victoirePossible = vector<Combinaison>(vicPoss);

		this->nbCarteJoues_J2 = 0;
		this->nbCartesJoue_J1 = 0;
		
		this->claim = 0;

		this->cartesC_j1 = vector<Carte_c>();
		this->cartesC_j2 = vector<Carte_c>();

		this->cartesT_j1 = vector<Carte_t>();
		this->cartesT_j2 = vector<Carte_t>();

	};

};

#endif // !TUILE_H



