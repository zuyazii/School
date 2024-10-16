// Student name: 57842890
// Student ID  : Chan Lik Ho

/*
	Submission deadline: Friday, 27 Sept 2024, 11:59 pm

	This exercise is on the conversion of IPv6 address from text format to binary.
	The 128-bit IPv6 address is represented by an array of 16 bytes (unsigned char).

	Upload your .cpp file to Canvas.

	Put down your name and student ID at the top of your program file.
	10% Marks will be deducted if your program file does not contain your name and ID.

	Late submission or submission by other means are not accepted.
*/

#include <iostream>
#include <bitset>
#include <cstring>

using namespace std;

unsigned int hexstrToInt(const char* str) {
	unsigned int result = 0;
    char c;
    int i = 0;
    while ((c = str[i]) != '\0') {
        result *= 16;
        if (c >= '0' && c <= '9')
            result += c - '0';
        else if (c >= 'A' && c <= 'F')
            result += c - 'A' + 10;
        else if (c >= 'a' && c <= 'f')
            result += c - 'a' + 10;
        else {} // Ignore invalid characters
        i++;
    }
    return result;
}

void text2bin_IPv6(const char* a, unsigned char* v) 
{
	// a[] is the text format representation of the IPv6 address.
	// v[] is the binary IPv6 address to be produced by the conversion function.
	// v[0] is the leftmost byte of the 128-bit IPv6 address, 
	// bit-7 of v[0] is the leftmost (1st) bit of the IPv6 address.

	for (int k = 0; k < 16; k++)
		v[k] = 0;

	// Variables Declaration 
	char hextets[8][5]; // Groups for the hextets (8 x (4 hex digits + 1 Null terminator))
	int hextetTokens = 0; 
	int i = 0; // Index for a[]
	int j = 0; // Index for hextets[hextetTokens]
	int doubleColonIndex = -1;
	char cPrev = 0; 
	char c; 

	for (int t = 0; t < 8; t++)
		hextets[t][0] = 0;

	while ((c == a[i]) != '\0') {
		if (c == ':') {
			// Check if it's a double colon
			if (cPrev == ':') {
				doubleColonIndex = hextetTokens;
				hextetTokens++;
			}
			else {
				hextets[hextetTokens][j] = 0;
				hextetTokens++;
				j = 0;
			}
		}
		else {
			hextets[hextetTokens][j] = c;
			j++;
		}
		cPrev = c;
		c++;
	}

	// Add the last token if input doesn't end with ':'
	if (cPrev != ':') {
        hextets[hextetTokens][j] = '\0';
        hextetTokens++;
    }

	// Insert zeros for double colon
	int zerosToInsert = 0;
	if (doubleColonIndex != -1) {
		zerosToInsert = 8 - (hextetTokens - 1);
	}

	int idx = 0; // Index for v[]
    for (int t = 0; t < hextetTokens; t++) {
        if (doubleColonIndex == t) {
            idx += zerosToInsert;
        } else {
            unsigned int value = hexstrToInt(hextets[t]);
			v[idx * 2] = value / 256;   // MSB
			v[idx * 2 + 1] = value % 256; // LSB
            idx++;
        }
    }
}

// --------------------------------------- functions given to students
char toHex(unsigned d)
{
	if (d >= 10)
		return d - 10 + 'a';
	return d + '0';
}

void printIPv6address_hex(const unsigned char* v)
{
	cout << "IPv6 address (hex)  ";
	for (int i = 0; i < 16; i++)
	{
		cout << toHex(v[i] / 16) << toHex(v[i] % 16);
		if (i % 2 && i < 14)
			cout << ':';
	}
	cout << endl;
}

void printIPv6address_bin(const unsigned char* v)
{
	cout << "IPv6 address (bin)  ";
	for (int i = 0; i < 16; i++)
	{
		cout << bitset<8>(v[i]);
		if (i % 2 && i < 14)
			cout << "-";
	}
	cout << endl;
}

void test(const char* a)
{
	cout << "-----------------------------------------------------------\n";
	cout << "IPv6 address (text) " << a << endl;

	unsigned char v[16];  // 16 bytes memory to store the 128-bit IPv6 address
	text2bin_IPv6(a, v);
	printIPv6address_hex(v);
	printIPv6address_bin(v);
}

int main()
{	
	// Test data : IPv6 addresses in text format
	char a1[] = "::";
	char a2[] = "::1";
	char a3[] = "1234:abc:0:78:ff00:0:30:5";
	char a4[] = "2001:db8:a3::200:8";
	char a5[] = "2001:db8::";
	char a6[] = "::101:7000:3:0:4";

	test(a1);
	test(a2);
	test(a3);
	test(a4);
	test(a5);
	test(a6);

	system("pause");
	return 0;
}