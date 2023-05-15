#pragma once
#ifndef TUILE_H
#define TUILE_H
//#include "Carte.h"
#include "Carte_c.h"
#include "Carte_t.h"
#include "Combinaison.h"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


class nodeHist_c {
private:
	int idJoueur;
	int positionCarte;
public:
	nodeHist_c(int id, int pos) : idJoueur(id), positionCarte(pos) {};

	int getJoueur() {
		return idJoueur;
	}

	int getPositionCarte() {
		return positionCarte;
	}
};

class Tuile
{
private:
	int nbCarteMax;

	vector<Carte_c *> cartesC_j1;
	vector<Carte_t *> cartesT_j1;
	int nbCartes_J1;

	vector<Carte_c *> cartesC_j2;
	vector<Carte_t *> cartesT_j2;
	int nbCartes_J2;

	vector<nodeHist_c *> hist_c;

	vector<Combinaison *> victoirePossible;

	int claim;

public:
	Tuile(int nb_cartes, vector<Combinaison *> vicPoss) {
		nbCarteMax = nb_cartes;

		for (size_t i = 0; i < vicPoss.size(); i++)
			victoirePossible.push_back(vicPoss[i]);

		nbCartes_J2 = 0;
		nbCartes_J1 = 0;
		
		claim = 0;

		cartesC_j1 = vector<Carte_c *>();
		cartesC_j2 = vector<Carte_c *>();

		cartesT_j1 = vector<Carte_t *>();
		cartesT_j2 = vector<Carte_t *>();

	};

	void ajout_c(Carte_c* c, int idJoueur){
		
		if (idJoueur == 1) {
			
			if (getNbCartes_J1() <= getNbCartesMax()) {
			
				getCartesJ1().push_back(c);
				setNbCartes_J1(getNbCartes_J1() + 1);
				
				std::sort(getCartesJ1().begin(), getCartesJ1().end(), [](Carte_c* c1, Carte_c* c2) {
					return c1->getValeur() < c2->getValeur();
					});

				hist_c.push_back(new nodeHist_c(idJoueur, getNbCartes_J1()));
			}
			else {
				std::cout << "Tuile pleine pour vous" << std::endl;
			}
				
		}
		
		if (idJoueur == 2) {
			if (getNbCartes_J2() <= getNbCartesMax()) {
				getCartesJ2().push_back(c);
				setNbCartes_J2(getNbCartes_J2() + 1);

				
				std::sort(getCartesJ2().begin(), getCartesJ2().end(), [](Carte_c* c1, Carte_c* c2) {
					return c1->getValeur() < c2->getValeur();
					});

				hist_c.push_back(new nodeHist_c(idJoueur, getNbCartes_J2()));
			}
			else {
				std::cout << "Tuile pleine pour vous" << std::endl;
			}
		}

	}

	void claimProof(int joueur, vector<Tuile*> plateau) {

		vector<Carte_t *> checkTroupeElite;
		vector<Carte_c *> allCards;
		if (joueur == 1) {
			checkTroupeElite = getCartesT_J1();
		}
		else {
			checkTroupeElite = getCartesT_J2();
		}
		//TODO
		//Parcourir vector et set valeurs cartes Troupe d'elite

		proofCardGenerator(allCards);

	
		cardSubstractor(allCards, plateau);

		for (auto i = 0; i < allCards.size(); i++) {
			cout << "Valeur: " << allCards[i]->getValeur() << " Couleur: " << allCards[i]->getCouleur() << endl;
		}

		
		return;
	}


	void cardSubstractor(vector<Carte_c*>& toSub, vector<Tuile*> plateau) {
		int i = 0;

		while (i < toSub.size()) {
			if (isCardOnBoard(toSub[i], plateau))
				toSub.erase(toSub.begin() + i);
			else
				i++;
		}
	}

	bool isCardOnBoard(Carte_c* c, vector<Tuile*> plateau) {

		for (auto i = 0; i < plateau.size(); i++) {
			if (plateau[i]->isCardOnTuile(c)) return true;
		}

		return false;

	}

	bool isCardOnTuile(Carte_c* c) {
		vector<Carte_c*> vect;

		vect = this->getCartesJ1();

		for (auto i = 0; i < vect.size(); i++) {
			if (vect[i]->getCouleur() == c->getCouleur() && vect[i]->getValeur() == c->getValeur())
				return true;
		}

		vect = this->getCartesJ2();

		for (auto i = 0; i < vect.size(); i++) {
			if (vect[i]->getCouleur() == c->getCouleur() && vect[i]->getValeur() == c->getValeur())
				return true;
		}

		return false;

	}

	void proofCardGenerator(vector<Carte_c *> & gen) {

		int min, max;
		min = Carte_c::getValMin();
		max = Carte_c::getValMax();

		for (int color = (int)Couleur::Rouge; color < (int)Couleur::Gris; color++) {
			for (int i = min; i <= max; i++)
				gen.push_back(new Carte_c(i, (Couleur)color));
		}

		return;
	}

	void claimTuile(int idJoueur, vector<Tuile *> plateau){
		if (!isClaimable()) {
			std::cout << "Tuile non revendicable" << std::endl;
			return;
		}
			

		if (!canPlayerClaim(idJoueur)) {
			std::cout << "Tuile non revendicable par vous" << std::endl;
			return;
		}

		if (isClaimProof()) {
			std::cout << "ça marche" << std::endl;
			claimProof(idJoueur, plateau);
			std::cout << "ça marche toujour" << std::endl;
		}
		else {
			claimClassic(idJoueur);
		}

		return;

	}

	void claimClassic(int joueur) {

		vector<Carte_t*> checkTroupeElite;

		if (joueur == 1) {
			checkTroupeElite = getCartesT_J1();
		}
		else {
			checkTroupeElite = getCartesT_J2();
		}
		//TODO
		//Parcourir vector et set valeurs cartes Troupe d'elite


		Combinaison combiJ1(getCartesJ1()), combiJ2(getCartesJ2());

		
		if (combiJ1 > combiJ2)
			setClaim(1);

		else if (combiJ2 > combiJ1)
			setClaim(2);
		else
			casEgalite(getHist_c());
		
	}

	void casEgalite(vector<nodeHist_c *> hist_c) {
		
		int idJoueur = 0;
		size_t i = 0;

		while (idJoueur == 0 && i < hist_c.size()) {

			if (hist_c[i]->getPositionCarte() == getNbCartesMax()) {
				idJoueur = hist_c[i]->getJoueur();
			}
			i++;
		}

		if (idJoueur == 0) cout << "Priblème cas Egalité" << endl;

		setClaim(idJoueur);
		
		return;
	}



	bool canPlayerClaim(int idJoueur) {
		if (idJoueur == 1)
			return getNbCartes_J1() == getNbCartesMax();
		else
			return getNbCartes_J2() == getNbCartesMax();
	}

	bool isClaimProof() {
		return ((getNbCartes_J1() - getNbCartes_J2()) != 0);
	}

	bool isClaimable(){

		if (getClaim() != 0) {
			cout << "Deja revencdique" << endl;
			return false;
		}
		else {

			int nb_c1, nb_c2, nb_cMax;



			nb_c1 = getNbCartes_J1();
			nb_c2 = getNbCartes_J2();
			nb_cMax = getNbCartesMax();

			return (nb_c1 == nb_cMax) || (nb_c2 == nb_cMax);
		}
	}



	void setNbCartes_J1(int newNb){
		nbCartes_J1 = newNb;
	}

	void setNbCartes_J2(int newNb) {
		nbCartes_J2 = newNb;
	}

	void setClaim(int winner) {
		claim = winner;
	}

	int getClaim() {
		return claim;
	}

	int getNbCartes_J1() {
		return nbCartes_J1;
	}

	int getNbCartes_J2() {
		return nbCartes_J2;
	}

	int getNbCartesMax() {
		return nbCarteMax;
	}

	vector<Carte_c*>& getCartesJ1() {
		
		return cartesC_j1;
	}

	vector<Carte_c*>& getCartesJ2() {
		return cartesC_j2;
	}

	vector<Carte_t*>& getCartesT_J1() {

		return cartesT_j1;
	}

	vector<Carte_t*>& getCartesT_J2() {
		return cartesT_j2;
	}

	vector<nodeHist_c *>& getHist_c() {
		return hist_c;
	}


};

#endif // !TUILE_H



