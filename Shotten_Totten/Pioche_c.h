#pragma once
#ifndef PIOCHE_C_H
#define PIOCHE_C_H

#include <vector>
#include <ostream>
#include <random>
#include <algorithm>
#include "Carte_c.h"

/// <summary>
/// This class represents the collection of cards that are playable during the game.
/// These cards are drawn by players and put on the board.
/// This collection is for the classical cards.
/// </summary>
class Pioche_c
{

private:

	///collection of cards
	std::vector<Carte_c*> cartes;

public:
	/// <summary>
	/// COnstructor initializes the card vector
	/// </summary>
	/// <param name="c">the collection of cards to be set as the attribute</param>
	Pioche_c(std::vector<Carte_c*> const& c) :cartes(c) {};
	Pioche_c() { for (unsigned int i = 0; i < cartes.size(); i++) delete cartes[i]; }


	int getSize() const {
		return cartes.size();
	}

	std::vector<Carte_c*> getCartes() const {
		return cartes;
	}

	/// <summary>
	/// Allows the user to insert a card at the end of the vector
	/// </summary>
	/// <param name="c">the card to insert</param>
	void push(Carte_c* c);

	/// <summary>
	/// Allows the user to retrieve the first element of the vector
	/// </summary>
	/// <returns> the card on top of the collection</returns>
	Carte_c* pop();

	/// <summary>
	/// Allows the user to randomly shuffle the deck
	/// </summary>
	void shuffle() {
		srand(time(NULL));
		random_shuffle(cartes.begin(), cartes.end());
	}

	/// <summary>
	/// Default destructor
	/// </summary>
	~Pioche_c() = default;

	/// <summary>
	/// Allows the user to get the X first cards of the collection
	/// </summary>
	/// <param name="x">the number of cards to retrieve of the collection</param>
	/// <returns>a vector of the X first cards</returns>
	std::vector<Carte_c*> getXFirstCard(int x);

};


/// <summary>
/// Print ooperator overload to display the card and it's caracteristics
/// </summary>
/// <param name="os"> the output stream</param>
/// <param name="cc"> the card to display</param>
/// <returns> the output stream with the card's information</returns>
inline std::ostream& operator<<(std::ostream& os, const Pioche_c& p) {
	os << "[";
	for (int i = 0; i < p.getSize(); i++) {
		p.getCartes()[i]->print(os);
		if (i != p.getSize() - 1)
			os << ", ";
	}
	os << "]\n";
	return os;
}

#endif // !PIOCHE_C_H



