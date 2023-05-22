#pragma once
#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include <ostream>
#include "Jeu.h"
#include "Carte_c.h"
#include "Carte_t.h"

/// <summary>
/// Joueur represents the players.
/// </summary>

class Joueur
{
private:

	string nom;
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

	Joueur(string const& n) : nom(n)
	{
		id_joueur = prochain_id; //Attribuer l'id unique a l'instance actuelle
		prochain_id++;//Incrémenter l'id unique pour la prochaine instance
		nb_cartes = 0;
		score = 0;
	}

	int setNb_cartes() {
		nb_cartes = cartes_c.size() + cartes_t.size();
	}

	int setScore(int s) {
		score += s;
	}
	/// <summary>
	/// Default Destructor
	/// </summary>

	~Joueur() = default;

	friend std::ostream& operator<<(std::ostream& os, const Joueur& j);

	string getNom() const
	{
		return this->nom;
	}

	int getNbCartes() const
	{
		return this->nb_cartes;
	}

	int getScore() const
	{
		return this->score;
	}

	std::vector<Carte_c> getCarteC() const
	{
		return this->cartes_c;
	}

	std::vector<Carte_t> getCarteT() const
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
		}
	}

	Carte_t Pioche_t()
	{
		if (Pioche_t::getSize() == 0)
		{
		}
		else
		{
		}
	}

	void Poser_carte_c(Carte_c c, int id);
	void Poser_carte_t(Carte_t c, int id);
	void surrender();
	void to_claim();
	void look_graveyard();
};

int Joueur::prochain_id = 0; // Initialisation de la variable statique

/// <summary>
/// Print ooperator overload to display the player and it's caracteristics
/// </summary>
/// <param name="os"> the output stream</param>
/// <param name="j"> the player to display</param>
/// <returns> the output stream with the card's information</returns>
std::ostream& operator<<(std::ostream& os, const Joueur& j)
{
	os << "Joueur : \n\t Name : " << j.getNom() << "\n\t "
		<< "Nombre cartes : " << j.getNbCartes() << "\n\t "
		<< "Score : " << j.getScore() << "\n\t ";
	os << "Main : Carte_c[";
	for (int i = 0; i < j.getCarteC().size(); i++) {
		os << j.getCarteC()[i];
		if (i != j.getCarteC().size() - 1)
			os << ", ";
	}
	os << "]\n";
	os << "Main : Carte_t[";
	for (int i = 0; i < j.getCarteT().size(); i++) {
		os << j.getCarteT()[i];
		if (i != j.getCarteT().size() - 1)
			os << ", ";
	}
	os << "]\n" << std::endl;
	return os;
}

#endif // !JOUEUR_H
