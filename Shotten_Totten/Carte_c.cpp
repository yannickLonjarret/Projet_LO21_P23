#include "Carte_c.h"

/// <summary>
	/// Getter for the static attribute val_min
	/// </summary>
	/// <returns> val_min ; static int </returns>
int Carte_c::getValMin() {
	return val_min;
}

/// <summary>
/// Getter for the static attribute val_max
/// </summary>
/// <returns> val_max : static int </returns>
int Carte_c::getValMax() {
	return val_max;
}

/// <summary>
/// Getter for the value of the card (number)
/// </summary>
/// <returns> valeur : int </returns>
int Carte_c::getValeur() const {
	return this->valeur;
}


/// <summary>
/// Getter for the color of the card
/// </summary>
/// <returns> couleur : Couleur </returns>
const string& Carte_c::getCouleur() const {
	return this->couleur;
}

/// <summary>
/// Sets the value of val_min.
/// </summary>
/// <param name="vmin"> new value to be assigned to val_min </param>
void Carte_c::setValMin(int vmin) const {
	if (vmin > 0) {
		val_min = vmin;
	}
}

/// <summary>
/// Sets the value of val_min.
/// </summary>
/// <param name="vmax"> new value to be assigned to val_max </param>
void Carte_c::setValMax(int vmax) const {
	if (vmax > 0) {
		val_max = vmax;
	}
}

/// <summary>
/// Sets the value of valeur.
/// Has to be in bounds of val_min and val_max.
/// </summary>
/// <param name="val"> new value to be assigned to valeur</param>
void Carte_c::setValeur(int val) {
	if (val >= val_min && val <= val_max) {
		this->valeur = val;
	}
}

/// <summary>
/// Sets the value of the color of the card
/// </summary>
/// <param name="col"> the color to be assigned to the card</param>
void Carte_c::setCouleur(const string& col) {
	this->couleur = col;
}

/*

int Carte_c::val_min = 1;
int Carte_c::val_max = 9;

vector<string> Carte_c::couleurs(1, "NULL");

*/