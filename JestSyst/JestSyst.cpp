// JestSyst.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
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
		int tCount;
		Matrix2x2 temp = Matrix2x2::E();
		cout << "Решение жесткой ситемы:\n" << endl;
		cout << "u'(1) = -500.005 * u(1) + 499.995 * u(2)" << endl;
		cout << "u'(2) = 499.995 * u(1) - 500.005 * u(2)" << endl;
		cout << "Методом РК-II\n"<<endl;
		cout << "Ограничение на шаг: h > 0  and h < 0.002" << endl;
		cout << "Введите шаг: ";
		cin >> h;
		if (h <= 0) { throw 1; }
		int count;
		cout << "Введите количетсво итераций: ";
		cin >> count;
		int interval;
		cout << "Интервал вывода промежуточных значений: ";
		cin >> interval;

		cout << "Введите количество первых значений в таблице: ";
		cin >> tCount;
		vector<Row2> rows;
		rows.push_back({ 7,13 });
		std::cout << 0 << " Current v1 = " << v0.a << "  v2 = " << v0.b << endl;
		Row2 v1 = (E + A * h + A.pow(2)*h*h*0.5)*v0; // явный РК порядка 2 формула (16.4)
		for (int i = 1; i <= count; i++) {
			temp = temp * (E + A * h + A.pow(2)*(h*h*0.5));
			Row2 current = temp * v0;
			if (i <= tCount) {
				rows.push_back(current);
			}
			if (i % interval==0) {
				std::cout << i*h << " Current v1 = " << current.a << "  v2 = " << current.b << endl;
			}
		}
		char a;
		cout << "Подсчет окончен. Вывести таблицу? (y/n) ";
		cin >> a;
		
		if (a == 'y')
		{
			cout << "Добавить точное решение?  (y/n) ";
			char b;
			cin >> b;
			if (b == 'y') {
				vector<Row2> u;
				u.push_back({ 7,13 });
				for (int i = 1; i <= tCount; i++) {
					u.push_back({ -3 * exp(-1000 * i * h) + 10 * exp(-0.01 * i * h),3 * exp(-1000 * i * h) + 10 * exp(-0.01 * i * h) });
				}
				system("cls");
				cout << setw(40) << "Таблица" << endl;
				cout << setw(46) << "Явный метод РК - II, h = " << h << endl;
				cout << endl;
				cout << setprecision(10) << "x" << std::setw(16) << "v1" << std::setw(16) << "v2" << std::setw(16) << "u1" << std::setw(16) << "u2" << endl;;
				for (int i = 0; i < rows.size(); i++) {
					cout << (i)*h << std::setw(16) << std::right << rows[i].a << std::setw(16) << std::right << rows[i].b << std::setw(16)<<u[i].a<< std::setw(16) <<u[i].b<< endl;
				}
			}
			else {
			system("cls");
			cout << setw(30) << "Таблица" << endl;
			cout << setw(36) << "Явный метод РК - II, h = " << h << endl;
			cout << endl;
			cout << setprecision(14) << "x" << std::setw(20) << "v1" << std::setw(25) << "v2" << endl;
		//	cout << 0 << std::setw(20) << v0.a << std::setw(25) << v0.b << endl;
			for (int i = 0; i < rows.size(); i++) {
				cout << (i) * h << std::setw(20) << std::right << rows[i].a << std::setw(25) << std::right << rows[i].b << endl;
			}
		}
		}
	}