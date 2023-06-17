#pragma once
#ifndef JEU_H
#define JEU_H

#include "IA.h"
#include "Joueur.h"
#include "Pioche_c.h"
#include "Pioche_t.h"
#include "Tuile.h"


// vecteur de joueurs et boucler sur le vecteur avec des fonctions pareilles pour chaque
class Jeu
{
private:
	vector<Joueur*> joueurs;

	Pioche_c* pioche_c;
	//Pioche_t pioche_t;
	vector<Combinaison*> vic;
	vector<Tuile*> plateau;

	//singleton
	static Jeu* jeuUnique;



public:

	//méthodes pour le singleton
	static Jeu& donneInstance();
	static void libereInstance();
	static int possibleInstance() {
		if (jeuUnique == nullptr)
			return 1;
		return 0;
	}


	Jeu() {


		vic.push_back(new Combinaison(false, false, false));
		vic.push_back(new Combinaison(true, false, false));
		vic.push_back(new Combinaison(false, true, false));
		vic.push_back(new Combinaison(false, false, true));
		vic.push_back(new Combinaison(true, true, false));

		for (unsigned int i = 0; i < 9; i++) {
			Tuile* t = new Tuile(3, vic, 2);
			plateau.push_back(t);
		}

		pioche_c = new Pioche_c();

		Carte_c::getCouleurs().push_back("Vert");
		Carte_c::getCouleurs().push_back("Bleu");
		Carte_c::getCouleurs().push_back("Rouge");
		Carte_c::getCouleurs().push_back("Jaune");
		Carte_c::getCouleurs().push_back("Violet");
		Carte_c::getCouleurs().push_back("Marron");

		for (unsigned int i = 1; i < 10; i++) {
			for (unsigned int j = 1; j < Carte_c::getCouleurs().size(); j++) {
				pioche_c->push(new Carte_c(i, Carte_c::getCouleurs()[j]));
			}
		}

		pioche_c->shuffle();
	}

	virtual ~Jeu() {
		for (auto t : plateau)
			delete t;
		plateau.clear();

		for (auto combi : vic)
			delete combi;
		vic.clear();

		for (auto j : joueurs)
			delete j;
		joueurs.clear();

		delete pioche_c;

	}

	vector<Tuile*> getPlateau() const {
		return this->plateau;
	}

	Joueur* getJoueur1() const {
		return joueurs[0];
	}

	Joueur* getJoueur2() const {
		return joueurs[1];
	}

	vector<Joueur*> getJoueurs() const {
		return joueurs;
	}

	Pioche_c* getPioche_c() const {
		return pioche_c;
	}

	void claim(int idJoueur);

	void claimIA(int idJoueur);

	/// <summary>
	/// Allows the user to pick the first card of the classical pick
	/// </summary>
	/// <returns>The reference of the card</returns>
	Carte_c& piocher_c() {
		if (pioche_c->getSize() != 0)
			return *pioche_c->pop();
	}

	//Pioche_t getPioche_t() const {
	//	return pioche_t;
	//}

	void setJoueur1(string& s) {
		joueurs.push_back(new Joueur(s));
	}

	void setJoueur2(string& s) {
		joueurs.push_back(new Joueur(s));
	}

	void setIA() {
		joueurs.push_back(new IA());
	}


	bool estGagnant(int id_joueur);
	void displayBoard() const;
	void printTitles() const;
	void displayMenu() const;
	int getUserInput() const;

	void menu_selection();
	void playerSelection();
	int victory();
	virtual void startGame();
	void distribuerCartes(int nb_a_distribuer);

	//void play_card_c(int id_j, int id_tuile, Carte_c& c)
};


inline ostream& operator<< (ostream& os, const Jeu& j) {
	os << j.getJoueur1();
	os << j.getJoueur2();
	return os;
}

#endif // !JEU_H



