#pragma once
#ifndef TUILE_H
#define TUILE_H
#include "Carte.h"
#include <vector>
#include <list>
#include "Combinaison.h"

using namespace std;

class Tuile
{
private:
	Carte* tab1;
	Carte* tab2;
	vector<int* []> hist; //pas sur pour le tableau de pointeur sur des int pour l'historique mais à changer
	//list<Combinaison> ? ou tableau ?
	//Combinaison* list;

	int claim;

public:
	Tuile();
};

#endif // !TUILE_H



