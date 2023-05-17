#include "Pioche_t.h"

void Pioche_t::push(const Carte_t& c)
{
	this->cartes.push_back(c);
}
Carte_t Pioche_t::pop()
{
	return cartes.back();
}

std::vector<Carte_t*> Pioche_t::getXFirstCard(int x)
{
	std::vector<Carte_t*> ret;

	for (int i = 0; i < x; i++) {
		ret.push_back(&this->cartes[i]);
	}
	return std::vector<Carte_t*>();
}