#pragma once
#include <vector>
#include <iostream>

#include "Carte_c.h"
using namespace std;

/// <summary>
/// Classe combinaison
/// Elle permet de déterminer l'ensemble de carte gagnant entre plusieurs ensembles
/// Elle permet également de donner les mani_res de gagner sur une tuile précise
/// </summary>
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

	/// <summary>
	/// Constructeur de combinaison à partir de cartes
	/// Permet d'évaluer le gagnant sur les tuiles
	/// </summary>
	/// <param name="combi">Vecteur de cartes posées par un joueur/IA </param>
	/// <param name="szCombi">Taille de la combinaison</param>
	Combinaison(vector<Carte_c*>& combi, int szCombi = 3) : taille_combi(szCombi) {

		is_suite = isSuite(combi);
		is_couleur = isCouleur(combi);
		is_brelan = isBrelan(combi);

		valSumCartes = calculSumCombi(combi);
		scoreCombi = calculScoreCombi(this);

		
	}

	/// <summary>
	/// Constructeur de combinaison à partir de propriétés de combinaisons
	/// Permet de donner les victoires possibles sur une tuile
	/// </summary>
	/// <param name="suite">Si la combinaison est une suite de valeur</param>
	/// <param name="couleur">Si la combinaison possède que des cartes de même couleurs</param>
	/// <param name="brelan">Si la combinaison possède que des cartes de même valeurs</param>
	/// <param name="szCombi"></param>
	Combinaison(bool suite, bool couleur, bool brelan, int szCombi = 3) : taille_combi(szCombi) {

		is_suite = suite;
		is_couleur = couleur;
		is_brelan = brelan;

		valSumCartes = -1;
		scoreCombi = calculScoreCombi(this);
	}

	bool isSuite(vector<Carte_c*> combi);

	bool isBrelan(vector<Carte_c*> combi);

	bool isCouleur(vector<Carte_c*> combi);

	int calculSumCombi(vector<Carte_c*> combi);

	int calculScoreCombi(Combinaison* c);

	void dropDown(vector<Combinaison*> lstCombi);

	bool isCombiInLst(int scoreCombi, vector<Combinaison*> lstCombi);

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

	void setDefault() {
		is_brelan = false;
		is_couleur = false;
		is_suite = false;
		scoreCombi = 1;
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


	/// <summary>
	/// Surcharge de l'opérateur >
	/// Détermine si une combinaison est strictement supérieure à l'autre
	/// en évaluant le score puis la valeur de la somme si nécessaire 
	/// </summary>
	/// <param name="other">Une réference sur l'autre combinaison</param>
	/// <returns>Vrai si la combinaison est strictement supérieure, faux sinon</returns>
	bool operator>(Combinaison& other) {
		if (getScoreCombi() == other.getScoreCombi())
			return getSumCombi() > other.getSumCombi();

		return (getScoreCombi() > other.getScoreCombi());
	}

	/// <summary>
	/// Définition d'un comparateur entre pointeur
	/// Détermine si une combinaison est strictement supérieure à l'autre
	/// en évaluant le score puis la valeur de la somme si nécessaire 
	/// </summary>
	/// <param name="combi1">Combinaison dont on souhaite connaître la supériorité</param>
	/// <param name="combi2">Combinaison avec laquelle on compare la permière</param>
	/// <returns>Vrai si la première combinaison est strictement supérieure, faux sinon</returns>
	static bool cmpSup(Combinaison* combi1, Combinaison* combi2) {
		if (combi1->getScoreCombi() == combi2->getScoreCombi())
			return combi1->getSumCombi() > combi2->getSumCombi();

		return (combi1->getScoreCombi() > combi2->getScoreCombi());
	}

};
