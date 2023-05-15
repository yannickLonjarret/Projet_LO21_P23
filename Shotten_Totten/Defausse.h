#ifndef DEFAUSSE_H
#define DEFAUSSE_H

#include "Carte.h"
#include <vector>
#include <ostream>
using namespace std;

class Defausse {
private:
	static int nb_cartesMax;
	int nb_cartes;
	vector<Carte> cartes;

public:

	explicit Defausse(const vector<Carte>& cartes) : nb_cartes((int)cartes.size()), cartes(cartes) {
		nb_cartesMax = (int)cartes.size();
	}

	//FUNCTIONS
	Carte pop() const {
		return cartes.back();
	}

	void push(const Carte& c) {
		this->cartes.push_back(c);

	}

	vector<Carte*> getXFirstCard(int x) {
		std::vector<Carte*> ret;

		for (int i = 0; i < x; i++) {
			ret.push_back(&this->cartes[i]);
		}
		return std::vector<Carte*>();
	}

	int getSize() const {
		return nb_cartes;
	}

	vector<Carte> getCartes() const {
		return this->cartes;
	}


	~Defausse() = default;




};

std::ostream& operator<<(std::ostream& os, const Defausse& d) {
	os << "[";
	for (int i = 0; i < d.getSize(); i++) {
		os << d.getCartes()[i];
		if (i != d.getSize() - 1)
			os << ", ";
	}
	os << "]\n";
	return os;
}


#endif // !DEFAUSSE_H
