#include "Schotten1_tact.h"

Schotten1_tact::Schotten1_tact() {
	defausse = Defausse();
	vector<Carte_t> pioche;
	pioche.push_back(TroupeElite(elite, "Joker", -1, "Non couleur", 1, 9));
	pioche.push_back(TroupeElite(elite, "Joker", -1, "Non couleur", 1, 9));
	pioche.push_back(TroupeElite(elite, "Espion", -1, "Non couleur", 7, 7));
	pioche.push_back(TroupeElite(elite, "Porte-Bouclier", -1, "Non couleur", 1, 3));

	pioche.push_back(ModeCombat(combat, "Colin-Maillard", 3, vector<Combinaison*>));
	vector<Combinaison*> vecteur_combi; // Vecteur de combinaisons incompris, à changer -> Constructeur spéacialement conçu pour nous
	pioche.push_back(ModeCombat(combat, "Combat de Boue", 4, vecteur_combi)); // vecteur vide

	/*
	0 = piocher
	1 = placer carte sous pioche
	2 = choisir carte de notre main
	3 = placer carte sur borne non revendiquée ou defausser
	4 = choisir carte du cote adverse non revendiquée
	5 = défausser
	6 = placer devant une tuile non revendiquée de notre cote
	7 = choisir carte de notre cote
	*/
	vector<int> suite(0, 0, 0, 2, 1, 2, 1);
	pioche.push_back(Ruse(ruse, "Chasseur de Tete", suite));
	suite = (7, 3);
	pioche.push_back(Ruse(ruse, "Stratège", suite));
	suite = (4, 5);
	pioche.push_back(Ruse(ruse, "Banshee", suite));
	suite = (4, 6);
	pioche.push_back(Ruse(ruse, "Traitre", suite));

	pioche_tact = Pioche_t(pioche);
}

void Schotten1_tact::execRuse(Ruse& carte) {
	vector<int> actions = carte.getActions();
	Carte_c& carte_classique = nullptr; 
	Carte_t& carte_tactique = nullptr;
	for (int i = 0; i < actions.size(); i++) {
		switch (actions[i])
		{
		case 0:
			pioche(choixPioche());
			break;

		case 1:
			if (carte_classique != nullptr)
				Pioche_c::push(carte_classique);
			else
				Pioche_t::push(carte_tactique);
			break;

		case 2:
			
		default:
			break;
		}
	}
}

