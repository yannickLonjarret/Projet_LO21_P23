#include "Tuile.h"

/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <param name="idJoueur"></param>
void Tuile::ajout_carte(Carte* c, int idJoueur) {

	if (typeid(*c) == typeid(TroupeElite)) {
		Carte_t* t = (Carte_t*)c;
		ajout_TroupeElite((TroupeElite*)t, idJoueur);
	}
	else if (typeid(*c) == typeid(Carte_c))
		ajout_c((Carte_c*)c, idJoueur);

	else
		ajout_t((Carte_t*)c, idJoueur);
}

/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <param name="idJoueur"></param>
void Tuile::ajout_c(Carte_c* c, int idJoueur) {

	Cote* coteJoueur = getCotes()[idJoueur];

	if (coteJoueur->getNbCartes() <= getNbCartesMax()) {

		coteJoueur->getCartesC().push_back(c);
		coteJoueur->setNbCartes(coteJoueur->getNbCartes() + 1);
		cout << "## AJOUT_C";

		std::sort(coteJoueur->getCartesC().begin(), coteJoueur->getCartesC().end(), [](Carte_c* c1, Carte_c* c2) {
			return c1->getValeur() < c2->getValeur();
			});

		hist_c.push_back(new nodeHist_c(idJoueur, coteJoueur->getNbCartes()));
	}
	else {
		std::cout << "Tuile pleine pour vous" << std::endl;
	}

}

/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <param name="idJoueur"></param>
void Tuile::ajout_t(Carte_t* c, int idJoueur) {

	Cote* coteJoueur = getCotes()[idJoueur];

	coteJoueur->getCartesT().push_back(c);

}

/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <param name="idJoueur"></param>
void Tuile::ajout_TroupeElite(TroupeElite* c, int idJoueur) {
	int insertCtrl = getCotes()[idJoueur]->getCartesC().size();

	ajout_c((Carte_c*)c, idJoueur);

	if (insertCtrl == getCotes()[idJoueur]->getCartesC().size()) return;

	ajout_t((Carte_t*)c, idJoueur);
}

/// <summary>
/// 
/// </summary>
/// <param name="toSet"></param>
/// <param name="combiIncompl"></param>
/// <param name="cardsToTest"></param>
/// <param name="complete"></param>
/// <param name="prevEvaluated"></param>
/// <returns></returns>
bool Tuile::computeProofCarteT(TroupeElite* toSet, vector<Carte_c*> combiIncompl, vector<Carte_c*> cardsToTest, Combinaison* complete, vector<Carte_c*> prevEvaluated) {
	int lowB, hiB;

	bool combiGagne = false;

	lowB = toSet->getDebut();
	hiB = toSet->getFin();

	for (int i = lowB; i < hiB; i++) {
		for (int j = 0; j < Carte_c::getCouleurs().size() - 1; j++) {
			toSet->setCouleur(Carte_c::getCouleurs()[j]);
			toSet->setValeur(i);

			std::sort(combiIncompl.begin(), combiIncompl.end(), [](Carte_c* c1, Carte_c* c2) {
				return c1->getValeur() < c2->getValeur();
				});

			combiGagne = proofComputer(combiIncompl, cardsToTest, complete, prevEvaluated);

			if (combiGagne) return combiGagne;
		}

	}

	return combiGagne;
}

/// <summary>
/// 
/// </summary>
/// <param name="joueur"></param>
/// <param name="plateau"></param>
void Tuile::claimProof(int joueur, vector<Tuile*> plateau) {
	vector<Carte_c*> allCards;

	if (getCotes()[joueur]->getCartesC()[0]->getValeur() == -1)
		claimTroupeE_CardSetter(getCotes()[joueur]->getCartesC());

	Combinaison* complete = new Combinaison(getCotes()[joueur]->getCartesC(), getNbCartesMax());

	proofCardGenerator(allCards);
	cardSubstractor(allCards, plateau);

	vector<Carte_c*> mem = vector<Carte_c*>();

	if (!proofComputer(getCotes()[(joueur + 1) % 2]->getCartesC(), allCards, complete, mem))
		setClaim(joueur);

	//Remise ŕ défaut de toutes les cartes TroupeElite
	for (int i = 0; i < getCotes().size(); i++) {
		for (int j = 0; j < getCotes()[i]->getCartesC().size(); j++)
			getCotes()[i]->getCartesC()[j]->setDefault();
	}

	std::for_each(allCards.begin(), allCards.end(), [](Carte_c* c) {delete c; });
	delete complete;
	std::for_each(mem.begin(), mem.end(), [](Carte_c* c) {delete c; });
	return;
}

/// <summary>
/// 
/// </summary>
/// <param name="combiIncompl"></param>
/// <param name="cardsToTest"></param>
/// <param name="complete"></param>
/// <param name="prevEvaluated"></param>
/// <returns></returns>
bool Tuile::proofComputer(vector<Carte_c*> combiIncompl, vector<Carte_c*> cardsToTest, Combinaison* complete, vector<Carte_c*> prevEvaluated) {

	if (combiIncompl.size() < complete->getTailleCombi()) {
		if (combiIncompl.size() != 0 && combiIncompl[0]->getValeur() == -1) {
			return computeProofCarteT((TroupeElite*)combiIncompl[0], combiIncompl, cardsToTest, complete, prevEvaluated);
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
		Combinaison* incompl = new Combinaison(combiIncompl, getNbCartesMax());

		if (Combinaison::cmpSup(incompl, complete)) {
			delete incompl;
			return true;
		}
		else {
			return false;
		}
	}


}

/// <summary>
/// 
/// </summary>
/// <param name="combiIncompl"></param>
/// <param name="cardsToTest"></param>
/// <param name="complete"></param>
/// <param name="prevEvaluated"></param>
/// <returns></returns>
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

/// <summary>
/// 
/// </summary>
/// <param name="toSub"></param>
/// <param name="plateau"></param>
void Tuile::cardSubstractor(vector<Carte_c*>& toSub, vector<Tuile*> plateau) {
	int i = 0;

	while (i < toSub.size()) {
		if (isCardOnBoard(toSub[i], plateau))
			toSub.erase(toSub.begin() + i);
		else
			i++;
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <param name="plateau"></param>
/// <returns></returns>
bool Tuile::isCardOnBoard(Carte_c* c, vector<Tuile*> plateau) {

	for (auto i = 0; i < plateau.size(); i++) {
		if (plateau[i]->isCardOnTuile(c)) return true;
	}

	return false;

}

/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
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

/// <summary>
/// 
/// </summary>
/// <param name="gen"></param>
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


/// <summary>
/// Implémentation pour 2 joueurs uniquement car aucune idées des rčgles ŕ ajouter en cas d'égalité ou de revendication par preuve
/// </summary>
/// <param name="idJoueur"></param>
/// <param name="plateau"></param>
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

/// <summary>
/// 
/// </summary>
/// <param name="idJoueur"></param>
/// <returns></returns>
Carte_c* Tuile::defausseSoi(int idJoueur) {
	Carte_c* toDefausse = nullptr;
	char valid;

	cout << "Vous défaussez votre tuile" << endl;

	while (true) {
		for (size_t i = 0; i < getCotes()[idJoueur]->getCartesC().size(); i++) {
			cout << "Voulez vous défaussez cette carte ?" << endl << *getCotes()[idJoueur]->getCartesC()[i];
			cin >> valid;

			if (valid == 'o') {
				toDefausse = getCotes()[idJoueur]->getCartesC()[i];
				int nb_cartes_precedent = getCotes()[idJoueur]->getNbCartes(); 
				getCotes()[idJoueur]->getCartesC().erase(getCotes()[idJoueur]->getCartesC().begin() + i);
				getCotes()[idJoueur]->setNbCartes(nb_cartes_precedent - 1);

				return toDefausse;
			}
		}
	}

}

/// <summary>
/// 
/// </summary>
/// <param name="idJoueur"></param>
/// <returns></returns>
Carte_c* Tuile::defausseAdverse(int idJoueur) {

	Carte_c* toDefausse = nullptr;
	char valid;

	cout << "Vous défaussez la tuile adverse" << endl;

	while (true) {
		for (size_t i = 0; i < getCotes()[(idJoueur + 1) % 2]->getCartesC().size(); i++) {
			cout << "Voulez vous défaussez cette carte ? (o pour oui)" << endl << *getCotes()[(idJoueur + 1) % 2]->getCartesC()[i];
			cin >> valid;

			if (valid == 'o') {
				toDefausse = getCotes()[(idJoueur + 1) % 2]->getCartesC()[i];
				int nb_cartes_precedent = getCotes()[(idJoueur + 1) % 2]->getNbCartes(); 
				getCotes()[(idJoueur + 1) % 2]->getCartesC().erase(getCotes()[(idJoueur + 1) % 2]->getCartesC().begin() + i);
				getCotes()[(idJoueur + 1) % 2]->setNbCartes(nb_cartes_precedent-1);
				return toDefausse;
			}
		}
	}

}

/// <summary>
/// 
/// </summary>
/// <param name="idJoueur"></param>
/// <returns></returns>
Carte_c* Tuile::defausseTout(int idJoueur) {
	vector<Carte_c*> soi = getCotes()[idJoueur]->getCartesC();
	vector<Carte_c*> adv = getCotes()[(idJoueur + 1) % 2]->getCartesC();
	Carte_c* toDefausse = nullptr;
	char valid;


	while (true) {
		cout << "Vous défaussez votre tuile" << endl;
		for (size_t i = 0; i < soi.size(); i++) {
			cout << "Voulez vous défaussez cette carte ?" << endl << *soi[i];
			cin >> valid;

			if (valid == 'o') {
				toDefausse = soi[i];
				soi.erase(soi.begin() + i);

				return toDefausse;
			}
		}

		cout << "Vous défaussez la tuile adverse" << endl;
		for (size_t i = 0; i < adv.size(); i++) {
			cout << "Voulez vous défaussez cette carte ?" << endl << *adv[i];
			cin >> valid;

			if (valid == 'o') {
				toDefausse = adv[i];
				adv.erase(adv.begin() + i);

				return toDefausse;
			}
		}
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="v"></param>
void Tuile::claimTroupeE_CardSetter(vector<Carte_c*> v) {
	int id_col, value;
	TroupeElite* cast;
	cout << "Here are the possible colors: " << endl;
	for (int i = 1; i < Carte_c::getCouleurs().size(); i++)
		cout << " Index " << i << ": " << Carte_c::getCouleurs()[i] << endl;

	while (v[0]->getValeur() == -1) {

		cast = (TroupeElite*)v[0];
		cout << "Please type in the index of the color." << endl;
		cin >> id_col;
		while (id_col < 1 || id_col >= Carte_c::getCouleurs().size()) {
			cout << "Invalid value for the color" << endl;
			cout << "Please type in a value between " << 1 << " and " << Carte_c::getCouleurs().size() - 1 << endl;
			cin >> id_col;

		}

		cout << "Please type in the value of the card." << endl;
		cout << "Here are the range for your card : " << cast->getDebut() << " : " << cast->getFin() << endl;
		cin >> value;

		while (value < cast->getDebut() || value > cast->getFin()) {
			cout << "Invalid value for the card" << endl;
			cout << "Please type in a value between " << cast->getDebut() << " and " << cast->getFin() << endl;
			cin >> value;
		}

		v[0]->setCouleur(Carte_c::getCouleurs()[id_col]);
		v[0]->setValeur(value);

		std::sort(v.begin(), v.end(), [](Carte_c* c1, Carte_c* c2) {
			return c1->getValeur() < c2->getValeur();
			});

	}

}

/// <summary>
/// 
/// </summary>
/// <param name="joueur"></param>
void Tuile::claimClassic(int joueur) {
	vector<Carte_c*> jCourant, jAdv;

	jCourant = getCotes()[joueur]->getCartesC();
	jAdv = getCotes()[(joueur + 1) % 2]->getCartesC();

	if (jCourant[0]->getValeur() == -1) {
		cout << "Please set values and colors for your cards. " << endl;
		claimTroupeE_CardSetter(jCourant);
	}

	if (jAdv[0]->getValeur() == -1) {
		cout << "Please set values and colors for your opponent. (do not cheat plz) " << endl;
		claimTroupeE_CardSetter(jAdv);
	}

	//Implémentation pour 2 joueurs uniquement car aucune idées des rčgles ŕ ajouter en cas d'égalité
	Combinaison combiJ1(getCotes()[0]->getCartesC(), getNbCartesMax()), combiJ2(getCotes()[1]->getCartesC(), getNbCartesMax());
	combiJ1.dropDown(getVictoires());
	combiJ2.dropDown(getVictoires());

	if (combiJ1 > combiJ2)
		setClaim(joueur);

	else if (combiJ2 > combiJ1)
		setClaim((joueur + 1) % 2);
	else
		casEgalite();

}

/// <summary>
/// 
/// </summary>
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

	if (idJoueur == -1) cout << "Problčme cas Egalité" << endl;

	setClaim(idJoueur);

	return;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Tuile::isClaimable() {

	if (getClaim() != -1) {
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

/// <summary>
/// 
/// </summary>
void Tuile::clearVictoires() {
	vector<Combinaison*> toClr = getVictoires();
	Combinaison* tmp;

	while (toClr.size() != 0) {
		tmp = toClr[0];
		toClr.erase(toClr.begin());
		delete tmp;
	}

}

/// <summary>
/// 
/// </summary>
/// <param name="newVict"></param>
void Tuile::setVictoires(vector<Combinaison*> newVict) {
	if (newVict.size() == 0) return;
	
	vector<Combinaison*> toChng = getVictoires();

	clearVictoires();

	for (auto i = 0; i < newVict.size(); i++)
		toChng.push_back(newVict[i]);

}