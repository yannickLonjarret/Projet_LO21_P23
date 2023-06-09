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
	/// nb_cartes_tactiques_jouees represents the number of tactical cards played by each player (each player id corresponds to each id of the vector
	/// </summary>
	vector<int> nb_cartes_tactiques_jouees;
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
		pioche_tact.push(new TroupeElite(elite, "Joker", -1, "Non couleur", 1, 9));
		pioche_tact.push(new TroupeElite(elite, "Joker", -1, "Non couleur", 1, 9));
		pioche_tact.push(new TroupeElite(elite, "Espion", -1, "Non couleur", 7, 7));
		pioche_tact.push(new TroupeElite(elite, "Porte Bouclier", -1, "Non couleur", 1, 3));

		// Création des cartes Mode de Combat
		Combinaison* c1 = new Combinaison(1, 0, 0);
		Combinaison* c2 = new Combinaison(1, 1, 0);
		Combinaison* c3 = new Combinaison(0, 0, 1);
		Combinaison* c4 = new Combinaison(0, 1, 0);
		vector<Combinaison*> vecteur_combi;
		pioche_tact.push(new ModeCombat(combat, "Combat de Boue", 4, vecteur_combi)); // vecteur vide
		vecteur_combi.push_back(c1);
		vecteur_combi.push_back(c2);
		vecteur_combi.push_back(c3);
		vecteur_combi.push_back(c4);
		pioche_tact.push(new ModeCombat(combat, "Colin Maillard", 3, vecteur_combi));

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
		suite = { 4, 5 };
		pioche_tact.push(new Ruse(ruse, "Banshee", suite));
		suite = { 4, 6 };
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
				cout << getJoueurs()[i]->getNom() << " choisis une borne[chiffre entre 0 et 8] : ";
				int id_tuile = getUserInput();
				vector<Carte*> vect;
				cout << "on est là" << endl;
				Carte* carte_a_jouer = choisirCarte(i, vect);
				cout << "Choix carte fait !" << endl;
				if (typeid(*carte_a_jouer) == typeid(Ruse)) {
					cout << "RUSE !" << endl;
					execRuse(dynamic_cast<Ruse*>(carte_a_jouer), i);
					cout << "Exécution terminée ! " << endl;
				}
				else {
					cout << "je suis dans le else" << endl;
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
				piocher(choixPioche(), i);

				for (int i = 0; i < 100; i++)
					cout << endl;
				cout << getJoueurs()[i]->getNom() << " a termine son tour. \n## Entrez un caractère pour confirmer que vous avez change de place..." << endl;
				string temp_prompt = "";
				cin >> temp_prompt;
				cout << endl;
			}

		}
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
		if (vecteur.size() == 0)
			cout << " Choisis une carte [chiffre entre 0 et " << getJoueurs()[id_joueur]->getNbCartes() - 1<< "] : ";
		else
			cout << " Choisis une carte [chiffre entre 0 et " << getJoueurs()[id_joueur]->getNbCartes() - 1 + vecteur.size() << "] : ";
		int choix_carte = Jeu::getUserInput();
		cout << "Choix carte : " << choix_carte << endl;
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
				if (carte_classique != nullptr) {
					cout << *carte_classique << endl;
					for (auto it = 0; it < carte->getAllCartes().size(); it++) {
						if ((Carte*)carte->getAllCartes()[it] == (Carte*)carte_classique) {
							cout << "Suppression du vecteur" << endl;
							carte->getAllCartes().erase(carte->getAllCartes().begin() + it);
							break;
						}
					}
					for (auto it = 0; it < getJoueurs()[id_joueur]->getCarteC().size(); it++) {
						if (getJoueurs()[id_joueur]->getCarteC()[it] == carte_classique) {
							getJoueurs()[id_joueur]->getCarteC().erase(getJoueurs()[id_joueur]->getCarteC().begin() + it);
							break;
						}
					}

					getPioche_c()->push(carte_classique);
				}
				else {
					cout << *carte_tactique << endl;
					for (auto it = 0; it < carte->getAllCartes().size(); it++) {
						cout << "BOUCLE" << endl;
						if ((Carte*)carte->getAllCartes()[it] == (Carte*)carte_tactique) {
							cout << "Suppression du vecteur" << endl; 
							carte->getAllCartes()[0]->print(cout);
							carte->getAllCartes()[it]->print(cout); 
							cout << carte->getAllCartes().size() << endl;
							//std::erase(carte->getAllCartes(), carte->getAllCartes()[it]);
							//carte->getAllCartes().erase(it); 
							break;
						}
					}
					for (auto it = 0; it < getJoueurs()[id_joueur]->getCarteT().size(); it++) {
						if (getJoueurs()[id_joueur]->getCarteT()[it] == carte_tactique) {
							getJoueurs()[id_joueur]->getCarteT().erase(getJoueurs()[id_joueur]->getCarteT().begin() + it);
							break;
						}
					}

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
				carte_tactique = dynamic_cast<Carte_t*>(c);
				if (carte_tactique == nullptr)
					carte_classique = dynamic_cast<Carte_c*>(c);
				break;

			case 3:
				// 3 = placer carte sur borne non revendiquée de notre côté ou defausser
				cout << "Voulez-vous défausser la carte ou la placer sur une autre borne de votre cote ? (d = defausser / p = placer) " << endl;

				std::cin >> choix;
				while (true) {
					if (choix.front() == 'd' || choix.front() == 'D') {
						displayBoard();
						cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
						int id_tuile = getUserInput();
						carte_classique = getPlateau()[id_tuile]->defausseSoi(id_joueur);
						defausse.push((Carte*)carte_classique);
						cout << "C'est tout bon ! " << endl;
						break;
					}
					else if (choix.front() == 'p' || choix.front() == 'P') {
						displayBoard();
						cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
						int id_tuile = getUserInput();
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
				if (id_joueur)
					carte_classique = getPlateau()[id_tuile]->defausseSoi(id_joueur - 1);
				else
					carte_classique = getPlateau()[id_tuile]->defausseSoi(id_joueur + 1);
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
				getJoueurs()[id_joueur]->poser_carte((Carte*)carte_classique, id_joueur, getPlateau()[id_tuile]);
				cout << "C'est bon !" << endl;
				displayBoard();
				break;

			case 7:
				// 7 = choisir carte de notre cote
				displayBoard();
				cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
				id_tuile = getUserInput();
				carte_classique = getPlateau()[id_tuile]->defausseSoi(id_joueur);
				break;

			default:
				throw("Erreur dans la suite d'actions de la carte Ruse");
				break;
			}
		}
		for (unsigned int i = 0; i < carte->getAllCartes().size(); i++) {

			if (typeid(*carte->getAllCartes()[i]) == typeid(Carte_t)) {
				getJoueurs()[id_joueur]->ajouter_Carte_t(dynamic_cast<Carte_t*>(carte->getAllCartes()[i]));
			}
			else {
				getJoueurs()[id_joueur]->ajouter_Carte_c(dynamic_cast<Carte_c*>(carte->getAllCartes()[i]));
			}
		}
	}

	bool tactiqueJouable(int id_j1, int id_j2) const {
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