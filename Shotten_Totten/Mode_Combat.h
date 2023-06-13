#ifndef MODE_COMBAT_H
#define MODE_COMBAT_C
#include "Carte.h"

/// @brief ModeCombat represents cards 'Mode de Combat' (playable on a Tuile)
class ModeCombat : public Carte_t
{
private:
	/// @brief The number of cards to be able to claim the Tuile object where the card will be played
	int nb_cartes;

	/// @brief The vector of the different combinations accepted for the Tuile object where the card will be played
	vector<Combinaison*> victoirePossible;

public:
	/// @brief Constructor of a ModeCombat card
	/// @param t : the type of the card
	/// @param n : the name of the card
	/// @param nb : the number of cards (in order to claim the Tuile object)
	/// @param combi : the vector of Combinaison objects accepted (in order to claim the Tuile object)
	ModeCombat(types t, string n, int nb, vector<Combinaison*> combi) : Carte_t(t, n), nb_cartes(nb), victoirePossible(combi) {}

	/// @brief Default destructor
	~ModeCombat() { 
		for (unsigned int i = 0; i < victoirePossible.size(); i++) delete victoirePossible[i];
	}

	/// @brief Allows the user to get the number of cards
	/// @return the number of card 
	int getNbCartes() const {
		return nb_cartes;
	}

	/// @brief Allows the user to get the Combinaison vector
	/// @return a reference on the Combinaison objects vector
	const vector<Combinaison*>& getCombinaison() const {
		return victoirePossible;
	}

	//overriding the print function
	void print(std::ostream& os) const override {
		os << "[" << this->getNom() << "]" << std::endl;
	}
};

/// <summary>
/// Print ooperator overload to display the card and its caracteristics
/// </summary>
/// <param name="os"> the output stream</param>
/// <param name="mc"> the card to display</param>
/// <returns> the output stream with the card's information</returns>

inline std::ostream& operator<<(std::ostream& os, const ModeCombat& mc) {
	os << "[" << mc.getNom() << "]";
	return os;
}

#endif // !MODE_COMBAT_H