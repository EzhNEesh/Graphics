#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "PNM.h"

using namespace std;

int main(int argc, char* argv[])
{
	PNM A;
	A.input(argv[1]);
	int kom = atoi(argv[3]);
	switch (kom)
	{
	case (0):
		A.negative(argv[2]);
		break;
	case (1):
		A.HorMir(argv[2]);
		break;
	case(2):
		A.VerMir(argv[2]);
		break;
	case(3):
		A.ClockwiseRotate(argv[2]);
		break;
	case(4):
		A.CounterClockwiseRotate(argv[2]);
		break;
	default:
		cout << "Uknown command";
		break;
	}
	return 0;
}