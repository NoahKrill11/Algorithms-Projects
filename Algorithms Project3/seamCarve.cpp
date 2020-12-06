#include "seamCarve.hpp"
void getEnergy(int ** grayScaleValue,int ** energyAr, const int &rows, const int &columns)
{
	for(int i=0; i<rows; ++i)
	{
		for (int j=0; j<columns;++j)
		{
			if(i==0 && j==0) {
                //only do right and down
                energyAr[i][j] = (abs((grayScaleValue[i][j])-(grayScaleValue[i+1][j])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i][j+1])));
            }
            //up and right
            else if((i==0) && (j==(columns-1))){
                //only do left and down
                energyAr[i][j] = (abs((grayScaleValue[i][j])-(grayScaleValue[i][j-1])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i+1][j])));
            }
            //down and left
            else if((i==(rows-1)) && (j==0)) {
                //only do up and right
                energyAr[i][j] = (abs((grayScaleValue[i][j])-(grayScaleValue[i-1][j])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i][j+1])));
            }
            //down and right
            else if((i==(rows-1)) && (j==(columns-1))){
                //only do up and left
                energyAr[i][j] = (abs((grayScaleValue[i][j])-(grayScaleValue[i-1][j])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i][j-1])));
            }
            //for top row
            else if(i==0) {
                //right, left and bottom
                energyAr[i][j] = (abs((grayScaleValue[i][j])-(grayScaleValue[i][j+1])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i][j-1])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i+1][j])));
            }
            //for bottom row
            else if(i==(rows-1)){
                //top, left and right
                energyAr[i][j] = (abs((grayScaleValue[i][j])-(grayScaleValue[i][j+1])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i][j-1])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i-1][j])));
            }
            //for first column
            else if(j==0) {
                //right, top and bottom
                energyAr[i][j] = (abs((grayScaleValue[i][j])-(grayScaleValue[i][j+1])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i-1][j])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i+1][j])));
            }
            else if(j==(columns-1)){
                //left, top and bottom
                energyAr[i][j] = (abs((grayScaleValue[i][j])-(grayScaleValue[i][j-1])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i+1][j])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i-1][j])));
            } else {
                energyAr[i][j] = (abs((grayScaleValue[i][j])-(grayScaleValue[i-1][j])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i+1][j])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i][j-1])) +
                                   abs((grayScaleValue[i][j])-(grayScaleValue[i][j+1])));
            }
        }
    }
}
void accumulateVEnergy(int **energyAr,int **minEnergy,const int &rows,const int &columns)
{
	for(int i=0; i <rows; ++i)
	{
		for(int j=0; j<columns; ++j)
		{
			if(i==0)
			{
				minEnergy[i][j]= energyAr[i][j];
			}
			else
			{
				if(j==0)
				{
					minEnergy[i][j]=energyAr[i][j]+std::min(minEnergy[i-1][j], minEnergy[i-1][j+1]);
				}
				else if(j==(columns-1))
				{
					minEnergy[i][j] = energyAr[i][j] + std::min(minEnergy[i-1][j-1], minEnergy[i-1][j]);
                } else 
                {
                    //find the min energy to add to the running total
                    minEnergy[i][j] = energyAr[i][j] + std::min(std::min(minEnergy[i-1][j-1], minEnergy[i-1][j]),minEnergy[i-1][j+1]);
                }
            }
        }
    }
}
void accumulateHEnergy(int** energyAr, int** minEnergy, const int &rows, const int &columns) {
    //loop through the col
    for(int j=0; j<columns; j++) {
        //loop through the rows
        for(int i=0; i<rows; i++) {
            //do this only for the first column
            if(j==0){
                //copy over values
                minEnergy[i][j] = energyAr[i][j];
            } else {
                //top row
                if(i==0) {
                    //ignore out of bounds
                    minEnergy[i][j] = energyAr[i][j] + std::min(minEnergy[i][j-1], minEnergy[i+1][j-1]);
                } else if(i==(rows-1)) {
                    //ignore out of bounds
                    minEnergy[i][j] = energyAr[i][j] + std::min(minEnergy[i][j-1], minEnergy[i-1][j-1]);
                } else {
                    //find the min energy to add to the running total
                    minEnergy[i][j] = energyAr[i][j] + std::min(std::min(minEnergy[i-1][j-1], minEnergy[i][j-1]), minEnergy[i+1][j-1]);
                }
            }
        }
    }
}
void vSeams(int **grayScaleValue, int **minEnergy, const int &rows, const int &columns)
{
	int mIndex=0;
	int min = minEnergy[rows-1][mIndex];
	for(int i =0; i <columns; ++i)
	{
		if(minEnergy[rows-1][i] <= min)
		{
			mIndex =i;
			min = minEnergy[rows-1][i];
		}
	}
	for (int i=(rows-2); i>=0; i--)
	{
		if(mIndex==0)
		{
		    if (minEnergy[i][mIndex+1]< minEnergy[i][mIndex])
			{
				mIndex=mIndex+1;
			}

		}
		else if(mIndex==(columns-1))
		{
			if(minEnergy[i][mIndex-1] < minEnergy[i][mIndex]){
                //return left
                mIndex = mIndex-1;
            }
		}
		else
		{
			 if((minEnergy[i][mIndex+1] < minEnergy[i][mIndex]) && (minEnergy[i][mIndex+1] < minEnergy[i][mIndex-1])){
                //return right
                mIndex = mIndex+1;
            } // check left as min
            else if((minEnergy[i][mIndex-1] < minEnergy[i][mIndex]) && (minEnergy[i][mIndex-1] < minEnergy[i][mIndex+1])){
                //return left
                mIndex = mIndex-1;
            } // if both left and right are equal and less than middle
            else if((minEnergy[i][mIndex-1] < minEnergy[i][mIndex]) && (minEnergy[i][mIndex+1] < minEnergy[i][mIndex]) && (minEnergy[i][mIndex+1] == minEnergy[i][mIndex-1])){
                // by default return the left
                mIndex = mIndex-1;
            }
        }
        // delete mIndex value and shift all the values over
        for(int it = mIndex; it < (columns-1);it++){
            //copy over the left element
            grayScaleValue[i][it] = grayScaleValue[i][it+1];
        }
    }
}
void hSeams(int **grayScaleValue, int **minEnergy, const int &rows, const int & columns)
{
	int mIndex=columns-1, min = 999999;
	for(int i=0; i<rows; ++i)
	{
		if (minEnergy[i][columns-1]<min)
		{
			mIndex = i;
			min = minEnergy[i][columns-1];
		}
	}
	for(int i = mIndex; i<(rows-1); ++i)
	{
		grayScaleValue[i][columns-1]=grayScaleValue[i+1][columns-1];
	}
	for(int j=(columns-2); j>=0;--j)
	{
		if(mIndex == 0)
		{
			if(minEnergy[mIndex+1][j] < minEnergy[mIndex][j])
			{
                //return bottom
                mIndex = mIndex+1;
            }
		}
		else if(mIndex==(rows-1))
		{
			if(minEnergy[mIndex-1][j] < minEnergy[mIndex][j]){
                //return top
                mIndex = mIndex-1;
            }
		}
		else
		{
			if((minEnergy[mIndex-1][j] < minEnergy[mIndex][j]) && (minEnergy[mIndex-1][j] < minEnergy[mIndex+1][j])){
                //return top
                mIndex = mIndex-1;
            } // check bottom as min
            else if((minEnergy[mIndex+1][j] < minEnergy[mIndex][j]) && (minEnergy[mIndex+1][j] < minEnergy[mIndex-1][j])){
                //return bottom
                mIndex = mIndex+1;
            }
            // if both top and bottom are equal and less than left
            else if((minEnergy[mIndex+1][j] < minEnergy[mIndex][j]) && (minEnergy[mIndex-1][j] < minEnergy[mIndex][j]) && (minEnergy[mIndex+1][j] == minEnergy[mIndex-1][j])){
                // by default return the top
                mIndex = mIndex-1;
            }
        }
		for(int i = mIndex; i < (rows-1);i++){
            //copy over the left element
            grayScaleValue[i][j] = grayScaleValue[i+1][j];
        }
    }
   }
   void writeFile(int** array, const int &rows, const int &columns, std::string outFileName)
    {
    std::ofstream outFile;
    outFileName.append("_processed.pgm");
    outFile.open(outFileName.c_str());
    if (!outFile.is_open()) {
        std::cout << "Can't open output file"  << outFileName << std::endl;
        return;
    }

    // write the header of the pgm file
    outFile << "P2\n" << "#Output file for " << outFileName << "\n" << columns << " " << rows << "\n255\n";

    //writes the contents of the array to a .pgm file for viewing
    for(int i=0; i<rows; i++) {
        //loops through rows and col
        for(int j=0; j<columns-1; j++) {
            outFile << array[i][j] << " ";
        }
        //last column case appends new line
        outFile << array[i][columns-1] << std::endl;
    }
    outFile.close();
 }