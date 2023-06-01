#pragma once
#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include <ostream>
#include "Carte_c.h"
#include "Carte_t.h"

class Jeu;

/// <summary>
/// Joueur represents the players.
/// </summary>

class Joueur
{
protected:

	std::string nom;
	//test pour donner un identifiant unique
	static int prochain_id;
	int id_joueur;
	int nb_cartes;
	int score;
	std::vector<Carte_c> cartes_c;
	std::vector<Carte_t> cartes_t;

public:
	/// <summary>
	/// Constructor for the Joueur class.
	/// Initializes the attributes.
	/// </summary>
	/// <param name="nom"> name of the player : string </param>
	/// <param name="nb_cartes"> optional, player card number : int </param>
	/// <param name="score"> optional, player score : int </param>
	/// <param name="cartes_c"> optionnal, player classic card vector : vector<cartes_c> </param>
	/// <param name="cartes_t"> optionnal, player tactic card vector : vector<cartes_t> </param>

	Joueur(std::string const& n) : nom(n)
	{
		id_joueur = prochain_id; //Attribuer l'id unique a l'instance actuelle
		prochain_id++;//Incrémenter l'id unique pour la prochaine instance
		nb_cartes = 0;
		score = 0;
	}

	//FUNCTIONS

	/// <summary>
	/// Set the value of nb_cartes
	/// </summary>


	void setNb_cartes() {
		nb_cartes = cartes_c.size() + cartes_t.size();
	}

	/// <summary>
	/// Set the value of score
	/// </summary>

	void setScore(int s) {
		score += s;
	}

	/// <summary>
	/// Default Destructor
	/// </summary>

	~Joueur() = default;

	friend std::ostream& operator<<(std::ostream& os, const Joueur& j);

	/// <summary>
	/// Return player's name
	/// </summary>

	std::string getNom() const
	{
		return this->nom;
	}

	/// <summary>
	/// Return player's nb_cartes
	/// </summary>

	int getNbCartes() const
	{
		return this->nb_cartes;
	}

	/// <summary>
	/// Return player's score
	/// </summary>

	int getScore() const
	{
		return this->score;
	}

	/// <summary>
	/// Return player's classic card
	/// </summary>

	std::vector<Carte_c> getCarteC() const
	{
		return this->cartes_c;
	}

	/// <summary>
	/// Return player's tactic card
	/// </summary>

	std::vector<Carte_t> getCarteT() const
	{
		return this->cartes_t;
	}

	/// <summary>
	/// Allows the player to draw a classic card
	/// </summary>
	///<param name="jeu"> enables interaction and communication between "Joueur" and game functionality : Jeu& </param>

	Carte_c* Pioche_c(Jeu& jeu);

	/// <summary>
	/// Allows the player to draw a tactic card
	/// </summary>
	///<param name="jeu"> enables interaction and communication between "Joueur" and game functionality : Jeu& </param>

	Carte_t* Pioche_t(Jeu& jeu);

	/// <summary>
	/// Allowss the player to place a classic card
	/// </summary>
	/// <param name="c"> classic card to place : Carte_c </param>
	///<param name="id"> Player's id : int </param>
	///<param name="jeu"> enables interaction and communication between "Joueur" and game functionality : Jeu& </param>

	void Poser_carte_c(Carte_c& c, int id, Jeu& jeu);

	/// <summary>
	/// Allowss the player to place a tactic card
	/// </summary>
	/// <param name="c"> tactic card to place : Carte_t </param>
	/// <param name="id"> Player's id : int </param>
	///<param name="jeu"> enables interaction and communication between "Joueur" and game functionality : Jeu& </param>

	void Poser_carte_t(Carte_t& c, int id, Jeu& jeu);


	void surrender();
	void to_claim();
	void look_graveyard();
};

/// <summary>
/// Print ooperator overload to display the player and it's caracteristics
/// </summary>
/// <param name="os"> the output stream</param>
/// <param name="j"> the player to display</param>
/// <returns> the output stream with the players's information</returns>
inline std::ostream& operator<<(std::ostream& os, const Joueur& j)
{
	os << "Joueur : \n\t Name : " << j.getNom() << "\n\t "
		<< "Nombre cartes : " << j.getNbCartes() << "\n\t "
		<< "Score : " << j.getScore() << "\n\t "
		<< "Main (Cartes_c) : ";

	for (const auto& carteC : j.getCarteC()) {
		os << carteC << " ";
	}

	os << "\n\t Main (Cartes T) :";

	for (const auto& carteT : j.getCarteT()) {
		os << carteT << " ";
	}

	os << "\n";
	return os;
}

#endif // !JOUEUR_H
