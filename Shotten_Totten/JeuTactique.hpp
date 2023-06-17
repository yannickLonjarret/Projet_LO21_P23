#pragma once
#ifndef JeuTactique_H
#define JeuTactique_H
#include "Jeu.h"
#include "Carte_t.h"
#include "Carte_Ruse.h"
#include "Pioche_c.h"
#include "Pioche_t.h"
#include "Troupe_Elite.h"
#include "Mode_Combat.h"
#include "Defausse.h"
#include "Joueur.h"
#include <vector>
#include <iostream>
#include <cstdlib> 

using namespace std;

/// <summary>
/// Represents the tactical version of the game, with specific conditions and methods
/// </summary>
class JeuTactique : public Jeu {
private:
	//singleton
	static JeuTactique* jeuTactiqueUnique;
	/// <summary>
	/// pioche_tact represents the tactical deck
	/// </summary>
	Pioche_t pioche_tact;
	/// <summary>
	/// defausse represents the collections of discarded cards (tactical and potentially classical either)
	/// </summary>
	Defausse defausse;
	/// <summary>
	/// nb_cartes_tactiques_jouees represents the number of tactical cards played by each player (each player id corresponds to each id of the vector)
	/// </summary>
	vector<int> nb_cartes_tactiques_jouees;
	/// <summary>
	/// nb_jokers_joues represents the number of joker cards played by each player (each player id corresponds to each id of the vector)
	/// </summary>
	vector<int> nb_jokers_joues;
public:
	//methodes pour le singleton
	static JeuTactique* donneInstance() {
		if (jeuTactiqueUnique == nullptr && Jeu::possibleInstance()) {
			jeuTactiqueUnique = new JeuTactique();
		}
		else if (!Jeu::possibleInstance()) {
			cout << "Erreur : un jeu classique est deja en cours" << endl;
		}
		return jeuTactiqueUnique;
	}

	static void libereInstance() {
		delete jeuTactiqueUnique;
		jeuTactiqueUnique = nullptr;
	}

	/// <summary>
	/// Constructor which creates the deck with all the specific tactical cards required, and initializes the discard defausse
	/// </summary>
	JeuTactique() : Jeu() {
		defausse = Defausse();
		pioche_tact = Pioche_t();
		nb_cartes_tactiques_jouees = { 0, 0 };
		nb_jokers_joues = { 0, 0 };

		// Creation des cartes Troupe d'Elite
		pioche_tact.push(new TroupeElite(elite, "Joker", -1,Carte_c::getCouleurs()[0], 1, 9));
		pioche_tact.push(new TroupeElite(elite, "Joker", -1, Carte_c::getCouleurs()[0], 1, 9));
		pioche_tact.push(new TroupeElite(elite, "Espion", -1, Carte_c::getCouleurs()[0], 7, 7));
		pioche_tact.push(new TroupeElite(elite, "Porte Bouclier", -1, Carte_c::getCouleurs()[0], 1, 3));

		// Creation des cartes Mode de Combat 
		/*Combinaison* c1 = ;
		Combinaison* c2 = new Combinaison(true, false, false);
		Combinaison* c3 = new Combinaison(false, true, false);
		Combinaison* c4 = new Combinaison(false, false, true);
		Combinaison* c5 = new Combinaison(true, true, false);*/
		vector<Combinaison*> vecteur_combi = { new Combinaison(false, false, false) }; 
		//vecteur_combi.push_back(new Combinaison(false, false, false));
		pioche_tact.push(new ModeCombat(combat, "Colin Maillard", -1, vecteur_combi)); 
		vecteur_combi = {};
		pioche_tact.push(new ModeCombat(combat, "Combat de boue", 4, vecteur_combi)); 
		
		// Creation des cartes Ruse
		/*
		0 = piocher 
		1 = placer carte sous pioche 
		2 = choisir carte de notre main (et le vecteur de Ruse) 
		3 = placer carte sur borne non revendiquee de notre côte ou defausser
		4 = choisir carte du cote adverse non revendiquee
		5 = defausser du cote adverse
		6 = placer devant une tuile non revendiquee de notre cote
		7 = choisir carte de notre cote
		*/
		
		vector<int> suite = { 0, 0, 0, 2, 1, 2, 1 };
		pioche_tact.push(new Ruse(ruse, "Chasseur de Tete", suite));
		suite = { 7, 3 };
		pioche_tact.push(new Ruse(ruse, "Stratège", suite));
		suite = {4, 5};
		pioche_tact.push(new Ruse(ruse, "Banshee", suite));
		suite = {4, 6};
		pioche_tact.push(new Ruse(ruse, "Traitre", suite));
		
		pioche_tact.shuffle();
	}

	~JeuTactique() {}

	/// <summary>
	/// Allows the user to pick the first card of the tactical deck
	/// </summary>
	/// <returns>The pointer of the card</returns>
	Carte_t* piocher_t() {
		if (pioche_tact.getSize() != 0)
			return pioche_tact.pop();
	}
	
	/// <summary>
	/// Method which start a tactical game, turn by turn
	/// </summary>
	void startGame() {
		system("CLS");

		string empty;
		int winner = -1;

		// On distribue les cartes
		distribuerCartes(7);

		while (winner == -1) {

			for (unsigned int i = 0; i < getJoueurs().size(); i++) {
				cout << R"(
 _____           _   _
|  __ \         | | (_)
| |__) |_ _ _ __| |_ _  ___    ___ _ __     ___ ___  _   _ _ __ ___
|  ___/ _` | '__| __| |/ _ \  / _ \ '_ \   / __/ _ \| | | | '__/ __|
| |  | (_| | |  | |_| |  __/ |  __/ | | | | (_| (_) | |_| | |  \__ \  
|_|   \__,_|_|   \__|_|\___|  \___|_| |_|  \___\___/ \__,_|_|  |___/


	   )" << endl;

				displayBoard();
				cout << "\nDefausse : " << defausse << endl;

				if (getJoueurs()[i]->estIA()) {
					// Poser la carte choisie
					cout << " ## C'est au joueur " << getJoueurs()[i]->getNom() << " de jouer ## " << endl;
					vector<Carte*> vect;
					int id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size() - 1);
					int id_carte = getJoueurs()[i]->choix_ia(0, getJoueurs()[i]->getNbCartes());
					bool tactique_jouable = tactiqueJouable(i);
					bool joker_jouable = jokerJouable(i);
					Carte* carte_a_jouer;
					if (id_carte >= getJoueurs()[i]->getCarteC().size()) {
						carte_a_jouer = (Carte*)getJoueurs()[i]->getCarteT()[id_carte - getJoueurs()[i]->getCarteC().size()];
					}
					else {
						carte_a_jouer = (Carte*)getJoueurs()[i]->getCarteC()[id_carte];
					}
					while (dynamic_cast<Carte_t*>(carte_a_jouer) != nullptr && (!tactique_jouable || (!joker_jouable && dynamic_cast<Carte_t*>(carte_a_jouer)->getNom() == "Joker"))){
						id_carte = getJoueurs()[i]->choix_ia(0, getJoueurs()[i]->getNbCartes());
						if (id_carte >= getJoueurs()[i]->getCarteC().size()) {
							carte_a_jouer = (Carte*)getJoueurs()[i]->getCarteT()[id_carte - getJoueurs()[i]->getCarteC().size()];
						}
						else {
							carte_a_jouer = (Carte*)getJoueurs()[i]->getCarteC()[id_carte];
						}
					}
					if (id_carte >= getJoueurs()[i]->getCarteC().size()) {
						nb_cartes_tactiques_jouees[i]++;
						carte_a_jouer = (Carte*)getJoueurs()[i]->getCarteT()[id_carte - getJoueurs()[i]->getCarteC().size()]; 
						if (dynamic_cast<Carte_t*>(carte_a_jouer)->getNom() == "Joker")
							nb_jokers_joues[i]++;
					}
					else {
						carte_a_jouer = (Carte*)getJoueurs()[i]->getCarteC()[id_carte];
					}
					if (typeid(*carte_a_jouer) == typeid(Ruse)) {
						getJoueurs()[i]->eraseCarte(carte_a_jouer);
						defausse.push(carte_a_jouer);
						execRuseIA(dynamic_cast<Ruse*>(carte_a_jouer), i);
						nb_cartes_tactiques_jouees[i]++;
					}
					else if (typeid(*carte_a_jouer) == typeid(ModeCombat)) {
						id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size()-1); 
						while (!tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {   
							id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size()-1);    
						}
						getJoueurs()[i]->poser_carte(carte_a_jouer, i, getPlateau()[id_tuile]);
						getPlateau()[id_tuile]->setNbCartesMax(dynamic_cast<ModeCombat*>(carte_a_jouer)->getNbCartes());
						getPlateau()[id_tuile]->setVictoires(dynamic_cast<ModeCombat*>(carte_a_jouer)->getCombinaison());
						nb_cartes_tactiques_jouees[i]++; 
					}
					else {
						id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size()-1); 
						while (!posePossible(getPlateau()[id_tuile], i) || !tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {
							id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size()-1); 
						}
						getJoueurs()[i]->poser_carte(carte_a_jouer, i, getPlateau()[id_tuile]);
						if (typeid(*carte_a_jouer) == typeid(TroupeElite)) {
							nb_cartes_tactiques_jouees[i]++;
							if (dynamic_cast<Carte_t*>(carte_a_jouer)->getNom() == "Joker")
								nb_jokers_joues[i]++;
						}
					}
					displayBoard();
					cout << "\nDefausse : " << defausse << endl;

					// Pas de revendication pour l'IA (choix arbitraire)

					// Piocher (classique / tactique)
					// while taillle_main < 7 -> s'adapte si une nouvelle carte Ruse
					while (getJoueurs()[i]->getNbCartes() < 7)
						piocher(choixPiocheIA(), i);  

					cout << getJoueurs()[i]->getNom() << " a termine son tour. \n## Entrez un caractere pour confirmer que vous avez change de place..." << endl;
					cin >> empty; 
				}
				else {
					getJoueurs()[i]->afficherMain();
					// Poser la carte choisie
					cout << " ## C'est au joueur " << getJoueurs()[i]->getNom() << " de jouer ## " << endl;
					vector<Carte*> vect = {}; 
					Carte* carte_a_jouer = choisirCarte(i, vect);
					bool tactique_jouable = tactiqueJouable(i);
					bool joker_jouable = jokerJouable(i);
					while (dynamic_cast<Carte_t*>(carte_a_jouer) != nullptr && (!tactique_jouable || (!joker_jouable && dynamic_cast<Carte_t*>(carte_a_jouer)->getNom() == "Joker"))) {
						if (!joker_jouable)
							cout << "Il est impossible de poser deux jokers" << endl;
						else
							cout << "Il est impossible de poser deux cartes tactiques de plus que votre adversaire" << endl;
						carte_a_jouer = choisirCarte(i, vect);
					}
					if (typeid(*carte_a_jouer) == typeid(Carte_t)) {
						nb_cartes_tactiques_jouees[i]++;
						if (dynamic_cast<Carte_t*>(carte_a_jouer)->getNom() == "Joker")
							nb_jokers_joues[i]++;
					}
					if (typeid(*carte_a_jouer) == typeid(Ruse)) {
						cout << "RUSE !" << endl;
						getJoueurs()[i]->eraseCarte(carte_a_jouer);
						defausse.push(carte_a_jouer);
						execRuse(dynamic_cast<Ruse*>(carte_a_jouer), i);
						cout << "Execution terminee ! " << endl;
						nb_cartes_tactiques_jouees[i]++;     
					}
					else if (typeid(*carte_a_jouer) == typeid(ModeCombat)) {
						cout << getJoueurs()[i]->getNom() << " choisis une borne[chiffre entre 1 et 9] : ";
						int id_tuile = getUserInput();
						id_tuile--;
						while (!checkBornes(0, 8, id_tuile) || !tuileNonRevendiquee(getPlateau()[id_tuile])) {
							cout << "Choix impossible, la borne est deja revendiquee ou inexistante, veuillez reessayer." << endl;
							cout << getJoueurs()[i]->getNom() << " choisis une borne[chiffre entre 1 et 9] : ";
							id_tuile = getUserInput();
							id_tuile--;
						}
						getJoueurs()[i]->poser_carte(carte_a_jouer, i, getPlateau()[id_tuile]);
						getPlateau()[id_tuile]->setNbCartesMax(dynamic_cast<ModeCombat*>(carte_a_jouer)->getNbCartes());
						getPlateau()[id_tuile]->setVictoires(dynamic_cast<ModeCombat*>(carte_a_jouer)->getCombinaison());
						cout << getPlateau()[id_tuile]->getVictoires().size() << endl;
						nb_cartes_tactiques_jouees[i]++;   
					}
					else {
						cout << getJoueurs()[i]->getNom() << " choisis une borne[chiffre entre 1 et 9] : ";
						int id_tuile = getUserInput();
						id_tuile--;
						cout << checkBornes(0, 8, id_tuile) << endl;
						while (!checkBornes(0, 8, id_tuile) || !posePossible(getPlateau()[id_tuile], i) || !tuileNonRevendiquee(getPlateau()[id_tuile])) {
							cout << "Choix impossible, la borne est pleine, deja revendiquee ou inexistante, veuillez reessayer." << endl;
							cout << getJoueurs()[i]->getNom() << " choisis une borne[chiffre entre 1 et 9] : ";
							id_tuile = getUserInput();
							id_tuile--;
						}
						getJoueurs()[i]->poser_carte(carte_a_jouer, i, getPlateau()[id_tuile]);
						if (typeid(*carte_a_jouer) == typeid(TroupeElite)) {
							nb_cartes_tactiques_jouees[i]++;
							if (dynamic_cast<Carte_t*>(carte_a_jouer)->getNom() == "Joker")
								nb_jokers_joues[i]++;
						}
					}
					displayBoard();
					cout << "\nDefausse : " << defausse << endl;
					getJoueurs()[i]->afficherMain();

					// Possible revendication
					string choix;
					cout << "Voulez-vous revendiquer une borne ? (O / N) ";
					cin >> choix;
					if (choix.front() == 'O' || choix.front() == 'o') {
						claim(i);
					}

					// Piocher (classique / tactique)
					// while taillle_main < 7 -> s'adapte si une nouvelle carte Ruse
					while (getJoueurs()[i]->getNbCartes() < 7)
						piocher(choixPioche(), i);

					cout << getJoueurs()[i]->getNom() << " a termine son tour. \n## Entrez un caractere pour confirmer que vous avez change de place..." << endl;
					cin >> empty; 
				}

				for (int i = 0; i < 100; i++)
					cout << endl;
				winner = victory();
				if (winner != -1) break; 
			}
		}
		cout << "Partie terminee, le gagnant est " << getJoueurs()[winner]->getNom();
		getJoueurs()[winner]->setScore(getJoueurs()[winner]->getScore() + 1);
	}

	/// <summary>
	/// Allows the user to check if a number is within an interval [b1, b2] 
	/// </summary>
	/// <param name="b1">The inferior born of the interval</param>
	/// <param name="b2">The superior born of the interval</param>
	/// <param name="input">The number to check</param>
	/// <returns>A boolean (true if it is within, false if not)</returns>
	bool checkBornes(int b1, int b2, int input) {
		return b1 <= input && input <= b2;  
	}

	/// <summary>
	/// Allows the user to check if a Tuile object is not already claimed
	/// </summary>
	/// <param name="tuile">The Tuile object to check</param>
	/// <returns>A boolean (true if not already claimed, false if it is)</returns>
	bool tuileNonRevendiquee(Tuile* tuile) {
		return tuile->getClaim() == -1; 
	}

	/// <summary>
	/// Allows the user to check if a card can be placed on a tile
	/// </summary>
	/// <param name="tuile">The tile where the card should be placed</param>
	/// <param name="id_joueur">The id of the user who wants to place the card</param>
	/// <returns>A boolean (true if it can be placed, false if not)</returns>
	bool posePossible(Tuile* tuile, int id_joueur) {
		int nb_cartes_posees = tuile->getCotes()[id_joueur]->getNbCartes(); 
		int nb_cartes_posables = tuile->getNbCartesMax();
		return (nb_cartes_posees != nb_cartes_posables); 
	}

	/// <summary>
	/// Allows the user to ask the player in which deck they want to pick
	/// </summary>
	/// <returns>0 for the classical one, 1 for the tactical one, -1 for non (both empty)</returns>
	int choixPioche() const {
		if (getPioche_c()->getSize() == 0) {
			cout << "Vous ne pouvez piocher que dans la pioche classique, la pioche tactique est vide." << endl;
			return 0;
		}
		else if (pioche_tact.getSize() == 0) {
			cout << "Vous ne pouvez piocher que dans la pioche tactique, la pioche classique est vide." << endl; 
			return 1;
		}
		else if (getPioche_c()->getSize() == 0 && pioche_tact.getSize() == 0) {
			cout << "Vous ne pouvez plus piocher, les pioches sont vides." << endl;
			return -1;
		}
		else {
			std::cout << "Voulez-vous piocher dans la pioche classique ou tactique (C/T) : " << std::endl;
			string choix;
			std::cin >> choix;
			while (true) {
				if (choix.front() == 'C' || choix.front() == 'c')
					return 0;
				else if (choix.front() == 'T' || choix.front() == 't')
					return 1;
				else
					std::cout << "Choix invalide, recommencez (C/T) : " << std::endl;
				choix = "";
			}
		}
	}

	/// <summary>
	/// Allows the user to ask the IA in which deck they want to pick
	/// </summary>
	/// <returns>0 for the classical one, 1 for the tactical one, -1 for non (both empty)</returns>
	int choixPiocheIA() {
		if (getPioche_c()->getSize() == 0)
			return 0;
		else if (pioche_tact.getSize() == 0)
			return 1;
		else if (getPioche_c()->getSize() == 0 && pioche_tact.getSize() == 0)
			return -1;
		else
			return rand() % 2;
	}

	/// <summary>
	/// Allows the user to pick in a deck
	/// </summary>
	/// <param name="choix_pioche">The id of the deck (0 = classical, 1 = tactical, -1 = none)</param>
	/// <param name="id_joueur">The id of the player picking a card</param>
	void piocher(int choix_pioche, int id_joueur) {
		if (choix_pioche)
			getJoueurs()[id_joueur]->ajouter_Carte_t(piocher_t());
		else if (choix_pioche == 0)
			getJoueurs()[id_joueur]->ajouter_Carte_c(&piocher_c());
	}

	/// <summary>
	/// Allows the user to add a card from a deck to the cards vector in a Ruse card
	/// </summary>
	/// <param name="choix_pioche">The id of a deck (0 = classical, 1 = tactical)</param>
	/// <param name="carte">The Ruse card where the picked card has to be added</param>
	void piocheRuse(int choix_pioche, Ruse* carte) {
		if (choix_pioche)
			carte->addCartes(piocher_t());
		else
			carte->addCartes((Carte*)&Jeu::piocher_c());
	}

	/// <summary>
	/// Allows the user to ask the player which card they want to play
	/// </summary>
	/// <param name="id_joueur">The id of the player</param>
	/// <param name="vecteur">The possible vector of a Ruse card to take into account</param>
	/// <returns>A pointer of the chosen card</returns>
	Carte* choisirCarte(int id_joueur, vector<Carte*> vecteur) {
		int nb_cartes;
		if (vecteur.size() == 0) {
			cout << " Choisis une carte [chiffre entre 1 et " << getJoueurs()[id_joueur]->getNbCartes() << "] : ";
			nb_cartes = getJoueurs()[id_joueur]->getNbCartes() - 1;
		}
		else {
			cout << " Choisis une carte [chiffre entre 1 et " << getJoueurs()[id_joueur]->getNbCartes() + vecteur.size() << "] : ";
			nb_cartes = getJoueurs()[id_joueur]->getNbCartes() - 1 + vecteur.size(); 
		}
		int choix_carte = Jeu::getUserInput();
		choix_carte--; 

		while (!checkBornes(0, nb_cartes, choix_carte)) { 
			cout << "Carte inexistante, veuillez reessayer." << endl;
			choix_carte = Jeu::getUserInput();
			choix_carte--;
		}
		int taille_main_classique = getJoueurs()[id_joueur]->getCarteC().size();
		int taille_main_tactique = getJoueurs()[id_joueur]->getCarteT().size();
		int taille_main = taille_main_classique + taille_main_tactique;
		if (choix_carte < taille_main_classique) {
			return (Carte*)getJoueurs()[id_joueur]->getCarteC()[choix_carte];
		}
		else if (choix_carte < taille_main) {
			choix_carte -= taille_main_classique;
			cout << *getJoueurs()[id_joueur]->getCarteT()[choix_carte] << endl;    
			return (Carte*)getJoueurs()[id_joueur]->getCarteT()[choix_carte];
		}
		else {
			choix_carte -= taille_main;
			vecteur[choix_carte]->print(cout);
			return vecteur[choix_carte];
		}
	}

	/// <summary>
	/// Allows the user to ask the IA which card they want to play
	/// </summary>
	/// <param name="id_joueur">The id of the player</param>
	/// <param name="vecteur">The possible vector of a Ruse card to take into account</param>
	/// <returns>A pointer of the chosen card</returns>
	Carte* choisirCarteIA(int id_joueur, vector<Carte*> vecteur) {
		int nb_cartes;
		if (vecteur.size() == 0)
			nb_cartes = getJoueurs()[id_joueur]->getNbCartes() - 1;
		else 
			nb_cartes = getJoueurs()[id_joueur]->getNbCartes() - 1 + vecteur.size();
		int choix_carte = getJoueurs()[id_joueur]->choix_ia(0, nb_cartes-1);
		int taille_main_classique = getJoueurs()[id_joueur]->getCarteC().size();
		int taille_main_tactique = getJoueurs()[id_joueur]->getCarteT().size();
		int taille_main = taille_main_classique + taille_main_tactique;
		if (choix_carte < taille_main_classique) {
			return (Carte*)getJoueurs()[id_joueur]->getCarteC()[choix_carte];
		}
		else if (choix_carte < taille_main) {
			choix_carte -= taille_main_classique;
			return (Carte*)getJoueurs()[id_joueur]->getCarteT()[choix_carte];
		}
		else {
			choix_carte -= taille_main;
			return vecteur[choix_carte];
		}
	}

	/// <summary>
	/// Allows the user to execute a Ruse card for a player
	/// </summary>
	/// <param name="carte">The Ruse card</param>
	/// <param name="id_joueur">The player who has played the card</param>
	void execRuse(Ruse* carte, int id_joueur) {
		vector<int> actions = carte->getActions();
		Carte_c* carte_classique = nullptr;
		Carte_t* carte_tactique = nullptr;
		int id_tuile;
		string choix;
		int choix_pioche;
		Carte* c;
		for (int i = 0; i < actions.size(); i++) {
			switch (actions[i])
			{
			case 0:
				// 0 = piocher
				choix_pioche = choixPioche();
				cout << choix_pioche << endl;
				piocheRuse(choix_pioche, carte); 
				break;

			case 1:
				// 1 = placer carte sous pioche
				if (carte_classique != nullptr) {
					carte->eraseCarte((Carte*)carte_classique); 
					getJoueurs()[id_joueur]->eraseCarte((Carte*)carte_classique);
					getPioche_c()->push(carte_classique);
				}
				else {
					carte->eraseCarte((Carte*)carte_tactique);
					getJoueurs()[id_joueur]->eraseCarte((Carte*)carte_tactique);
					pioche_tact.push(carte_tactique); 
				}
				cout << "Carte placee sous la pioche." << endl;
				break;

			case 2:
				// 2 = choisir carte de notre main (et le vecteur de Ruse)
				cout << "Choisir une carte" << endl;
				getJoueurs()[id_joueur]->afficherMain();
				for (unsigned int i = 0; i < carte->getAllCartes().size(); i++)
					carte->getAllCartes()[i]->print(cout);
				c = choisirCarte(id_joueur, carte->getAllCartes()); 
				if (typeid(*c) == typeid(Carte_t)) {
					carte_tactique = (Carte_t*)(c);
					carte_classique = nullptr;
				}
				else {
					carte_classique = (Carte_c*)(c);
					cout << *carte_classique << endl;
					carte_tactique = nullptr;
				}
				break;

			case 3:
				// 3 = placer carte sur borne non revendiquee de notre côte ou defausser
				cout << "Voulez-vous defausser la carte ou la placer sur une autre borne de votre cote ? (d = defausser / p = placer) " << endl;

				std::cin >> choix;
				while (true) {
					if (choix.front() == 'd' || choix.front() == 'D') {
						//displayBoard();
						defausse.push((Carte*)carte_classique);
						break;
					}
					else if (choix.front() == 'p' || choix.front() == 'P') {
						//displayBoard();
						cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 1 et 9] : ";
						int id_tuile = getUserInput();
						id_tuile--;
						while (!posePossible(getPlateau()[id_tuile], id_joueur) || !tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {
							cout << "Choix impossible, la borne est pleine, deja revendiquee ou inexistante, veuillez reessayer." << endl;
							cout << getJoueurs()[id_joueur]->getNom() << " choisis une borne[chiffre entre 1 et 9] : ";
							id_tuile = getUserInput(); 
							id_tuile--;
						} 
						getJoueurs()[id_joueur]->poser_carte((Carte*)carte_classique, id_joueur, getPlateau()[id_tuile]);
						if (typeid(*carte_classique) == typeid(TroupeElite)) {
							nb_cartes_tactiques_jouees[id_joueur] += 1;
							if (dynamic_cast<Carte_t*>(carte_classique)->getNom() == "Joker") 
								nb_jokers_joues[id_joueur] += 1;
						}
						//displayBoard();
						break;
					}
					else
						std::cout << "Choix invalide, recommencez (d/p) : " << std::endl;
					choix = "";
				}
				break;

			case 4:
				// 4 = choisir carte du cote adverse non revendiquee
				//displayBoard();
				cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 1 et 9] : ";
				id_tuile = getUserInput();
				id_tuile--;
				while (!checkBornes(0, 8, id_tuile) || !tuileNonRevendiquee(getPlateau()[id_tuile])) {
					cout << "Choix impossible, la borne est deja revendiquee ou inexistante, veuillez reessayer." << endl;
					cout << getJoueurs()[id_joueur]->getNom() << " choisis une borne[chiffre entre 1 et 9] : ";
					id_tuile = getUserInput(); 
					id_tuile--;
				} 
				carte_classique = getPlateau()[id_tuile]->defausseAdverse(id_joueur); 
				if (typeid(*carte_classique) == typeid(TroupeElite)) {
					nb_cartes_tactiques_jouees[(id_joueur + 1) % 2] -= 1;  
					if (dynamic_cast<Carte_t*>(carte_classique)->getNom() == "Joker")
						nb_jokers_joues[(id_joueur + 1) % 2] -= 1;
				}
				break;

			case 5:
				// 5 = defausser de la main
				if (carte_classique != nullptr)
					defausse.push((Carte*)carte_classique);
				else 
					defausse.push((Carte*)carte_tactique);
				break;

			case 6:
				// 6 = placer devant une tuile non revendiquee de notre cote
				//displayBoard();
				cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 1 et 9] : ";
				id_tuile = getUserInput();
				id_tuile--;
				while (!checkBornes(0, 8, id_tuile) || !posePossible(getPlateau()[id_tuile], id_joueur) || !tuileNonRevendiquee(getPlateau()[id_tuile])) {
					cout << "Choix impossible, la borne est pleine, deja revendiquee ou inexistante, veuillez reessayer." << endl;
					cout << getJoueurs()[id_joueur]->getNom() << " choisis une borne[chiffre entre 1 et 9] : ";
					id_tuile = getUserInput();
					id_tuile--;
				} 
				getJoueurs()[id_joueur]->poser_carte((Carte*)carte_classique, id_joueur, getPlateau()[id_tuile]);
				if (typeid(*carte_classique) == typeid(TroupeElite)) {
					nb_cartes_tactiques_jouees[id_joueur] += 1;
					if (dynamic_cast<Carte_t*>(carte_classique)->getNom() == "Joker")
						nb_jokers_joues[id_joueur] += 1;
				}
				//displayBoard();
				break;

			case 7:
				// 7 = choisir carte de notre cote
				//displayBoard();
				cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 1 et 9] : ";
				id_tuile = getUserInput();
				id_tuile--;
				while (!checkBornes(0, 8, id_tuile) || !tuileNonRevendiquee(getPlateau()[id_tuile])) {
					cout << "Choix impossible, la borne est deja revendiquee ou inexistante, veuillez reessayer." << endl;
					cout << getJoueurs()[id_joueur]->getNom() << " choisis une borne[chiffre entre 1 et 9] : ";
					id_tuile = getUserInput();
					id_tuile--;
				}
				carte_classique = getPlateau()[id_tuile]->defausseSoi(id_joueur);
				break;

			default:
				throw("Erreur dans la suite d'actions de la carte Ruse");
				break;
			}
		}
		for (unsigned int i = 0; i < carte->getAllCartes().size(); i++) {

			if (dynamic_cast<Carte_t*>(carte->getAllCartes()[i]) != nullptr) {
				getJoueurs()[id_joueur]->ajouter_Carte_t((Carte_t*)carte->getAllCartes()[i]);
			}
			else {
				getJoueurs()[id_joueur]->ajouter_Carte_c((Carte_c*)carte->getAllCartes()[i]);
			}
		}
	}

	/// <summary>
	/// Allows the user to execute a Ruse card for an IA
	/// </summary>
	/// <param name="carte">The Ruse card</param>
	/// <param name="id_joueur">The IA who has played the card</param>
	void execRuseIA(Ruse* carte, int id_joueur) {
		vector<int> actions = carte->getActions();
		Carte_c* carte_classique = nullptr;
		Carte_t* carte_tactique = nullptr;
		int id_tuile;
		string choix;
		int choix_pioche;
		Carte* c;
		for (int i = 0; i < actions.size(); i++) {
			switch (actions[i])
			{
			case 0:
				// 0 = piocher
				piocheRuse(choixPiocheIA(), carte);
				break;

			case 1:
				// 1 = placer carte sous pioche
				if (carte_classique != nullptr) {
					carte->eraseCarte((Carte*)carte_classique);
					getJoueurs()[id_joueur]->eraseCarte((Carte*)carte_classique);
					getPioche_c()->push(carte_classique);
				}
				else {
					carte->eraseCarte((Carte*)carte_tactique);
					getJoueurs()[id_joueur]->eraseCarte((Carte*)carte_tactique);
					pioche_tact.push(carte_tactique);
				}
				break;

			case 2:
				// 2 = choisir carte de notre main (et le vecteur de Ruse)
				getJoueurs()[id_joueur]->afficherMain();
				for (unsigned int i = 0; i < carte->getAllCartes().size(); i++)
					carte->getAllCartes()[i]->print(cout);
				c = choisirCarteIA(id_joueur, carte->getAllCartes());
				if (typeid(*c) == typeid(Carte_t)) {
					carte_tactique = (Carte_t*)(c);
					carte_classique = nullptr;
				}
				else {
					carte_classique = (Carte_c*)(c);
					carte_tactique = nullptr;
				}
				break;

			case 3:
				// 3 = placer carte sur borne non revendiquee de notre côte ou defausser
				while (true) {
					if (getJoueurs()[i]->choix_ia(0, 1)) {
						defausse.push((Carte*)carte_classique);
						break;
					}
					else {
						int id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size() - 1); 
						while (!posePossible(getPlateau()[id_tuile], id_joueur) || !tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {
							id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size() - 1);
						}
						getJoueurs()[id_joueur]->poser_carte((Carte*)carte_classique, id_joueur, getPlateau()[id_tuile]);
						if (typeid(*carte_classique) == typeid(TroupeElite)) {
							nb_cartes_tactiques_jouees[id_joueur] += 1;
							if (dynamic_cast<Carte_t*>(carte_classique)->getNom() == "Joker")
								nb_jokers_joues[id_joueur] += 1;
						}
						break;
					}
					choix = "";
				}
				break;

			case 4:
				// 4 = choisir carte du cote adverse non revendiquee
				id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size() - 1);
				while (!tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {
					id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size() - 1);
				}
				carte_classique = getPlateau()[id_tuile]->defausseAdverseIA(id_joueur);
				if (typeid(*carte_classique) == typeid(TroupeElite)) {
					nb_cartes_tactiques_jouees[(id_joueur + 1) % 2] -= 1;
					if (dynamic_cast<Carte_t*>(carte_classique)->getNom() == "Joker")
						nb_jokers_joues[(id_joueur + 1) % 2] -= 1;
				}
				break;

			case 5:
				// 5 = defausser de la main
				if (carte_classique != nullptr)
					defausse.push((Carte*)carte_classique);
				else
					defausse.push((Carte*)carte_tactique);
				break;

			case 6:
				// 6 = placer devant une tuile non revendiquee de notre cote
				id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size() - 1);    
				while (!posePossible(getPlateau()[id_tuile], id_joueur) || !tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {
					id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size() - 1);   
				}
				getJoueurs()[id_joueur]->poser_carte((Carte*)carte_classique, id_joueur, getPlateau()[id_tuile]);
				if (typeid(*carte_classique) == typeid(TroupeElite)) {
					nb_cartes_tactiques_jouees[id_joueur] += 1;
					if (dynamic_cast<Carte_t*>(carte_classique)->getNom() == "Joker") 
						nb_jokers_joues[id_joueur] += 1;
				}
				break;

			case 7:
				// 7 = choisir carte de notre cote
				id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size() - 1);
				while (!tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {
					id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size() - 1);
				}
				carte_classique = getPlateau()[id_tuile]->defausseSoiIA(id_joueur);
				break;

			default:
				throw("Erreur dans la suite d'actions de la carte Ruse");
				break;
			}
		}
		for (unsigned int i = 0; i < carte->getAllCartes().size(); i++) {

			if (typeid(*carte->getAllCartes()[i]) == typeid(Carte_t)) {
				getJoueurs()[id_joueur]->ajouter_Carte_t((Carte_t*)carte->getAllCartes()[i]);
			}
			else {
				getJoueurs()[id_joueur]->ajouter_Carte_c((Carte_c*)carte->getAllCartes()[i]);
			}
		}
	}

	/// <summary>
	/// Allows the user to check if a tactical card is playable for a player
	/// </summary>
	/// <param name="id_joueur">The player to check</param>
	/// <returns>A boolean (true if playable, false if not)</returns>
	bool tactiqueJouable(int id_joueur) const {
		return nb_cartes_tactiques_jouees[id_joueur] <= nb_cartes_tactiques_jouees[(id_joueur + 1) % 2]; 
	}

	/// <summary>
	/// Allows the user to check if a "Joker" card is playable for a player
	/// </summary>
	/// <param name="id_joueur">The player to check</param>
	/// <returns>A boolean (true if playable, false if not)</returns>
	bool jokerJouable(int id_joueur) const { 
		return nb_jokers_joues[id_joueur] <= nb_jokers_joues[(id_joueur + 1) % 2];  
	}
};

JeuTactique* JeuTactique::jeuTactiqueUnique = nullptr; 

#endif // !JeuTactique_H