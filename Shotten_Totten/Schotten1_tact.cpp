#include "Schotten1_tact.h"
#include <string>

Schotten1_tact::Schotten1_tact() {
	defausse = Defausse();
	vector<Carte_t> pioche;
	nb_cartes_tactiques_jouees = vector<int>;
	nb_cartes_tactiques_jouees.push_back(0);
	nb_cartes_tactiques_jouees.push_back(0); 

	// Création des cartes Troupe d'Elite
	pioche.push_back(TroupeElite(elite, "Joker", -1, "Non couleur", 1, 9));
	pioche.push_back(TroupeElite(elite, "Joker", -1, "Non couleur", 1, 9));
	pioche.push_back(TroupeElite(elite, "Espion", -1, "Non couleur", 7, 7));
	pioche.push_back(TroupeElite(elite, "Porte-Bouclier", -1, "Non couleur", 1, 3));

	// Création des cartes Mode de Combat
	Combinaison c1 = Combinaison(1, 0, 0); 
	Combinaison c2 = Combinaison(1, 1, 0); 
	Combinaison c3 = Combinaison(0, 0, 1); 
	Combinaison c4 = Combinaison(0, 1, 0); 
	vector<Combinaison*> vecteur_combi; 
	vecteur_combi.push_back(&c1); 
	vecteur_combi.push_back(&c2); 
	vecteur_combi.push_back(&c3); 
	vecteur_combi.push_back(&c4);
	pioche.push_back(ModeCombat(combat, "Colin-Maillard", 3, vecteur_combi));
	pioche.push_back(ModeCombat(combat, "Combat de Boue", 4, vector<Combinaison*>)); // vecteur vide

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
	vector<int> suite(0, 0, 0, 2, 1, 2, 1);
	pioche.push_back(Ruse(ruse, "Chasseur de Tete", suite));
	suite = (7, 3);
	pioche.push_back(Ruse(ruse, "Stratège", suite));
	suite = (4, 5);
	pioche.push_back(Ruse(ruse, "Banshee", suite));
	suite = (4, 6);
	pioche.push_back(Ruse(ruse, "Traitre", suite));

	// Création de la pioche tactique
	pioche_tact = Pioche_t(pioche);
}

int Schotten1_tact::choixPioche() const {
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

// Ajoute dans le vecteur de la carte Ruse
void Schotten1_tact::piocheRuse(int choix_pioche, Ruse& carte) {
	if (choix_pioche)
		carte.addCartes(piocher_t());
	else
		carte.addCartes(Jeu::piocher_c());
}

Carte* Schotten1_tact::choisirCarte(int id_joueur, vector<Carte*> vecteur) {
	cout << " Choisis une carte [chiffre entre 0 et " << joueurs[id_joueur].getNbCartes() << "] : ";
	int choix_carte = Jeu::getUserInput();
	int taille_main_classique = joueurs[id_joueur].getCarteC().size(); 
	int taille_main_tactique = joueurs[id_joueur].getCarteT().size();
	int taille_main = taille_main_classique + taille_main_tactique;
	if (choix_carte < taille_main_classique) {
		return joueurs[id_joueur].getCarteC()[choix_carte];
	}
	else if (choix_carte < taille_main) {
		choix_carte -= taille_main_classique;
		return joueurs[id_joueur].getCarteT()[choix_carte];
	}
	else {
		choix_carte -= taille_main;
		return vecteur[choix_carte];
	}
}

void Schotten1_tact::execRuse(Ruse& carte, int id_joueur) {
	vector<int> actions = carte.getActions();
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
				if (*find(actions.begin(), actions.end(), carte_classique) == carte_classique)
					actions.erase(carte_classique);
				else
					joueurs[id_joueur].getCarteC().erase(carte_classique);
				getPioche_c().Pioche_c::push(carte_classique);
			}
			else {
				if (*find(actions.begin(), actions.end(), carte_tactique) == carte_tactique)
					actions.erase(carte_tactique);
				else
					joueurs[id_joueur].getCarteT().erase(carte_tactique);
				pioche_tact.Pioche_t::push(carte_tactique);
			}
			break;

		case 2:
			// 2 = choisir carte de notre main (et le vecteur de Ruse)
			Carte* c = choisirCarte(int id_joueur, carte.getAllCartes()); // fonction à définir dans joueur ?
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
					displayBoard(joueurs[i]);
					cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
					int id_tuile = getUserInput();
					carte_classique = getPlateau()[id_tuile]->defausseSoi(id_joueur);
					defausse.push(carte_classique);
					cout << "C'est tout bon ! " << endl;
					break;
				else if (choix[0] == "p" || choix[0] == "P")
					displayBoard(joueurs[i]);
					cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
					int id_tuile = getUserInput();
					joueurs[id_joueur].poser_carte(carte_classique, id_joueur, getPlateau()[id_tuile]);
					cout << "C'est bon !" << endl; 
					displayBoard(joueurs[i]);
					break;
				else
					std::cout << "Choix invalide, recommencez (d/p) : " << std::endl;
				choix = "";
			}
			break;

		case 4:
			// 4 = choisir carte du cote adverse non revendiquée
			displayBoard(joueurs[i]);
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
			displayBoard(joueurs[i]); 
			cout << " J" << id_joueur + 1 << " choisis une borne[chiffre entre 0 et 8] : ";
			int id_tuile = getUserInput(); 
			joueurs[id_joueur].poser_carte(carte_classique, id_joueur, getPlateau()[id_tuile]); 
			cout << "C'est bon !" << endl;
			displayBoard(joueurs[i]); 
			break;

		case 7:
			// 7 = choisir carte de notre cote
			displayBoard(joueurs[i]); 
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
			joueurs[id_joueur].ajouter_Carte_c(carte_classique); 
		}
		else {
			joueurs[id_joueur].ajouter_Carte_t(carte_tactique); 
		}
	}
}

bool Schotten1_tact::tactiqueJouable(int id_j1, int id_j2) {
	return (nb_cartes_tactiques_jouees[joueurs[id_j1]] <= nb_cartes_tactiques_jouees[joueurs[id_j2]]);
}