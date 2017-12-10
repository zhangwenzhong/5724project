#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>
using namespace std;

int main()
{
	int size;
	int dim;
	int count=0;
	ifstream infile;
	infile.open("dataset2.txt");
	infile >> size;
	infile >> dim;
	cout << size << dim;
	int **data = new int*[size];//row
	for (int u = 0;u < size;u++)
	{
		data[u] = new int[dim+1];//column
		for (int j = 0;j < (dim + 1);j++)
		{
			infile >> data[u][j];
		}
	}
	cout << data[1][0];
	system("pause");
	double  *vector = new double[dim];
	int *v = new int[dim];
	for (int i = 0;i < dim;i++)
	{
		vector[i] = 0;
	}
	for (int i = 0;i < size;i++)
	{
		int sum=0;
		for (int j = 0;j < dim;j++)
		{
			sum += vector[j] * data[i][j];
			v[j] = data[i][j];
		}
		if ((sum > 0) && (data[i][dim] == 1))
		{
			continue;
		}
		else if ((sum < 0) && (data[i][dim] == 0))
		{
			continue;

		}
		else if ((sum > 0) && (data[i][dim] == 0))
		{
			for(int i= 0;i<dim;i++)
			{
				vector[i] = vector[i] + v[i];
			}
			
		}
		else if ((sum < 0) && (data[i][dim] == 1))
		{
			for (int i = 0;i<dim;i++)
			{
				vector[i] = vector[i] - v[i];
			}

		}

	}

}