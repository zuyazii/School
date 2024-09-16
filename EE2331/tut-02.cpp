// Student name:
// Student ID  :

/*
	Submission deadline: Friday, 20 Sept 2024, 11:59 pm

	Upload your .cpp file to Canvas.

	Put down your name and student ID at the top of your program file.
	10% marks will be deducted if your program file does not contain your name and ID.

	Submitted program that cannot be compiled (with syntax errors) by Visual Studio
	will receive no more than 30% marks.

	Late submissions or submissions by other means are not accepted.

	This tutorial is on sorting and searching of 2D array.
	
*/

#include <iostream>
#include <iomanip>  //setw()
#include <cstdlib>
#include <ctime>

using namespace std;

//---------------------------------------------- function to be implemented by student

void sort2DArray(int** A, int m, int n)
{
	// Array A[][] has m rows and n columns. 
	// After sorting, elements in A[][] are arranged in ascending order column by column, and within a column.

	// Use any sorting method that you know, e.g. insertion sort.
	// Do not create any other dynamic array in your design.

}

void search2DArray(int** A, int m, int n, int v, int& r, int& c)
{
	// Array A[][] has m rows and n columns.
	// Numbers in A[][] are arranged in ascending order column by column and within a column. 
	// Search for the value v in the 2D array A[][] using binary search.
	// If v is present in A[][], determine r and c such that A[r][c] == v.
	// If v is not present in A[][], then r and c are set to -1.

}


//----------------------------------------------- functions prepared for you

int** gen2DArray(int m, int n)
{
	int** A = new int*[m];
	for (int i = 0; i < m; i++)
		A[i] = new int[n];

	srand(time(NULL));
	int k = m * n * 3 + 1;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = 1 + rand() % k;

	return A;
}

void print2DArray(int** A, int m, int n)
{
   for (int i = 0; i < m; i++)
   {
	   for (int j = 0; j < n; j++)
		   cout << setw(5) << A[i][j] << ",";
	   cout << endl;
   }
   cout << endl;
}


int main()
{
	int row, col;
	cout << "Enter number of rows: ";
	cin >> row;

	cout << "Enter number of cols: ";
	cin >> col;

	int** A = gen2DArray(row, col);
	print2DArray(A, row, col);

	sort2DArray(A, row, col);
	cout << endl << "Sort A[][] by column-major order" << endl;
	print2DArray(A, row, col);

	int value = 0;
	while (value >= 0)
	{
		cout << "Enter search value (negative value to exit): ";
		cin >> value;
		if (value < 0)
			break;

		int r = -1, c = -1;
		search2DArray(A, row, col, value, r, c);

		if (r >= 0 && c >= 0)
			cout << value << " is found at A[" << r << "][" << c << "]" << endl << endl;
		else
			cout << value << " is not found in A[][]" << endl << endl;
	}

	system("pause");
	return 0;
}