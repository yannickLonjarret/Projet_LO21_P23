#pragma once
#ifndef CARTE_H
#define CARTE_H

#include <ostream>
class Carte
{

protected:

	virtual void print(ostream& where) const;

public:
	friend ostream& operator<< (ostream& out, const Carte& mc) {
		mc.print(out);
		return out;
	}

};

#endif
