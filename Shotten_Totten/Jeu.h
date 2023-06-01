#pragma once
#ifndef JEU_H
#define JEU_H

#include "Joueur.h"
#include "Pioche_c.h"
#include "Pioche_t.h"
#include "Tuile.h"


class Jeu
{
private:
	Joueur j1;
	Joueur j2;

	Pioche_c pioche_c;
	Pioche_t pioche_t;


	//defausse ? classe à part ?
	Tuile* plateau;

public:
	Jeu() = default;

	Joueur getJoueur1() const {
		return j1;
	}

	Joueur getJoueur2() const {
		return j2;
	}

	Pioche_c getPioche_c() const {
		return pioche_c;
	}

	Pioche_t getPioche_t() const {
		return pioche_t;
	}

	void setJoueur1(const string& s) {
		j1 = Joueur(s);
	}

	void setJoueur2(const string& s) {
		j2 = Joueur(s);
	}

	void printPlateau() const;
	void printTitles() const;
	void displayMenu() const;
	int getUserInput() const;

	void playGame();
	bool playerSelection();
};



inline ostream& operator<< (ostream& os, const Jeu& j) {
	os << j.getJoueur1();
	os << j.getJoueur2();
	return os;
}

#endif // !JEU_H



