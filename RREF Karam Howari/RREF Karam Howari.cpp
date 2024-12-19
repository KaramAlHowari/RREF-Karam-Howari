#include <iostream>
#include <string>
using namespace std;

// Matrix class
class Matrix
{
private:
	int rows;
	int columns;
	double** data;
public:
	// Constructors
	Matrix()
	{
		rows = 0;
		columns = 0;
		data = NULL;
	}
	Matrix(int row, int column)
	{
		rows = row;
		columns = column;
		data = new double* [rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[columns];
		}
	}
	Matrix(const Matrix& m)
	{
		rows = m.rows;
		columns = m.columns;
		data = new double* [rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[columns];
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				data[i][j] = m.data[i][j];
			}
		}
	}

	// Print Matrix function
	void print() const
	{
		for (int i = 0; i < rows; i++)
		{
			cout << "| ";
			for (int j = 0; j < columns; j++)
			{
				if (data[i][j] == 0)
				{
					cout << 0 << " ";
				}
				else
				{
					cout << data[i][j] << " ";
				}
			}
			cout << "|";
			cout << "\n";
		}
	}

	// Enter Matrix function
	void enter()
	{
		// Deallocating memory for data array
		if (data != NULL)
		{
			for (int i = 0; i < rows; i++)
			{
				delete[] data[i];
			}
			delete[] data;
		}

		// prompting the user to enter the number of rows and columns
		setrows();
		setcolumns();

		// Allocating memory for data array
		data = new double* [rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[columns];
		}


		// Prompting the user to enter the matrix
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				double element;
				element = getDoubleInput("Enter the element in row " + to_string(i + 1) + " and column " + to_string(j + 1) + ": ", -10000000000, 10000000000);
				setdata(i, j, element);
			}
		}


		// Checking if the matrix is correct
		int x = 2;
		while (x == 2)
		{
			print();
			x = getIntegerInput("Is this the correct matrix? Enter 1 for yes and 0 for no: ", 0, 1);
			if (x == 1)
			{
				break;
			}
			else if(x == 0)
			{
				x == 2;
				enter();
			}
		}
		
	}

	// Setters
	void setrows()
	{	
		rows = getIntegerInput("Enter the number of rows between 1 and 100: ", 1, 100);
	}
	void setcolumns()
	{	
		columns = getIntegerInput("Enter the number of columns between 1 and 100: ", 1, 100);
	}
	void setdata(int row, int column, double data)
	{
		this->data[row][column] = data;
	}

	// Matrix row operations functions
	void multiplyrow(int row, double scalar)
	{
		for (int i = 0; i < columns; i++)
		{
			data[row][i] *= scalar;
		}
	}
	void addrows(int row1, int row2, double scalar)
	{
		for (int i = 0; i < columns; i++)
		{
			data[row1][i] += scalar * data[row2][i];
		}
	}
	void swaprows(int row1, int row2)
	{
		for (int i = 0; i < columns; i++)
		{
			double temp = data[row1][i];
			data[row1][i] = data[row2][i];
			data[row2][i] = temp;
		}
	}

	// Input validation functions
	int getIntegerInput(string message, int min_value, int max_value)
	{
		string input;
		int number;
		bool validInput = false;
		while (!validInput) {
			cout << message;
			cin >> input;
			try {
				number = stoi(input);
				if (number >= min_value && number <= max_value)
				{
					validInput = true;
				}
				else
				{
					cout << "Invalid input. Please enter a number between " << min_value << " and " << max_value << endl;
				}
			}
			catch (invalid_argument& e) {
				cout << "Invalid input. Please enter a valid number." << endl;
			}
			catch (out_of_range& e) {
				cout << "Invalid input. Please enter a number within the valid range." << endl;
			}
		}
		return number;
	}
	double getDoubleInput(string message, int min_value, int max_value)
	{
		string input;
		int number;
		bool validInput = false;
		while (!validInput) {
			cout << message;
			cin >> input;
			try {
				number = stod(input);
				if (number > min_value && number < max_value)
				{
					validInput = true;
				}
				else
				{
					cout << "Invalid input. Please enter a number between " << min_value << " and " << max_value << endl;
				}
			}
			catch (invalid_argument& e) {
				cout << "Invalid input. Please enter a valid number." << endl;
			}
			catch (out_of_range& e) {
				cout << "Invalid input. Please enter a number within the valid range." << endl;
			}
		}
		return number;
	}


	// Matrix RREF function
	void RREF()
	{
		int lead = 0; // Initialize the lead variable to track the leading column
		for (int r = 0; r < rows; r++)
		{
			if (columns <= lead)
			{
				return; // If the number of columns is less than or equal to the lead, return
			}

			int i = r;
			while (data[i][lead] == 0)
			{
				i++;
				if (i == rows)
				{
					i = r;
					lead++;
					if (columns == lead)
					{
						return; // If the lead exceeds the number of columns, return
					}
				}
			}

			if (i != r)
			{
				swaprows(i, r); // Swap the current row with the row having a non-zero lead element
			}

			if (data[r][lead] != 0)
			{
				multiplyrow(r, 1 / data[r][lead]); // Normalize the lead element to 1
			}

			for (i = 0; i < rows; i++)
			{
				if (i != r)
				{
					addrows(i, r, -data[i][lead]); // Eliminate the lead element from other rows
				}
			}

			lead++; // Move to the next column
		}
	}

	// Destructor
	~Matrix()
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}
};

// Main function
int main()
{
	Matrix m;

	m.enter();

	m.RREF();

	m.print();


	return 0;
}
//add a comment