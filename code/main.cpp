#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ChangeString(ifstream& inputFile, ofstream& outputFile, const string& searchString, const string& replaceString)
{
	int compareIndex = 0;
	char processingSymbol = 0;
	inputFile.get(processingSymbol);

	while (!inputFile.eof())
	{
		while (processingSymbol == searchString[compareIndex] && !inputFile.eof())
		{
			++compareIndex;
			inputFile.get(processingSymbol);
		}

		if (compareIndex == searchString.length())
		{
			outputFile << replaceString;
			compareIndex = 0;
		}
		else if (compareIndex > 0)
		{
			outputFile << searchString[0];
			inputFile.seekg(-compareIndex, inputFile.cur);
			compareIndex = 0;
			inputFile.get(processingSymbol);
        }
		else
		{
			outputFile << processingSymbol;
			inputFile.get(processingSymbol);
		}
	}
	return;
}

int main (int argc, char* argv[])
{
	if (argc < 5) 
	{
		cout << "Usage <input file> <output file> <search string> <replace string>" << endl;
		return 0;
	}
	
	ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		cout << "Input file opening error" << endl;
		return 1;
	}
	ofstream outputFile(argv[2]);
	if (!outputFile.is_open())
	{
		inputFile.close();
		cout << "Output file opening error" << endl;
	}

	const string searchString(argv[3]);
	const string replaceString(argv[4]);

	ChangeString(inputFile, outputFile, searchString, replaceString);

	inputFile.close();
	outputFile.close();

	return 0;
}
