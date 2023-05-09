#pragma once
#ifndef CARTES_C_H
#define CARTES_C_H

#include "Carte.h"
#include <ostream>

/// <summary>
/// Enumerates the possible color a card can have.
/// The color defines the clan to which it belongs.
/// </summary>
enum Couleur {
	Rouge, Vert, Bleu, Jaune, Noir, Gris
};


/// <summary>
/// Carte_c represents the classical cards (the ones that are not special in any way).
/// </summary>
class Carte_c : Carte
{
private:
	static int val_max; //maximum value
	static int val_min; //minimum value

	Couleur couleur; //color of the card
	int valeur; // value of the card ranging number [val_min, val_max]

public:

	/// <summary>
	/// Constructor for the Carte class.
	/// Initializes the attributes.
	/// Initializes the static attributes is the optionnal parameters are specified
	/// </summary>
	/// <param name="val"> value of the card : int </param>
	/// <param name="col"> color of the card : Couleur </param>
	/// <param name="vmin"> optionnal, minimal value of the card </param>
	/// <param name="vmax"> optionnal, maximal value of the card </param>
	Carte_c(int val, Couleur col) :couleur(col), valeur(val) {
	}

	///FUNCTIONS
	void setValeur(int val);
	void setCouleur(Couleur col);
	static int getValMax();
	static int getValMin();
	void setValMax(int vmax);
	void setValMin(int vmin);
	Couleur getCouleur() const;
	int getValeur() const;


	/// <summary>
	/// Default Destructor 
	/// </summary>
	~Carte_c() = default;


};

/// <summary>
/// Print ooperator overload to display the card and it's caracteristics
/// </summary>
/// <param name="os"> the output stream</param>
/// <param name="cc"> the card to display</param>
/// <returns> the output stream with the card's information</returns>
std::ostream& operator<<(std::ostream& os, const Carte_c& cc) {
	os << "+------CARTE_C------+\n"
		<< "|   Valeur :" << cc.getValeur() << "    \n"
		<< "|   Couleur:" << cc.getCouleur() << "    \n"
		<< "+-------------------+" << std::endl;
	return os;
}


#endif // !CARTES_C_H


