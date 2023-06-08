#include "JeuTactique.h"
#include <string>

using namespace std;
/*
JeuTactique::JeuTactique() : Jeu() {
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
	*//*
	vector<int> suite = { 0, 0, 0, 2, 1, 2, 1 };
	pioche_tact.push(new Ruse(ruse, "Chasseur de Tete", suite));
	suite = { 7, 3 };
	pioche_tact.push(new Ruse(ruse, "Stratège", suite));
	suite = { 4, 5 };
	pioche_tact.push(new Ruse(ruse, "Banshee", suite));
	suite = { 4, 6 };
	pioche_tact.push(new Ruse(ruse, "Traitre", suite));
}*/



int JeuTactique::choixPioche() const {
	std::cout << "Voulez-vous piocher dans la pioche classique ou tactique (C/T) : " << std::endl;
	string choix;
	std::cin >> choix;
	while (true) {
		if (choix[0] == "C" || choix[0] == "c")
			return 0;
		else if (choix[0] == "T" || choix[0] == "t")
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
		getJoueurs()[id_joueur].ajouter_Carte_c(piocher_c());
}

// Ajoute dans le vecteur de la carte Ruse
void JeuTactique::piocheRuse(int choix_pioche, Ruse* carte) {
	if (choix_pioche)
		carte->addCartes(piocher_t());
	else
		carte->addCartes(Jeu::piocher_c());
}

Carte* JeuTactique::choisirCarte(int id_joueur, vector<Carte*> vecteur) {
	cout << " Choisis une carte [chiffre entre 0 et " << getJoueurs()[id_joueur].getNbCartes() << "] : ";
	int choix_carte = Jeu::getUserInput();
	int taille_main_classique = getJoueurs()[id_joueur].getCarteC().size();
	int taille_main_tactique = getJoueurs()[id_joueur].getCarteT().size();
	int taille_main = taille_main_classique + taille_main_tactique;
	if (choix_carte < taille_main_classique) {
		return getJoueurs()[id_joueur].getCarteC()[choix_carte];
	}
	else if (choix_carte < taille_main) {
		choix_carte -= taille_main_classique;
		return getJoueurs()[id_joueur].getCarteT()[choix_carte];
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
				if (*find(carte->getAllCartes().begin(), carte->getAllCartes().end(), carte_classique) == carte_classique)
					carte->getAllCartes().erase(carte_classique);
				else
					getJoueurs()[id_joueur].getCarteC().erase(carte_classique);
				getPioche_c().Pioche_c::push(carte_classique);
			}
			else {
				if (*find(carte->getAllCartes().begin(), carte->getAllCartes().end(), carte_tactique) == carte_tactique)
					carte->getAllCartes().erase(carte_tactique); 
				else
					getJoueurs()[id_joueur].getCarteT().erase(carte_tactique);
				pioche_tact.Pioche_t::push(carte_tactique);
			}
			break;

		case 2:
			// 2 = choisir carte de notre main (et le vecteur de Ruse)
			Carte * c = choisirCarte(int id_joueur, carte->getAllCartes()); // fonction à définir dans joueur ?
			carte_tactique = dynamic_cast<Carte_t*>(c);
			if (carte_tactique != nullptr)
				carte_classique = dynamic_cast<Carte_c*>(c);
			break;

		case 3:
			// 3 = placer carte sur borne non revendiquée de notre côté ou defausser
			cout << "Voulez-vous défausser la carte ou la placer sur une autre borne de votre cote ? (d = defausser / p = placer) " << endl;
			string choix;
			std::cin >> choix;
			while (true) {
				if (choix[0] == "d" || choix[0] == "D")
					displayBoard(getJoueurs()[i]);
				cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
				int id_tuile = getUserInput();
				carte_classique = getPlateau()[id_tuile]->defausseSoi(id_joueur);
				defausse.push(carte_classique);
				cout << "C'est tout bon ! " << endl;
				break;
				else if (choix[0] == "p" || choix[0] == "P")
					displayBoard(getJoueurs()[i]);
				cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
				int id_tuile = getUserInput();
				getJoueurs()[id_joueur].poser_carte(carte_classique, id_joueur, getPlateau()[id_tuile]);
				cout << "C'est bon !" << endl;
				displayBoard(getJoueurs()[i]);
				break;
				else
					std::cout << "Choix invalide, recommencez (d/p) : " << std::endl;
				choix = "";
			}
			break;

		case 4:
			// 4 = choisir carte du cote adverse non revendiquée
			displayBoard(getJoueurs()[i]);
			cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
			int id_tuile = getUserInput();
			if (id_joueur)
				carte_classique = getPlateau()[id_tuile]->defausseSoi(id_joueur - 1);
			else
				carte_classique = getPlateau()[id_tuile]->defausseSoi(id_joueur + 1);
			break;

		case 5:
			// 5 = défausser de la main
			if (carte_classique != nullptr)
				defausse.push(carte_classique);
			else
				defausse.push(carte_tactique);
			break;

		case 6:
			// 6 = placer devant une tuile non revendiquée de notre cote
			displayBoard(getJoueurs()[i]);
			cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
			int id_tuile = getUserInput();
			getJoueurs()[id_joueur].poser_carte(carte_classique, id_joueur, getPlateau()[id_tuile]);
			cout << "C'est bon !" << endl;
			displayBoard(getJoueurs()[i]);
			break;

		case 7:
			// 7 = choisir carte de notre cote
			displayBoard(getJoueurs()[i]);
			cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
			int id_tuile = getUserInput();
			carte_classique = getPlateau()[id_tuile]->defausseSoi(id_joueur);
			break;

		default:
			throw("Erreur dans la suite d'actions de la carte Ruse");
			break;
		}
	}
	for (unsigned int i = 0; i < actions.size(); i++) {
		carte_tactique = dynamic_cast<Carte_t*>(actions[i]);
		if (carte_tactique != nullptr) {
			carte_classique = dynamic_cast<Carte_c*>(actions[i]);
			getJoueurs()[id_joueur].ajouter_Carte_c(carte_classique);
		}
		else {
			getJoueurs()[id_joueur].ajouter_Carte_t(carte_tactique);
		}
	}
}

bool JeuTactique::tactiqueJouable(int id_j1, int id_j2) const {
	return (nb_cartes_tactiques_jouees[getJoueurs()[id_j1]] <= nb_cartes_tactiques_jouees[getJoueurs()[id_j2]]);
}

void JeuTactique::distribuerCartes() {
	for (unsigned int i = 0; i < getJoueurs.size(); i++) {
		for (unsigned int j = 0; j < 7; j++) {
			getJoueurs()[i].ajouter_Carte_c(getPioche_c().pop());
		}
	}
}

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
	distribuerCartes();

	while (isOver == false) {
		
		for (unsigned int i = 0; i < getJoueurs().size(); i++) {

			displayBoard();
			getJoueurs()[i].afficherMain(); 

			// Poser la carte choisie
			cout << " ## C'est au joueur " << getJoueurs()[i].getNom() << " de jouer ## " << endl;
			cout << getJoueurs()[i].getNom() << " choisis une borne[chiffre entre 0 et 8] : ";
			int id_tuile = getUserInput();
			cout << getJoueurs()[i].getNom() << " choisis sa carte a poser [chiffre entre 0 et " << getJoueurs()[i].getNbCartes() - 1 << "] : ";
			int choix_carte = getUserInput();
			Carte* carte_a_jouer = choisirCarte(i, vector<Carte*>);
			if (typeid(*carte_a_jouer) == typeid(Ruse)) {
				execRuse(dynamic_cast<Ruse*>(carte_a_jouer), i); 
				cout << "Exécution terminée ! " << endl; 
			}
			else {
				getJoueurs()[i].poser_carte(, i, plateau[id_tuile]); 
			}
			for (int i = 0; i < 10; i++)
				cout << endl;
			displayBoard();

			// Possible revendication
			string choix;
			cout << "Voulez-vous revendiquer une borne ? (O / N) ";
			cin >> choix; 
			if (choix[0] == "O" || choix[0] == "o") {
				claim(i);
			}
			getJoueurs()[i].afficherMain();

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