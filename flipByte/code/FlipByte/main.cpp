#include <iostream>
#include <string>

using namespace std;
#define BYTE unsigned char

BYTE FlipByte(const BYTE processingNumber)
{
	int resultNumber = processingNumber;
	resultNumber = (resultNumber & 0xF0) >> 4 | (resultNumber & 0x0F) << 4;
	resultNumber = (resultNumber & 0xCC) >> 2 | (resultNumber & 0x33) << 2;
	resultNumber = (resultNumber & 0xAA) >> 1 | (resultNumber & 0x55) << 1;
	return resultNumber;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Usage: <decimal number in [0,255]>" << endl;
		return 0;
	}
	int inputNumber = 0;
	try
	{
		inputNumber = stoi(string(argv[1]));
		if (inputNumber < 0 || inputNumber > 255)
		{
			throw(inputNumber);
		}
	}
	catch (...)
	{
		cout << "Input number is invalid" << endl;
		return 0;
	}
	BYTE processingNumber = BYTE(inputNumber);

	cout << int(FlipByte(processingNumber)) << endl;
	return 0;
}