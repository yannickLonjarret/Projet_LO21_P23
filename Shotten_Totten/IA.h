#pragma once
#ifndef IA_H
#define IA_H
#include "Joueur.h"
#include <cstdlib>

/// <summary>
/// IA represents the IA.
/// </summary>



class IA : public Joueur
{
private:

public:
	IA() : Joueur("Bob") {}

	int choix_ia(int min, int max) override;

	bool estIA() const override
	{
		return true;
	}

	~IA() = default;
};



/// <summary>
/// Print ooperator overload to display the IA and it's caracteristics
/// </summary>
/// <param name="os"> the output stream</param>
/// <param name="j"> the player to display</param>
/// <returns> the output stream with the card's information</returns>
/*std::ostream& operator<<(std::ostream& os, const IA& j)
{
	os << "Joueur : \n\t Name : " << j.getNom() << "\n\t "
	   << "Nombre cartes : " << j.getNbCartes() << "\n\t "
	   << "Score : " << j.getScore() << "\n\t "
	   << "Main : " << j.getCarteC << j.getCarteT() << "\n\t "
	   << std::endl;
	return os;
}
*/
#endif // !IA_H
