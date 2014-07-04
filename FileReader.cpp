#include "StdAfx.h"
#include "FileReader.h"
#include "antAgent.h"



 double PHEROMONE_PERSISTENCE = 0.3; // between 0 and 1
 double INITIAL_PHEROMONES = 0.8; // can be anything

/*
The file content looks quite like this:
1 565.0 575.0
2 25.0 185.0
3 345.0 750.0
4 945.0 685.0

On the leftmost side is the ID of the vertex, in the middle is the x-coordinate and on the rightmost side is the y-coordinate in the euclidian plane.
So our first intention is to write a parser for it and safe the whole graph as an 2D array of doubles which represents the distances between the points.
*/


std::string::size_type sz;     // alias of size_t
int NUM_AGENTS = 2048 * 1000;

FileReader::FileReader(string &str)
{
	m_inFile.open(str);

}

bool FileReader::Read()
{
	bool status = true;
	bool ReadAhead = false;

	if(m_inFile.is_open())
	{
		m_inFile.setf(ios::skipws);

		while(!m_inFile.eof() && m_inFile.good())
		{
			//we need to read up to the newline
			getline(m_inFile , sInput , '\n');
						
			if(ReadAhead)
			{
				//split up the input into tokens of whit spaces
				Tk ti(sInput.c_str() , TokenFinder(" ")); // find white spaces
				Coords cd;

				
				while( ti++ != Tk()) // skip the first as format in "place" , distance , distance , dont need the first
				{
					//convert the string to a double
					cd.x = std::stod (*ti,&sz);
					++ti; //get the next token
					cd.y = std::stod (*ti,&sz);
					//add the struct to the vector to to be stored
					m_strVector.push_back(cd);
				
					++ti;
				}


				//m_strVector.push_back(sInput);
			}
			//start of the COORDS in the TSP format , so read the coords from here....
			if(sInput == "NODE_COORD_SECTION")
			{
				ReadAhead = true;
			}
				
		}
		int Vsize = m_strVector.size();

	   	static MatrixArrayType theMatrix(Vsize , Vsize);
	    static MatrixArrayType invertedMatrix(Vsize , Vsize);
	    static MatrixArrayType pheromones(Vsize , Vsize);

	    matrix_calculate(theMatrix);
	    invertMatrix(theMatrix ,invertedMatrix);
		initializePheromones(pheromones , 0.8);

		m_theMatrix = &theMatrix;
		m_invertedMatrix = &invertedMatrix;
		m_pheromones = &pheromones;
		//int waypoints[52];
		std::vector<int> antway_vecctor;

    	//debug
		//PrintMatrix(theMatrix);

		double m_bestDistancetodate=0;
		

		std::uniform_int_distribution<int> distribution(0,Vsize -1);

	     for (int agentNumber = 0; agentNumber < NUM_AGENTS; agentNumber++) 
		 {
			antAgent aAgent(this , getGaussianDistributionRowIndex(distribution));
			AntWalkedWay way =aAgent.Start();

				
			if (m_bestDistancetodate == 0 || (way.getDistance() < m_bestDistancetodate)) 
			{
			  m_bestDistancetodate = way.getDistance();
			  antway_vecctor = way.getWay();
			  cout << "\nAgent returned with new best distance of: "  << m_bestDistancetodate << "\n";

			  for(unsigned int i =0; i< antway_vecctor.size(); i++)
						cout << antway_vecctor[i] << ", ";
			}

		 }

	cout << "\nfound best distance of: "  << m_bestDistancetodate << " Waypoints ";
		for(unsigned int i =0; i< antway_vecctor.size(); i++)
			cout << antway_vecctor[i] << ", ";

	}

	cout << "\n Opt Solution  of: 7544,36. "; 
	return status;

}
int FileReader::getGaussianDistributionRowIndex(std::uniform_int_distribution<int> &distribution)
{
	//std::uniform_int_distribution<int> distribution1(0,51);
	int dist = distribution(m_generator);
    return dist;
}
void FileReader::invertMatrix(MatrixArrayType& theMatrix , MatrixArrayType& invertedMatrix) 
{
 	for(unsigned int i = 0; i < theMatrix.size(); i++)
	{
			 for(unsigned int j = 0; j < theMatrix[i].size(); j++)
			 {	
				 double distance = theMatrix[i][j];

				 if(distance == 0)
					invertedMatrix[i][j] = 0;
				 else
					invertedMatrix[i][j] = 1 / distance ;
			 }
	}
	
  }


///add inital Pheromones
void FileReader::initializePheromones(MatrixArrayType& Pheromones , double value) 
{

	for(unsigned int i = 0; i < Pheromones.size(); i++)
	{
			 for(unsigned int j = 0; j < Pheromones[i].size(); j++)
			 {	
					Pheromones[i][j] = value;
			 }
	}
	
}



double FileReader::calculateEuclidianDistance(double x1, double y1,double x2, double y2) 
{
   double x = x1 - x2;
   double y = y1 - y2;
   double dist=pow(x,2)+pow(y,2);           //calculating distance by euclidean formula
   return  sqrt(dist);    
}

void FileReader::matrix_calculate(MatrixArrayType& theMatrix)
{
	 for(unsigned int i = 0; i < m_strVector.size(); i++)
	 {
        for(unsigned int j = 0; j < m_strVector.size(); j++){
          
		   theMatrix[i][j]=calculateEuclidianDistance(m_strVector[i].x, m_strVector[i].y, m_strVector[j].x, m_strVector[j].y);
          // cout << theMatrix[i][j] << " ";
        }
       // cout << "\n";
    }
}

void FileReader::PrintMatrix(MatrixArrayType& theMatrix)	
{

	for (MatrixArrayType::iterator it = theMatrix.begin(); it != theMatrix.end(); ++it)
	{
			 for(unsigned int j = 0; j < (*it).size(); j++)
			 {	
				std::cout << ' ' << (*it)[j] << ' ' ;

			 }
	}


}

  void FileReader::adjustPheromone(int x, int y, double newPheromone)
  {
      double result = calculatePheromones((*m_pheromones)[x][y], newPheromone);
      if (result >= 0.0)
	  {
        (*m_pheromones)[x][y] = result;
      }
	  else
	  {
        (*m_pheromones)[x][y] = 0;
      }
  }
 

  double FileReader::calculatePheromones(double current, double newPheromone) 
  {
    double result = (1 - PHEROMONE_PERSISTENCE) * current + newPheromone;
    return result;
  }




void FileReader::Print(void)
{
	std::cout << "Print values read"; 
	for (Coords_vector::iterator it = m_strVector.begin(); it != m_strVector.end(); ++it)
				std::cout << ' ' << (*it).x << ' ' << (*it).y << '\n'; ;
	std::cout << '\n';
}
FileReader::~FileReader(void)
{
	m_inFile.close();
}

/*
Initialize the best distance to infinity
Choose a random vertex in the graph where to plant your ant
Let the ant work their best paths using the formulas from above
Let the ant update the pheromones on our graph
If the worker returned with a new best distance update our currently best distance
Start from 2. until we found our best way or we have reached our maximum workers.
Return or output the best distance
/*/


void FileReader::Run()
{
	int test = 1;
	double distance = 0;
//	AntWalkedWay bestDistance(&test, distance);
  
}




