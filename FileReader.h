#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "Coords.h"

using namespace std;


typedef vector<Coords> Coords_vector;

class FileReader
{
private: 
	std::ifstream m_inFile; 
	string sInput;
	string m_fileName;
	Coords_vector m_strVector;

public:
	bool Read();
	void Print();
	FileReader(string &str);
	~FileReader(void);
	

private:
	//open
	bool Openfile();

};

