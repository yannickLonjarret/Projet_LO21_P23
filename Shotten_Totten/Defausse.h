#ifndef DEFAUSSE_H
#define DEFAUSSE_H

#include "Carte.h"
#include <vector>
#include <ostream>
using namespace std;

/// <summary>
/// This class stores cards that are discarded during the game
/// </summary>
class Defausse {
private:

	static const int nb_cartesMax = 64; //maximum number of cards
	int nb_cartes = 0; // number of cards at a given time
	vector<Carte*> cartes; // the cards that are stored

public:

	/// <summary>
	/// Constructor for the Defausse , initialy the defausse is empty, so is the number of cards.
	///
	Defausse() = default;

	//FUNCTIONS

	/// <summary>
	/// Retrives the last card on the defausse. Decreases the number of cards in the defausse
	/// </summary>
	/// <returns>the last card on the defausse</returns>
	Carte* pop() {
		this->nb_cartes--;
		return cartes.back();
	}

	/// <summary>
	/// Adds a card to the defausse.
	/// Increases the number of cards
	/// </summary>
	/// <param name="c">the card to add</param>
	void push(Carte* c) {
		this->cartes.push_back(c);
		this->nb_cartes++;
	}

	/// <summary>
	/// retreieves the X first card of the defausse for visualization.
	/// </summary>
	/// <param name="x">x first cards to retrieve</param>
	/// <returns>a vector of the x first cards</returns>
	vector<Carte*> getXFirstCard(int x) {
		std::vector<Carte*> ret;

		for (int i = 0; i < x; i++) {
			ret.push_back(cartes[i]);
		}
		return ret;
	}

	/// <summary>
	/// returns thr size of the defausse. number of cards
	/// </summary>
	/// <returns>the number of cards</returns>
	int getSize() const {
		return nb_cartes;
	}

	/// <summary>
	/// Retirveves the whole defausse.
	/// </summary>
	/// <returns>the cards in the defausse</returns>
	vector<Carte*> getCartes() const {
		return this->cartes;
	}


	/// <summary>
	/// default destructor
	/// </summary>
	~Defausse() = default;

	static int getNbCartesMax() {
		return nb_cartesMax;
	}
};

/// <summary>
/// Allows to print out the defausse.
/// </summary>
/// <param name="os">the output stream to print the defausse on</param>
/// <param name="d">the defausse</param>
/// <returns>the output stream with the defausse displayed on</returns>

inline std::ostream& operator<<(std::ostream& os, const Defausse& d) {
	os << "[";
	for (int i = 0; i < d.getSize(); i++) {
		d.getCartes()[i]->print(os); //particularité de l'appel de print -> permet de print n'importe quelle sous classe de Carte.
		if (i != d.getSize() - 1)
			os << ", ";
	}
	os << "]\n";
	return os;
}


#endif // !DEFAUSSE_H
