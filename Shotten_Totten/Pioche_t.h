#pragma once
#ifndef PIOCHE_T_H
#define PIOCHE_T_H

#include <vector>
#include <ostream>
#include "Carte_t.h"

/// <summary>
/// This class represents the collection of tactical cards that are playable during the game.
/// These cards are drawn by players and put on the board.
/// This collection is for the tactical cards.
/// </summary>
class Pioche_t
{

private:

	///collection of cards
	std::vector<Carte_t> cartes;

public:
	/// <summary>
	/// Constructor initializes the card vector
	/// </summary>
	/// <param name="c">the collection of cards to be set as the attribute</param>
	Pioche_t(std::vector<Carte_t> const& c) :cartes(c) {};

	size_t getSize() const {
		return this->cartes.size();
	}

	std::vector<Carte_t> getCartes() const {
		return this->cartes;
	}

	/// <summary>
	/// Allows the user to insert a card at the end of the vector
	/// </summary>
	/// <param name="c">the card to insert</param>
	void push(const Carte_t& c);

	/// <summary>
	/// Allows the user to retrieve the first element of the vector
	/// </summary>
	/// <returns> the card on top of the collection</returns>
	Carte_t pop();

	/// <summary>
	/// Default destructor
	/// </summary>
	~Pioche_t() = default;

	/// <summary>
	/// Allows the user to get the X first cards of the collection
	/// </summary>
	/// <param name="x">the number of cards to retrieve of the collection</param>
	/// <returns>a vector of the X first cards</returns>
	std::vector<Carte_t*> getXFirstCard(int x);
};


/// <summary>
/// Print operator overload to display the card and its caracteristics
/// </summary>
/// <param name="os"> the output stream</param>
/// <param name="cc"> the card to display</param>
/// <returns> the output stream with the card's information</returns>
inline std::ostream& operator<<(std::ostream& os, const Pioche_t& p) {
	os << "[";
	for (int i = 0; i < p.getSize(); i++) {
		p.getCartes()[i].print(os);
		if (i != p.getSize() - 1)
			os << ", ";
	}
	os << "]\n";
	return os;
}

#endif // !PIOCHE_T_H





