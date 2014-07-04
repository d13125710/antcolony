#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <random>


#include <array> //for std::array
#include "Coords.h"
#include "Tokenizer.h"
#include "TokenFinder.h"

#include "AntWalkedWay.h"
#include "Record.h"


using namespace std;


typedef vector<Coords> Coords_vector;
typedef Tokenizer<TokenFinder> Tk;

typedef std::vector<std::vector<double> > MatrixArrayType;


class FileReader
{
private: 
	std::ifstream m_inFile; 
	string sInput;
	string m_fileName;
	Coords_vector m_strVector;

	 MatrixArrayType *m_theMatrix;
	 MatrixArrayType *m_invertedMatrix;
	 MatrixArrayType *m_pheromones;


	 std::default_random_engine m_generator;
	



public:
	bool Read();
	void Print();
	FileReader(string &str);
	~FileReader(void);

	int getSize() const
	{
		return m_strVector.size();
	}

	double readPheromone(int x, int y) const
	{
		double p = (*m_pheromones)[x][y];
		return p;
	}

	double ReadinvertedMatrix(int x, int y) const
	{
		return (*m_invertedMatrix)[x][y];
	}

	 double ReadMatrix(int x, int y) const
	 {
		 double d=(*m_theMatrix) [x][y];
		 return  d;
	 }

	 
	 void adjustPheromone(int x, int y, double newPheromone);
  
  double calculatePheromones(double current, double newPheromone) ;
 
  int getGaussianDistributionRowIndex(std::uniform_int_distribution<int> &distribution);
	

private:
	//open
	bool Openfile();
	void Run();
	void matrix_calculate(MatrixArrayType& theMatrix);
	double calculateEuclidianDistance(double x1, double y1,double x2, double y2); 
	void invertMatrix(MatrixArrayType& theMatrix , MatrixArrayType& invertedMatrix);

	void initializePheromones(MatrixArrayType& Pheromones , double value);

	//debug
	void PrintMatrix(MatrixArrayType& theMatrix);	
	

};

