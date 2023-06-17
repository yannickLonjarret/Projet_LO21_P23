#include "Tuile.h"

/// <summary>
/// Identifie le type d'une carte et l'ajoute sur la tuile 
/// dans le vector correspondant
/// </summary>
/// <param name="c">Carte à poser</param>
/// <param name="idJoueur">Joueur souhaitant poser une caret</param>
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
/// Ajoute une carte classique du côté du joueur sur une tuile
/// </summary>
/// <param name="c">Pointeur de la carte à poser</param>
/// <param name="idJoueur">Id du joueur souhaitant poser une carte</param>
void Tuile::ajout_c(Carte_c* c, int idJoueur) {

	Cote* coteJoueur = getCotes()[idJoueur];

	if (coteJoueur->getNbCartes() < getNbCartesMax()) {

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

/// <summary>
/// Ajoute une carte tactique du côté du joueur sur une tuile
/// </summary>
/// <param name="c">Pointeur de la carte à poser</param>
/// <param name="idJoueur">Id du joueur souhaitant poser une carte</param>
void Tuile::ajout_t(Carte_t* c, int idJoueur) {

	Cote* coteJoueur = getCotes()[idJoueur];

	coteJoueur->getCartesT().push_back(c);

}

/// <summary>
/// Ajoute une carte TroupeElite sur une tuile
/// </summary>
/// <param name="c">Pointeur de la carte à poser</param>
/// <param name="idJoueur">Id du joueur souhaitant poser une carte</param>
void Tuile::ajout_TroupeElite(TroupeElite* c, int idJoueur) {
	int insertCtrl = getCotes()[idJoueur]->getCartesC().size();

	ajout_c((Carte_c*)c, idJoueur);

	if (insertCtrl == getCotes()[idJoueur]->getCartesC().size()) return;

	ajout_t((Carte_t*)c, idJoueur);
}

/// <summary>
/// Méthode composante du calcul de preuve
/// Partie Tactique:
/// Itère sur toutes les valeurs et toutes les couleurs d'une carte TroupeElite.
/// A chaque itération, appelle la porte de contrôle
/// </summary>
/// <param name="toSet">Carte sur laquelle on va itérer</param>
/// <param name="combiIncompl">Combinaison incomplète de l'adversaire</param>
/// <param name="cardsToTest">Ensemble de cartes classique non posées à tester</param>
/// <param name="complete">Pointeur de la combinaison déjà complète</param>
/// <param name="prevEvaluated">Ensemble des cartes classiques déjà testé</param>
/// <returns>Vrai si une meilleur combinaison a été trouvée, faux sinon</returns>
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
/// Méthode d'entrée du calcul de preuve
/// Accorde la tuile au joueur uniquement si aucune combinaison strictement supérieur n'a été trouvée
/// </summary>
/// <param name="joueur">Id du joueur voulant revendiquer</param>
/// <param name="plateau">Plateau de jeu, détermine les cartes déjà posées</param>
void Tuile::claimProof(int joueur, vector<Tuile*> plateau) {
	vector<Carte_c*> allCards;

	//Determine les valeurs des TroupeElite au joueur
	if (getCotes()[joueur]->getCartesC()[0]->getValeur() == -1)
		claimTroupeE_CardSetter(getCotes()[joueur]->getCartesC());

	Combinaison* complete = new Combinaison(getCotes()[joueur]->getCartesC(), getNbCartesMax());

	proofCardGenerator(allCards);
	cardSubstractor(allCards, plateau);

	vector<Carte_c*> mem = vector<Carte_c*>();

	if (!proofComputer(getCotes()[(joueur + 1) % 2]->getCartesC(), allCards, complete, mem))
		setClaim(joueur);

	//Remise à défaut de toutes les cartes TroupeElite
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
/// Méthode de calcul de la preuve
/// Cherche une combinaison strictement supérieur à celle existante parmi toutes les cartes
/// classiques non posées
/// </summary>
/// <param name="combiIncompl">Combinaison de cartes à compléter</param>
/// <param name="cardsToTest">Cartes non posées non testées</param>
/// <param name="complete">Combinaison complète</param>
/// <param name="prevEvaluated">Carte non posées testées</param>
/// <returns>Vrai si une meilleur combinaison a été trouvée, faux sinon</returns>
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
/// Méthode composante du calcul de preuve
/// Partie Classique:
/// Test toute les cartes non posées en les ajoutant à la combinaison incomplète
/// </summary>
/// <param name="combiIncompl">Combinaison de cartes à compléter</param>
/// <param name="cardsToTest">Cartes non posées non testées</param>
/// <param name="complete">Combinaison complète</param>
/// <param name="prevEvaluated">Carte non posées testées</param>
/// <returns>Vrai si une meilleur combinaison a été trouvée, faux sinon</returns>
bool Tuile::computeProofCarteC(vector<Carte_c*> combiIncompl, vector<Carte_c*> cardsToTest, Combinaison* complete, vector<Carte_c*> prevEvaluated) {

	bool combiGagne = false;

	for (int i = 0; i < cardsToTest.size(); i++) {

		//Evaluation sans répétition des cartes par consultation d'un historique
		for (int j = 0; j < prevEvaluated.size(); j++) {
			if (cardsToTest[i] == prevEvaluated[j])
				i++;

		}

		if (i < cardsToTest.size()) {

			combiIncompl.push_back(cardsToTest[i]);

			//Maj de l'historique
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
/// Retire toutes les cartes déjà posée sur le plateau d'un vecteur contenant toute les cartes classique du jeu
/// </summary>
/// <param name="toSub">Vecteur de carte à modifier</param>
/// <param name="plateau">Plateau sur lequel on doit chercher l'existence de la carte</param>
void Tuile::cardSubstractor(vector<Carte_c*>& toSub, vector<Tuile*> plateau) {
	int i = 0;
	Carte_c* c;
	while (i < toSub.size()) {
		if (isCardOnBoard(toSub[i], plateau)) {
			c = toSub[i];
			toSub.erase(toSub.begin() + i);
			delete c;
		}
		else
			i++;
	}
}

/// <summary>
/// Cherche si une carte est sur le plateau
/// </summary>
/// <param name="c">Carte que l'on cherche</param>
/// <param name="plateau">Plateau sur lequel on cherche la carte</param>
/// <returns>Vrai si trouvé, faux sinon</returns>
bool Tuile::isCardOnBoard(Carte_c* c, vector<Tuile*> plateau) {

	for (auto i = 0; i < plateau.size(); i++) {
		if (plateau[i]->isCardOnTuile(c)) return true;
	}

	return false;

}

/// <summary>
/// Recherche si une carte est présente sur une tuile
/// </summary>
/// <param name="c">Carte à chercher</param>
/// <returns>Vrai si la carte est présente, faux sinon</returns>
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
/// Génère toutes les cartes du jeu pour le calcul de preuve
/// Doit être utilisé avec le cardSubtractor
/// </summary>
/// <param name="gen">Vecteur de carte dans lequel ajouter les cartes</param>
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
/// Permet à un joueur de revendiquer une tuile spécifique
/// Implémentation pour 2 joueurs uniquement car aucune idées des rčgles ŕ ajouter en cas d'égalité ou de revendication par preuve
/// </summary>
/// <param name="idJoueur">Id du joueur voulant revendiquer</param>
/// <param name="plateau">Ensemble des tuiles du jeu, nécessaire pour calcul de la preuve</param>
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
		
		claimProof(idJoueur, plateau);
		
	}
	else {
		claimClassic(idJoueur);
	}

	return;

}

/// <summary>
/// Defausse une carte du côté du joueur sur une tuile
/// </summary>
/// <param name="idJoueur">Id du joueur souhaitant défausser une carte</param>
/// <returns>Pointeur sur la carte à défausser</returns>
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
/// Permet à une IA de défausser une carte de son côté
/// </summary>
/// <param name="idJoueur">Id de l'IA</param>
/// <returns>Pointeur sur la carte défaussée</returns>
Carte_c* Tuile::defausseSoiIA(int idJoueur) {
	int i = rand() % (getCotes()[idJoueur]->getCartesC().size());
	Carte_c* toDefausse = getCotes()[idJoueur]->getCartesC()[i];
	int nb_cartes_precedent = getCotes()[idJoueur]->getNbCartes();
	getCotes()[idJoueur]->getCartesC().erase(getCotes()[idJoueur]->getCartesC().begin() + i);
	getCotes()[idJoueur]->setNbCartes(nb_cartes_precedent - 1);
	return toDefausse; 
}

/// <summary>
/// Permet à un joueur de défausser une carte du côté adverse sur une tuile
/// </summary>
/// <param name="idJoueur">Id du joueur faisant le choix de défausse</param>
/// <returns>Pointeur sur la carte défaussée</returns>
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
/// Permet à une IA de défausser une carte de l'adversaire 
/// </summary>
/// <param name="idJoueur">Id de l'IA</param>
/// <returns>Pointeur sur la carte défaussée</returns>
Carte_c* Tuile::defausseAdverseIA(int idJoueur) {

	int i = rand() % (getCotes()[(idJoueur + 1) % 2]->getCartesC().size());

	Carte_c* toDefausse = getCotes()[(idJoueur + 1) % 2]->getCartesC()[i];     
	int nb_cartes_precedent = getCotes()[(idJoueur + 1) % 2]->getNbCartes();
	getCotes()[(idJoueur + 1) % 2]->getCartesC().erase(getCotes()[(idJoueur + 1) % 2]->getCartesC().begin() + i);
	getCotes()[(idJoueur + 1) % 2]->setNbCartes(nb_cartes_precedent - 1);
	return toDefausse;
}

/// <summary>
/// Permet de défausser une carte classique d'une tuile
/// Le choix est fait par le joueur dont l'id est idJoueur
/// </summary>
/// <param name="idJoueur">Id du joueur faisant le choix de défausse</param>
/// <returns>Pointeur sur la carte défaussée</returns>
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
/// Demande les valeurs et les couleurs que devront prendre les cartes TroupeElite
/// </summary>
/// <param name="v">Vector de carte dans lequel se trouve les cartes</param>
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
/// Determine le vainqueur d'une tuile lorsque les deux joueurs ont posés toutes les cartes
/// </summary>
/// <param name="joueur">Id du joueur souhaitant revendiquer</param>
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
	Combinaison combiJCourant(jCourant, getNbCartesMax()), combiJAdv(jAdv, getNbCartesMax());
	
	combiJCourant.dropDown(getVictoires());
	combiJAdv.dropDown(getVictoires());
	
	if (combiJCourant > combiJAdv)
		setClaim(joueur);
	else if (combiJAdv > combiJCourant)
		setClaim((joueur + 1) % 2);
	else
		casEgalite();

}

/// <summary>
/// Permet de déterminer le vainqueur d'une tuile
/// lorsque les deux combinaisons sont de même valeur et de même score
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

	if (idJoueur == -1) cout << "Probleme cas Egalite" << endl;

	setClaim(idJoueur);

	return;
}

/// <summary>
/// Determine si une tuile peut être revendiquée
/// </summary>
/// <returns>Vrai si la tuile est revendiquable, faux sinon</returns>
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
/// Met à jour les combinaisons possibles de victoire
/// </summary>
/// <param name="newVict">Nouvelles combinaisons de victoires</param>
void Tuile::setVictoires(vector<Combinaison*> newVict) {
	if (newVict.size() == 0) return;
	
	vector<Combinaison*> toChng = getVictoires();


	for (auto i = 0; i < newVict.size(); i++)
		toChng.push_back(newVict[i]);

}