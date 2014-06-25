#pragma once
#include <vector>
#include <string>
#include <istream>
#include <fstream>

using namespace std;


typedef vector<string> string_vector;


class CPreProcessor  
{

private:
		
	ifstream inFile;
	string m_sBuffer;
	string_vector m_vect;
	string *m_DataString;
	//////////////////////////////////////////////////////////////////////
	//
	//  Function	: AddToken
	//
	//  Args		: String 'The Key to search for'
	//
	//
	//	returns		: Adds the new token to the string before the key is 
	//				: Found..
	//
	//////////////////////////////////////////////////////////////////////
	void AddToken(const string &s) const
	{	
		//searches the string for the search string and inserts the token
		int nPos = m_DataString->find(s);
		if(nPos != -1)
			m_DataString->insert(nPos , "####|");
	}

	//not allowed
	CPreProcessor(const CPreProcessor &s){};

public:

	//////////////////////////////////////////////////////////////////////
	//
	//  Function	: ctor , dtor
	//
	//  Args		: FileName to open as the key
	//
	//	returns		: n/a
	//
	//////////////////////////////////////////////////////////////////////
	CPreProcessor(const char* const filename = "Keys.file")  
	{
		inFile.open("keys.file");
		m_DataString=0;
	}
	~CPreProcessor()
	{
	}
	//////////////////////////////////////////////////////////////////////
	//
	//  Function	: ReadKeys
	//
	//  Args		: None
	//
	//  Description : Reads the keys form the file. If the file does not exist
	//				: Then we create a file from the default keys stored in memory
	//				: ,And add these keys to the vector.
	//
	//	returns		: Reads the keys from a file or from memory
	//
	//////////////////////////////////////////////////////////////////////
	void ReadKeys() throw()
	{
		try
		{
			if(!inFile.is_open())
			{
				ofstream oFile("keys.file" , ios::out);
				//read strings from the static table in defs
				char **p=czkeyStrings;
				
				while(**p) //null character at the end
				{
					//load the vector skipping ;
					if(**p != ';' && strlen(*p) > 1)
						m_vect.push_back(*p);
					//output to a file
					oFile << *p << '\n';
					p++;
				}
			}
	  		else
			{
				//read the keys from a file
				while(!inFile.eof())
				{
					getline(inFile , m_sBuffer );
					if(m_sBuffer[0] != ';' && m_sBuffer.length() > 2)
						m_vect.push_back(m_sBuffer);
				}
			}
		}
		catch(...)
		{
		}
	}
	//////////////////////////////////////////////////////////////////////
	//
	//  Function	: ProcessString
	//
	//  Args		: the String Record
	//
	//	Description : This Function is passed the record , it then goes 
	//				: through each Key and adds #### to the start of the
	//				: Token , The reson behind this is that the input string
	//				: does not have a delimiter so here we add one
	//
	//	returns		: true of false stating success
	//
	//////////////////////////////////////////////////////////////////////
	bool ProcessString(string &str)  throw()
	{
		try
		{
			//set the member pointer to point to the str
			m_DataString = &str;
			//process the string
			string_vector::iterator p = m_vect.begin();
			while(p != m_vect.end())
			{
				AddToken(*p);
				p++;
			}
		
		}
		catch(...)
		{
			return false;
		}
	
		return true;

	
	}
	//////////////////////////////////////////////////////////////////////
	//
	//  Function	: GetVector
	//
	//  Args		: None
	//
	//	returns		: Returns the vector
	//
	//////////////////////////////////////////////////////////////////////
	const string_vector &GetKeysVector() const 
	{
		return m_vect;
	}

};

