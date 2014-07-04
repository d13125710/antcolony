#pragma once

#include <ctime>
#include <cstdlib>

class RandomGen
{
	public:
        RandomGen(unsigned int seed);
        RandomGen();
        int Next(int min, int max);
        int Next(int max);
        int Next();
        double NextDouble();
        float NextFloat();

	~RandomGen(void);
};

