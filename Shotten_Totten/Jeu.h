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

	vector<Tuile*> plateau;
	//je dois initialiser les tuiles
	//pour chaque tuile itérer sur les joueurs du vecteur
	//il faut 9 tuile puis pour chaque joueur créer un côté (selon l'odre du vecteur)




public:
	Jeu() {

		vector<Combinaison*> vic;
		vic.push_back(new Combinaison(false, false, false));
		vic.push_back(new Combinaison(true, false, false));
		vic.push_back(new Combinaison(false, true, false));
		vic.push_back(new Combinaison(false, false, true));
		vic.push_back(new Combinaison(true, true, false));

		for (unsigned int i = 0; i < 9; i++) {
			Tuile* t = new Tuile(3, vic, 2);
			plateau.push_back(t);
		}
		vector<Joueur> joueurs;

		pioche_c = new Pioche_c();
		vector<string> couleurs = { "Vert", "Bleu", "Rouge", "Jaune", "Violet", "Marron" };
		
		for (unsigned int i = 1; i < 10; i++) {
			for (unsigned int j = 0; j < couleurs.size(); j++) {
				pioche_c->push(new Carte_c(i, couleurs[j]));
			}
		}

		pioche_c->shuffle(); 
	}

	virtual ~Jeu() {
		for (unsigned int i = 0; i < joueurs.size(); i++) delete joueurs[i]; 
		delete Pioche_c;
		for (unsigned int i = 0; i < plateau.size(); i++) delete plateau[i];
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


	void displayBoard() const;
	void printTitles() const;
	void displayMenu() const;
	int getUserInput() const;

	void menu_selection();
	void playerSelection();
	bool estGagnant(int id_joueur); 
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



