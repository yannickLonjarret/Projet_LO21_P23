#pragma once

/// <summary>
/// Classe cote permettant de standardiser la gestion des cartes sur une tuile.
/// </summary>
class Cote
{

private:
	/// <summary>
	/// Indice du joueur dans le vecteur de cote dans la classe tuile
	/// </summary>
	int idJoueur;

	/// <summary>
	/// Nombre de cartes classique jouée par le joueur
	/// </summary>
	int nbCartesJoue;

	/// <summary>
	/// Ensemble des cartes classiques présente du côté d'un joueur sur la tuile
	/// </summary>
	vector<Carte_c*> cartesC;

	/// <summary>
	/// Ensemble des cartes classiques présente du côté d'un joueur sur la tuile
	/// </summary>
	vector<Carte_t*> cartesT;

public:
	Cote(int id) : idJoueur(id) {
		nbCartesJoue = 0;
		cartesC = vector<Carte_c*>();
		cartesT = vector<Carte_t*>();
	}



	int getNbCartes() const {
		return nbCartesJoue;
	}

	/// <summary>
	/// Met à jour le nombre de carte classique jouée sur le côté d'un joueur
	/// </summary>
	/// <param name="newVal">Nouveau nombre de carte classique présent sur une tuile</param>
	void setNbCartes(int newVal) {
		nbCartesJoue = newVal;
	}

	/// <summary>
	///
	/// </summary>
	/// <returns></returns>
	int getIdJoueur() const {
		return idJoueur;
	}

	/// <summary>
	/// Retourne l'ensemble des cartes classiques jouée sur le côté d'un joueur
	/// </summary>
	/// <returns>Une référence d'un vecteur pour pouvoir enregistrer les modifications</returns>
	vector<Carte_c*>& getCartesC() {

		return cartesC;
	}

	/// <summary>
	/// Retourne l'ensemble des cartes tactiques jouée sur le côté d'un joueur
	/// </summary>
	/// <returns>Une référence d'un vecteur pour pouvoir enregistrer les modifications</returns>
	vector<Carte_t*>& getCartesT() {

		return cartesT;
	}

	~Cote() {
		for (auto cc : getCartesC())
			delete cc;
		getCartesC().clear();

		for (auto ct : getCartesT())
			delete ct;
		getCartesT().clear();
	}

};



