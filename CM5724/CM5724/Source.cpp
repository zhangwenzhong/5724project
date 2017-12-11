#include<fstream>
#include<math.h>
using namespace std;

/*Self-defined function to implement the Margin Perceptron algorithm given a particular guess margin. 
Return true if no violation exists, and return false if number of iteration exceeds the maximum limit*/
bool MarPer(int size, int dim, double R, double margin, double** data, double* vector); 


int main()
{
	//Read data from a txt file
	int size, dim;
	double** data;
	ifstream infile;
	infile.open("dataset2.txt");
	infile >> size;
	infile >> dim;
	//Create a 2D array to store the whole data points
	data = new double*[size];//row
	for (int u = 0; u < size; u++)
	{
		data[u] = new double[dim + 2];//column
		for (int j = 0; j < (dim + 2); j++)
		{
			if (j == dim) {
				data[u][j] = 1; //Add one dimension to make the seperation plane passing through the origin
			}
			else {
				infile >> data[u][j];
			}
		}
	}
	infile.close();

	/*Incremental Algorithm. Output a seperation plane with a margin at least half of the guess margin, 
	i.e. 1/4 of the optimal margin, if exists. Otherwise output "Seperation plane is not found" indicating
	that the dataset is not linearly seperable.*/
	double R;
	double guess_margin;
	double* vector = new double[dim + 1];
	double current, max = 0;
	for (int i = 0; i < size; i++) {
		current = 0;
		for (int j = 0; j < dim + 1; j++) {
			current += data[i][j] * data[i][j];
		}
		if (current > max) {
			max = current;
		}
	}
	R = sqrt(max);
	guess_margin = R;
	ofstream ofile;
	ofile.open("Result.txt");
	while (true) {
		if (MarPer(size, dim, R, guess_margin, data, vector)) {
			ofile.clear();
			ofile << "Seperation plane is found as:" << endl;
			for (int i = 0; i < dim; i++) {
				ofile << "(" << vector[i] << ")" << "x" << i + 1 << " + ";
			}
			ofile << "(" << vector[dim] << ")" << " = 0" << endl
				<< "with a margin at least " << guess_margin / 2;
			for (int i = 0; i < size; i++) {
				delete[] data[i];
			}
			delete[] data;
			return 0;
		}
		else {
			guess_margin = guess_margin / 2;
		}
		if (guess_margin < 0.000001) {
			ofile.clear();
			ofile << "Seperation plane is not found. The dataset is not linearly seperable.";
			for (int i = 0; i < size; i++) {
				delete[] data[i];
			}
			delete[] data;
			return 0;
		}
	}
}

bool MarPer(int size, int dim, double R, double margin, double** data, double* vector) {
	int counter = 0; //counter for iteration
	double product, distance, squareMag;
	int state; //0 or 1
	for (int i = 0; i < dim + 1; i++) { 
		vector[i] = 0;
	}
	while (true) {
		for (int i = 0; i < size; i++) {
			product = 0;
			squareMag = 0;
			state = data[i][dim + 1];
			for (int j = 0; j < dim + 1; j++) {
				product += vector[j] * data[i][j];
				squareMag += vector[j] * vector[j];
			}
			distance = abs(product) / sqrt(squareMag);
			if ((distance <= margin / 2) || (product >= 0 && state == 1) || (product <= 0 && state == 0)) { //violation exists
				switch (state)
				{
				case 0:
					for (int j = 0; j < dim + 1; j++) {
						vector[j] += data[i][j];
					}
					break;
				case 1:
					for (int j = 0; j < dim + 1; j++) {
						vector[j] -= data[i][j];
					}
					break;
				}
				break;
			}
			else if (i == size - 1) {//all data points are evaluated
				return true;
			}
		}
		counter++;
		if (counter > 1 + 12 * pow(R, 2) / pow(margin, 2)) { //number of iterations exceeds the limit since the guess margin is too large
			return false;
		}
	}
}