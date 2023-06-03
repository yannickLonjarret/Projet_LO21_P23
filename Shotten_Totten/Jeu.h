#pragma once
#ifndef JEU_H
#define JEU_H

#include "Joueur.h"
#include "Pioche_c.h"
#include "Pioche_t.h"
#include "Tuile.h"


// vecteur de joueurs et boucler sur le vecteur avec des fonctions pareilles pour chaque
class Jeu
{
private:
	Joueur j1;
	Joueur j2;

	Pioche_c pioche_c;
	//Pioche_t pioche_t;

	vector<Tuile*> plateau;
	//je dois initialiser les tuiles
	//pour chaque tuile itérer sur les joueurs du vecteur
	//il faut 9 tuile puis pour chaque joueur créer un côté (selon l'odre du vecteur)




public:
	Jeu();

	Joueur getJoueur1() const {
		return j1;
	}

	Joueur getJoueur2() const {
		return j2;
	}

	Pioche_c getPioche_c() const {
		return pioche_c;
	}

	//Pioche_t getPioche_t() const {
	//	return pioche_t;
	//}

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
	void poser_carte_c(int id_j, int id_tuile, const Carte_c& c) {

	}
	void poser_carte_t(int id_j, int id_tuile, const Carte_t& ct);

	void menu_selection();
	void playerSelection();
	void startGame(const Joueur& j1, const Joueur& j2);
};



inline ostream& operator<< (ostream& os, const Jeu& j) {
	os << j.getJoueur1();
	os << j.getJoueur2();
	return os;
}

#endif // !JEU_H



