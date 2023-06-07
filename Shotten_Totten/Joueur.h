#pragma once
#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include <ostream>
#include "Carte_c.h"
#include "Carte_t.h"
#include "Pioche_c.h"
#include "Pioche_t.h"
#include "Tuile.h"

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
	std::vector<Carte_c*> cartes_c; //main du joueur en bas du plateau.
	std::vector<Carte_t*> cartes_t;

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

	Joueur() = default;

	//FUNCTIONS

	/// <summary>
	/// Set the value of nb_cartes
	/// </summary>


	void setNb_cartes() {
		//vérifier que le nb de cartes est positif (if)
		if (cartes_c.size() + cartes_t.size() >= 0) {
			nb_cartes = cartes_c.size() + cartes_t.size();
		}
		else {
			cout << "Joueur::setNbCartes() -> le nombre de cartes n'est pas >= 0" << endl;
		}
	}


	void ajouter_Carte_c(Carte_c* c) {
		this->cartes_c.push_back(c);
		setNb_cartes();
	}

	void ajouter_Carte_t(Carte_t* c) {
		this->cartes_t.push_back(c);
		setNb_cartes();
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
	friend bool operator==(const Joueur& j1, const Joueur& j2);
	/// <summary>
	/// Return player's name
	/// </summary>

	std::string getNom() const
	{
		return this->nom;
	}

	/// <summary>
	/// return's the players id
	/// </summary>
	/// <returns>id</returns>
	int getJId() const {
		return this->id_joueur;
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
	/// Return player's id
	/// </summary>

	int getId() const
	{
		return this->id_joueur;
	}

	/// <summary>
	/// Return player's classic card
	/// </summary>

	std::vector<Carte_c*> getCarteC() const
	{
		return this->cartes_c;
	}

	/// <summary>
	/// Return player's tactic card
	/// </summary>

	std::vector<Carte_t*> getCarteT() const
	{
		return this->cartes_t;
	}



	/// <summary>
	/// Allows the user to insert a card at the end of the hand
	/// </summary>
	/// <param name="c">the card to insert</param>
	void push(const Carte_c& c);

	//Carte_c* piocher_c(Pioche_c& pc); //mettre pioche_c à la place de jeu et reafctor dans .cpp

	/// <summary>
	/// Allows the user to insert a card at the end of the hand
	/// </summary>
	///<param name="jeu"> enables interaction and communication between "Joueur" and game functionality : Jeu& </param>

	//Carte_t* piocher_t(Pioche_t& pt); //pareil pour pioche_t

	/// <summary>
	/// Allows the user to retrieve a classic card of the hand
	/// </summary>
	/// <param name="c"> classic card to place : Carte_c </param>
	///<param name="id"> Player's id : int </param>
	///<param name="jeu"> enables interaction and communication between "Joueur" and game functionality : Jeu& </param>

	void poser_carte(Carte_c* c, int id, Tuile* t); // ######### juste poser carte Tuile gère cc ou ct

	/// <summary>
	/// Allows the user to retrieve a tactical card of the hand
	/// </summary>
	/// <param name="c">the card to retrieve</param>
	void pop(const Carte_t& c);

	void surrender();
	void to_claim();
	void look_graveyard(); // joueur->defausse->lookXfirstCard()
};

/// <summary>
/// Print ooperator overload to display the player and it's caracteristics
/// </summary>
/// <param name="os"> the output stream</param>
/// <param name="j"> the player to display</param>
/// <returns> the output stream with the players's information</returns>
inline std::ostream& operator<<(std::ostream& os, const Joueur& j) //display à revoir n'afficher que le nom et le nb_carte + la main.
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


inline bool operator==(const Joueur& j1, const Joueur& j2) {
	if (j1.getJId() == j2.getJId() || j1.getNom() == j2.getNom()) {
		return true;
	}
	else {
		return false;
	}
}
#endif // !JOUEUR_H
