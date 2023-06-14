#include "Combinaison.h"

/// <summary>
/// Permet de d�terminer si les valeurs d'un ensemble de carte forment une suite de valeur num�rique
/// </summary>
/// <param name="combi">Suite de carte � �valuer</param>
/// <returns>Vrai si c'est une suite num�rique, faux autrement</returns>
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

/// <summary>
/// Permet de d�terminer si les valeurs d'un ensemble de carte sont toutes identiques
/// </summary>
/// <param name="combi">Suite de carte � �valuer</param>
/// <returns>Vrai si c'est un brelan, faux autrement</returns>
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

/// <summary>
/// Permet de d�terminer si les couleurs d'un ensemble de carte sont toutes identiques
/// </summary>
/// <param name="combi">Suite de carte � �valuer</param>
/// <returns>Vrai si c'est une couleur, faux autrement</returns>
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

/// <summary>
/// Calcule la somme de la valeur des cartes d'une suite de carte
/// </summary>
/// <param name="combi">Suite de carte dont on veux conna�tre la somme des valeurs des cartes</param>
/// <returns>Somme des valeurs des cartes</returns>
int Combinaison::calculSumCombi(vector<Carte_c*> combi) {
	int s = 0;

	for (size_t i = 0; i < getTailleCombi(); i++) {
		s += combi[i]->getValeur();
	}
	return s;
}

/// <summary>
/// D�termine le score d'une combinaison en consultant ses caract�ristiques.
/// Le score est un entier arbitraire choisi en fonction des r�gles du jeu
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
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

/// <summary>
/// Permet de convertir une combinaison donn�e en la premi�re variante inf�rieure (ou �gale) jouable.
/// Existe pour g�rer les cartes modes de combat de la variante tactique
/// </summary>
/// <param name="lstCombi">Ensemble de combinaison pouvant �tre jou�e sur une tuile donn�e</param>
void Combinaison::dropDown(vector<Combinaison*> lstCombi) {
	switch (getScoreCombi())
	{
	case 5:
		//Pas de dropdown si la combinaison existe
		if (isCombiInLst(5, lstCombi))
			return;

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
		//Pas de dropdown si la combinaison existe
		if (isCombiInLst(4, lstCombi))
			return;

		//Un brelan peut �tre une couleur dans la variante tactique
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
		//Pas de dropdown si la combinaison existe
		if (isCombiInLst(3, lstCombi))
			return;

		setDefault();
		convertToSomme();

		return;

	case 2:
		//Pas de dropdown si la combinaison existe
		if (isCombiInLst(2, lstCombi))
			return;

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

/// <summary>
/// Permet de d�terminer l'existence d'une combinaison dans une liste � partir du score de la combinaison
/// </summary>
/// <param name="scoreCombi">Score de la combinaison que l'on souhaite chercher</param>
/// <param name="lstCombi">Ensemble de combinaison parmis lesquels chercher</param>
/// <returns>Vrai si la combinaison existe, faux autrement</returns>
bool Combinaison::isCombiInLst(int scoreCombi, vector<Combinaison*> lstCombi) {
	for (int i = 0; i < lstCombi.size(); i++) {
		if (lstCombi[i]->getScoreCombi() == scoreCombi)
			return true;
	}

	return false;
}