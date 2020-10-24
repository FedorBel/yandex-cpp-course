#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <fstream>
#include <stdexcept>
#include <sstream>

using namespace std;

class Matrix
{
public:
	Matrix()
	{
		row = 0;
		col = 0;
	}

	Matrix(int num_rows, int num_cols)
	{
		Reset(num_rows, num_cols);
	}

	void Reset(int num_rows, int num_cols)
	{
		if (num_rows < 0 || num_cols < 0)
		{
			throw out_of_range("");
		}

		if (num_rows == 0 || num_cols == 0) 
		{
			num_rows = num_cols = 0;
		}

		row = num_rows;
		col = num_cols;

		matrix.assign(num_rows, vector<int>(num_cols));
	}

	int At(int num_rows, int num_cols) const
	{
		if (num_rows < 0 || num_cols < 0 || num_rows > GetNumRows())
		{
			throw out_of_range("");
		}
		else if (num_rows < GetNumRows() && num_cols > GetNumColumns())
		{
			throw out_of_range("");
		}

		return matrix.at(num_rows).at(num_cols);
	}

	int& At(int num_rows, int num_cols)
	{
		if (num_rows < 0 || num_cols < 0 || num_rows > GetNumRows())
		{
			throw out_of_range("");
		}
		else if (num_rows < GetNumRows() && num_cols > GetNumColumns())
		{
			throw out_of_range("");
		}

		return matrix.at(num_rows).at(num_cols);
	}

	int GetNumRows() const
	{
		return row;
	}

	int GetNumColumns() const
	{
		return col;
	}

private:
	int row;
	int col;
	vector<vector<int>> matrix;
};

istream& operator>>(istream& stream, Matrix& mat)
{
	int num_rows = 0;
	int num_cols = 0;

	stream >> num_rows >> num_cols;
	mat.Reset(num_rows, num_cols);

	for (int i = 0; i < mat.GetNumRows(); i++)
	{
		for (int j = 0; j < mat.GetNumColumns(); j++)
		{
			stream >> mat.At(i, j);
		}
	}

	return stream;
}

ostream& operator<<(ostream& stream, const Matrix& mat)
{
	stream << mat.GetNumRows() << " " << mat.GetNumColumns() << endl;

	for (int i = 0; i < mat.GetNumRows(); i++)
	{
		for (int j = 0; j < mat.GetNumColumns(); j++)
		{
			if (j > 0)
			{
				stream << " ";
			}
			stream << mat.At(i, j);
		}
		stream << endl;
	}

	return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns())
	{
		if (lhs.GetNumRows() == 0 && lhs.GetNumColumns() == 0)
		{
			return true;
		}

		for (int i = 0; i < lhs.GetNumRows(); i++)
		{
			for (int j = 0; j < lhs.GetNumColumns(); j++)
			{
				if (lhs.At(i, j) != rhs.At(i, j))
				{
					return false;
				}
			}
		}

		return true;
	}

	return false;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns())
	{
		throw invalid_argument("");
	}
	Matrix result;

	if (lhs.GetNumRows() == 0 && lhs.GetNumColumns() == 0)
	{
		return result;
	}

	result.Reset(lhs.GetNumRows(), lhs.GetNumColumns());

	for (int i = 0; i < lhs.GetNumRows(); i++)
	{
		for (int j = 0; j < lhs.GetNumColumns(); j++)
		{
			result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}

	return result;
}

int main()
{
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << one + two << endl;

	return 0;
}