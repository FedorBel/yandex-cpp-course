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

		matrix.clear();
		matrix.resize(num_rows);
		for (auto& rw : matrix)
		{
			rw.resize(num_cols);
		}

		row = num_rows;
		col = num_cols;
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

		return matrix[num_rows][num_cols];
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

		return matrix[num_rows][num_cols];
	}

	int GetNumRows() const
	{
		return row;
	}

	int GetNumColumns() const
	{
		return col;
	}

	friend istream& operator>>(istream& stream, Matrix& mat);
	friend ostream& operator<<(ostream& stream, const Matrix& mat);
	friend bool operator==(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);

private:
	int row;
	int col;
	vector<vector<int>> matrix;
};

istream& operator>>(istream& stream, Matrix& mat)
{
	int num_rows = 0;
	int num_cols = 0;
	stream >> num_rows;
	stream.ignore(1);
	stream >> num_cols;
	mat.Reset(num_rows, num_cols);
	for (auto& rw : mat.matrix)
	{
		for (auto& cl : rw)
		{
			stream >> cl;
		}
	}

	return stream;
}

ostream& operator<<(ostream& stream, const Matrix& mat)
{		
	stream << mat.GetNumRows() << " " << mat.GetNumColumns() << endl;

	for (auto& rw : mat.matrix)
	{
		for (auto& cl : rw)
		{
			stream << cl << " ";
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
				if (lhs.matrix[i][j] != rhs.matrix[i][j])
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
			result.matrix[i][j] = lhs.matrix[i][j] + rhs.matrix[i][j];
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