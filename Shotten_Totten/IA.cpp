#include "IA.h"

int IA::choix_ia(int min, int max)
{
	srand(time(NULL));
	return min + rand() % (max - min + 1);
}

