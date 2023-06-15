#include <iostream>
#include <vector>
#include <algorithm>

#include "Combinaison.h"
#include "Tuile.h"
#include <chrono>
#include "Jeu.h"
#include "Troupe_Elite.h"
#include "Defausse.h"
#include "JeuTactique.hpp"


const int NUM_ZONES = 9;
const int BOARD_WIDTH = 40;

// Function to display the game board
void displayGameBoard(const std::vector<std::string>& leftSide, const std::vector<std::string>& rightSide) {
	std::cout << std::string(BOARD_WIDTH, ' ') << " | " << std::string(BOARD_WIDTH, ' ') << std::endl;

	for (int i = NUM_ZONES - 1; i >= 0; i--) {
		std::string leftZone = (i < leftSide.size()) ? leftSide[i] : "";
		std::string rightZone = (i < rightSide.size()) ? rightSide[i] : "";

		std::string leftPadding(BOARD_WIDTH - leftZone.length(), ' ');
		std::string rightPadding(BOARD_WIDTH - rightZone.length(), ' ');

		std::cout << leftZone << leftPadding << " | " << rightZone << rightPadding << std::endl;
	}

	std::cout << std::string(BOARD_WIDTH, ' ') << " | " << std::string(BOARD_WIDTH, ' ') << std::endl;
}


int main() {


	/*
	vector<Combinaison*> vic; //vic

	vector<Carte_c*> cards;
	vector<Tuile*> tuile; //plateau

	Carte_c::getCouleurs().push_back("Vert");
	Carte_c::getCouleurs().push_back("Bleu");
	Carte_c::getCouleurs().push_back("Rouge");
	Carte_c::getCouleurs().push_back("Jaune");
	Carte_c::getCouleurs().push_back("Violet");
	Carte_c::getCouleurs().push_back("Marron");


	TroupeElite* joker = new TroupeElite((types)0, "Joker", "Le putain de joker", -1, Carte_c::getCouleurs()[0], 1, 9);
	TroupeElite* joker2 = new TroupeElite((types)0, "Joker", "Le putain de joker", -1, Carte_c::getCouleurs()[0], 1, 9);
	TroupeElite* joker3 = new TroupeElite((types)0, "Joker", "Le putain de joker", -1, Carte_c::getCouleurs()[0], 1, 9);



	Carte_t* j1 = joker;
	Carte_t* j2 = joker2;
	Carte_t* j3 = joker3;

	vic.push_back(new Combinaison(false, false, false));
	vic.push_back(new Combinaison(true, false, false));
	vic.push_back(new Combinaison(false, true, false));
	vic.push_back(new Combinaison(false, false, true));
	vic.push_back(new Combinaison(true, true, false));

	Tuile* t = new Tuile(3, vic, 2);

	tuile.push_back(t);

	t->ajout_carte((Carte*)new Carte_c(3, "Rouge"), 0);
	t->ajout_carte((Carte*)new Carte_c(2, "Rouge"), 0);
	t->ajout_carte((Carte*)new Carte_c(1, "Rouge"), 0);

	cards = t->getCotes()[0]->getCartesC();
	cout << "Nb cartes J1: " << cards.size() << endl;

	for (int i = 0; i < cards.size(); i++) {
		cout << cards[i]->getValeur() << " " << cards[i]->getCouleur() << endl;
	}
	cout << "Nb cartes J2: " << t->getCotes()[1]->getCartesC().size() << endl;
	for (int i = 0; i < t->getCotes()[1]->getCartesC().size(); i++) {
		cout << t->getCotes()[1]->getCartesC()[i]->getValeur() << " " << t->getCotes()[1]->getCartesC()[i]->getCouleur() << endl;
	}

	t->ajout_carte((Carte*)j1, 1);
	t->ajout_carte((Carte*)j2, 1);
	t->ajout_carte((Carte*)j3, 1);

	cards = t->getCotes()[1]->getCartesC();

	for (int i = 0; i < cards.size(); i++) {
		cout << cards[i]->getValeur() << " " << cards[i]->getCouleur() << endl;
	}


	auto startTime = std::chrono::high_resolution_clock::now();

	t->claimTuile(0, tuile);
	auto endTime = std::chrono::high_resolution_clock::now();
	cout << "gagnant: " << t->getClaim() << endl;

	std::chrono::duration<double> duration = endTime - startTime;
	double seconds = duration.count();


	t->ajout_c(new Carte_c(9, "Bleu"), 1);
	t->ajout_c(new Carte_c(8, "Bleu"), 1);
	t->ajout_c(new Carte_c(7, "Bleu"), 1);


	cout << "Nb cartes J2: " << t->getCotes()[1]->getCartesC().size() << endl;

	cards = t->getCotes()[1]->getCartesC();

	for (int i = 0; i < cards.size(); i++) {
		cout << cards[i]->getValeur() << " " << cards[i]->getCouleur() << endl;
	}

	cout << endl;
	vector<Carte_t*> card = t->getCotes()[1]->getCartesT();

	for (int i = 0; i < card.size(); i++) {
		cout << *card[i]<< endl;
	}

	//t->claimTuile(0, tuile);
	cout << "gagnant: " << t->getClaim() << endl;

	cout << "Temps de preuve: " << seconds << endl;
	cout << *t;
	*/

	std::cout << R"(

   _____      _           _   _                _______    _   _             
  / ____|    | |         | | | |              |__   __|  | | | |            
 | (___   ___| |__   ___ | |_| |_ ___ _ __ ______| | ___ | |_| |_ ___ _ __  
  \___ \ / __| '_ \ / _ \| __| __/ _ \ '_ \______| |/ _ \| __| __/ _ \ '_ \ 
  ____) | (__| | | | (_) | |_| ||  __/ | | |     | | (_) | |_| ||  __/ | | |
 |_____/ \___|_| |_|\___/ \__|\__\___|_| |_|     |_|\___/ \__|\__\___|_| |_|
            
 BOUCHARD REMI & BRUNIAUX ALIENOR & LAGUE PIERRE & LONJARRET YANNICK & MONDESERT JULES
                                                
                                                                            
)" << '\n';

	int choice;
	bool quit = false;
	Jeu* jeu_classique;
	JeuTactique* jeu_tactique;

	while (!quit) {
		std::cout << R"(
  __  __                  
 |  \/  |                 
 | \  / | ___ _ __  _   _ 
 | |\/| |/ _ \ '_ \| | | |
 | |  | |  __/ | | | |_| |
 |_|  |_|\___|_| |_|\__,_|
                          
 1 - Jouer en version classique
 2 - Joueur en version tactique
 3 - Quitter  
                     
		)" << '\n';

		std::string input;
		std::cout << "Choisissez une option : ";
		std::cin >> input;
		choice = std::stoi(input);
		switch (choice)
		{
		case 1:
			quit = true;
			jeu_classique = &Jeu::donneInstance();
			jeu_classique->printTitles();
			jeu_classique->menu_selection();
			jeu_classique->startGame();
			Jeu::libereInstance();
			break;
		case 2:
			quit = true;
			jeu_tactique = new JeuTactique();
			jeu_tactique->printTitles();
			jeu_tactique->menu_selection();
			jeu_tactique->startGame();
			delete jeu_tactique;
			break;
		case 3:
			quit = true;
			std::cout << "Au revoir !" << std::endl;
			return 0;

		default:
			std::cout << "Option invalide, respectez les choix et réessayez." << std::endl;
			break;
		}
	}

	/*
	if (choice) {
		Jeu* jeu = new Jeu();
		jeu->printTitles();
		jeu->menu_selection();
	}
	else {
		JeuTactique* jeu = new JeuTactique();
	}
	*/
	return 0;
}
