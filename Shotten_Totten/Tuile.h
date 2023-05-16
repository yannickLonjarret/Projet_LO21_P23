#pragma once
#ifndef TUILE_H
#define TUILE_H
//#include "Carte.h"
#include "Carte_c.h"
#include "Carte_t.h"
#include "Combinaison.h"
#include "Cote.h"

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

	vector<Cote*> joueurs;

	vector<nodeHist_c *> hist_c;
	vector<Combinaison *> victoirePossible;

	int claim;

public:
	Tuile(int nb_cartes, vector<Combinaison *> vicPoss, int nbJoueur) {
		nbCarteMax = nb_cartes;

		for (int i = 0; i < vicPoss.size(); i++)
			victoirePossible.push_back(vicPoss[i]);

		for (int i = 0; i < nbJoueur; i++)
			joueurs.push_back(new Cote(i));
		

		claim = 0;



	};

	void ajout_c(Carte_c* c, int idJoueur){
		
		Cote* coteJoueur = getCotes()[idJoueur];

		if (idJoueur == 1) {
			
			if (coteJoueur->getNbCartes() <= getNbCartesMax()) {
			
				coteJoueur->getCartesC().push_back(c);
				coteJoueur->setNbCartes(coteJoueur->getNbCartes() + 1);
				
				std::sort(coteJoueur->getCartesC().begin(), coteJoueur->getCartesC().end(), [](Carte_c* c1, Carte_c* c2) {
					return c1->getValeur() < c2->getValeur();
					});

				hist_c.push_back(new nodeHist_c(idJoueur, coteJoueur->getNbCartes()));
			}
			else {
				std::cout << "Tuile pleine pour vous" << std::endl;
			}
				
		}
		
		

	}

	void claimProof(int joueur, vector<Tuile*> plateau) {

		vector<Carte_t *> checkTroupeElite;
		vector<Carte_c *> allCards;
		
		checkTroupeElite = getCotes()[joueur]->getCartesT();
		
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

		for (size_t i = 0; i < getCotes().size(); i++) {
			
			vect = getCotes()[i]->getCartesC();

			for (auto j = 0; j < vect.size(); j++) {
				if (vect[j]->getCouleur() == c->getCouleur() && vect[j]->getValeur() == c->getValeur())
					return true;
			}
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


	//Implémentation pour 2 joueurs uniquement car aucune idées des règles à ajouter en cas d'égalité ou de revendication par preuve
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

		checkTroupeElite = getCotes()[joueur]->getCartesT();
		//TODO
		//Parcourir vector et set valeurs cartes Troupe d'elite

		//Implémentation pour 2 joueurs uniquement car aucune idées des règles à ajouter en cas d'égalité
		Combinaison combiJ1(getCotes()[0]->getCartesC()), combiJ2(getCotes()[1]->getCartesC());

		
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

		if (idJoueur == 0) cout << "Problème cas Egalité" << endl;

		setClaim(idJoueur);
		
		return;
	}



	bool canPlayerClaim(int idJoueur) {
			return getCotes()[idJoueur]->getNbCartes() == getNbCartesMax();
	}

	bool isClaimProof() {
		return ((getCotes()[0]->getNbCartes() - getCotes()[1]->getNbCartes()) != 0);
	}

	bool isClaimable(){

		if (getClaim() != 0) {
			cout << "Deja revencdique" << endl;
			return false;
		}
		else {

			int nb_c1, nb_c2, nb_cMax;

			nb_c1 = getCotes()[0]->getNbCartes();
			nb_c2 = getCotes()[1]->getNbCartes();
			nb_cMax = getNbCartesMax();

			return (nb_c1 == nb_cMax) || (nb_c2 == nb_cMax);
		}
	}


	void clearVictoires() {
		vector<Combinaison*> toClr = getVictoires();
		Combinaison* tmp;

		while (toClr.size() != 0) {
			tmp = toClr[0];
			toClr.erase(toClr.begin());
			delete tmp;
		}

	}


	void setClaim(int winner) {
		claim = winner;
	}

	void setVictoires(vector<Combinaison*> newVict) {
		vector<Combinaison*> toChng = getVictoires();
		
		clearVictoires();

		for (auto i = 0; i < newVict.size(); i++)
			toChng.push_back(newVict[i]);

	}


	int getClaim() {
		return claim;
	}



	int getNbCartesMax() {
		return nbCarteMax;
	}


	vector<nodeHist_c *>& getHist_c() {
		return hist_c;
	}

	vector<Cote *>& getCotes() {

		return joueurs;
	}

	vector<Combinaison*>& getVictoires() {
		return victoirePossible;
	}


};

#endif // !TUILE_H



