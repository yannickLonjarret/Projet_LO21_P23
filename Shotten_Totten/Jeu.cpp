#include "Jeu.h"
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <iomanip>


Jeu* Jeu::jeuUnique = nullptr;


Jeu& Jeu::donneInstance() {
	if (jeuUnique == nullptr) {
		jeuUnique = new Jeu();
	}
	return *jeuUnique;
}

void Jeu::libereInstance() {
	delete jeuUnique;
	jeuUnique = nullptr;
}

void Jeu::displayBoard() const {
	system("CLS");
	cout << "\t\tJoueur 1: " << getJoueur1()->getNom() << "\t\t\t\t\tJoueur 2:  " << getJoueur2()->getNom() << "\n";

	for (int i = 0; i < getPlateau().size(); i++) {
		cout << "Tuile :" << i + 1;
		cout << *getPlateau()[i];
	}
}

void Jeu::printTitles() const {
	system("CLS");
	std::cout << R"(

   _____      _           _   _                _______    _   _             
  / ____|    | |         | | | |              |__   __|  | | | |            
 | (___   ___| |__   ___ | |_| |_ ___ _ __ ______| | ___ | |_| |_ ___ _ __  
  \___ \ / __| '_ \ / _ \| __| __/ _ \ '_ \______| |/ _ \| __| __/ _ \ '_ \ 
  ____) | (__| | | | (_) | |_| ||  __/ | | |     | | (_) | |_| ||  __/ | | |
 |_____/ \___|_| |_|\___/ \__|\__\___|_| |_|     |_|\___/ \__|\__\___|_| |_|
            
 BOUCHARD REMI & BRUNIAUX ALIENOR & LAGUE PIERRE & LONJARRET YANNICK & MONDESERT JULES
                                                
                                                                            
)" << '\n';
}


void Jeu::distribuerCartes(int nb_a_distribuer) {
	for (unsigned int i = 0; i < joueurs.size(); i++) {
		for (unsigned int j = 0; j < nb_a_distribuer; j++) {
			joueurs[i]->ajouter_Carte_c(pioche_c->pop());
		}
	}
}

void Jeu::displayMenu() const {
	system("CLS");
	std::cout << R"(
  __  __                  
 |  \/  |                 
 | \  / | ___ _ __  _   _ 
 | |\/| |/ _ \ '_ \| | | |
 | |  | |  __/ | | | |_| |
 |_|  |_|\___|_| |_|\__,_|
                          
 1 - Jouer
 2 - Quitter  
                     
)" << '\n';
}

int Jeu::getUserInput() const {
	int choice;
	std::string input;

	while (true) {
		std::cout << "Choisissez une option : ";
		std::cin >> input;

		try {
			choice = std::stoi(input);
			break;
		}
		catch (std::invalid_argument&) {
			std::cout << "Entrée invalide. Veuillez saisir un entier." << std::endl;
		}
	}

	return choice;
}

void Jeu::claim(int idJoueur) {
	char choice = 'o';
	string empty;
	int choixTuile;

	while (choice == 'o') {
		do {
			cout << "Veuillez choisir une tuilee. [chiffre entre 1 et " << getPlateau().size() << "]" << endl;
			cin >> choixTuile;
			choixTuile--;

		} while (choixTuile < 0 || choixTuile > getPlateau().size() - 1);

		getPlateau()[choixTuile]->claimTuile(idJoueur, getPlateau());

		cout << "Veuillez saisir un caractère pour poursuivre" << endl;
		cin >> empty;
		system("CLS");
		displayBoard();
		getJoueurs()[idJoueur]->afficherMain();

		cout << "Souhaitez vous revendiquer une autre tuile ? (o pour oui)" << endl;
		cin >> choice;
	}
}

void Jeu::claimIA(int idJoueur) {
	bool revendication = 1;
	int choixTuile;

	while (revendication) {
		getPlateau()[getJoueurs()[idJoueur]->choix_ia(0, getPlateau().size()-1)]->claimTuile(idJoueur, getPlateau());
		revendication = getJoueurs()[idJoueur]->choix_ia(0, 1); 
	}
}


void Jeu::menu_selection() {
	bool quit = false;
	system("CLS");
	while (!quit) {
		displayMenu();
		int choice = getUserInput();

		switch (choice)
		{
		case 1:
			playerSelection();
			quit = true;
			break;
		case 2:
			quit = true;
			std::cout << "Au revoir !" << std::endl;
			break;
		default:
			std::cout << "Option invalide, respectez les choix et réessayez." << std::endl;
			break;
		}
	}


}



void Jeu::playerSelection() {
	system("CLS");
	std::cout << R"(

   _____      _           _   _                    _                             
  / ____|    | |         | | (_)                  | |                            
 | (___   ___| | ___  ___| |_ _  ___  _ __        | | ___  _   _  ___ _   _ _ __ 
  \___ \ / _ \ |/ _ \/ __| __| |/ _ \| '_ \   _   | |/ _ \| | | |/ _ \ | | | '__|
  ____) |  __/ |  __/ (__| |_| | (_) | | | | | |__| | (_) | |_| |  __/ |_| | |   
 |_____/ \___|_|\___|\___|\__|_|\___/|_| |_|  \____/ \___/ \__,_|\___|\__,_|_|                                                                                   
                                                                                
 1 - Jouer contre un humain
 2 - Jouer contre l'IA
 3 - Retour

)" << std::endl;

	std::string player1;
	std::string player2;

	bool quit = false;

	while (!quit) {

		int choice = getUserInput();

		switch (choice)
		{
		case 1:

			std::cout << "## Entrez le nom du joueur 1 : ";
			std::cin >> player1;
			setJoueur1(player1);

			std::cout << "## Entrez le nom du joueur 2 : ";
			std::cin >> player2;
			setJoueur2(player2);

			std::cout << "Le jeu commence ! " << player1 << " VERSUS " << player2 << std::endl;
			quit = true;
			break;

		case 2:

			std::cout << "## Entrez le nom du joueur 1 : ";
			std::cin >> player1;
			setJoueur1(player1);
			setIA();
			std::cout << "Le jeu commence ! " << player1 << " VERSUS IA" << std::endl;
			quit = true;
			break;

		case 3:
			quit = true;
			displayMenu();

		default:
			cout << "L'entrée n'est pas valide, recommencez." << endl;
		}

	}
}

bool Jeu::estGagnant(int id_joueur) {
	int score = 0;
	for (unsigned i = 1; i <= plateau.size() - 2; i++) {
		if (plateau[i - 1]->getClaim() == id_joueur && plateau[i]->getClaim() == id_joueur && plateau[i + 1]->getClaim() == id_joueur)
			return true;
		if (plateau[i]->getClaim() == id_joueur)
			score++;
		cout << "score : " << score << endl;
	}
}
int Jeu::victory() {
	int J1 = 0;
	int J2 = 1;
	int vict1 = 0;
	int vict2 = 0;
	int victConsec = 0;
	int idGagnantPrec = -1;

	for (auto i = 0; i < plateau.size(); i++) {

		if (plateau[i]->getClaim() == J1) {
			vict1++;
			if (idGagnantPrec == J1)
				victConsec++;
			else {
				idGagnantPrec = J1;
				victConsec = 1;
			}

		}
		else if (plateau[i]->getClaim() == J2) {
			vict2++;
			if (idGagnantPrec == J2)
				victConsec++;
			else {
				idGagnantPrec = J2;
				victConsec = 1;
			}
		}
		else {
			idGagnantPrec = -1;
			victConsec = 0;
		}

		if (victConsec == 3)
			return idGagnantPrec;

	}

	if (vict1 == 5)
		return J1;
	else if (vict2 == 5)
		return J2;
	else
		return -1;

}

void Jeu::startGame() {

	system("CLS");
	cout << R"(
  _____           _   _                                              
 |  __ \         | | (_)                                             
 | |__) |_ _ _ __| |_ _  ___    ___ _ __     ___ ___  _   _ _ __ ___ 
 |  ___/ _` | '__| __| |/ _ \  / _ \ '_ \   / __/ _ \| | | | '__/ __|
 | |  | (_| | |  | |_| |  __/ |  __/ | | | | (_| (_) | |_| | |  \__ \
 |_|   \__,_|_|   \__|_|\___|  \___|_| |_|  \___\___/ \__,_|_|  |___/
                                                                     
                                                                     
)" << endl;

	int winner = -1;
	string empty;
	int id_tuile;
	int choix_carte;
	char choice;
	bool confirm_card = false;

	distribuerCartes(6);


	while (winner == -1) {
		system("CLS");

		for (unsigned int i = 0; i < joueurs.size(); i++) {
			if (joueurs[i]->estIA()) {
				cout << joueurs[i]->getNom() << "joue " << endl;


				id_tuile = joueurs[i]->choix_ia(0, getPlateau().size() - 1);
				choix_carte = joueurs[i]->choix_ia(0, joueurs[i]->getNbCartes() - 1);

				while (getPlateau()[id_tuile]->isTuilePleine(i)) {
					id_tuile = joueurs[i]->choix_ia(0, getPlateau().size() - 1);
				}

				joueurs[i]->poser_carte((Carte*)joueurs[i]->getCarteC()[choix_carte], i, plateau[id_tuile]);
				joueurs[i]->piocher_c(getPioche_c()->pop());

				system("CLS");

				displayBoard();
				cout << joueurs[i]->getNom() << " a termine son tour. \n## Entrez un caractère pour confirmer que vous avez change de place..." << endl;
				cin >> empty;
			}
			else {

				displayBoard();
				joueurs[i]->afficherMain();

				cout << " ## C'est au joueur " << joueurs[i]->getNom() << " de jouer ## " << endl;

				if (joueurs[i]->getCarteC().size() != 0) {
					while (!confirm_card) {
						cout << joueurs[i]->getNom() << " choisis sa carte a poser [chiffre entre 1 et " << joueurs[i]->getNbCartes() << "] : ";
						choix_carte = getUserInput();
						choix_carte--;

						while (choix_carte < 0 || choix_carte > joueurs[i]->getNbCartes() - 1) {
							cout << "Carte inexistante, veuillez choisir un chiffre entre [1 et " << joueurs[i]->getNbCartes() << "] ";
							choix_carte = getUserInput();
							choix_carte--;
						}

						cout << "Vous avez choisi la carte: " << *joueurs[i]->getCarteC()[choix_carte] << endl;
						cout << "Est-ce la bonne carte ? (o pour oui)";
						cin >> choice;

						confirm_card = choice == 'o';
					}
					confirm_card = false;


					cout << joueurs[i]->getNom() << " choisis une borne[chiffre entre 1 et 9] : ";
					id_tuile = getUserInput();
					id_tuile--;

					while ((id_tuile < 0 || id_tuile > 8) || getPlateau()[id_tuile]->isTuilePleine(i)) {

						if ((id_tuile < 0 || id_tuile > 8)) {

							cout << "Tuile inexistante, veuillez choisir un chiffre entre [1 et 9] ";
							id_tuile = getUserInput();
							id_tuile--;
						}
						else if (getPlateau()[id_tuile]->isTuilePleine(i)) {
							cout << "Tuile pleine, veuillez choisir une autre tuile" << endl;
							id_tuile = getUserInput();
							id_tuile--;

						}

					}


					joueurs[i]->poser_carte((Carte*)joueurs[i]->getCarteC()[choix_carte], i, plateau[id_tuile]);
					system("CLS");
					displayBoard();

				}

				joueurs[i]->piocher_c(getPioche_c()->pop());
				joueurs[i]->afficherMain();

				cout << "Souhaitez vous revendiquer une tuile ? (o pour oui)";
				cin >> choice;

				if (choice == 'o')
					claim(i);

				system("CLS");
				displayBoard();
				cout << joueurs[i]->getNom() << " a termine son tour. \n## Entrez un caractère pour confirmer que vous avez change de place..." << endl;

				cin >> empty;


			}

			winner = victory();
			if (winner != -1) break;

		}
	}

	cout << "Partie terminée, le gagnant est " << joueurs[winner]->getNom();
	joueurs[winner]->setScore(joueurs[winner]->getScore() + 1);
}

