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
		pioche_tact.push(new ModeCombat(combat, "Colin Maillard", 3, vecteur_combi));
		vecteur_combi.push_back(c2);
		vecteur_combi.push_back(c3);
		vecteur_combi.push_back(c4);
		vecteur_combi.push_back(c5);
		pioche_tact.push(new ModeCombat(combat, "Combat de boue", 4, vecteur_combi));
		
		// Création des cartes Ruse
		/*
		0 = piocher 
		1 = placer carte sous pioche 
		2 = choisir carte de notre main (et le vecteur de Ruse) 
		3 = placer carte sur borne non revendiquée de notre côté ou defausser
		4 = choisir carte du cote adverse non revendiquée
		5 = défausser de la main
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

		cout << pioche_tact << endl; 
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
				getJoueurs()[i]->afficherMain();

				// Poser la carte choisie
				cout << " ## C'est au joueur " << getJoueurs()[i]->getNom() << " de jouer ## " << endl; 
				vector<Carte*> vect;
				Carte* carte_a_jouer = choisirCarte(i, vect);
				cout << "Choix carte fait !" << endl;
				if (typeid(*carte_a_jouer) == typeid(Ruse)) {
					cout << "RUSE !" << endl;
					getJoueurs()[i]->eraseCarte(carte_a_jouer);
					defausse.push(carte_a_jouer);
					execRuse(dynamic_cast<Ruse*>(carte_a_jouer), i);
					cout << "Exécution terminée ! " << endl;
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
/*
	void claim(int idJoueur) override {
		char choice = 'o';
		int choixTuile;

		while (choice == 'o' || choice == 'O') {
			do {
				cout << "Veuillez saisir le numéro de tuile à revendiquer [valeur entre 0 et " << getPlateau().size() - 1 << "] : " << endl;
				choixTuile = getUserInput();

			} while (choixTuile < 0 || choixTuile >= getPlateau().size());

			vector<Carte_t*> cartes_tactiques = getPlateau()[choixTuile]->getCotes()[idJoueur]->getCartesT();
			 
			for (auto i = 0; i < cartes_tactiques.size(); i++) {
				if (typeid(*cartes_tactiques[i]) == typeid(TroupeElite)) {
					if (cartes_tactiques[i]->getNom() == "Joker") {
						int valeur; 
						cout << "Quelle valeur doit-prendre la carte Joker ? [1 à 9] : " << endl; 
						valeur = getUserInput();  
						while (!checkBornes(0, 9, valeur)) {
							cout << "Choix impossible, veuillez réessayer. [1 à 9]" << endl;
							valeur = getUserInput(); 
						}
						string couleur; 
						cout << "Quelle couleur doit-prendre la carte Joker ? : " << endl; 
						cin >> couleur; 
						dynamic_cast<TroupeElite*>(cartes_tactiques[i])->TroupeElite::definir_carte(valeur, couleur);
					}
					else if (cartes_tactiques[i]->getNom() == "Espion") {
						string couleur;  
						cout << "Quelle couleur doit-prendre la carte Espion ? : " << endl;
						cin >> couleur; 
						dynamic_cast<TroupeElite*>(cartes_tactiques[i])->TroupeElite::definir_carte(7, couleur);
					}
					else {
						int valeur;
						cout << "Quelle valeur doit-prendre la carte Porte Bouclier ? [1 à 3] : " << endl;
						valeur = getUserInput();
						while (!checkBornes(0, 3, valeur)) {
							cout << "Choix impossible, veuillez réessayer. [1 à 3]" << endl;
							valeur = getUserInput();
						}
						string couleur;
						cout << "Quelle couleur doit-prendre la carte Joker ? : " << endl;
						cin >> couleur;
						dynamic_cast<TroupeElite*>(cartes_tactiques[i])->TroupeElite::definir_carte(valeur, couleur);
					}
				}
			}

			getPlateau()[choixTuile]->claimTuile(idJoueur, getPlateau());

			cout << "Souhaitez vous revendiquer une autre tuile ? (O / N)" << endl;
			cin >> choice;
		}
	}
	*/

	bool checkBornes(int b1, int b2, int input) {
		return b1 <= input <= b2; 
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

	void piocher(int choix_pioche, int id_joueur) {
		if (choix_pioche)
			getJoueurs()[id_joueur]->ajouter_Carte_t(piocher_t());
		else
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
				if (true) {
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

	bool tactiqueJouable(int id_j1, int id_j2) const {
		// ATTENTION : Chaque joueur ne peut poser qu'un seul joker -> à vérifier en plus du nombre total de cartes jouées
		return nb_cartes_tactiques_jouees[id_j1] <= nb_cartes_tactiques_jouees[id_j2];
	}

	/*
	/// <summary>
	/// Allows the user to add the picked card (in the tactical or the classical deck) to the vector in a card Ruse
	/// </summary>
	/// <param name="choix_pioche">The deck where the user wants to pick a card (tactical or classical)</param>
	/// <param name="carte">The Ruse card permitting the picking</param>
	void piocheRuse(int choix_pioche, Ruse* carte);

	/// <summary>
	/// Executes the different actions of a Ruse card
	/// </summary>
	/// <param name="carte">The Ruse card to play</param>
	/// <param name="id_joueur">The id of the player whose the Ruse card belongs to</param>
	void execRuse(Ruse* carte, int id_joueur);

	/// <summary>
	/// Allows the user to choose in what deck to pick
	/// </summary>
	/// <returns>0 for the classical deck and 1 for the tactical one</returns>
	int choixPioche() const;

	/// <summary>
	/// Allows the user to choose a card in the player hand or in the vector of a Ruse card which is playing
	/// </summary>
	/// <param name="id_joueur">The id of the player</param>
	/// <param name="vecteur">The vector in the Ruse card</param>
	/// <returns></returns>
	Carte* choisirCarte(int id_joueur, vector<Carte*> vecteur);

	/// <summary>
	/// Returns the possibility of the player (id_j1) to play a tactical card
	/// </summary>
	/// <param name="id_j1">The id of the player 1</param>
	/// <param name="id_j2">The id of the player 2</param>
	/// <returns>A boolean : True if playable or False if not</returns>
	bool tactiqueJouable(int id_j1, int id_j2) const;

	void startGame(); 

	void piocher(int choix_pioche, int id_joueur); 
	*/
};

#endif // !JeuTactique_H