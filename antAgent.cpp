#include "StdAfx.h"
#include "antAgent.h"

#include <math.h>       /* pow */


double ALPHA = 1;
// rapid selection
double BETA = 10;
// heuristic parameters
double Q = 0.5; // somewhere between 0 and 1



antAgent::antAgent(FileReader *callbackInstance , int pos)
{
	this->callbackInstance = callbackInstance;
	unsigned int size = this->callbackInstance->getSize();
	m_distanceWalked = 0;

	for(unsigned int i = 0 ; i < size ; i++)
	{
	    boolArrayVisited.push_back(false);
	}

	boolArrayVisited[pos] = true;
	m_length = size;
	toVisit = size - 1;
	m_start = pos;
}

 /*
 * (pheromones ^ ALPHA) * ((1/length) ^ BETA) divided by the sum of all rows.
 */
 double antAgent::calculateProbability(int row, int column, double sum)
 {
    double p = pow(callbackInstance->readPheromone(column, row), ALPHA)* pow(callbackInstance->ReadinvertedMatrix(column, row),BETA);
    return p / sum;
  }

 
int antAgent::getNextProbableNode(int y)
{
	if(toVisit > 0 )
	{
	  int danglingUnvisited = -1;

	  double weights[52];
	  for(int i =0 ;i<52;i++)
		  weights[i] =0;
     
	  double columnSum = 0.0;
      for (int i = 0; i < m_length; i++) 
      {
        columnSum += pow(callbackInstance->readPheromone(y, i), ALPHA ) * pow(callbackInstance->ReadinvertedMatrix(y , i), BETA);
      }

	  
	  double sum = 0.0;
      for (unsigned int x = 0; x < boolArrayVisited.size(); x++)
	  {
        if (!boolArrayVisited[x]) 
		{
          weights[x] = calculateProbability(x, y, columnSum);
          sum += weights[x];
          danglingUnvisited = x;
        }
      }

      if (sum == 0.0)
        return danglingUnvisited;

      // weighted indexing stuff
      double pSum = 0.0;
      for (unsigned int i = 0; i < boolArrayVisited.size(); i++) 
	  {
        pSum += weights[i] / sum;
        weights[i] = pSum;
      }

      double r = m_random.NextDouble();
      for (unsigned int i = 0; i < boolArrayVisited.size(); i++) 
	  {
        if (!boolArrayVisited[i])
		{
          if (r <= weights[i])
		  {
			
            return i;
          }
        }
      }

    }
	
    return -1;
  }



AntWalkedWay antAgent::Start()
{
	int test=0;
	double distance = 0;
	int lastNode = this->m_start;
    int next = this->m_start;
    int i = 0;
    while ((next = getNextProbableNode(lastNode)) != -1) 
	{
	  antway_vecctor.push_back(lastNode);
      m_distanceWalked += this->callbackInstance->ReadMatrix(lastNode , next);
      double phero = (Q / (m_distanceWalked));
      callbackInstance->adjustPheromone(lastNode, next, phero);
      boolArrayVisited[next] = true;
      lastNode = next;
	  this->toVisit--;
    }

    m_distanceWalked += callbackInstance->ReadMatrix(lastNode,m_start);
	antway_vecctor.push_back(lastNode);
    return AntWalkedWay(antway_vecctor, m_distanceWalked);
}

   
	  



antAgent::~antAgent(void)
{
	//delete [] m_bvisited;
//	delete [] ant_way;
}
