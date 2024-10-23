// Student name: Chan Lik Ho
// Student ID  : 57842890

/*
	Submission deadline: Thursday, 17 Oct 2024, 11:59 pm

	Upload your .cpp file to Canvas.

	Put down your name and student ID at the top of your program file.
	10% marks will be deducted if your program file does not contain your name and ID.

	Submitted program that cannot be compiled (with syntax errors) by Visual Studio
	will receive no more than 30% marks.

	Late submissions or submissions by other means are not accepted.

	This tutorial is on circular array.
	A circular array is obtained by wrapping a linear array to form a logical ring.
	Refer to the pdf file for a diagram that shows the logical structure of a circular array.

	In this exercise, you need to implement 4 functions
	getMinLoc_seqSearch()
	getMinLoc_binSearch()
	getMedian()
	divideDataSet()
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int getMinLoc_seqSearch(const int* a, int n)
{
	// Preconditions: n > 1 and a[] is distinct. Numbers are arranged in ascending order (circularly).
	// Return the index of the smallest number in a[].
	// Implement this function using sequential search.

	int minLoc = 0;
	int minVal = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] < minVal)
		{
			minVal = a[i];
			minLoc = i;
		}
	}
	return minLoc;
}

int getMinLoc_binSearch(const int* a, int n)
{	
	// Preconditions: n > 1 and a[] is distinct. Numbers are arranged in ascending order (circularly)

	// Return the index of the smallest number in a[].
	// Implement this function using the binary search approach.

	int low = 0, high = n - 1;

	while (low <= high)
	{
		if (a[low] <= a[high]) // Subarray is sorted
			return low;

		int mid = low + (high - low) / 2;
		int next = (mid + 1) % n;
		int prev = (mid + n - 1) % n;

		if (a[mid] <= a[next] && a[mid] <= a[prev])
			return mid;

		if (a[mid] >= a[low])
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

double getMedian(const int* a, int n)
{
	// Preconditions: n > 1 and a[] is distinct. Numbers are arranged in ascending order (circularly)
	// Return the median value of the dataset a[].

	int minLoc = getMinLoc_binSearch(a, n);
	int m = n / 2;
	if (n % 2 == 1) // Odd number of elements
	{
		int medianIndex = (minLoc + m) % n;
		return a[medianIndex];
	}
	else // Even number of elements
	{
		int medianIndex1 = (minLoc + m - 1) % n;
		int medianIndex2 = (minLoc + m) % n;
		return (a[medianIndex1] + a[medianIndex2]) / 2.0;
	}
}

void divideDataSet(const int* a, int n)
{
	// Preconditions: n > 1 and a[] is distinct. Numbers are arranged in ascending order (circularly)

	// Simple division of the dataset into 2 ascending sequences (in circular manner)
	// of elements such that the difference in the weight of the 2 sequences (sum of the numbers)
	// is the smallest among all possible division.

	// Print the 2 sequences (numbers are printed in ascending order).
	// Refer to the screenshot of the expected outputs to design your print statements.

	cout << "Divide the data set into 2 ascending sequences with smallest difference in weight\n";

	int minLoc = getMinLoc_binSearch(a, n);

	// Build sorted array starting from minLoc
	// Compute cumulative sums
	int* cumSum = new int[n];
	cumSum[0] = a[minLoc];
	int totalSum = a[minLoc];
	for (int i = 1; i < n; i++)
	{
		int idx = (minLoc + i) % n;
		totalSum += a[idx];
		cumSum[i] = cumSum[i - 1] + a[idx];
	}

	// Find split index where the difference of sums is minimized
	int minDiff = abs(cumSum[0] - (totalSum - cumSum[0]));
	int splitIndex = 0;
	for (int k = 1; k < n - 1; k++)
	{
		int sum1 = cumSum[k];
		int sum2 = totalSum - sum1;
		int diff = abs(sum1 - sum2);
		if (diff < minDiff)
		{
			minDiff = diff;
			splitIndex = k;
		}
	}

	int sum1 = cumSum[splitIndex];
	int sum2 = totalSum - sum1;

	// Output the two sequences
	cout << "Sequence 1 (sum = " << sum1 << "): ";
	for (int i = 0; i <= splitIndex; i++)
	{
		int idx = (minLoc + i) % n;
		cout << a[idx] << " ";
	}
	cout << endl;
	cout << "Sequence 2 (sum = " << sum2 << "): ";
	for (int i = splitIndex + 1; i < n; i++)
	{
		int idx = (minLoc + i) % n;
		cout << a[idx] << " ";
	}
	cout << endl << endl;

	delete[] cumSum;
}

// functions prepared for you ---------------------------------------------------
int* genCircularArray(int n)
{
	// Generate a circular array of size n with distinct natural (non-negative) numbers, 
	// and numbers are arranged in ascending order (circularly).
	int* a = new int[n];
	int start = rand() % n;
	int t = rand() % 3;

	for (int i = 0; i < n; i++)
	{
		a[(start + i) % n] = t;
		t = t + rand() % 5 + 1;
	}
	return a;
}

void printArray(const int* a, int n)
{
	cout << "Input array : len = " << n << endl;
	for (int i = 0; i < n; i++)
	{
		if (i > 0 && i % 10 == 0)  // print up to 10 elements in a row
			cout << endl;
		cout << setw(4) << a[i] << ", ";  
	}
	cout << endl << endl;
}

void test(const int* a, int n)
{
	cout << "-----------------------------------------------------------" << endl;
	printArray(a, n);

	int minLoc_1 = getMinLoc_seqSearch(a, n);
	int minLoc_2 = getMinLoc_binSearch(a, n);
	cout << "Index of the smallest element = " << minLoc_1 << " ( sequential Search )\n";
	cout << "Index of the smallest element = " << minLoc_2 << " ( binary Search )\n";
	cout << "Largest value = " << a[(minLoc_1 + n - 1) % n] << endl;
	cout << "Smallest value = " << a[minLoc_1] << endl;
	cout << "Median = " << getMedian(a, n) << endl << endl;

	divideDataSet(a, n);
}

int main()
{	
	int a1[] = { 33, 38, 0, 4, 7, 13, 19, 22, 26, 30 };
	int n1 = 10;
	int a2[] = { 1, 5, 10, 14, 16, 20, 23, 27, 30 };
	int n2 = 9;

	test(a1, n1);
	test(a2, n2);

	srand((unsigned)time(NULL));  
	for (int i = 1; i <= 3; i++)
	{
		int n = 9 + rand() % 16;
		int* a = genCircularArray(n);
		test(a, n);
		delete[] a;
	}
	
	system("pause");
	return 0;
}