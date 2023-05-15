#pragma once
#ifndef COMBINAISON_H
#define COMBINAISON_H
#include <vector>
#include <iostream>
//#include "Tuile.h"

#include "Carte_c.h"
using namespace std;


class Combinaison
{
private:
	int taille_combi;
	int scoreCombi;
	int val_somme;
	bool is_suite;
	bool is_couleur;
	bool is_brelan;

public:

	Combinaison(vector<Carte_c*> & combi, int szCombi = 3): taille_combi(szCombi){
		
		is_suite = isSuite(combi);
		is_couleur = isCouleur(combi);
		is_brelan = isBrelan(combi);

		val_somme = calculSumCombi(combi);
		scoreCombi = calculScoreCombi(this);
	}

	Combinaison(bool suite, bool couleur, bool brelan, int szCombi = 3) : taille_combi(szCombi) {

		is_suite = suite;
		is_couleur = couleur;
		is_brelan = brelan;

		val_somme = -1;
		scoreCombi = calculScoreCombi(this);
	}

	bool isSuite(vector<Carte_c*> combi) {
		bool res = true;

		size_t i = 1;

		while(res && i < getTailleCombi()) {
			
			if (combi[i - 1]->getValeur() != combi[i]->getValeur() - 1)
				res = false;

			i++;
		}

		return res;
	}

	bool isBrelan(vector<Carte_c*> combi) {
		bool res = true;

		size_t i = 1;

		while (res && i < getTailleCombi()) {

			if (combi[i - 1]->getValeur() != combi[i]->getValeur())
				res = false;

			i++;
		}

		return res;
	}

	bool isCouleur(vector<Carte_c*> combi) {
		bool res = true;

		size_t i = 1;

		while (res && i < getTailleCombi()) {

			if (combi[i - 1]->getCouleur() != combi[i]->getCouleur())
				res = false;

			i++;
		}

		return res;

	}

	int calculSumCombi(vector<Carte_c*> combi) {
		int s = 0;

		for (size_t i = 0; i < getTailleCombi(); i++)
			s += combi[i]->getValeur();

		return s;
	}

	int calculScoreCombi(Combinaison* c) {
		if (c->getCouleur() && c->getSuite())
			return 5;

		if (c->getBrelan())
			return 4;

		if (c->getCouleur())
			return 3;

		if (c->getSuite())
			return 2;

		return 1;
	}

	int getTailleCombi() {
		return taille_combi;
	}

	void setScoreCombi(int v) {
		scoreCombi = v;
	}

	void setSumCombi(int s) {
		val_somme = s;
	}

	int getScoreCombi() {
		return scoreCombi;
	}

	int getSumCombi() {
		return val_somme;
	}

	bool getBrelan() {
		return is_brelan;
	}

	bool getCouleur() {
		return is_couleur;
	}

	bool getSuite() {
		return is_suite;
	}

	bool operator>(Combinaison& other) {
		if (getScoreCombi() == other.getScoreCombi())
			return getSumCombi() > other.getSumCombi();

		return (getScoreCombi() > other.getScoreCombi());
	}

};


#endif // !COMBINAISON_H


