#ifndef SCHOTTEN1_TACT_H
#define SCHOTTEN1_TACT_H
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
class Schotten1_tact : public Jeu{
private:
	/// <summary>
	/// pioche_tact represents the tactical pick
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
	/// Constructor which creates the pick with all the specific tactical cards required, and initializes the discard defausse
	/// </summary>
	Schotten1_tact();

	/// <summary>
	/// Allows the user to pick the first card of the tactical pick
	/// </summary>
	/// <returns>The reference of the card</returns>
	Carte_t& piocher_t() {
		if (pioche_tact.getSize() != 0)
			return pioche_tact.pop();
	}

	void piocheRuse(int choix_pioche, Ruse& carte);

	void execRuse(Ruse& carte, int id_joueur);
	int choixPioche() const;
	Carte* choisirCarte(int id_joueur, vector<Carte*> vecteur);
	/// <summary>
	/// Returns the possibility of the player (id_j1) to play a tactical card
	/// </summary>
	/// <param name="id_j1">The id of the player 1</param>
	/// <param name="id_j2">The id of the player 2</param>
	/// <returns>A boolean : True if playable or False if not</returns>
	bool tactiqueJouable(int id_j1, int id_j2); 
	void jouer(); // méthode virtuelle de Jeu normalement
};

#endif // !SCHOTTEN1_TACT_H