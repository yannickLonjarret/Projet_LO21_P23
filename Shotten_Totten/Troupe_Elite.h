#ifndef TROUPE_ELITE_H
#define TROUPE_ELITE_H
#include "Carte_t.h"
using namespace std;

/// @brief TroupeElite represents cards which correspond to Troupe d'Elite cards (playable as clan cards)
class TroupeElite : public Carte_t, public Carte_c
{
private:
	/// @brief The minimum value this card is allowed to take
	int val_deb;

	/// @brief The maximum value this card is allowed to take
	int val_fin;
public:
	/// @brief Constructor of a TroupeElite card
	/// @param t : type of the card
	/// @param n : name of the card
	/// @param v : value of the card
	/// @param c : color of the card
	/// @param vd : minimum value
	/// @param vf : maximum value
	TroupeElite(types t, const string& n, const string& d, int v, const string& c, int vd, int vf) :Carte_t(t, n, d), Carte_c(v, c), val_deb(vd), val_fin(vf) {}

	/// @brief Default destructor
	~TroupeElite() = default;

	/// @brief Allows the user to get the minimum value the card can take
	/// @return the minimum value
	int getDebut() const { return val_deb; }

	/// @brief Allows the user to get the maximum value the card can take
	/// @return the maximum value
	int getFin() const { return val_fin; }

	/// @brief Allows the user to change the minimum value takeable
	/// @param v : the desired minimum value
	void setDebut(int v) { val_deb = v; }

	/// @brief Allows the user to change the maximum value takeable
	/// @param v : the desired maximum value
	void setFin(int v) { val_fin = v; }

	/// @brief Allows the user to change both the minimum and the maximum values takeable
	/// @param vd : minimum value
	/// @param vf : maximum value	
	void setAll(int vd, int vf) { val_deb = vd; val_fin = vf; }

	/// <summary>
	/// Sets a elite troop to default settings using the class casting.
	/// </summary>
	void setDefault() override {
		this->setValeur(-1);
		this->setCouleur(getCouleurs()[0]);
	}

	/// @brief Allows the user to define the TroupeElite card to a Carte_c card (to claim)
	/// @param v : the value the card has to take
	/// @param c : the color the card has to take
	/// @return a Carte_c object 
	Carte_c definir_carte(int v, const string& c);
};

#endif // !TROUPE_ELITE_H