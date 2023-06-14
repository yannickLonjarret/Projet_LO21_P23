#pragma once
#include <vector>
#include <iostream>

#include "Carte_c.h"
using namespace std;

/// <summary>
/// Classe combinaison
/// Elle permet de d�terminer l'ensemble de carte gagnant entre plusieurs ensembles
/// Elle permet �galement de donner les mani_res de gagner sur une tuile pr�cise
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
	/// Constructeur de combinaison � partir de cartes
	/// Permet d'�valuer le gagnant sur les tuiles
	/// </summary>
	/// <param name="combi">Vecteur de cartes pos�es par un joueur/IA </param>
	/// <param name="szCombi">Taille de la combinaison</param>
	Combinaison(vector<Carte_c*>& combi, int szCombi = 3) : taille_combi(szCombi) {

		is_suite = isSuite(combi);
		is_couleur = isCouleur(combi);
		is_brelan = isBrelan(combi);

		valSumCartes = calculSumCombi(combi);
		scoreCombi = calculScoreCombi(this);

		
	}

	/// <summary>
	/// Constructeur de combinaison � partir de propri�t�s de combinaisons
	/// Permet de donner les victoires possibles sur une tuile
	/// </summary>
	/// <param name="suite">Si la combinaison est une suite de valeur</param>
	/// <param name="couleur">Si la combinaison poss�de que des cartes de m�me couleurs</param>
	/// <param name="brelan">Si la combinaison poss�de que des cartes de m�me valeurs</param>
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
	/// Surcharge de l'op�rateur >
	/// D�termine si une combinaison est strictement sup�rieure � l'autre
	/// en �valuant le score puis la valeur de la somme si n�cessaire 
	/// </summary>
	/// <param name="other">Une r�ference sur l'autre combinaison</param>
	/// <returns>Vrai si la combinaison est strictement sup�rieure, faux sinon</returns>
	bool operator>(Combinaison& other) {
		if (getScoreCombi() == other.getScoreCombi())
			return getSumCombi() > other.getSumCombi();

		return (getScoreCombi() > other.getScoreCombi());
	}

	/// <summary>
	/// D�finition d'un comparateur entre pointeur
	/// D�termine si une combinaison est strictement sup�rieure � l'autre
	/// en �valuant le score puis la valeur de la somme si n�cessaire 
	/// </summary>
	/// <param name="combi1">Combinaison dont on souhaite conna�tre la sup�riorit�</param>
	/// <param name="combi2">Combinaison avec laquelle on compare la permi�re</param>
	/// <returns>Vrai si la premi�re combinaison est strictement sup�rieure, faux sinon</returns>
	static bool cmpSup(Combinaison* combi1, Combinaison* combi2) {
		if (combi1->getScoreCombi() == combi2->getScoreCombi())
			return combi1->getSumCombi() > combi2->getSumCombi();

		return (combi1->getScoreCombi() > combi2->getScoreCombi());
	}

};
