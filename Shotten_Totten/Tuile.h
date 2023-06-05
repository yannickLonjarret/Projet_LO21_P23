#pragma once

#include "Carte_t.h"
#include "Cote.h"

#include <iostream>
#include <algorithm>
#include <ostream>

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

	vector<nodeHist_c*> hist_c;
	vector<Combinaison*> victoirePossible;

	int claim;

public:

	Tuile(int nb_cartes, vector<Combinaison*> vicPoss, int nbJoueur) {
		nbCarteMax = nb_cartes;

		for (int i = 0; i < vicPoss.size(); i++)
			victoirePossible.push_back(vicPoss[i]);

		for (int i = 0; i < nbJoueur; i++)
			joueurs.push_back(new Cote(i));


		claim = -1;

	};

	void ajout_c(Carte_c* c, int idJoueur);


	//Implémentation pour 2 joueurs uniquement car aucune idées des règles à ajouter en cas d'égalité ou de revendication par preuve
	void claimProof(int joueur, vector<Tuile*> plateau);

	bool proofComputer(vector<Carte_c*> combiIncompl, vector<Carte_c*> cardsToTest, Combinaison* complete, vector<Carte_c*> prevEvaluated); 

	/*
	//To finish and test
	bool computeProofCarteT(TroupeElite* toSet, vector<Carte_c*> combiIncompl, vector<Carte_c*> cardsToTest, Combinaison* complete) {
		int lowB, hiB;

		bool combiGagne = false;

		lowB = toSet->getDebut();
		hiB = toSet->getFin();

		for (int i = lowB; i < hiB; i++) {
			for (int j = 0; j < Carte_c::getCouleurs().size() - 1; j++) {
				//toSet->setCouleur();
				//toSet->setValeur();

				//sort combiIncompl
				combiGagne = proofComputer(combiIncompl, cardsToTest, complete);

				if (combiGagne) return combiGagne;
			}

		}

		return combiGagne;
	}

	*/

	bool computeProofCarteC(vector<Carte_c*> combiIncompl, vector<Carte_c*> cardsToTest, Combinaison* complete, vector<Carte_c*> prevEvaluated);



	void cardSubstractor(vector<Carte_c*>& toSub, vector<Tuile*> plateau);

	bool isCardOnBoard(Carte_c* c, vector<Tuile*> plateau);

	bool isCardOnTuile(Carte_c* c);

	void proofCardGenerator(vector<Carte_c*>& gen); 


	//Implémentation pour 2 joueurs uniquement car aucune idées des règles à ajouter en cas d'égalité ou de revendication par preuve
	void claimTuile(int idJoueur, vector<Tuile*> plateau);
	void claimClassic(int joueur);

	void casEgalite();



	bool canPlayerClaim(int idJoueur) {
		return getCotes()[idJoueur]->getNbCartes() == getNbCartesMax();
	}

	bool isClaimProof() {
		return ((getCotes()[0]->getNbCartes() - getCotes()[1]->getNbCartes()) != 0);
	}

	bool isClaimable();

	void clearVictoires();
	
	void setVictoires(vector<Combinaison*> newVict);

	void setClaim(int winner) {
		claim = winner;
	}

	


	int getClaim() {
		return claim;
	}


	int getNbCartesMax() {
		return nbCarteMax;
	}


	vector<nodeHist_c*>& getHist_c() {
		return hist_c;
	}

	vector<Cote*>& getCotes() {

		return joueurs;
	}

	vector<Combinaison*>& getVictoires() {
		return victoirePossible;
	}


	
};



