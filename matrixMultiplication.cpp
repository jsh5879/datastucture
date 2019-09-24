/* matrixMultiplication.cpp - 2차원 행렬을 1차원으로 저장, + 구현
학번: 201524561
이름: 장석환
Github ID: jsh5879
Matrix의 <<, >>, +, -, *의 구현
operator *()의 구현시에 transpose 결과를 사용
comments로 표시된 함수는 사용하지 않음
*/

#include <iostream>
using namespace std;
#include <stdlib.h>

class Matrix {
public:
	Matrix(int row, int col);
	//int GetData();
	Matrix Transpose();
	//int Display();
	//Matrix Add(Matrix b);
	//Matrix Multiply(Matrix b);
	int CompareRowCol(Matrix b);
	friend istream & operator >> (istream& stream, Matrix& m);
	friend ostream & operator << (ostream& stream, Matrix& m);
	Matrix& operator+(const Matrix& m);
	Matrix& operator-(const Matrix& m);
	Matrix& operator*(const Matrix& m);
	Matrix& operator=(const Matrix& m);
	int getRow() { return rows; }
	int getCol() { return cols; }

private:
	int rows, cols;
	//int Term[rows][cols];
	int* Term;//the add 2.6ress of a[i][j] = 0 + i * cols + j => Fig2.6
};

Matrix::Matrix(int row, int col) : rows(row), cols(col)
{
	Term = new int[rows * cols];
}
/*
int Matrix::GetData() {
	int input_value;
	cout << "rows = " << rows << "  cols = " << cols << endl;
	for (int j = 0; j < rows * cols; j++)
	{
		cout << "term value = ";
		cin >> input_value;
		cout << " " << endl;
		Term[j] = input_value;
	}
	return 0;
}
*/
Matrix Matrix::Transpose() {
	Matrix b(cols, rows);
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			b.Term[(rows * c) + r] = Term[(cols * r) + c];
	return b;
}
/*
Matrix Matrix::Multiply(Matrix b) {
	if (cols != b.rows) cout << "Incompatible matrices" << endl;
	Matrix bXpose = b.Transpose();
	Matrix d(rows, b.cols);
	// 학생들이 code 작성
	return d;
}
*/
int Matrix::CompareRowCol(Matrix b) {
	if (cols != b.rows) return 1;
	else return 0;
}

/*
int Matrix::Display() {
	int n;
	n = rows * cols;
	for (int i = 0; i < rows; i++)
	{
		cout << endl;
		for (int j = 0; j < cols; j++)
			cout << Term[i * cols + j] << " ";
	}
	cout << endl;
	return 0;
}
*/

istream& operator >> (istream& stream, Matrix& m) {
	int input_value;
	for (int j = 0; j < m.getRow() * m.getCol(); j++)
	{
		stream >> input_value;
		m.Term[j] = input_value;
	}
	return stream;
}


ostream& operator << (ostream& stream, Matrix& m) {
	int n;
	n = m.getRow() * m.getCol();
	for (int i = 0; i < m.getRow(); i++)
	{
		stream << endl;
		for (int j = 0; j < m.getCol(); j++)
			stream << m.Term[i * m.getCol() + j] << " ";
	}
	stream << endl;
	return stream;
}

Matrix& Matrix::operator+(const Matrix& m)
{
	Matrix m3(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			m3.Term[i * cols + j] = Term[i * cols + j] + m.Term[i * cols + j];
		}
	}
	return m3;
}

Matrix& Matrix::operator-(const Matrix& m)
{
	Matrix m3(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			m3.Term[i * cols + j] = Term[i * cols + j] - m.Term[i * cols + j];
		}
	}
	return m3;
}
/*
Matrix Matrix::Multiply(Matrix b) {
	if (cols != b.rows) cout << "Incompatible matrices" << endl;
	Matrix bXpose = b.Transpose();
	Matrix d(rows, b.cols);
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < b.cols; c++) {
			d.Term[(b.cols * r) + c] = 0;
			for (int i = 0; i < cols; i++)
				d.Term[(b.cols * r) + c] += Term[(cols * r) + i] * bXpose.Term[(bXpose.cols * c) + i];
		}
	return d;
}*/

Matrix& Matrix::operator*(const Matrix& m)
{
	if (cols != m.rows) cout << "Incompatible matrices" << endl;
	Matrix bXpose = Transpose();
	Matrix d(rows, m.cols);
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < m.cols; c++) {
			d.Term[(m.cols * r) + c] = 0;
			for (int i = 0; i < cols; i++)
				d.Term[(m.cols * r) + c] += Term[(cols * r) + i] * bXpose.Term[(bXpose.cols * c) + i];
		}
	return m;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	Matrix m3(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Term[i * cols + j] = m.Term[i * cols + j];
		}
	}
	return m3;
}


int main()
{
	Matrix a(2, 3);
	Matrix b(3, 4);
	Matrix c(2, 4), d(2, 4);

	cout << "Enter first matrix: " << endl;
	//a.GetData();
	cin >> a;
	cout << "Enter second matrix: " << endl;
	//b.GetData();
	cin >> b;

	cout << "Display first matrix: " << endl;
	//a.Display();
	cout << a;
	cout << "Display second matrix: " << endl;
	//b.Display();
	cout << b;

	Matrix d(4, 3);
	d = b.Transpose();
	cout << "Transpose() of Matrix b" << endl;
	//d.Display();
	cout << d;

	/* If colum of first matrix in not equal to row of second matrix, asking user to enter the size of matrix again. */
	if (a.CompareRowCol(b))
	{
		cout << "Error! column of first matrix not equal to row of second.";
		cout << "Enter rows and columns for first matrix: ";
	}
	//c = a.Multiply(b);
	c = a * d;//d는 transpose 행렬
	cout << "Multiply of Matrix a,b" << endl;
	//c.Display();
	cout << c;
	cin >> d;
	cout << c + d << c - d;
	system("pause");
	return 0;
}

