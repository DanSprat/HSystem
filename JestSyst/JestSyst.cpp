// JestSyst.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
class Row2 {
public:
	long double a;
	long double b;
public:
	Row2(long double a1, long double b1) : a(a1), b(b1) {
	};
	Row2(const Row2& row) {
		a = row.a;
		b = row.b;
	}
	Row2& operator=(const Row2& row) {
		a = row.a;
		b = row.b;
	}
}; // Столбец высоты 2
	class Matrix2x2 {
	private:

		long double arr[4];
	public:
		static Matrix2x2 E() {
			return Matrix2x2(1, 0, 0, 1);
		}
		Matrix2x2(long double a, long double b, long double c, long  double d) {
			arr[0] = a;
			arr[1] = b;
			arr[2] = c;
			arr[3] = d;
		}
		Matrix2x2& operator *=(long double a) {
			for (int i = 0; i < 4; i++) {
				arr[i] *= a;
			}
			return *this;
		}
		Row2 operator*(const Row2 &row) {
			return Row2(arr[0] * row.a + arr[1] * row.b, arr[2] * row.a + arr[3] * row.b);
		}
		Matrix2x2 operator *(long double a) {
			return Matrix2x2(arr[0], arr[1], arr[2], arr[3]) *= a;
		}
		Matrix2x2 operator *(const Matrix2x2 &matrix) {
			Matrix2x2 res(*this);
			res.arr[0] = arr[0] * matrix.arr[0] + arr[1] * matrix.arr[2];
			res.arr[1] = arr[0] * matrix.arr[2] + arr[1] * matrix.arr[3];
			res.arr[2] = arr[2] * matrix.arr[0] + arr[3] * matrix.arr[2];
			res.arr[3] = arr[2] * matrix.arr[1] + arr[3] * matrix.arr[3];
			return res;
		}

		Matrix2x2 pow(int p) {
			if (p < 0) {
				throw 1;
			}
			if (p == 1) {
				return Matrix2x2(*this);
			}
			Matrix2x2 result(*this);

			for (int i = 2; i <= p; i++) {
				result = result * (*this);
			}
			return result;
		}
		Matrix2x2& operator +=(const Matrix2x2& matrix) {
			for (int i = 0; i < 4; i++) {
				arr[i] += matrix.arr[i];
			}
			return(*this);
		}
		Matrix2x2& operator=(const Matrix2x2& matrix) {
			if (this == &matrix) {
				return (*this);
			}
			for (int i = 0; i < 4; i++) {
				arr[i] = matrix.arr[i];
			}
			return (*this);
		}
		Matrix2x2 operator+(const Matrix2x2& matrix) {
			return Matrix2x2(arr[0], arr[1], arr[2], arr[3]) += matrix;
		}
		Matrix2x2(const Matrix2x2 &matrix) {
			for (int i = 0; i < 4; i++) {
				arr[i] = matrix.arr[i];
			}
		}
		~Matrix2x2()
		{
		}
	};// Матрица 2x2

	int main()
	{
		setlocale(LC_ALL, "Russian");
		Matrix2x2 E = Matrix2x2::E(); // Получение единичной матрицы
		Matrix2x2 A(-500.005, 499.995, 499.995, -500.005); 
		Row2 v0(7, 13); // Вектор v0
		double h; // Шаг
		Matrix2x2 temp = Matrix2x2::E();
		cout << "Введите шаг: ";
		cin >> h;
		int count;
		cout << "Введите максимальное количетсво итераций: ";
		cin >> count;
		int interval;
		cout << "Интервал вывода промежуточных значений: ";
		cin >> interval;
		Row2 v1 = (E + A * h + A.pow(2)*h*h*0.5)*v0; // явный РК порядка 2 формула (16.4)
		for (int i = 1; i <= count; i++) {
			temp = temp * (E + A * h + A.pow(2)*(h*h*0.5));
			Row2 current = temp * v0;
			if (i % interval==0) {
				std::cout << i << " Current v1 = " << current.a << "  v2 = " << current.b << endl;
			}
		}
	}