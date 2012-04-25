//**************************************************************************
// Implementación de una clase que calcula valores aleatorios entre dos
// valores extremos
//
// Domingo Martin Perandres 2004
//
// GPL
//**************************************************************************

#ifndef _RANDOM
#define _RANDOM

#include <time.h>

class _random
{
public:
			_random(float Minimum1,float Maximum1){Minimum=Minimum1;Maximum=Maximum1;Factor=(Maximum-Minimum)/(float) RAND_MAX;};
void	init(float Minimum1,float Maximum1){Minimum=Minimum1;Maximum=Maximum1;Factor=(Maximum-Minimum)/(float) RAND_MAX;};
float	value(){return(Factor*random()+Minimum);};
void	seed(){time_t t1;t1=time((time_t *)NULL);srandom((int) t1);};

private:
float Minimum,Maximum;
float Factor;
};




#endif
