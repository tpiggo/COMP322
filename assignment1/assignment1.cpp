#include <iostream>
#include <map>
#include <cstdlib>
#include <time.h>
using namespace std;


/**
 * Name: Timothy Piggott
 * ID: 260855765
 * 
 * */

void checkPassword()
{
	string var;
	// Print
	cout << "Please enter your password (must be 8 characters long!):";
	// Take in input
	cin >> var;
	if (var.length() < 8) 
	{
		cout << "Error! Password not long enough (min 8 characters)!\n\n" << endl;
		// Return out of the function
		return;
	}
	// Mapping of the elements in the password
	map<char, int> charMap = map<char, int>();
	bool hasNum = false;
	bool hasSpecial = false;
	// Want to make an array of tuples???? IDK how
	for (size_t i = 0; i < var.length(); i++) {
		if (!hasNum && var[i] >= '0' && var[i] <= '9')
		{
			hasNum = true;
		} 
		else if (!hasSpecial && var[i] == '*' || var[i] == '#' || var[i] == '$') 
		{
			hasSpecial = true;
		}
		// increment the element in the map/
		charMap[var[i]] += 1;
		// more than 2, error!
		if (charMap[var[i]] > 2)
		{
			cout << "Error! Repeated character " << var[i] << " too many times!\n\n" << endl;
			return;
		}
	}
	if (!hasNum)
	{
		cout << "Error! Missing a number in the password!\n\n" << endl;
		// Return out of the function
		return;
	}
	else if (!hasSpecial)
	{
		cout << "Error! Missing a special character *, #, $ in the password!\n\n" << endl;
		return;
	}
	cout << "Password has been accepted!\n\n" << endl;
}
void convertPhonetic()
{
	// Creating the alphabet of phonetics
	const char *phonetics[26] = { "Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel",
		"India", "Juliett", "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo",
		"Sierra", "Tango", "Uniform", "Victor", "Whiskey", "X-ray","Yankee", "Zulu" };
	string var;
	// Print
	cout << "Please enter a word:";
	// Take in input
	cin >> var;
	string phoneticString;
	for (size_t i = 0; i < var.length(); i++)
	{
		// Error checking characters 1 by 1
		if (var[i] < 'A' || (var[i] < 'a' && var[i] > 'Z') || var[i] > 'z')
		{
			cout << "Error! Bad character. Ending!\n\n" << endl;
			return;
		}
		int ascii = (var[i] >= 'A' && var[i] < 'Z')? var[i] - 65: var[i] - 97;
		// append a space if not the first word
		if (i != 0)
		{
			phoneticString.append(" ");
		}
		// append the phonetic replacement
		phoneticString.append(phonetics[ascii]);
	}
	cout << phoneticString << "\n\n\n" << endl;
}

const int rows = 5;
const int cols = 5;
// Used to seed the arrays when filling
int a = 1;

/**
* filling matrix with random numbers
*/
void fillMatrix(int matrix[rows][cols]) 
{
	// add a simple static increment.
	a++;
	// seed the random num generator.
	srand(time(NULL) + a);
	// Create the matrix
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = (int)(rand() % 26);
		}
	}
}

/**
* Iteratively printing the array
*/
void printMatrix(int matrix[rows][cols])
{
	cout << "Printing Matrix:" << endl;
	cout << "------------------------------" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << matrix[i][j];
			if (j < cols - 1)
			{
				cout << " | ";
			}
		}
		cout << endl;
		cout << "------------------------------" << endl;
	}
	cout << "\n\n" << endl;
}

void multiplyMatrices(int matrix_left[rows][cols],
	int matrix_right[rows][cols],
	int matrix_result[rows][cols])
{
	// Need these to persist through the multiplication
	static int i = 0, j = 0, k = 0;

	if (i >= rows) 
	{
		// Done the multiplcation
		return;
	}
	if (j < cols)
	{
		// Checking if we have reached the end of the column, don't multiple
		if (k < cols)
		{
			// Do the matrix multiplication for the [i,j]th cell. 
			if (k == 0)
			{
				matrix_result[i][j] = matrix_left[i][k] * matrix_right[k][j];
			}
			else
			{
				matrix_result[i][j] += matrix_left[i][k] * matrix_right[k][j];
			}
			k++;
			// recursive call
			return multiplyMatrices(matrix_left, matrix_right, matrix_result);
		}
		else
		{
			k = 0;
			j++;
			return multiplyMatrices(matrix_left, matrix_right, matrix_result);
		}
	}
	else
	{
		j = 0; 
		i++;
		return multiplyMatrices(matrix_left, matrix_right, matrix_result);
	}
}

/**
* Iteratively multiplying arrays
*/
void multiplyMatricesIterative(int matrix_left[rows][cols],
	int matrix_right[rows][cols],
	int matrix_result[rows][cols])
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			// Set the [i,j]th cell to zero
			matrix_result[i][j] = 0;
			for (int k = 0; k < rows; k++)
			{
				// Put the sum into the [i,j]th cell
				matrix_result[i][j]  += matrix_left[i][k] * matrix_right[k][j];
			}
		}
	}
}


int main()
{
	// Standard testing functions given by prof.
	checkPassword();
	convertPhonetic();
	int matrix[rows][cols];
	int matrix2[rows][cols];
	int matrix_result[rows][cols];
	fillMatrix(matrix);
	fillMatrix(matrix2);
	printMatrix(matrix);

	multiplyMatrices(matrix, matrix2, matrix_result);
	printMatrix(matrix_result);
	return 0;
}