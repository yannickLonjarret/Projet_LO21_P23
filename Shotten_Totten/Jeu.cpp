#include "Jeu.h"
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <iomanip>





void Jeu::displayBoard() const {
	const int NUM_ZONES = 9;
	const int BOARD_WIDTH = 50;

	int longueur_borne = 46;
	cout << " \n COTE J1                                                           COTE J2               \n";

	string leftZone = "";
	string rightZone = "";

	for (int i = NUM_ZONES - 1; i >= 0; i--) {

		string claimable = (getPlateau()[i]->isClaimable() == true ? "REVENDICABLE" : "NON REVENDICABLE");

		if (getPlateau()[i]->getCotes()[0]->getNbCartes() == 0) {

			std::string leftZone = "";
			std::string rightZone = "";

			std::string leftPadding(BOARD_WIDTH - (BOARD_WIDTH / 2 + leftZone.length()) + 20, ' ');
			std::string rightPadding(BOARD_WIDTH - rightZone.length() + 3, ' ');
			cout << leftPadding << leftZone << " | | " << rightZone << rightPadding << claimable << endl;;
		}
		else {

			Tuile tile = *getPlateau()[i];

			std::string leftPadding(BOARD_WIDTH - (BOARD_WIDTH / 2) + 20, ' ');
			std::string rightPadding(BOARD_WIDTH, ' ');
			cout << leftPadding << tile << rightPadding << claimable << endl;
		}
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


void Jeu::distribuer_cartes() {

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

/*
void Jeu::play_card_c(int id_j, int id_tuile, Carte_c& c) {
	// Find the player with the given id_j
	Joueur& joueur = (id_j == 1) ? j1 : j2;


	// Check if the card is in the player's hand
	bool cardFound = false;
	for (Carte_c* carte : joueur.getCarteC()) {
		if (*carte == c) {
			cardFound = true;
			break;
		}
	}

	if (!cardFound) {
		std::cout << "La carte n'est pas dans la main du joueur." << std::endl;
		return;
	}

	// Place the card on the tile

	plateau[id_tuile]->Tuile::ajout_c(&c, id_j);

	// Remove the card from the player's hand
	joueur.pop(c);
}
*/

/*
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
*/





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

		default:
			cout << "L'entrée n'est pas valide, recommencez." << endl;
		}

	}
}


void Jeu::startGame(Joueur& jou1, Joueur& jou2) {

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


	jou1.ajouter_Carte_c(new Carte_c(1, "Rouge"));
	jou1.ajouter_Carte_c(new Carte_c(5, "Vert"));
	jou1.ajouter_Carte_c(new Carte_c(6, "Bleu"));
	jou1.ajouter_Carte_c(new Carte_c(3, "Rouge"));
	jou1.ajouter_Carte_c(new Carte_c(9, "Bleu"));
	jou1.ajouter_Carte_c(new Carte_c(5, "Jaune"));
	//remplacer les instruction avant par la méthode distibuer cartes qui donne des cartes de la pioche vers la main du joueur.

	jou2.ajouter_Carte_c(new Carte_c(5, "Jaune"));
	jou2.ajouter_Carte_c(new Carte_c(1, "Rouge"));
	jou2.ajouter_Carte_c(new Carte_c(1, "Jaune"));
	jou2.ajouter_Carte_c(new Carte_c(6, "Bleu"));
	jou2.ajouter_Carte_c(new Carte_c(4, "Rouge"));
	jou2.ajouter_Carte_c(new Carte_c(9, "Bleu"));



	joueurs.emplace_back(jou1);
	joueurs.emplace_back(jou2);

	while (isOver == false) {
		cout << joueurs.size();
		for (unsigned int i = 0; i < joueurs.size(); i++) {

			displayBoard();
			joueurs[i].afficherMain();

			cout << " ## C'est au joueur " << joueurs[i].getNom() << " de jouer ## " << endl;
			cout << joueurs[i].getNom() << " choisis une borne[chiffre entre 0 et 8] : ";
			int id_tuile = getUserInput();
			cout << joueurs[i].getNom() << " choisis sa carte a poser [chiffre entre 0 et " << joueurs[i].getNbCartes() - 1 << "] : ";
			int choix_carte = getUserInput();
			joueurs[i].poser_carte(joueurs[i].getCarteC()[choix_carte], i, plateau[id_tuile]);
			displayBoard();
			joueurs[i].afficherMain();
			//joueurs[i].piocher_c(this->pioche_c);

			cout << joueurs[i].getNom() << " a termine son tour. \n## Entrez un caractère pour confirmer que vous avez change de place..." << endl;
			string temp_prompt = "";
			cin >> temp_prompt;
			cout << endl;
		}
	}
}

