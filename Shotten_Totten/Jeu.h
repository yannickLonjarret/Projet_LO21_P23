#pragma once
#ifndef JEU_H
#define JEU_H

#include "Joueur.h"
#include "Pioche_c.h"
#include "Pioche_t.h"
#include "Tuile.h"


class Jeu
{
private:
	Joueur j1;
	Joueur j2;

	Pioche_c pioche_c;
	Pioche_t pioche_t;

	//defausse ? classe à part ?
	Tuile* plateau;

public:
	Jeu();

};



#endif // !JEU_H



