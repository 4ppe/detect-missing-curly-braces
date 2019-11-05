#include "Linked Stack.h"
#include <iostream>				// I/O definitions
#include <vector>
#include <fstream>
#include <string>

using namespace std;				// make std:: accessible

int countSpaces(string& inputStr);
void print(std::vector<string>& input);
string getNumberOfLine(string& inputStr);

vector<string> getCurlyBrace() 
{
	vector<string> braces;			// store curly braces lines

	ifstream fin("a.cpp");

	int lineCount = 0;
	string line;
    	string str;
	int spaces = 0;

	while (getline(fin, line))				// read until end of file 
	{
		lineCount++;
        	str = "";

		int bOpen = line.find("{", 0);			// scan open curly braces
		int bClose = line.find("}", 0);             	// scan closed curly braces

		if (bOpen > -1)					// Found open braces
		{   
			spaces = countSpaces(line);       	// get spaces from line
			for (int i = 0; i < spaces; i++)
			{
				str = str + " ";
			}
			str = str + "{"+to_string(lineCount);	// add line number to braces vector
			braces.push_back(str);

			str = "";
			spaces = 0;
		}// End if

		if (bClose > -1)
		{
			spaces = countSpaces(line);
			for (int i = 0; i < spaces; i++)
			{
				str = str + " ";
			}
			str = str + "}" + to_string(lineCount); 

			braces.push_back(str);

			str = "";
			spaces = 0;
		}// End if
        
	}// End while
	return braces;						// return vector of braces
}

bool isCurlyBracesMatched(const vector<string>& braces) 
{	
	string wrongCurlyBraces;
	bool returnValue = true;				//To check the return value	
	string str;
	int bOpen;
	int bClose;
	LinkedStack S;						// stack for opening braces
	typedef vector<string>::const_iterator Iter;		// iterator type
	// iterate through vector
	for (Iter p = braces.begin(); p != braces.end(); ++p) 
	{ 	
	
		bOpen = p->find("{",0);

		if (bOpen > -1)			// is curly braces opened ?
		{
			S.push(*p);
		}
		else
		{
			if(S.empty())   
			{   				
				wrongCurlyBraces = *p;
				// Satirda acilmayan bir parantez kapatilmaya calisilmis
				cout<<"Attempts to close an unopened parenthesis in line "<<getNumberOfLine(wrongCurlyBraces)<<endl; 
				returnValue = false;
			}
			else
			{
				bClose = p->find("}",0);
				string tempStr = S.top();  		// store the string at the top of the stack
				int len = countSpaces(tempStr); 	// get spaces length from the top of the stack 

				if (( bClose > -1 && len == bClose ))
				{
					S.pop();			//pop if opened braces are closed
				}
				else if( bClose > -1 && bClose > len)
				{	
					wrongCurlyBraces = *p;
					
					// Satirda acilmayan bir parantez kapatilmaya calisilmis
					cout<<"Attempts to close an unopened parenthesis in line "<<getNumberOfLine(wrongCurlyBraces)<<endl; 
					
					returnValue = false;  		//sets false the return if spaces do not match
					
				}else if (bClose > -1 && bClose < len)
				{	
					wrongCurlyBraces = S.top();
					
					// Satırda parantez açılmış ama kapatılmamış
					cout<<"Attempts to open an unclosed parentheses in line "<<getNumberOfLine(wrongCurlyBraces)<<endl;
					
					S.pop();   			//error found and used pop for continue the search
					p--;  				//to check again current p
					returnValue = false;  		//sets false the return if spaces do not match
				}	
			}
		}
	} 
	
	while (!S.empty())			//if the stack is not empty
	{	
		wrongCurlyBraces = S.top();
		// Satırda parantez açılmış ama kapatılmamış
		cout<<"Attempts to open an unclosed parentheses in line "<<getNumberOfLine(wrongCurlyBraces)<<endl;
		S.pop();
		returnValue = false;		//sets false the return if the stack is not empty
	}// end while
	
	return returnValue;	
} 


string getNumberOfLine(string& inputStr)  	// Gets number of the braces line for add braces vector
{
	int len;
	int bOpen = -1;
	int bClose = -1;
	string line = "";
	len = inputStr.length();
	bOpen = inputStr.find("{",0);
	bClose = inputStr.find("}",0);

	if (bOpen > -1)
	{
		for (int i = (bOpen + 1) ; i < len; i++)
		{
			line = line + inputStr[i];
		}
		
	}else if(bClose > -1)
	{
		for (int i = (bClose + 1) ; i < len; i++)
		{
			line = line + inputStr[i];
		}
	}
	return line;
}


int countSpaces(string& inputStr) 	// counts the spaces of the entered string up to curly braces
{
   	int num = 0;
   	char space = ' ';
    	const char TAB = '\t' ;
	for (int i = 0; i < inputStr.length()  ; i++)
	{

		if (inputStr[i] == '{' || inputStr[i] == '}')
		{
			return num;
		}
		if (inputStr[i] == space)
		{
			num++;
		}else if (inputStr[i] == TAB)
		{			
			num += 4;
		}
	}
   return 0;
}

int main() 
{ 
	if(isCurlyBracesMatched(getCurlyBrace())){
	 	cout<<endl<<"MATCHED"<<endl;
	 }else
	 {
	 	cout<<endl<<"NOT MATCHED"<<endl;
	 }
	return 0;
}
