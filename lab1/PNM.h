#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "RGB.h"

using namespace std;

class PNM
{
public:
	bool error = false;
	string error_type;
	void input(const string &file);
	void negative(const string& filepnm);
	void output(const string& filepnm);
	void HorMir(const string& filepnm);
	void VerMir(const string& filepnm);
	void ClockwiseRotate(const string& filepnm);
	void CounterClockwiseRotate(const string& filepnm);
private:
	string format;
	int height, width, deep;
	vector<vector<unsigned char>> Mass;
	vector<vector <RGB>> RGBMass;
};
