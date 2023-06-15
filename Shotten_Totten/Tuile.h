#pragma once

#include "Carte_t.h"
#include "Troupe_Elite.h"
#include "Cote.h"

#include <iostream>
#include <algorithm>
#include <ostream>
#include <sstream>

using namespace std;

/// <summary>
/// Classe permettant d'enregistrer l'ordre et la position sur son côté respectif des cartes posées sur une tuile
/// </summary>
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

	~nodeHist_c() = default;
};

/// <summary>
/// Classe modélisant une borne sur un plateau. Cette classe se charge de la gestion de la pose des cartes et de la victoire d'un joueur sur une tuile
/// </summary>
class Tuile
{

private:
	/// <summary>
	/// Nombre maximum de carte posable sur une tuile.
	/// </summary>
	int nbCarteMax;

	/// <summary>
	/// Ensembles des joueurs sur une tuiles. Existe pour standardiser la gestion de pose/défausse des cartes
	/// </summary>
	vector<Cote*> joueurs;

	/// <summary>
	/// Historique de l'ordre des cartes posées. Permet de départager 2 joueurs dans le cas de combinaison égale.
	/// </summary>
	vector<nodeHist_c*> hist_c;

	/// <summary>
	/// Ensemble de combinaison permettant de gagner sur une tuile.
	/// </summary>
	vector<Combinaison*> victoirePossible;

	/// <summary>
	/// Id du joueur ayant remporté la tuile.
	/// </summary>
	int claim;

public:

	/// <summary>
	/// Unique constructeur de la classe
	/// </summary>
	/// <param name="nb_cartes"> Nombre maximum de cartes jouable sur un côté d'une tuile</param>
	/// <param name="vicPoss">Vecteur de combinaison gagnante sur une tuile</param>
	/// <param name="nbJoueur"> Nombre de joueur sur une tuile, donne le nombre de côté</param>
	Tuile(int nb_cartes, vector<Combinaison*> vicPoss, int nbJoueur) {
		nbCarteMax = nb_cartes;

		for (int i = 0; i < vicPoss.size(); i++)
			victoirePossible.push_back(vicPoss[i]);

		for (int i = 0; i < nbJoueur; i++)
			joueurs.push_back(new Cote(i));

		//Absence de victoire, valeur de contrôle
		claim = -1;

	};

	/// <summary>
	/// La méthode identifie le type de la carte et l'ajoute en tant que carte classique, tactique ou les deux
	/// </summary>
	/// <param name="c">Carte à ajouter</param>
	/// <param name="idJoueur">Joueur à qui ajouter la carte, représente son indice dans le vector de côté</param>
	void ajout_carte(Carte* c, int idJoueur);

	/// <summary>
	/// La méthode permet d'ajouter une carte classique à un joueur s'il peut la poser
	/// </summary>
	/// <param name="c">Carte classique à ajouter sur la borne courante</param>
	/// <param name="idJoueur">Joueur à qui ajouter la carte, représente son indice dans le vector de côté</param>
	void ajout_c(Carte_c* c, int idJoueur);

	/// <summary>
	/// La méthode permet d'ajouter une carte tactique à un joueur, l'effet ayant déjà été appliqué
	/// </summary>
	/// <param name="c">Carte tactique à ajouter à un joueur sur la borne courante</param>
	/// <param name="idJoueur">Joueur à qui ajouter la carte, représente son indice dans le vector de côté</param>
	void ajout_t(Carte_t* c, int idJoueur);
	
	/// <summary>
	/// La méthode permet d'ajouter correctement une troupe d'élite dans la tuile. 
	/// </summary>
	/// <param name="c">carte TroupeElite à ajouter sur la tuile</param>
	/// <param name="idJoueur">Joueur à qui ajouter la carte, représente son indice dans le vector de côté</param>
	void ajout_TroupeElite(TroupeElite* c, int idJoueur);

	/// <summary>
	/// Méthode d'entrée dans la revendication, détermine la possibilité et le type de revendication.
	/// </summary>
	/// <param name="idJoueur"> Joueur demandant à revendiquer une tuile, représente son indice dans le vector de côté </param>
	/// <param name="plateau"> Enesemble des tuiles du plateau, permet de calculer toutes las cartes non posées dans le cas de la revendication par preuve>
	void claimTuile(int idJoueur, vector<Tuile*> plateau);
	
	/// <summary>
	/// 
	/// </summary>
	void claimProof(int joueur, vector<Tuile*> plateau);
	
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool proofComputer(vector<Carte_c*> combiIncompl, vector<Carte_c*> cardsToTest, Combinaison* complete, vector<Carte_c*> prevEvaluated);

	bool computeProofCarteT(TroupeElite* toSet, vector<Carte_c*> combiIncompl, vector<Carte_c*> cardsToTest, Combinaison* complete, vector<Carte_c*> prevEvaluated);

	bool computeProofCarteC(vector<Carte_c*> combiIncompl, vector<Carte_c*> cardsToTest, Combinaison* complete, vector<Carte_c*> prevEvaluated);

	void claimTroupeE_CardSetter(vector<Carte_c*> v);

	void cardSubstractor(vector<Carte_c*>& toSub, vector<Tuile*> plateau);

	bool isCardOnBoard(Carte_c* c, vector<Tuile*> plateau);

	bool isCardOnTuile(Carte_c* c);

	void proofCardGenerator(vector<Carte_c*>& gen);

	bool isTuilePleine(int idJoueur) {
		return getCotes()[idJoueur]->getNbCartes() == getNbCartesMax();
	}
	
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

	void setNbCartesMax(int nb) {
		if(nb != -1) nbCarteMax = nb;
	}

	void setClaim(int winner) {
		claim = winner;
	}


	Carte_c* defausseSoi(int idJoueur);

	Carte_c* defausseAdverse(int idJoueur);

	Carte_c* defausseTout(int idJoueur);


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

	inline friend ostream& operator<<(ostream& os, Tuile& t);

	string toString() {
		stringstream ss;
		ss << (*this);
		return ss.str();
	}

	~Tuile() {
		for (auto c : getCotes())
			delete c;
		getCotes().clear();

		for (auto h : getHist_c())
			delete h;
		getHist_c().clear();

	}

};

/// <summary>
/// 
/// </summary>
ostream& operator<<(ostream& os, Tuile& t) {

	for (int i = 0; i < t.getNbCartesMax() -  t.getCotes()[0]->getNbCartes() ; i++)
		os << "         "  ;
	

	for (int i = 0; i < t.getCotes()[0]->getNbCartes(); i++) 
		os << *t.getCotes()[0]->getCartesC()[i];

	if(t.getClaim() == -1)
		os << "\t[][][" << t.getClaim() << "][][]\t";
	else
		os << "\t[][][" << t.getClaim() + 1 << "][][]\t";

	for (int i = 0; i < t.getCotes()[1]->getNbCartes(); i++) 
		os << *t.getCotes()[1]->getCartesC()[i];
	
	for (int i = 0; i < t.getNbCartesMax() - t.getCotes()[0]->getNbCartes(); i++)
		os << "         ";

	os << "\t";

	for (int i = 0; i < t.getCotes()[0]->getCartesT().size(); i++) 
		os << " " << *t.getCotes()[0]->getCartesT()[i];
	

	for (int i = 0; i < t.getCotes()[1]->getCartesT().size(); i++)
		os << " " << *t.getCotes()[1]->getCartesT()[i];
	
	os << endl;


	return os;
}



