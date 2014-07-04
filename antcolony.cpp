// antcolony.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileReader.h"









int _tmain(int argc, _TCHAR* argv[])
{
	string file("berlin52.tsp");
	FileReader fileReader(file);
	fileReader.Read();
	//fileReader.Print();
	return 0;
}

