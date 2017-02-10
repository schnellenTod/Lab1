#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
#define longint long long

string ConvertToBin(longint inputNumber)
{
	string resultNumber;
	for (int i = 0; i < sizeof(longint) * 8; ++i)
	{
		if (inputNumber & longint(1))
		{
			resultNumber.push_back('1');
		}
		else
		{
			resultNumber.push_back('0');
		}
		inputNumber = inputNumber >> 1;
	}
	reverse(resultNumber.begin(), resultNumber.end());
	size_t pos = resultNumber.find('1');
	if (pos != string::npos)
	{
		resultNumber.erase(resultNumber.begin(), resultNumber.begin() + pos);
	}
	else {
		resultNumber = "0";
	}
	return resultNumber;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Usage: <decimal number in [0,2^32 - 1]>" << endl;
		return 0;
	}
	longint inputNumber = 0;
	try
	{
		inputNumber = stoll(string(argv[1]));
		if (inputNumber < 0 || inputNumber > 0xFFFFFFFF)
		{
			throw(inputNumber);
		}
	}
	catch (...)
	{
		cout << "Input number is invalid" << endl;
		return 0;
	}

	cout << ConvertToBin(inputNumber) << endl;

	return 0;
}