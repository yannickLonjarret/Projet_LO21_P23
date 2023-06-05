#include "Tuile.h"

void Tuile::ajout_c(Carte_c* c, int idJoueur) {

	Cote* coteJoueur = getCotes()[idJoueur];

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

void Tuile::claimProof(int joueur, vector<Tuile*> plateau) {
	//vector<Carte_t*> checkTroupeElite;
	vector<Carte_c*> allCards;

	//checkTroupeElite = getCotes()[joueur]->getCartesT();

	Combinaison* complete = new Combinaison(getCotes()[joueur]->getCartesC());
	//TODO
	//Parcourir vector et set valeurs cartes Troupe d'elite

	proofCardGenerator(allCards);

	cardSubstractor(allCards, plateau);
	vector<Carte_c*> mem = vector<Carte_c*>();
	if (!proofComputer(getCotes()[(joueur + 1) % 2]->getCartesC(), allCards, complete, mem))
		setClaim(joueur);

	std::for_each(allCards.begin(), allCards.end(), [](Carte_c* c) {delete c; });
	delete complete;
	std::for_each(mem.begin(), mem.end(), [](Carte_c* c) {delete c; });
	return;
}

bool Tuile::proofComputer(vector<Carte_c*> combiIncompl, vector<Carte_c*> cardsToTest, Combinaison* complete, vector<Carte_c*> prevEvaluated) {

	if (combiIncompl.size() < complete->getTailleCombi()) {
		if (combiIncompl.size() != 0 && combiIncompl[0]->getValeur() == -1) {
			//return computeProofCarteT((TroupeElite*)combiIncompl[0], combiIncompl, cardsToTest, complete);
		}
		else {
			return computeProofCarteC(combiIncompl, cardsToTest, complete, prevEvaluated);
		}
	}
	else {

		//Trie par valeur croissante pour la combinaison
		std::sort(combiIncompl.begin(), combiIncompl.end(), [](Carte_c* c1, Carte_c* c2) {
			return c1->getValeur() < c2->getValeur();
			});

		//2 pointeurs, pour la comparaison
		//operator> n'apprecie pas un type différent
		Combinaison* incompl = new Combinaison(combiIncompl);

		if (Combinaison::cmpSup(incompl, complete)) {
			delete incompl;
			return true;
		}
		else {
			return false;
		}
	}


}

bool Tuile::computeProofCarteC(vector<Carte_c*> combiIncompl, vector<Carte_c*> cardsToTest, Combinaison* complete, vector<Carte_c*> prevEvaluated) {

	bool combiGagne = false;

	for (int i = 0; i < cardsToTest.size(); i++) {

		//Evaluation sans répétition des cartes par consultation d'un hist
		for (int j = 0; j < prevEvaluated.size(); j++) {
			if (cardsToTest[i] == prevEvaluated[j])
				i++;

		}

		if (i < cardsToTest.size()) {

			combiIncompl.push_back(cardsToTest[i]);

			//Maj de l'hist
			prevEvaluated.push_back(cardsToTest[i]);

			combiGagne = proofComputer(combiIncompl, cardsToTest, complete, prevEvaluated);
			if (combiGagne) return combiGagne;


			for (int del = 0; del < combiIncompl.size(); del++) {

				if (combiIncompl[del] == cardsToTest[i]) {
					combiIncompl.erase(combiIncompl.begin() + del);

				}
			}
		}

	}
	return combiGagne;
}

void Tuile::cardSubstractor(vector<Carte_c*>& toSub, vector<Tuile*> plateau) {
	int i = 0;

	while (i < toSub.size()) {
		if (isCardOnBoard(toSub[i], plateau))
			toSub.erase(toSub.begin() + i);
		else
			i++;
	}
}

bool Tuile::isCardOnBoard(Carte_c* c, vector<Tuile*> plateau) {

	for (auto i = 0; i < plateau.size(); i++) {
		if (plateau[i]->isCardOnTuile(c)) return true;
	}

	return false;

}

bool Tuile::isCardOnTuile(Carte_c* c) {
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

void Tuile::proofCardGenerator(vector<Carte_c*>& gen) {
	int min, max;
	min = Carte_c::getValMin();
	max = Carte_c::getValMax();
	vector<string> couleurs = Carte_c::getCouleurs();
	for (int color = 1; color < couleurs.size(); color++) {
		for (int i = min; i <= max; i++) {
			gen.push_back(new Carte_c(i, couleurs[color]));
		}
	}

	return;
}

//Implémentation pour 2 joueurs uniquement car aucune idées des règles à ajouter en cas d'égalité ou de revendication par preuve
void Tuile::claimTuile(int idJoueur, vector<Tuile*> plateau) {
	if (!isClaimable()) {
		std::cout << "Tuile non revendicable" << std::endl;
		return;
	}


	if (!canPlayerClaim(idJoueur)) {
		std::cout << "Tuile non revendicable par vous" << std::endl;
		return;
	}

	if (isClaimProof()) {
		std::cout << "ca marche" << std::endl;
		claimProof(idJoueur, plateau);
		std::cout << "ca marche toujour" << std::endl;
	}
	else {
		claimClassic(idJoueur);
	}

	return;

}

void Tuile::claimClassic(int joueur) {

	//vector<Carte_t*> checkTroupeElite;

	//checkTroupeElite = getCotes()[joueur]->getCartesT();
	//TODO
	//Parcourir vector et set valeurs cartes Troupe d'elite

	//Implémentation pour 2 joueurs uniquement car aucune idées des règles à ajouter en cas d'égalité
	Combinaison combiJ1(getCotes()[0]->getCartesC()), combiJ2(getCotes()[1]->getCartesC());
	combiJ1.dropDown(getVictoires());
	combiJ2.dropDown(getVictoires());

	if (combiJ1 > combiJ2)
		setClaim(joueur);

	else if (combiJ2 > combiJ1)
		setClaim((joueur + 1) % 2);
	else
		casEgalite();

}

void Tuile::casEgalite() {

	int idJoueur = 0;
	size_t i = 0;
	vector<nodeHist_c*> hist_c = getHist_c();

	while (idJoueur == -1 && i < hist_c.size()) {

		if (hist_c[i]->getPositionCarte() == getNbCartesMax()) {
			idJoueur = hist_c[i]->getJoueur();
		}
		i++;
	}

	if (idJoueur == -1) cout << "Problème cas Egalité" << endl;

	setClaim(idJoueur);

	return;
}


bool Tuile::isClaimable() {

	if (getClaim() != -1) {
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


void Tuile::clearVictoires() {
	vector<Combinaison*> toClr = getVictoires();
	Combinaison* tmp;

	while (toClr.size() != 0) {
		tmp = toClr[0];
		toClr.erase(toClr.begin());
		delete tmp;
	}

}

void Tuile::setVictoires(vector<Combinaison*> newVict) {
	vector<Combinaison*> toChng = getVictoires();

	clearVictoires();

	for (auto i = 0; i < newVict.size(); i++)
		toChng.push_back(newVict[i]);

}