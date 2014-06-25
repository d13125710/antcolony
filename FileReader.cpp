#include "StdAfx.h"
#include "FileReader.h"
#include "Tokenizer.h"
#include "TokenFinder.h"


#include <array> //for std::array


typedef Tokenizer<TokenFinder> Tk;
std::string::size_type sz;     // alias of size_t


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
	}
	return status;

}
void FileReader::Print(void)
{
		 std::cout << 'Print values read'; 
	for (Coords_vector::iterator it = m_strVector.begin(); it != m_strVector.end(); ++it)
				std::cout << ' ' << (*it).x << ' ' << (*it).y << '\n'; ;
	 std::cout << '\n';
}
FileReader::~FileReader(void)
{
	m_inFile.close();
}
