#pragma once
#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include <ostream>
#include "Jeu.h"

/// <summary>
/// Joueur represents the players.
/// </summary>

class Joueur
{
private:
	string nom;
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

	Joueur(string const &n) : nom(n)
	{
		nb_cartes = 0;
		score = 0;
	}

	/// <summary>
	/// Default Destructor
	/// </summary>

	~Joueur() = default;

	friend std::ostream &operator<<(std::ostream &os, const Joueur &j);

	string getNom()
	{
		return this->nom;
	}

	int getNbCartes()
	{
		return this->nb_cartes;
	}

	int getScore()
	{
		return this->score;
	}

	std::vector<Carte_c> getCarteC()
	{
		return this->cartes_c;
	}

	std::vector<Carte_t> getCarteT()
	{
		return this->cartes_t;
	}

	Carte_c Pioche_c()
	{
		if (Pioche_c::getSize() == 0)
		{
		}
		else
		{
			main.Pioche_c::pop();
		}
	}

	Carte_t Pioche_t()
	{
		if (Pioche_t::getSize() == 0)
		{
		}
		else
		{
			main.Pioche_t::pop();
		}
	}

	void Poser_carte_c(Carte_c c);
	void Poser_carte_t(Carte_t c);
	void surrender();
	void to_claim();
	void look_graveyard();
};

/// <summary>
/// Print ooperator overload to display the player and it's caracteristics
/// </summary>
/// <param name="os"> the output stream</param>
/// <param name="j"> the player to display</param>
/// <returns> the output stream with the card's information</returns>
std::ostream &operator<<(std::ostream &os, const Joueur &j)
{
	os << "Joueur : \n\t Name : " << j.getNom() << "\n\t "
	   << "Nombre cartes : " << j.getNbCartes() << "\n\t "
	   << "Score : " << j.getScore() << "\n\t "
	   << "Main : " << j.getCarteC << j.getCarteT() << "\n\t "
	   << std::endl;
	return os;
}

#endif // !JOUEUR_H
