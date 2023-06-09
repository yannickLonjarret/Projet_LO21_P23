#include "JeuTactique.h"
#include <string>
#include <iostream>

void JeuTactique::startGame() {
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
			getJoueurs()[i].afficherMain();

			// Poser la carte choisie
			cout << " ## C'est au joueur " << getJoueurs()[i].getNom() << " de jouer ## " << endl;
			cout << getJoueurs()[i].getNom() << " choisis une borne[chiffre entre 0 et 8] : ";
			int id_tuile = getUserInput();
			vector<Carte*> vect;
			Carte* carte_a_jouer = choisirCarte(i, vect);
			if (typeid(*carte_a_jouer) == typeid(Ruse)) {
				execRuse(dynamic_cast<Ruse*>(carte_a_jouer), i);
				cout << "Exécution terminée ! " << endl;
			}
			else {
				(getJoueurs()[i]).poser_carte(carte_a_jouer, i, getPlateau()[id_tuile]);
				cout << "Taille main : " << getJoueurs()[i].getCarteC().size() << endl;
			}
			for (int i = 0; i < 10; i++)
				cout << endl;
			displayBoard();
			cout << "\nDefausse : " << defausse << endl;
			getJoueurs()[i].afficherMain();

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
			cout << getJoueurs()[i].getNom() << " a termine son tour. \n## Entrez un caractère pour confirmer que vous avez change de place..." << endl;
			string temp_prompt = "";
			cin >> temp_prompt;
			cout << endl;
		}

	}
}

int JeuTactique::choixPioche() const {
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

void JeuTactique::piocher(int choix_pioche, int id_joueur) {
	if (choix_pioche)
		getJoueurs()[id_joueur].ajouter_Carte_t(piocher_t());
	else
		getJoueurs()[id_joueur].ajouter_Carte_c(&piocher_c());
}

// Ajoute dans le vecteur de la carte Ruse
void JeuTactique::piocheRuse(int choix_pioche, Ruse* carte) {
	if (choix_pioche)
		carte->addCartes(piocher_t());
	else
		carte->addCartes((Carte*)&Jeu::piocher_c());
}

Carte* JeuTactique::choisirCarte(int id_joueur, vector<Carte*> vecteur) {
	cout << " Choisis une carte [chiffre entre 0 et " << getJoueurs()[id_joueur].getNbCartes() - 1 << "] : ";
	int choix_carte = Jeu::getUserInput();
	int taille_main_classique = getJoueurs()[id_joueur].getCarteC().size();
	int taille_main_tactique = getJoueurs()[id_joueur].getCarteT().size();
	int taille_main = taille_main_classique + taille_main_tactique;
	if (choix_carte < taille_main_classique) {
		return (Carte*)getJoueurs()[id_joueur].getCarteC()[choix_carte];
	}
	else if (choix_carte < taille_main) {
		choix_carte -= taille_main_classique;
		return (Carte*)getJoueurs()[id_joueur].getCarteT()[choix_carte];
	}
	else {
		choix_carte -= taille_main;
		return vecteur[choix_carte];
	}
}

void JeuTactique::execRuse(Ruse* carte, int id_joueur) {
	vector<int> actions = carte->getActions();
	Carte_c* carte_classique = nullptr;
	Carte_t* carte_tactique = nullptr;
	int id_tuile;
	string choix;
	Carte* c;
	for (int i = 0; i < actions.size(); i++) {
		switch (actions[i])
		{
		case 0:
			// 0 = piocher
			piocheRuse(choixPioche(), carte); // a définir
			break;

		case 1:
			// 1 = placer carte sous pioche
			if (carte_classique != nullptr) {

				for (auto it = 0; it < carte->getAllCartes().size(); it++) {
					if ((Carte*)carte->getAllCartes()[it] == (Carte*)carte_classique) {
						carte->getAllCartes().erase(carte->getAllCartes().begin() + it);
						break;
					}
				}
				for (auto it = 0; it < getJoueurs()[id_joueur].getCarteC().size(); it++) {
					if (getJoueurs()[id_joueur].getCarteC()[it] == carte_classique) {
						getJoueurs()[id_joueur].getCarteC().erase(getJoueurs()[id_joueur].getCarteC().begin() + it);
						break;
					}
				}

				getPioche_c().Pioche_c::push(carte_classique);
			}
			else {
				for (auto it = 0; it < carte->getAllCartes().size(); it++) {
					if ((Carte*)carte->getAllCartes()[it] == (Carte*)carte_tactique) {
						carte->getAllCartes().erase(carte->getAllCartes().begin() + it);
						break;
					}
				}
				for (auto it = 0; it < getJoueurs()[id_joueur].getCarteT().size(); it++) {
					if (getJoueurs()[id_joueur].getCarteT()[it] == carte_tactique) {
						getJoueurs()[id_joueur].getCarteT().erase(getJoueurs()[id_joueur].getCarteT().begin() + it);
						break;
					}
				}

				pioche_tact.Pioche_t::push(carte_tactique);
			}
			break;

		case 2:
			// 2 = choisir carte de notre main (et le vecteur de Ruse)
			c = choisirCarte(id_joueur, carte->getAllCartes()); // fonction à définir dans joueur ?
			carte_tactique = dynamic_cast<Carte_t*>(c);
			if (carte_tactique != nullptr)
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
					getJoueurs()[id_joueur].poser_carte((Carte*)carte_classique, id_joueur, getPlateau()[id_tuile]);
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
			getJoueurs()[id_joueur].poser_carte((Carte*)carte_classique, id_joueur, getPlateau()[id_tuile]);
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
			getJoueurs()[id_joueur].ajouter_Carte_t(dynamic_cast<Carte_t*>(carte->getAllCartes()[i]));
		}
		else {
			getJoueurs()[id_joueur].ajouter_Carte_c(dynamic_cast<Carte_c*>(carte->getAllCartes()[i]));
		}
	}
}

bool JeuTactique::tactiqueJouable(int id_j1, int id_j2) const {
	return nb_cartes_tactiques_jouees[id_j1] <= nb_cartes_tactiques_jouees[id_j2];
}