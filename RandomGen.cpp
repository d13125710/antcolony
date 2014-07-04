#include "StdAfx.h"
#include "RandomGen.h"

RandomGen::RandomGen()
{
    RandomGen( time(NULL));
}

RandomGen::RandomGen(unsigned int seed)
{
    srand(seed);
}

int RandomGen::Next(int min, int max)
{
    return rand() % ((max+1) - min) + min;
}

int RandomGen::Next(int max)
{
    return Next(0, max);
}

int RandomGen::Next()
{
    return Next(RAND_MAX);
}

double RandomGen::NextDouble()
{
    return ((double)Next() / (double)RAND_MAX);
}

float RandomGen::NextFloat()
{
    return (float)NextDouble();
} 

RandomGen::~RandomGen()
{
   
}




