#pragma once
#ifndef CARTES_C_H
#define CARTES_C_H

#include "Carte.h"
#include <ostream>
#include <string>
#include <vector>

using namespace std;

/// <summary>
/// Carte_c represents the classical cards (the ones that are not special in any way).
/// </summary>
class Carte_c : Carte
{
private:
	static int val_max;
	static int val_min;
	static vector<string> couleurs;

	int valeur;
	string couleur;

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
	Carte_c(int val, const string& col) :valeur(val), couleur(col) {
		val_min = 0;
		val_max = 0;
		couleurs.push_back("Bleu");
		couleurs.push_back("Rouge");
		couleurs.push_back("Vert");
		couleurs.push_back("Jaune");
		couleurs.push_back("Noir");
		couleurs.push_back("Gris");

	}

	///FUNCTIONS
	void setValeur(int val);
	void setCouleur(const string& col);
	static int getValMax();
	static int getValMin();
	void setValMax(int vmax) const;
	void setValMin(int vmin) const;
	const string& getCouleur() const;
	int getValeur() const;

	static vector<string> getCouleurs() {
		return couleurs;
	}



	//overriding the print function
	void print(std::ostream& os) const override {
		os << "Carte_c : \n\t Couleur : " << this->getCouleur() << "\n\t "
			<< "Valeur : " << this->getValeur() << std::endl;
	}

	/*
	static vector<string>& getCouleurs() {
		return couleurs;
	}*/

	/// <summary>
	/// Default Destructor 
	/// </summary>
	~Carte_c() = default;

	friend std::ostream& operator<<(std::ostream& os, const Carte_c& cc);
};

/// <summary>
/// Print ooperator overload to display the card and it's caracteristics
/// </summary>
/// <param name="os"> the output stream</param>
/// <param name="cc"> the card to display</param>
/// <returns> the output stream with the card's information</returns>
std::ostream& operator<<(std::ostream& os, const Carte_c& cc) {
	os << "Carte_c : \n\t Couleur : " << cc.getCouleur() << "\n\t "
		<< "Valeur : " << cc.getValeur() << std::endl;
	return os;
}


#endif // !CARTES_C_H


