#include "Jeu.h"
#include <iostream>
#include <stdexcept>
#include <stdlib.h>

void Jeu::printPlateau() const {

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

void Jeu::play_card_c(int id_j,int id_tuile, Carte_c& c) {
	// Find the player with the given id_j
	Joueur& joueur = (id_j == 1) ? j1 : j2;


	// Check if the card is in the player's hand
	bool cardFound = false;
	for (const Carte_c& carte : joueur.Joueur::getCarteC()) {
		if (carte == c) {
			cardFound = true;
			break;
		}
	}

	if (!cardFound) {
		std::cout << "La carte n'est pas dans la main du joueur." << std::endl;
		return;
	}

	// Place the card on the tile

	plateau[id_tuile]->Tuile::ajout_c(&c , id_j);

	// Remove the card from the player's hand
	joueur.pop(c);
}

void Jeu::draw_card_c(int id_j)
{
	// Find the player with the given id_j
	Joueur& joueur = (id_j == 1) ? j1 : j2;
	
	// Check if the classic card deck is empty
	if (pioche_c.Pioche_c::getSize() == 0)
	{
		std::cout << "La pioche classique est vide." << std::endl;
		return;
	}

	// Draw a card from the classic card deck
	Carte_c carte = pioche_c.Pioche_c::pop();

	// Add the card to the player's hand
	joueur.push(carte);

	// Output a message to indicate the successful draw
	std::cout << "Joueur " << id_j << " a pioché une carte classique." << std::endl;
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

	std::string player1, player2;

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
			startGame(j1, j2);
			break;

		case 2:

			std::cout << "## Entrez le nom du joueur 1 : ";
			std::cin >> player1;
			std::cout << "Le jeu commence ! " << player1 << " VERSUS IA" << std::endl;
			quit = true;
			break;

		case 3:
			quit = true;
			displayMenu();
		}
	}
}


void Jeu::startGame(const Joueur& jou1, const Joueur& jou2) {

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
	vector<Joueur> joueurs;
	joueurs.push_back(jou1);
	joueurs.push_back(jou2);


	//displayBoard(jou1, jou2);

	while (isOver) {

		for (unsigned int i = 0; i < joueurs.size(); i++) {

			cout << " ## C'est au joueur " << joueurs[i].getNom() << " de jouer ## " << endl;
			cout << " J" << i + 1 << " choisis une borne[chiffre entre 0 et 5] : ";
			int id_tuile = getUserInput();
			cout << " J" << i + 1 << " choisis sa carte à poser [chiffre entre 0 et " << joueurs[i].getNbCartes() << "] : ";
			int choix_carte = getUserInput();
			play_card_c(0, id_tuile, j1.getCarteC()[choix_carte]);
			draw_card_c(i);

			//displayBoard(jou1, jou2);


		}
	}
}

