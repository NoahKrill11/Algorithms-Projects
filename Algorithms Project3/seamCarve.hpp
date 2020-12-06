#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <algorithm>
#ifndef SEAMCARVE_H
#define SEAMCARVE_H


void getEnergy(int **, int** , const int &, const int &);
void accumulateVEnergy(int **, int **, const int &, const int&);
void vSeams(int **, int **, const int &, const int &);
void hSeams(int **, int **, const int &, const int &);
void writeFile(int** array, const int &, const int &, std::string);
void accumulateHEnergy(int** energyAr, int** minEnergy, const int &rows, const int &columns);


#endif
