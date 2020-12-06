//Noah Krill
//main file for seam carving
#include "seamCarve.hpp"
void error();
int main(int argc, char *argv[])
{
	
	if(argc < 3)
	{
		error();
	}
	else
	{
	int rows=0, columns=0, greyScaleMax=255;
	std::string filename = argv[1];
	int verticleSeams = atoi(argv[2]);
	int horizontalSeams = atoi(argv[3]);
	std::string outFileName = filename.substr(0, filename.size()-4);
	//file.open(filename);

	std::ifstream pgm(filename.c_str());
	std::stringstream ss;
	std::string input ="";

	std::getline(pgm,input);
	std::getline(pgm,input);
	ss << pgm.rdbuf();
	ss >> columns >> rows;
	ss >> greyScaleMax;

	int ** greyScaleValue = new int *[rows];
	for(int i =0; i < rows; ++i)
	{
		greyScaleValue[i]= new int [columns];
	}

	for (int i=0; i < rows; ++i)
	{
		for(int j=0; j< columns;++j)
		{
			ss >> greyScaleValue[i][j];
		}
	}

	pgm.close();

	for(int i=0; i <verticleSeams; ++i)
	{
		int ** energyAr = new int * [rows];
		for(int j = 0; j <rows; ++j)
		{
			energyAr[j]=new int[columns];
		}
		int ** minEnergy = new int *[rows];
		for (int k =0; k < rows; ++k)
		{
			minEnergy[k]= new int [columns];
		}
		getEnergy(greyScaleValue,energyAr,rows,columns);
		accumulateVEnergy(energyAr,minEnergy,rows,columns);
		vSeams(greyScaleValue, minEnergy, rows, columns);
		columns--;

		for(int i=0; i<rows;++i)
		{
			delete[] energyAr[i];
			delete[] minEnergy[i];
		}
			delete[]energyAr;
			delete[]minEnergy;
		}
		for(int i=0; i <horizontalSeams; ++i)
		{
			int ** energyAr = new int * [rows];
			for(int j = 0; j <rows; ++j)
			{
				energyAr[j]=new int[columns];
			}
			int ** minEnergy = new int *[rows];
			for (int k =0; k < rows; ++k)
			{
				minEnergy[k]= new int [columns];
			}
			getEnergy(greyScaleValue,energyAr,rows,columns);
			accumulateHEnergy(energyAr,minEnergy,rows,columns);
			hSeams(greyScaleValue, minEnergy, rows, columns);
			rows--;

			for (int k=0; k<rows; k++)
			{
				delete[] energyAr[k];
				delete[] minEnergy[k];
			}
			delete[]energyAr;
			delete[]minEnergy;
		}

	//write grayScaleValue to a file
	writeFile(greyScaleValue, rows, columns, outFileName);

	//delete memory associated with grayScaleValue
	for (int k=0; k<rows; k++) 
	delete[] greyScaleValue[k];
	
	delete[]greyScaleValue;

	return 0;
}
}

void error()
{
std::cout << "The format should be a.exe filename #verticle seams number of horizontal seams";
}