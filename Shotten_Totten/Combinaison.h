#pragma once
#include <vector>
#include <iostream>

#include "Carte_c.h"
using namespace std;


class Combinaison
{
private:
	int taille_combi;
	int scoreCombi;
	int valSumCartes;
	bool is_suite;
	bool is_couleur;
	bool is_brelan;

public:

	Combinaison(vector<Carte_c*>& combi, int szCombi = 3) : taille_combi(szCombi) {

		is_suite = isSuite(combi);
		is_couleur = isCouleur(combi);
		is_brelan = isBrelan(combi);

		valSumCartes = calculSumCombi(combi);
		scoreCombi = calculScoreCombi(this);

		
	}

	Combinaison(bool suite, bool couleur, bool brelan, int szCombi = 3) : taille_combi(szCombi) {

		is_suite = suite;
		is_couleur = couleur;
		is_brelan = brelan;

		valSumCartes = -1;
		scoreCombi = calculScoreCombi(this);
	}

	bool isSuite(vector<Carte_c*> combi) {
		bool res = true;

		size_t i = 1;

		while (res && i < getTailleCombi()) {

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

		for (size_t i = 0; i < getTailleCombi(); i++) {
			s += combi[i]->getValeur();
		}
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

	void dropDown(vector<Combinaison*> lstCombi) {
		switch (getScoreCombi())
		{
		case 5:
			if (isCombiInLst(3, lstCombi)) {
				setDefault();
				convertToCouleur();
			}
			else if (isCombiInLst(2, lstCombi)) {
				setDefault();
				convertToSuite();
			}
			else {
				setDefault();
				convertToSomme();
			}
			return;

		case 4:
			if (isCombiInLst(3, lstCombi)) {
				setDefault();
				convertToCouleur();
			}
			else {
				setDefault();
				convertToSomme();
			}
			return;

		case 3:
			setDefault();
			convertToSomme();

			return;

		case 2:
			setDefault();
			convertToSomme();

			return;
			break;
		case 1:
			//Do nothing
			break;
		default:
			cout << "Erreur Dropdown combi: score inexistant" << endl;
			break;
		}

		return;
	}


	bool isCombiInLst(int scoreCombi, vector<Combinaison*> lstCombi) {
		for (int i = 0; i < lstCombi.size(); i++) {
			if (lstCombi[i]->getScoreCombi() == scoreCombi)
				return true;
		}

		return false;
	}


	void setDefault() {
		is_brelan = false;
		is_couleur = false;
		is_suite = false;
		scoreCombi = 1;
	}

	void convertToCouleur() {
		setCouleur(true);
		setScoreCombi(calculScoreCombi(this));
	}

	void convertToSuite() {
		setSuite(true);
		setScoreCombi(calculScoreCombi(this));
	}

	void convertToSomme() {

		setScoreCombi(calculScoreCombi(this));
	}

	void setSuite(bool s) {
		is_suite = s;
	}

	void setCouleur(bool s) {
		is_couleur = s;
	}

	int getTailleCombi() {
		return taille_combi;
	}

	void setScoreCombi(int v) {
		scoreCombi = v;
	}

	void setSumCombi(int s) {
		valSumCartes = s;
	}

	int getScoreCombi() {
		return scoreCombi;
	}

	int getSumCombi() {
		return valSumCartes;
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

	static bool cmpSup(Combinaison* combi1, Combinaison* combi2) {
		if (combi1->getScoreCombi() == combi2->getScoreCombi())
			return combi1->getSumCombi() > combi2->getSumCombi();

		return (combi1->getScoreCombi() > combi2->getScoreCombi());
	}

};
