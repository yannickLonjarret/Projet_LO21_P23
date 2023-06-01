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
public:
	/// @brief Constructor of a Ruse card
	/// @param t : the type of the card
	/// @param n : the name of the card
	/// @param suite_actions : a vector of the different actions permitted by this card
	Ruse(types t, string n, vector<int> suite_actions) : Carte_t(t, n), actions(suite_actions) {}

	/// @brief Default destructor
	~Ruse() = default;

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
};

#endif // !CARTE_RUSE_H