#include "Jeu.h"
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <iomanip>

void Jeu::displayBoard() const {
	
	cout << "\t\tJoueur 1: "<<getJoueur1()->getNom()<< "\t\t\t\t\tJoueur 2:  " << getJoueur2()->getNom() << "\n";

	for (int i = 0; i < getPlateau().size(); i++) {
		cout << "Tuile :" << i + 1;
		cout << *getPlateau()[i];
	}
}

void Jeu::printTitles() const {
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
	int choixTuile;
	
	while (choice == 'o') {
		do {
			cout << "Veuillez saisir le numéro de tuile. (valeur entre 1 et " << getPlateau().size() << ")" << endl;
			cin >> choixTuile;
			choixTuile--;

		} while (choixTuile < 0 || choixTuile > getPlateau().size() - 1);

		getPlateau()[choixTuile]->claimTuile(idJoueur, getPlateau());
		cout << "Veuillez saisir un caractère pour poursuivre" << endl;
		cin >> choice;
		system("CLS");
		displayBoard();
		getJoueurs()[idJoueur]->afficherMain();

		cout << "Souhaitez vous revendiquer une autre tuile ? (o pour oui)" << endl;
		cin >> choice;
	}
}



void Jeu::menu_selection() {
	bool quit = false;

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
	if (plateau[0]->getClaim() == id_joueur)
		score++;
	cout << "score : " << score << endl;
	if (plateau[plateau.size() - 1]->getClaim() == id_joueur)
		score++; 
	cout << "score : " << score << endl;
	if (score == 5)
		return true;
	return false;
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

	bool isOver = false;
	char empty;
	int id_tuile;
	int choix_carte; 
	distribuerCartes(6);




	
	while (isOver == false) {
		cout << joueurs.size();
		
		for (unsigned int i = 0; i < joueurs.size(); i++) {
			if (joueurs[i]->estIA()) {
				cout << joueurs[i]->getNom() << "joue " << endl;
				

				id_tuile = joueurs[i]->choix_ia(0, getPlateau().size() - 1);
				choix_carte = joueurs[i]->choix_ia(0,joueurs[i]->getNbCartes() - 1);

				while (getPlateau()[id_tuile]->isTuilePleine(i)) {
					id_tuile = joueurs[i]->choix_ia(0,getPlateau().size() - 1);
				}
				
				joueurs[i]->poser_carte((Carte*)joueurs[i]->getCarteC()[choix_carte], i, plateau[id_tuile]);
				joueurs[i]->piocher_c(getPioche_c()->pop());

				system("CLS");

				displayBoard();
				cout << joueurs[i]->getNom() << " a termine son tour. \n## Entrez un caractère pour confirmer que vous avez change de place..." << endl;
				cin >> empty;
			}
			else{

				displayBoard();
				joueurs[i]->afficherMain();

				cout << " ## C'est au joueur " << joueurs[i]->getNom() << " de jouer ## " << endl;

				//cout << joueurs[i]->getNom() << " choisis une borne[chiffre entre 0 et 8] : ";

				
				//cout << joueurs[i]->getNom() << " choisis sa carte a poser [chiffre entre 0 et " << joueurs[i]->getNbCartes() - 1 << "] : ";
				choix_carte = getUserInput();

				id_tuile = getUserInput();
				while (getPlateau()[id_tuile]->isTuilePleine(i)) {
					cout << "Tuile pleine, veuillez choisir une autre tuile" << endl;
					id_tuile = getUserInput();
				}
				joueurs[i]->poser_carte((Carte*)joueurs[i]->getCarteC()[choix_carte], i, plateau[id_tuile]);
				system("CLS");
				displayBoard();
				joueurs[i]->afficherMain();
				joueurs[i]->piocher_c(getPioche_c()->pop());
				
				//claim(i);


				//system("CLS");
				cout << joueurs[i]->getNom() << " a termine son tour. \n## Entrez un caractère pour confirmer que vous avez change de place..." << endl;
				
				cin >> empty;

				system("CLS");
			}
			
		}
	}
	
}

