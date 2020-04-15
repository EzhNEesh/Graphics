#include "PNM.h"
#include "RGB.h"
#include <fstream>

void PNM::input(const string& file)
{
	ifstream F(file.c_str(), ios::binary);
	if (!F.good())
	{
		error = true;
		error_type = "File isn't reading";
		return;
	}
	if (!((file.substr(file.length() - 4, 4) == ".pnm") || (file.substr(file.length() - 4, 4) == ".pgm")))
	{
		error = true;
	}
	F >> format >> width >> height >> deep;
	F.seekg(1, std::ios::cur);
	if (format == "P6")
	{
		RGBMass.resize(height);
		for (int i = 0; i < height; i++)
		{
			RGBMass[i].resize(width);
			for (int j = 0; j < width; j++)
			{
				unsigned char red, green, blue;
				F.read((char*)& red, sizeof(RGBMass[i][j].R));
				F.read((char*)& green, sizeof(RGBMass[i][j].G));
				F.read((char*)& blue, sizeof(RGBMass[i][j].B));

				RGBMass[i][j].R = red;
				RGBMass[i][j].G = green;
				RGBMass[i][j].B = blue;
			}
		}
		if (RGBMass.empty())
		{
			error = true;
			error_type = "Out of memory";
			return;
		}
	}
	else if (format == "P5")
	{
		Mass.resize(height);
		for (int i = 0; i < height; i++)
		{
			Mass[i].resize(width);
			for (int j = 0; j < width; j++)
			{
				unsigned char pixel;
				F.read((char*)& pixel, sizeof(unsigned char));
				Mass[i][j] = pixel;
			}
		}
		if (Mass.empty())
			{
				error = true;
				error_type = "Out of memory";
				return;
			}
	}
	else
	{
		error = true;
	}
}

void PNM::negative(const string& filepnm)
{
	if (format == "P6")
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				RGBMass[i][j].R = deep - RGBMass[i][j].R;
				RGBMass[i][j].G = deep - RGBMass[i][j].G;
				RGBMass[i][j].B = deep - RGBMass[i][j].B;
			}
	}
	else
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				Mass[i][j] = deep - Mass[i][j];
			}
	}
	output(filepnm);
}

void PNM::HorMir(const string& filepnm)
{
	if (format == "P6")
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width / 2; j++)
			{
				RGB Temp;
				Temp = RGBMass[i][j];
				RGBMass[i][j] = RGBMass[i][width - j - 1];
				RGBMass[i][width - j - 1] = Temp;
			}
	}
	else
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width / 2; j++)
			{
				int Temp;
				Temp = Mass[i][j];
				Mass[i][j] = Mass[i][width - j - 1];
				Mass[i][width - j - 1] = Temp;
			}
	}
	output(filepnm);
}

void PNM::VerMir(const string& filepnm)
{
	if (format == "P6")
	{
		for (int i = 0; i < height / 2; i++)
			for (int j = 0; j < width; j++)
			{
				RGB Temp;
				Temp = RGBMass[i][j];
				RGBMass[i][j] = RGBMass[height - i - 1][j];
				RGBMass[height - i - 1][j] = Temp;
			}
	}
	else
	{
		for (int i = 0; i < height / 2; i++)
			for (int j = 0; j < width; j++)
			{
				int Temp;
				Temp = Mass[i][j];
				Mass[i][j] = Mass[height - i - 1][j];
				Mass[height - i - 1][j] = Temp;
			}
	}
	output(filepnm);
}

void PNM::ClockwiseRotate(const string& filepnm)
{
	if (format == "P6")
	{
		int h = height;
		swap(width, height);
		vector<vector<RGB>> Temp = *&RGBMass;
		RGBMass.clear();
		RGBMass.resize(height);
		int x = 0, y;
		for (int i = 0; i < height; i++)
		{
			y = h - 1;
			RGBMass[i].resize(width);
			for (int j = 0; j < width; j++)
			{
				RGBMass[i][j].R = Temp[y][x].R;
				RGBMass[i][j].G = Temp[y][x].G;
				RGBMass[i][j].B = Temp[y][x].B;
				y--;
			}
			x++;
		}
		Temp.clear();
	}
	else
	{
		int h = height;
		swap(width, height);
		vector<vector<unsigned char>> Temp = *&Mass;
		Mass.clear();
		Mass.resize(height);
		int x = 0, y;
		for (int i = 0; i < height; i++)
		{
			y = h - 1;
			Mass[i].resize(width);
			for (int j = 0; j < width; j++)
			{
				Mass[i][j] = Temp[y][x];
				y--;
			}
			x++;
		}
		Temp.clear();
	}
	output(filepnm);
}

void PNM::CounterClockwiseRotate(const string& filepnm)
{
	if (format == "P6")
	{
		int w = width;
		swap(width, height);
		vector<vector<RGB>> Temp = *&RGBMass;
		RGBMass.clear();
		RGBMass.resize(height);
		int x = w - 1, y;
		for (int i = 0; i < height; i++)
		{
			y = 0;
			RGBMass[i].resize(width);
			for (int j = 0; j < width; j++)
			{
				RGBMass[i][j].R = Temp[y][x].R;
				RGBMass[i][j].G = Temp[y][x].G;
				RGBMass[i][j].B = Temp[y][x].B;
				y++;
			}
			x--;
		}
		Temp.clear();
	}
	else
	{
		int w = width;
		swap(width, height);
		vector<vector<unsigned char>> Temp = *&Mass;
		Mass.clear();
		Mass.resize(height);
		int x = w - 1, y;
		for (int i = 0; i < height; i++)
		{
			y = 0;
			Mass[i].resize(width);
			for (int j = 0; j < width; j++)
			{
				Mass[i][j] = Temp[y][x];
				y++;
			}
			x--;
		}
		Temp.clear();
	}
	output(filepnm);
}

void PNM::output(const string& filepnm)
{
	ofstream File(filepnm, ios::binary);
	if (!File.is_open())
	{
		error = true;
		error_type = "File isn't writing";
		return;
	}
	File << format << endl << width << ' ' << height << endl << deep << endl;
	if (format == "P6")
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				File.put(RGBMass[i][j].R);
				File.put(RGBMass[i][j].G);
				File.put(RGBMass[i][j].B);
			}
		}
	}
	else
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				File.put(Mass[i][j]);
			}
		}
	}
	if (File.fail())
	{
		error = true;
		error_type = "File isn't writing";
		return;
	}
	File.close();
}

