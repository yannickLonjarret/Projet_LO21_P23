#include "IA.h"

int IA::choix_ia(int min, int max)
{
	return min + rand() % (max - min + 1);
}

