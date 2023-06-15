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
	/// <summary>
	/// Test
	/// </summary>
	//void jouer();

	/// <summary>
	/// Constructor which creates the deck with all the specific tactical cards required, and initializes the discard defausse
	/// </summary>
	JeuTactique() : Jeu() {
		defausse = Defausse();
		pioche_tact = Pioche_t();
		nb_cartes_tactiques_jouees = { 0, 0 };
		nb_jokers_joues = { 0, 0 };

		// Création des cartes Troupe d'Elite
		pioche_tact.push(new TroupeElite(elite, "Joker", -1,Carte_c::getCouleurs()[0], 1, 9));
		pioche_tact.push(new TroupeElite(elite, "Joker", -1, Carte_c::getCouleurs()[0], 1, 9));
		pioche_tact.push(new TroupeElite(elite, "Espion", -1, Carte_c::getCouleurs()[0], 7, 7));
		pioche_tact.push(new TroupeElite(elite, "Porte Bouclier", -1, Carte_c::getCouleurs()[0], 1, 3));

		// Création des cartes Mode de Combat 
		Combinaison* c1 = new Combinaison(false, false, false);
		Combinaison* c2 = new Combinaison(true, false, false);
		Combinaison* c3 = new Combinaison(false, true, false);
		Combinaison* c4 = new Combinaison(false, false, true);
		Combinaison* c5 = new Combinaison(true, true, false);
		vector<Combinaison*> vecteur_combi;
		vecteur_combi.push_back(c1);
		pioche_tact.push(new ModeCombat(combat, "Colin Maillard", -1, vecteur_combi));
		vecteur_combi = {};
		pioche_tact.push(new ModeCombat(combat, "Combat de boue", 4, vecteur_combi));
		
		// Création des cartes Ruse
		/*
		0 = piocher 
		1 = placer carte sous pioche 
		2 = choisir carte de notre main (et le vecteur de Ruse) 
		3 = placer carte sur borne non revendiquée de notre côté ou defausser
		4 = choisir carte du cote adverse non revendiquée
		5 = défausser du cote adverse
		6 = placer devant une tuile non revendiquée de notre cote
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

	/// <summary>
	/// Allows the user to pick the first card of the tactical deck
	/// </summary>
	/// <returns>The pointer of the card</returns>
	Carte_t* piocher_t() {
		if (pioche_tact.getSize() != 0)
			return pioche_tact.pop();
	}
	
	void startGame() {
		system("CLS");
		cout << R"(
 _____           _   _
|  __ \         | | (_)
| |__) |_ _ _ __| |_ _  ___    ___ _ __     ___ ___  _   _ _ __ ___
|  ___/ _` | '__| __| |/ _ \  / _ \ '_ \   / __/ _ \| | | | '__/ __|
| |  | (_| | |  | |_| |  __/ |  __/ | | | | (_| (_) | |_| | |  \__ \  
|_|   \__,_|_|   \__|_|\___|  \___|_| |_|  \___\___/ \__,_|_|  |___/


	   )" << endl;

		bool isOver = false;

		// On distribue les cartes
		distribuerCartes(7);

		while (isOver == false) {

			for (unsigned int i = 0; i < getJoueurs().size(); i++) {

				displayBoard();
				cout << "\nDefausse : " << defausse << endl;

				if (getJoueurs()[i]->estIA()) {
					// Poser la carte choisie
					cout << " ## C'est au joueur " << getJoueurs()[i]->getNom() << " de jouer ## " << endl;
					vector<Carte*> vect;
					int id_tuile = getJoueurs()[i]->choix_ia(0, getPlateau().size() - 1);
					cout << "Tuile ok" << endl;
					int id_carte = getJoueurs()[i]->choix_ia(0, getJoueurs()[i]->getNbCartes());
					cout << "Carte ok" << endl;
					bool tactique_jouable = tactiqueJouable(i);
					cout << "Tactique ok" << i << endl;
					bool joker_jouable = jokerJouable(i);
					cout << "Joker ok" << endl;
					Carte* carte_a_jouer;
					cout << "if non ok" << endl;
					if (id_carte >= getJoueurs()[i]->getCarteC().size()) {
						cout << "if ok" << endl;
						carte_a_jouer = (Carte*)getJoueurs()[i]->getCarteT()[id_carte - getJoueurs()[i]->getCarteC().size()];
						cout << "Carte à jouer ok" << endl;
					}
					else {
						carte_a_jouer = (Carte*)getJoueurs()[i]->getCarteC()[id_carte];
						cout << "Carte à jouer ok" << endl;
					}
					while (typeid(*carte_a_jouer) == typeid(Carte_t) && (!tactique_jouable)){ 
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
					cout << "Choix carte fait !" << endl;
					if (typeid(*carte_a_jouer) == typeid(Ruse)) {
						cout << "RUSE !" << endl;
						getJoueurs()[i]->eraseCarte(carte_a_jouer);
						defausse.push(carte_a_jouer);
						execRuseIA(dynamic_cast<Ruse*>(carte_a_jouer), i);
						cout << "Exécution terminée ! " << endl;
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
					for (int i = 0; i < 10; i++)
						cout << endl;
					displayBoard();
					cout << "\nDefausse : " << defausse << endl;

					// Pas de revendication pour l'IA

					// Piocher (classique / tactique)
					// while taillle_main < 7 -> s'adapte si une nouvelle carte Ruse
					while (getJoueurs()[i]->getNbCartes() < 7)
						piocher(choixPiocheIA(), i);  
				}
				else {
					getJoueurs()[i]->afficherMain();
					// Poser la carte choisie
					cout << " ## C'est au joueur " << getJoueurs()[i]->getNom() << " de jouer ## " << endl;
					vector<Carte*> vect = {}; 
					Carte* carte_a_jouer = choisirCarte(i, vect);
					bool tactique_jouable = tactiqueJouable(i);
					bool joker_jouable = jokerJouable(i);
					while (typeid(*carte_a_jouer) == typeid(Carte_t) && (!tactique_jouable || (!joker_jouable && dynamic_cast<Carte_t*>(carte_a_jouer)->getNom() == "Joker"))) {
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
					cout << "Choix carte fait !" << endl;
					if (typeid(*carte_a_jouer) == typeid(Ruse)) {
						cout << "RUSE !" << endl;
						getJoueurs()[i]->eraseCarte(carte_a_jouer);
						defausse.push(carte_a_jouer);
						execRuse(dynamic_cast<Ruse*>(carte_a_jouer), i);
						cout << "Exécution terminée ! " << endl;
						nb_cartes_tactiques_jouees[i]++;     
					}
					else if (typeid(*carte_a_jouer) == typeid(ModeCombat)) {
						cout << getJoueurs()[i]->getNom() << " choisis une borne[chiffre entre 0 et 8] : ";
						int id_tuile = getUserInput();
						while (!tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {
							cout << "Choix impossible, la borne est déjà revendiquée ou inexistante, veuillez réessayer." << endl;
							cout << getJoueurs()[i]->getNom() << " choisis une borne[chiffre entre 0 et 8] : ";
							id_tuile = getUserInput();
						}
						getJoueurs()[i]->poser_carte(carte_a_jouer, i, getPlateau()[id_tuile]);
						getPlateau()[id_tuile]->setNbCartesMax(dynamic_cast<ModeCombat*>(carte_a_jouer)->getNbCartes());
						getPlateau()[id_tuile]->setVictoires(dynamic_cast<ModeCombat*>(carte_a_jouer)->getCombinaison());
						cout << getPlateau()[id_tuile]->getVictoires().size() << endl;
						nb_cartes_tactiques_jouees[i]++;   
					}
					else {
						cout << getJoueurs()[i]->getNom() << " choisis une borne[chiffre entre 0 et 8] : ";
						int id_tuile = getUserInput();
						cout << "je suis dans le else" << endl;
						while (!posePossible(getPlateau()[id_tuile], i) || !tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {
							cout << "Choix impossible, la borne est pleine, déjà revendiquée ou inexistante, veuillez réessayer." << endl;
							cout << getJoueurs()[i]->getNom() << " choisis une borne[chiffre entre 0 et 8] : ";
							id_tuile = getUserInput();
						}
						getJoueurs()[i]->poser_carte(carte_a_jouer, i, getPlateau()[id_tuile]);
						if (typeid(*carte_a_jouer) == typeid(TroupeElite)) {
							nb_cartes_tactiques_jouees[i]++;
							if (dynamic_cast<Carte_t*>(carte_a_jouer)->getNom() == "Joker")
								nb_jokers_joues[i]++;
						}
					}
					for (int i = 0; i < 10; i++)
						cout << endl;
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
				}

				for (int i = 0; i < 100; i++)
					cout << endl;
				if (estGagnant(i)) {
					cout << "VICTOIRE !" << endl;
					cout << "Bravo " << getJoueurs()[i]->getNom() << ", vous avez gagne !" << endl;
					isOver = true;
					break;
				}
				else {
					cout << getJoueurs()[i]->getNom() << " a termine son tour. \n## Entrez un caractère pour confirmer que vous avez change de place..." << endl;
					string temp_prompt = "";
					cin >> temp_prompt;
					cout << endl; 
				}
			}
		}
	}

	bool checkBornes(int b1, int b2, int input) {
		return b1 <= input && input <= b2;  
	}

	bool tuileNonRevendiquee(Tuile* tuile) {
		return tuile->getClaim() == -1; 
	}

	bool posePossible(Tuile* tuile, int id_joueur) {
		int nb_cartes_posees = tuile->getCotes()[id_joueur]->getNbCartes(); 
		int nb_cartes_posables = tuile->getNbCartesMax();
		return (nb_cartes_posees != nb_cartes_posables); 
	}

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

	void piocher(int choix_pioche, int id_joueur) {
		if (choix_pioche)
			getJoueurs()[id_joueur]->ajouter_Carte_t(piocher_t());
		else if (choix_pioche == 0)
			getJoueurs()[id_joueur]->ajouter_Carte_c(&piocher_c());
	}

	// Ajoute dans le vecteur de la carte Ruse
	void piocheRuse(int choix_pioche, Ruse* carte) {
		if (choix_pioche)
			carte->addCartes(piocher_t());
		else
			carte->addCartes((Carte*)&Jeu::piocher_c());
	}

	Carte* choisirCarte(int id_joueur, vector<Carte*> vecteur) {
		int nb_cartes;
		if (vecteur.size() == 0) {
			cout << " Choisis une carte [chiffre entre 0 et " << getJoueurs()[id_joueur]->getNbCartes() - 1 << "] : ";
			nb_cartes = getJoueurs()[id_joueur]->getNbCartes() - 1;
		}
		else {
			cout << " Choisis une carte [chiffre entre 0 et " << getJoueurs()[id_joueur]->getNbCartes() - 1 + vecteur.size() << "] : ";
			nb_cartes = getJoueurs()[id_joueur]->getNbCartes() - 1 + vecteur.size(); 
		}
		int choix_carte = Jeu::getUserInput();

		while (!checkBornes(0, nb_cartes, choix_carte)) { 
			cout << "Carte inexistante, veuillez reessayer." << endl;
			choix_carte = Jeu::getUserInput();
		}
		int taille_main_classique = getJoueurs()[id_joueur]->getCarteC().size();
		int taille_main_tactique = getJoueurs()[id_joueur]->getCarteT().size();
		int taille_main = taille_main_classique + taille_main_tactique;
		cout << "Taille classique : " << taille_main_classique << endl;
		cout << "Taille tactique : " << taille_main_tactique << endl;
		cout << "Taille totale : " << taille_main << endl;
		if (choix_carte < taille_main_classique) {
			cout << "CLASSIQUE !" << endl;
			return (Carte*)getJoueurs()[id_joueur]->getCarteC()[choix_carte];
		}
		else if (choix_carte < taille_main) {
			cout << "TACTIQUE !" << endl;
			choix_carte -= taille_main_classique;
			cout << "MAJ choix : " << choix_carte << endl;
			cout << *getJoueurs()[id_joueur]->getCarteT()[choix_carte] << endl;    
			return (Carte*)getJoueurs()[id_joueur]->getCarteT()[choix_carte];
		}
		else {
			cout << "VECTEUR" << endl;
			choix_carte -= taille_main;
			vecteur[choix_carte]->print(cout);
			return vecteur[choix_carte];
		}
	}

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
				cout << "PIOCHE ! " << endl;
				choix_pioche = choixPioche();
				cout << choix_pioche << endl;
				piocheRuse(choix_pioche, carte); 
				cout << "Fin pioche ! " << endl;
				break;

			case 1:
				// 1 = placer carte sous pioche
				cout << "PLACEMENT SOUS PIOCHE" << endl;
				if (carte_classique != nullptr) {
					cout << "AVANT LE ERASE CLASSIQUE" << endl; 
					carte->eraseCarte((Carte*)carte_classique); 
					getJoueurs()[id_joueur]->eraseCarte((Carte*)carte_classique);
					cout << "APRES LE ERASE " << endl; 
					getPioche_c()->push(carte_classique);
				}
				else {
					cout << "AVANT LE ERASE TACTIQUE" << endl;
					cout << *carte_tactique << endl;
					carte->eraseCarte((Carte*)carte_tactique);
					getJoueurs()[id_joueur]->eraseCarte((Carte*)carte_tactique);
					pioche_tact.push(carte_tactique); 
				}
				cout << "PLACEMENT TERMINE" << endl;
				break;

			case 2:
				// 2 = choisir carte de notre main (et le vecteur de Ruse)
				cout << "CHOIX CARTE" << endl;
				getJoueurs()[id_joueur]->afficherMain();
				for (unsigned int i = 0; i < carte->getAllCartes().size(); i++)
					carte->getAllCartes()[i]->print(cout);
				c = choisirCarte(id_joueur, carte->getAllCartes()); // fonction à définir dans joueur ?
				if (typeid(*c) == typeid(Carte_t)) {
					cout << "CAST TACTIQUE" << endl;
					carte_tactique = (Carte_t*)(c);
					carte_classique = nullptr;
				}
				else {
					cout << "CAST CLASSIQUE" << endl;
					carte_classique = (Carte_c*)(c);
					cout << *carte_classique << endl;
					carte_tactique = nullptr;
				}
				break;

			case 3:
				// 3 = placer carte sur borne non revendiquée de notre côté ou defausser
				cout << "Voulez-vous défausser la carte ou la placer sur une autre borne de votre cote ? (d = defausser / p = placer) " << endl;

				std::cin >> choix;
				while (true) {
					if (choix.front() == 'd' || choix.front() == 'D') {
						displayBoard();
						defausse.push((Carte*)carte_classique);
						cout << "C'est tout bon ! " << endl;
						break;
					}
					else if (choix.front() == 'p' || choix.front() == 'P') {
						displayBoard();
						cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
						int id_tuile = getUserInput();
						while (!posePossible(getPlateau()[id_tuile], id_joueur) || !tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {
							cout << "Choix impossible, la borne est pleine, déjà revendiquée ou inexistante, veuillez réessayer." << endl;
							cout << getJoueurs()[id_joueur]->getNom() << " choisis une borne[chiffre entre 0 et 8] : ";
							id_tuile = getUserInput(); 
						} 
						getJoueurs()[id_joueur]->poser_carte((Carte*)carte_classique, id_joueur, getPlateau()[id_tuile]);
						if (typeid(*carte_classique) == typeid(TroupeElite)) {
							nb_cartes_tactiques_jouees[id_joueur] += 1;
							if (dynamic_cast<Carte_t*>(carte_classique)->getNom() == "Joker") 
								nb_jokers_joues[id_joueur] += 1;
						}
						cout << "C'est bon !" << endl;
						displayBoard();
						break;
					}
					else
						std::cout << "Choix invalide, recommencez (d/p) : " << std::endl;
					choix = "";
				}
				break;

			case 4:
				// 4 = choisir carte du cote adverse non revendiquée
				displayBoard();
				cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
				id_tuile = getUserInput();
				while (!tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {
					cout << "Choix impossible, la borne est déjà revendiquée ou inexistante, veuillez réessayer." << endl;
					cout << getJoueurs()[id_joueur]->getNom() << " choisis une borne[chiffre entre 0 et 8] : ";
					id_tuile = getUserInput(); 
				} 
				carte_classique = getPlateau()[id_tuile]->defausseAdverse(id_joueur); 
				if (typeid(*carte_classique) == typeid(TroupeElite)) {
					nb_cartes_tactiques_jouees[(id_joueur + 1) % 2] -= 1;  
					if (dynamic_cast<Carte_t*>(carte_classique)->getNom() == "Joker")
						nb_jokers_joues[(id_joueur + 1) % 2] -= 1;
				}
				cout << "Défausse faite" << endl; 
				break;

			case 5:
				// 5 = défausser de la main
				if (carte_classique != nullptr)
					defausse.push((Carte*)carte_classique);
				else 
					defausse.push((Carte*)carte_tactique);
				break;

			case 6:
				// 6 = placer devant une tuile non revendiquée de notre cote
				displayBoard();
				cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
				id_tuile = getUserInput();
				while (!posePossible(getPlateau()[id_tuile], id_joueur) || !tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {
					cout << "Choix impossible, la borne est pleine, déjà revendiquée ou inexistante, veuillez réessayer." << endl;
					cout << getJoueurs()[id_joueur]->getNom() << " choisis une borne[chiffre entre 0 et 8] : ";
					id_tuile = getUserInput();
				} 
				getJoueurs()[id_joueur]->poser_carte((Carte*)carte_classique, id_joueur, getPlateau()[id_tuile]);
				if (typeid(*carte_classique) == typeid(TroupeElite)) {
					nb_cartes_tactiques_jouees[id_joueur] += 1;
					if (dynamic_cast<Carte_t*>(carte_classique)->getNom() == "Joker")
						nb_jokers_joues[id_joueur] += 1;
				}
				cout << "C'est bon !" << endl;
				displayBoard();
				break;

			case 7:
				// 7 = choisir carte de notre cote
				displayBoard();
				cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
				id_tuile = getUserInput();
				while (!tuileNonRevendiquee(getPlateau()[id_tuile]) || !checkBornes(0, 8, id_tuile)) {
					cout << "Choix impossible, la borne est déjà revendiquée ou inexistante, veuillez réessayer." << endl;
					cout << getJoueurs()[id_joueur]->getNom() << " choisis une borne[chiffre entre 0 et 8] : ";
					id_tuile = getUserInput();
				}
				carte_classique = getPlateau()[id_tuile]->defausseSoi(id_joueur);
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
				cout << "PLACEMENT SOUS PIOCHE" << endl;
				if (carte_classique != nullptr) {
					cout << "AVANT LE ERASE CLASSIQUE" << endl;
					carte->eraseCarte((Carte*)carte_classique);
					getJoueurs()[id_joueur]->eraseCarte((Carte*)carte_classique);
					cout << "APRES LE ERASE " << endl;
					getPioche_c()->push(carte_classique);
				}
				else {
					cout << "AVANT LE ERASE TACTIQUE" << endl;
					cout << *carte_tactique << endl;
					carte->eraseCarte((Carte*)carte_tactique);
					getJoueurs()[id_joueur]->eraseCarte((Carte*)carte_tactique);
					pioche_tact.push(carte_tactique);
				}
				cout << "PLACEMENT TERMINE" << endl;
				break;

			case 2:
				// 2 = choisir carte de notre main (et le vecteur de Ruse)
				cout << "CHOIX CARTE" << endl;
				getJoueurs()[id_joueur]->afficherMain();
				for (unsigned int i = 0; i < carte->getAllCartes().size(); i++)
					carte->getAllCartes()[i]->print(cout);
				c = choisirCarteIA(id_joueur, carte->getAllCartes());
				if (typeid(*c) == typeid(Carte_t)) {
					cout << "CAST TACTIQUE" << endl;
					carte_tactique = (Carte_t*)(c);
					carte_classique = nullptr;
				}
				else {
					cout << "CAST CLASSIQUE" << endl;
					carte_classique = (Carte_c*)(c);
					cout << *carte_classique << endl;
					carte_tactique = nullptr;
				}
				break;

			case 3:
				// 3 = placer carte sur borne non revendiquée de notre côté ou defausser
				while (true) {
					if (getJoueurs()[i]->choix_ia(0, 1)) {
						displayBoard();
						defausse.push((Carte*)carte_classique);
						break;
					}
					else {
						displayBoard();
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
						displayBoard();
						break;
					}
					choix = "";
				}
				break;

			case 4:
				// 4 = choisir carte du cote adverse non revendiquée
				displayBoard();
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
				// 5 = défausser de la main
				if (carte_classique != nullptr)
					defausse.push((Carte*)carte_classique);
				else
					defausse.push((Carte*)carte_tactique);
				break;

			case 6:
				// 6 = placer devant une tuile non revendiquée de notre cote
				displayBoard();
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
				displayBoard();
				break;

			case 7:
				// 7 = choisir carte de notre cote
				displayBoard();
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

	bool tactiqueJouable(int id_joueur) const {
		cout << "tactique jouable ok" << endl;
		cout << "Nb carte" << id_joueur << nb_cartes_tactiques_jouees[id_joueur] << endl;
		cout << "Nb carte" << (id_joueur + 1) % 2 << endl;
		cout << nb_cartes_tactiques_jouees[(id_joueur + 1) % 2] << endl;
		return nb_cartes_tactiques_jouees[id_joueur] <= nb_cartes_tactiques_jouees[(id_joueur + 1) % 2]; 
	}

	bool jokerJouable(int id_joueur) const { 
		cout << "joker ok" << endl;
		return nb_jokers_joues[id_joueur] <= nb_jokers_joues[(id_joueur + 1) % 2];  
	}
};

#endif // !JeuTactique_H