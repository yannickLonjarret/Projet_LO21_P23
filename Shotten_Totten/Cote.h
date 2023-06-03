#pragma once
class Cote
{

private:
	int idJoueur; //indice du vecteur du joueur
	int nbCartesJoue;

	vector<Carte_c*> cartesC;
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

	void setNbCartes(int newVal) {
		nbCartesJoue = newVal;
	}

	int getIdJoueur() const {
		return idJoueur;
	}

	vector<Carte_c*>& getCartesC() {

		return cartesC;
	}

	vector<Carte_t*>& getCartesT() {

		return cartesT;
	}

};



