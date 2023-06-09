#include "Combinaison.h"

bool Combinaison::isSuite(vector<Carte_c*> combi) {
	bool res = true;

	size_t i = 1;

	while (res && i < getTailleCombi()) {

		if (combi[i - 1]->getValeur() != combi[i]->getValeur() - 1)
			res = false;

		i++;
	}

	return res;
}

bool Combinaison::isBrelan(vector<Carte_c*> combi) {
	bool res = true;

	size_t i = 1;

	while (res && i < getTailleCombi()) {

		if (combi[i - 1]->getValeur() != combi[i]->getValeur())
			res = false;

		i++;
	}

	return res;
}

bool Combinaison::isCouleur(vector<Carte_c*> combi) {
	bool res = true;

	size_t i = 1;

	while (res && i < getTailleCombi()) {

		if (combi[i - 1]->getCouleur() != combi[i]->getCouleur())
			res = false;

		i++;
	}

	return res;

}

int Combinaison::calculSumCombi(vector<Carte_c*> combi) {
	int s = 0;

	for (size_t i = 0; i < getTailleCombi(); i++) {
		s += combi[i]->getValeur();
	}
	return s;
}

int Combinaison::calculScoreCombi(Combinaison* c) {
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

void Combinaison::dropDown(vector<Combinaison*> lstCombi) {
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
		if (isCombiInLst(3, lstCombi) && getCouleur()) {
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


bool Combinaison::isCombiInLst(int scoreCombi, vector<Combinaison*> lstCombi) {
	for (int i = 0; i < lstCombi.size(); i++) {
		if (lstCombi[i]->getScoreCombi() == scoreCombi)
			return true;
	}

	return false;
}