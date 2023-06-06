#ifndef SCHOTTEN1_TACT_H
#define SCHOTTEN1_TACT_H
#include "Jeu.h"
#include "Carte_t.h"
#include "Carte_Ruse.h"
#include "Pioche_t.h"
#include "Troupe_Elite.h"
#include "Mode_Combat.h"
#include "Defausse.h"

/// <summary>
/// Represents the tactical version of the game, with specific conditions and methods
/// </summary>
class Schotten1_tact : public Jeu{
private:
	/// <summary>
	/// pioche_tact represents the tactical pick
	/// </summary>
	Pioche_t pioche_tact;
	/// <summary>
	/// defausse represents the collections of discarded cards (tactical and potentially classical either)
	/// </summary>
	Defausse defausse;
public:
	/// <summary>
	/// Constructor which creates the pick with all the specific tactical cards required, and initializes the discard defausse
	/// </summary>
	Schotten1_tact();

	void execRuse(Ruse& carte);
};

#endif // !SCHOTTEN1_TACT_H