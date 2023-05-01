#pragma once
#ifndef CARTES_C_H
#define CARTES_C_H

#include "Carte.h"

enum Couleur {
	R, G, B, Y, D
};


class Carte_c : Carte
{
private:
	static int val_max;
	static int val_min;

	Couleur col;
	int valeur;
	
public:
	Carte_c();
};


#endif // !CARTES_C_H


