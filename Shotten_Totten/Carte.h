#pragma once
#ifndef CARTE_H
#define CARTE_H

#include <ostream>

class Carte
{
public:
	virtual ~Carte() {}
	virtual void print(std::ostream& os) const = 0;
};



#endif
