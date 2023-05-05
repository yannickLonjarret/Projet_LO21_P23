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
	int nbCartes_J1;

	vector<Carte_c> cartesC_j2;
	vector<Carte_t> cartesT_j2;
	int nbCartes_J2;

	vector<int* []> hist; //pas sur pour le tableau de pointeur sur des int pour l'historique mais à changer

	vector<Combinaison> victoirePossible;

	int claim;

public:
	Tuile(int nb_cartes, vector<Combinaison> vicPoss) {
		this->nbCarteMax = nb_cartes;
		this->victoirePossible = vector<Combinaison>(vicPoss);

		this->nbCartes_J2 = 0;
		this->nbCartes_J1 = 0;
		
		this->claim = 0;

		this->cartesC_j1 = vector<Carte_c>();
		this->cartesC_j2 = vector<Carte_c>();

		this->cartesT_j1 = vector<Carte_t>();
		this->cartesT_j2 = vector<Carte_t>();

	};

	void ajout_c(Carte_c c, vector<Carte_c> cartes){


	}


	bool isClaimable() {
		int nb_c1, nb_c2, nb_cMax;

		bool claimable = false;

		nb_c1 = this->getNbCartes_J1();
		nb_c2 = this->getNbCartes_J2();
		nb_cMax = this->getNbCartesMax();

		if (nb_c1 == nb_cMax || nb_c2 == nb_cMax) {
			if (abs(nb_c1 - nb_c2) <= 1)
				claimable = true;
		}

		return claimable;
	}

	int getNbCartes_J1() {
		return this->nbCartes_J1;
	}

	int getNbCartes_J2() {
		return this->nbCartes_J2;
	}

	int getNbCartesMax() {
		return this->nbCarteMax;
	}

	void setNbCartes_J1(int newNb){
		this->nbCartes_J1 = newNb;
	}

	void setNbCartes_J2(int newNb) {
		this->nbCartes_J2 = newNb;
	}
};

#endif // !TUILE_H



