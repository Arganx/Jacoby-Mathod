#include <iostream>

using namespace std;

class Matrix
{
private:
	double**M;
	double**LU;
	int n;
	double**D;
	double**T;
	double*C;
public:
	Matrix(int size)
	{
		n = size;
		M = new double*[n];
		for (int i = 0; i < size; i++)
		{
			M[i] = new double[n];
		}
		D = new double*[n];
		for (int i = 0; i < size; i++)
		{
			D[i] = new double[n];
		}

		T = new double*[n];
		for (int i = 0; i < size; i++)
		{
			T[i] = new double[n];
		}

		LU = new double*[n];
		for (int i = 0; i < size; i++)
		{
			LU[i] = new double[n];
		}
		C = new double[n];
	}

	~Matrix()
	{
		for (int i = 0; i < n; i++)
		{
			delete [] M[i];
		}
		delete[] M;

		for (int i = 0; i < n; i++)
		{
			delete[] D[i];
		}
		delete[] D;

		for (int i = 0; i < n; i++)
		{
			delete[] T[i];
		}
		delete[] T;

		for (int i = 0; i < n; i++)
		{
			delete[] LU[i];
		}
		delete[] LU;
		delete[] C;
	}

	void setM()
	{
		for (int i = 0; i < n; i++)
		{
			cout << "Dla rownania " << i + 1 << endl;
			for (int j = 0; j < n; j++)
			{
				cout << "Podaj x" << j + 1 << endl;
				cin >> M[i][j];
			}
		}
	}

	void displayM()
	{
		cout << "M" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "Dla rownania " << i + 1 << endl;
			for (int j = 0; j < n; j++)
			{
				cout << "x" << j + 1 << " wynosi ";
				cout << M[i][j] << endl;
			}
		}
	}

	void createD_()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i == j)
				{
					D[i][j] = 1/M[i][j];
				}
				else
				{
					D[i][j] = 0;
				}
			}
		}
	}

	void displayD()
	{
		cout << "D" << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << D[i][j] << "  ";
			}
			cout << endl;
		}
	}

	void createLU()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i == j)
				{
					LU[i][j] = 0;;
				}
				else
				{
					LU[i][j] = M[i][j];
				}
			}
		}
	}

	void createT()
	{
		double sum;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				sum = 0;
				for (int z = 0; z < n; z++)
				{
					sum += D[i][z] * -LU[z][j];
				}
				T[i][j] = sum;
			}
			cout << endl;
		}
	}


	void displayT()
	{
		cout << "T" << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << T[i][j] << "  ";
			}
			cout << endl;
		}
	}

	void createC(double* b)
	{
		double sum=0;
		for (int i = 0; i < n; i++)
		{
			sum = 0;
			for (int z = 0; z < n; z++)
			{
				sum += D[i][z] * b[i];
			}
			C[i] = sum;
		}
	}

	void displayC()
	{
		cout << "C" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << C[i] << endl;
		}
	}

	double* newresults(double* old)
	{
		double* result = new double[n];
		double sum = 0;
		for (int i = 0; i < n; i++)
		{
			sum = 0;
			for (int z = 0; z < n; z++)
			{
				sum += T[i][z] * old[z];
			}
			result[i] = sum + C[i];
		}
		return result;
	}

};


int main()
{
	cout << "Podaj liczbe rownan" << endl;
	int size;
	cin >> size;

	cout << "Podaj wyniki" << endl;
	double* b = new double[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Podaj " << i + 1 << " wynik" << endl;
		cin >> b[i];
	}

	cout << "Podaj poczatkowe rozwiazania" << endl;
	double* x = new double[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Podaj " << i + 1 << " rozwiazanie" << endl;
		cin >> x[i];
	}

	cout << "Podaj liczbe iteracji" << endl;
	int ite;
	cin >> ite;

	Matrix start(size);
	start.setM();
	start.displayM();
	start.createLU();
	start.createD_();
	start.displayD();
	start.createT();
	start.displayT();
	start.createC(b);
	start.displayC();

	for (int i = 0; i < ite; i++)
	{
		x = start.newresults(x);
	}
	cout << "Wynik" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << x[i] << endl;
	}

	delete[] b;
	delete[] x;
	system("pause");
}