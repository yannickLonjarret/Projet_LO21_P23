#pragma once
#include "Carte.h"
#ifndef CARTE_RUSE_h
#define CARTE_RUSE_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "Combinaison.h"
#include "Carte_c.h"
#include "Carte_t.h"

/// @brief Ruse represents cards Ruses (which add different actions to the player's turn)
class Ruse : public Carte_t
{
private:
	/// @brief Represents a vector which contains all the permitted actions of the card
	vector<int> actions;
	/// <summary>
	/// Represents a vector of the cards which have to be kept during the process of a card Ruse
	/// </summary>
	vector<Carte*> cartes;

public:
	/// @brief Constructor of a Ruse card
	/// @param t : the type of the card
	/// @param n : the name of the card
	/// @param suite_actions : a vector of the different actions permitted by this card
	Ruse(types t, string n, vector<int> suite_actions) : Carte_t(t, n), actions(suite_actions) {}

	/// @brief Destructor of a Ruse card
	~Ruse() { for (unsigned int i = 0; i < cartes.size(); i++) delete cartes[i]; }

	/// @brief Allows the user to get the actions of the card
	/// @return the vector of the different actions
	const vector<int>& getActions() const {
		return actions;
	}

	/// @brief Allows the user to add an action in the vector actions
	/// @param a : the action to add
	void addAction(int a) {
		actions.push_back(a);
	}

	/// <summary>
	/// Allows the user to add a Carte pointer in the vector cartes
	/// </summary>
	/// <param name="c">The Carte pointer to add</param>
	void addCartes(Carte* c) {
		cartes.push_back(c);
	}

	/// <summary>
	/// Return the entire vector cartes
	/// </summary>
	/// <returns>The vector with all the cards in it</returns>
	vector<Carte*> getAllCartes() const {
		return cartes;
	}

	void eraseCarte(Carte* carte) {
		for (auto it = 0; it < cartes.size(); it++) {
			cout << "BOUCLE" << endl;
			if (cartes[it] == carte) {
				cout << "Suppression du vecteur" << endl;
				cartes.erase(cartes.begin() + it);  
				break;
			}
		}
	}

	//overriding the print function
	void print(std::ostream& os) const override {
		os << "[" << this->getNom() << "]";
	}
};

/// <summary>
/// Print ooperator overload to display the card and its caracteristics
/// </summary>
/// <param name="os"> the output stream</param>
/// <param name="r"> the card to display</param>
/// <returns> the output stream with the card's information</returns>

inline std::ostream& operator<<(std::ostream& os, const Ruse& r) {
	os << "[" << r.getNom() << "]";
	return os;
}

#endif // !CARTE_RUSE_H