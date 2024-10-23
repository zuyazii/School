// Student name: Chan Lik Ho
// Student ID  : 57842890

/*
	Submission deadline: Friday, 25 Oct 2024, 11:59 pm

	Upload your .cpp file to Canvas.

	Put down your name and student ID at the top of your program file.
	10% marks will be deducted if your program file does not contain your name and ID.

	Submitted program that cannot be compiled (with syntax errors) by Visual Studio
	will receive no more than 30% marks.

	Late submissions or submissions by other means are not accepted.

	1. Parts of the function readDataFile() are done for you. 
	   Complete the implementation of the function.

	2. Implement the function findMostPopular().
	   You may define other supporting functions where appropriate.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cstring>  // For strncpy and strcmp

using namespace std;

struct videoRec   // record to hold input data read from data file
{
	long long timestamp;
	string vid;   // video ID
	string clientIP;
};

// Modified countRec to use fixed-size character array for vid
struct countRec   // record for holding the result
{
	int count;
	char vid[100];  // Adjust size as needed based on expected maximum video ID length
};

// Comparator for sorting pointers to videoRec by vid (ascending)
int compareVideoRecPointers(const void* a, const void* b)
{
	const videoRec* const* recA = (const videoRec* const*)a;
	const videoRec* const* recB = (const videoRec* const*)b;
	return ((*recA)->vid).compare((*recB)->vid);
}

// Comparator for sorting countRec by count (descending), then vid (ascending)
int compareCountRecDescending(const void* a, const void* b)
{
	const countRec* recA = (const countRec*)a;
	const countRec* recB = (const countRec*)b;
	if (recB->count != recA->count)
		return recB->count - recA->count;  // Descending order
	else
		return strcmp(recA->vid, recB->vid); // Ascending order for ties
}

videoRec* readDataFile(const string& filename, int& n)
{
	// Read the data file, and return an array of videoRec.
	// n = number of records read from data file

	// Each line in the data file contains 3 items separated by comma.
	// The 3 items are:
	// a timestamp (long integer), a video ID (string), and a clientIP (string, IPv4 address)

	// The getline(infile, line) function reads in 1 line of text from the data file.
	// You can use the function line.find(string) or line.find(string, int) to find
	// the index position of the comma in the string.
	// Use the line.substr() function to extract the data component.
	// See https://cplusplus.com/reference/string/string/ for details.

	ifstream infile;
	infile.open(filename);
	if (!infile.is_open())  // open data file
	{
		cout << "Cannot open data file" << endl;
		system("pause");
		exit(0);
	}

	int size = 1000;   // initial size of the array
	videoRec* list;
	list = new videoRec[size];  // dynamic memory allocation
	n = 0;

	string line;
	while (getline(infile, line))  // Corrected loop condition
	{
		if (line.length() > 0)  // line is not empty
		{
			// Parse the line to extract timestamp, vid, clientIP
			size_t pos1 = line.find(',');
			size_t pos2 = line.find(',', pos1 + 1);

			// Ensure that both commas are found
			if (pos1 == string::npos || pos2 == string::npos)
			{
				// Invalid line format; skip this line
				continue;
			}

			string timestamp_str = line.substr(0, pos1);
			string vid = line.substr(pos1 + 1, pos2 - pos1 - 1);
			string clientIP = line.substr(pos2 + 1);

			// Convert timestamp_str to long long integer
			long long timestamp = atoll(timestamp_str.c_str());

			// Store into list
			if (n >= size)
			{
				// Need to expand the array
				int newSize = size * 2;
				videoRec* newList = new videoRec[newSize];
				for (int i = 0; i < size; i++)
					newList[i] = list[i];
				delete[] list;
				list = newList;
				size = newSize;
			}

			list[n].timestamp = timestamp;
			list[n].vid = vid;
			list[n].clientIP = clientIP;
			n++;
		}
	}
	infile.close();
	return list;
}

void findMostPopular(videoRec* list, int n, int limit)
{
	// 1. Create an array of pointers to videoRec
	videoRec** ptrList = new videoRec*[n];
	for(int i = 0; i < n; ++i)
	{
		ptrList[i] = &list[i];
	}

	// 2. Sort the array of pointers by vid using qsort
	qsort(ptrList, n, sizeof(videoRec*), compareVideoRecPointers);

	// 3. Traverse the sorted array to count views per vid
	// Allocate a dynamic array for countRec with an upper bound of n unique vids
	countRec* res = new countRec[n];
	int t = 0;  // Number of unique vids

	int i = 0;
	while(i < n)
	{
		string current_vid = ptrList[i]->vid;
		int count = 1;
		int j = i + 1;
		while(j < n && ptrList[j]->vid == current_vid)
		{
			count++;
			j++;
		}
		// Safely copy the video ID into the countRec struct
		strncpy(res[t].vid, current_vid.c_str(), sizeof(res[t].vid) - 1);
		res[t].vid[sizeof(res[t].vid) - 1] = '\0';  // Ensure null-termination
		res[t].count = count;
		t++;
		i = j;
	}

	// 4. Sort the countRec array in descending order of count using qsort
	qsort(res, t, sizeof(countRec), compareCountRecDescending);

	// 5. Display the top 'limit' most popular videos
	int outputLimit = (limit < t) ? limit : t;
	cout << "Top " << limit << " most popular videos (video ID, view count):" << endl;
	for(int j = 0; j < outputLimit; j++)
		cout << setw(2) << j + 1 << " : " << res[j].vid << ", " << res[j].count << endl;

	// 6. Clean up dynamically allocated memory
	delete[] res;
	delete[] ptrList;
}

int main()  // Do not modify main()
{
	string filename = "videoData.txt";
	int n;
	videoRec* list = readDataFile(filename, n);
	cout << "number of records in data file = " << n << endl << endl;

	// Find the top 10 most popular videos
	findMostPopular(list, n, 10);

	delete[] list;  // Clean up dynamically allocated memory
	system("pause");
	return 0;
}
