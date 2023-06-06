#include "Pioche_c.h"

void Pioche_c::push(Carte_c* c)
{
	this->cartes.push_back(c);
}

Carte_c* Pioche_c::pop()
{
	return cartes.back();
}

std::vector<Carte_c*> Pioche_c::getXFirstCard(int x)
{
	std::vector<Carte_c*> ret;

	for (int i = 0; i < x; i++) {
		ret.push_back(this->cartes[i]);
	}
	return ret;
}

