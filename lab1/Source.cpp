#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "PNM.h"

using namespace std;

enum kommand
{
	negative = 0,
	HorMir = 1,
	VerMir = 2,
	ClockwiseRotate = 3,
	CounterClockwiseRotate = 4
};

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "ERROR: Wrong amount of arguments\n";
		return -1;
	}
	PNM A;
	A.input(argv[1]);
	if (A.error)
	{
		cout << "ERROR: " << A.error_type << '/n';
		return -1;
	}
	kommand kom;
	kom = (kommand)atoi(argv[3]);
	switch (kom)
	{
	case negative:
		A.negative(argv[2]);
		break;
	case HorMir:
		A.HorMir(argv[2]);
		break;
	case VerMir:
		A.VerMir(argv[2]);
		break;
	case ClockwiseRotate:
		A.ClockwiseRotate(argv[2]);
		break;
	case CounterClockwiseRotate:
		A.CounterClockwiseRotate(argv[2]);
		break;
	default:
		cout << "ERROR: Uknown command\n";
		return -1;
	}
	if (A.error)
	{
		cout << "ERROR: " << A.error_type << '/n';
		return -1;
	}
	return 0;
}
