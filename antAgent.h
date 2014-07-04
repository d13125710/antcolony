#pragma once
#include "FileReader.h"
#include "RandomGen.h"
#include "AntWalkedWay.h"

class antAgent
{
	FileReader *callbackInstance;
	std::vector<bool> boolArrayVisited;
	std::vector<int> antway_vecctor;
	unsigned int toVisit;
	int m_start;
	int m_length;
	double m_distanceWalked;
	RandomGen m_random;

public:

	int getNextProbableNode(int y);
	antAgent(FileReader *callbackInstance , int pos);
	double calculateProbability(int row, int column, double sum);
	~antAgent(void);
	AntWalkedWay Start();


};

