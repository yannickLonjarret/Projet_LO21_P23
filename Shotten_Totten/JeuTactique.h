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
	}

	/// <summary>
	/// Allows the user to pick the first card of the tactical deck
	/// </summary>
	/// <returns>The reference of the card</returns>
	Carte_t* piocher_t() {
		if (pioche_tact.getSize() != 0)
			return pioche_tact.pop();
	}

	/// <summary>
	/// Allows the user to add the picked card (in the tactical or the classical deck) to the vector in a card Ruse
	/// </summary>
	/// <param name="choix_pioche">The deck where the user wants to pick a card (tactical or classical)</param>
	/// <param name="carte">The Ruse card permitting the picking</param>
	void piocheRuse(int choix_pioche, Ruse& carte);

	/// <summary>
	/// Executes the different actions of a Ruse card
	/// </summary>
	/// <param name="carte">The Ruse card to play</param>
	/// <param name="id_joueur">The id of the player whose the Ruse card belongs to</param>
	void execRuse(Ruse& carte, int id_joueur);

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

	//void jouer(); // méthode virtuelle de Jeu normalement
};

#endif // !JeuTactique_H