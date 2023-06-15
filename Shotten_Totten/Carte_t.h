#pragma once
#include "Carte.h"
#ifndef CARTES_T_H
#define CARTES_T_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "Combinaison.h"
#include "Carte_c.h"

/// @brief Enumeration of the different types of tactical cards
enum types { elite, combat, ruse };

/// @brief This class represents errors due to a misuse of a function of Carte_t class
class Carte_tException {
	/// Error raised
	string info;
public:
	/// @brief Contructor initializes the string 'info'
	/// @param str : the message returned for this error
	Carte_tException(const string str) { info = str; }

	/// @brief Allows the user to access the message associated to the error
	/// @return The message associated to the error raised
	const string getInfo() const { return info; }
};

/// @brief Carte_t represents tactical cards
class Carte_t : public Carte
{
protected:
	/// @brief The type of the card
	types type;

	/// @brief The name of the card
	string nom;
public:
	/// @brief Constructor which initializes a Carte_t object
	/// @param t : type of the card
	/// @param n : name of the card
	Carte_t(types t, string n) :type(t), nom(n) {}

	/// @brief Default destructor 
	virtual ~Carte_t() = default; 

	/// @brief Allows the user to get the type of the card
	/// @return the type of the card
	types getType() const { return type; }

	/// @brief Allows the user to get the name of the card
	/// @return the name of the card
	string getNom() const { return nom; }

	/// @brief Allows the user to change the type of the card
	/// @param valeur : the desired type of the card
	void setType(types valeur) { type = valeur; }

	/// @brief Allows the user to change the name of the card
	/// @param name : the desired name of the card
	void setNom(string name) { nom = name; }

	//overriding the print function 
	void print(std::ostream& os) const override {
		os << "[" << this->getNom() << "]";
	}
};

/// <summary>
/// Print ooperator overload to display the card and its caracteristics
/// </summary>
/// <param name="os"> the output stream</param>
/// <param name="ct"> the card to display</param>
/// <returns> the output stream with the card's information</returns>
/// LE INLINE EST SUPER IMPORTANT POUR LA COMPREHENSION DU COMPILATEUR !!!
inline std::ostream& operator<<(std::ostream& os, const Carte_t& ct) {
	os << "[" << ct.getNom() << "]";
	return os;
}

/// Allows the comparison of two tactical cards
/// </summary>
/// <param name="c1">the first card</param>
/// <param name="c2">the second card to be compared to</param>
/// <returns></returns>

inline bool operator==(const Carte_t& c1, const Carte_t& c2) {
	if (c1.getType() == c2.getType() && c1.getNom() == c2.getNom()) {
		return true;
	}
	else {
		return false;
	}
}

#endif // !CARTES_T_H 



