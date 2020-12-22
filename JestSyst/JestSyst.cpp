// JestSyst.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<ctime>
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
		return *this;
	} 
	Row2() {
		a = 0;
		b = 0;
	}
}; 
// Столбец высоты 2

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


class Result {
public:
	int number;
	double x;
	double h;
	Row2 row;
	Result() {

	}
	Result(int n, double  x, double h, Row2 row) {
		this->number = n;
		this->x = x;
		this->h = h;
		this->row = row;
	}
};
	int main()
	{
		setlocale(LC_ALL, "Russian");
		Matrix2x2 E = Matrix2x2::E(); // Получение единичной матрицы
		Matrix2x2 A(-500.005, 499.995, 499.995, -500.005); 
		Row2 v0(7, 13); // Вектор v0
		double h=0.001; // Шаг
		vector <Result> res_vec;
		res_vec.push_back(Result(0, 0, 0, {7,13}));
		double epsUp = 0.000001;
		double epsDown = epsUp / pow(2, 3);


		Matrix2x2 temp = Matrix2x2::E();
		std::cout << "Программа Попова Даниила из Команда №7 (Мишин - Попов) \n" << endl;
		std::cout << "Решение жесткой ситемы:\n" << endl;
		std::cout << "u'(1) = -500.005 * u(1) + 499.995 * u(2)" << endl;
		std::cout << "u'(2) = 499.995 * u(1) - 500.005 * u(2)" << endl;
		std::cout << "Методом РК-II\n"<<endl;
		std::cout << "Ограничение на шаг:  0 < h < 0.002" << endl;
		int countPogran=0;

		char control;
		std::cout << "Включить контроль? (y или n)";
		std::cin >> control;

		double right_value;
		std::cout << "Введите правую границу: ";
		std::cin >> right_value;

		if (control == 'y') {
			std::cout << "Введите шаг: ";
			std::cin >> h;
			if (h <= 0) { throw 1; }

			int count;
			std::cout << "Введите максимальное  количество шагов: ";
			std::cin >> count;

			int tCount;
			std::cout << "Введите количество первых значений в таблице: ";
			std::cin >> tCount;

			vector<Row2> u;
			u.push_back({ 7,13 });
			double x =h;
			long time = clock();
			for (int i = 1; i <= count; i++) {
				if (x <= right_value  ) {
					if (x == right_value)
						break;
					Row2 perfect = { -3 * exp(-1000 * x) + 10 * exp(-0.01 * x),3 * exp(-1000 * x) + 10 * exp(-0.01 * x) };
					Matrix2x2 save = temp;
					temp = temp * (E + A * h + A.pow(2) * (h * h * 0.5));
					Row2 current = temp * v0;
					double abs1 = abs(current.a - perfect.a);
					if (abs1 <=epsUp) {
						if (x < 0.1) {
							countPogran++;
						}
						res_vec.push_back({ i,x,h,{current.a,current.b} });
						u.push_back(perfect);
						if (abs1 <= epsDown) {
							h =h* 2;
							if (h >= 0.002) {
								h = 0.002 - epsUp;
							}
						}
						x += h;
						if (x > 8500) {
							int  g = 0;
						}
					}
					else {
						if (abs1 >= epsUp ) {
							x -= h;
							h = h / 2;
							x += h;
							i--;
							temp = save;
						}
					}
				}
				else {
					x = x - h;
					h = right_value- x;
					x = right_value;
					Row2 perfect = { -3 * exp(-1000 * x) + 10 * exp(-0.01 * x),3 * exp(-1000 * x) + 10 * exp(-0.01 * x) };
					temp = temp * (E + A * h + A.pow(2) * (h * h * 0.5));
					Row2 current = temp * v0;
					u.push_back(perfect);
					res_vec.push_back({ i, x, h, {current.a,current.b} });
					x += h;
				}
			}
			time = clock() - time;
			char a;
			std::cout << "Подсчет окончен. Вывести таблицу? (y/n) ";
			std::cin >> a;
			if (a == 'y') {
				std::system("cls");
				std::cout << setw(60) << "Таблица" << endl;
				std::cout << setw(66) << "Явный метод РК - II" << endl;
				std::cout << setprecision(10) <<"N"<<std::setw(20) << "x" << std::setw(20) << "h" << std::setw(20) << "v1" << std::setw(20) << "v2" << std::setw(16) << "u1" << std::setw(16) << "u2" << std::setw(25) << "Гл. погрешность(1)" << std::setw(20) << "Гл.погрешность(2)" << endl;
			}
			int curve = 2;
			double max_pogran = 0;
			for (int i = 0; i <= countPogran; i++) {
				if (i <= tCount || i % 30 == 0 || countPogran-i<100) {
					std::cout << setprecision(10) << res_vec[i].number << std::setw(20) << res_vec[i].x << std::setw(20) << res_vec[i].h << std::setw(20) << res_vec[i].row.a << std::setw(20) << res_vec[i].row.b << std::setw(16) << u[i].a << std::setw(16) << u[i].b << std::setw(25) << res_vec[i].row.a - u[i].a << std::setw(20) << res_vec[i].row.b - u[i].b << endl;
				}
				if (max_pogran < abs(res_vec[i].row.a - u[i].a)) {
					max_pogran = abs(res_vec[i].row.a - u[i].a);
				}
			}
			double max_not_pogran = 0;
			for (int i = countPogran + 1; i < u.size(); ++i) {
					if ((i % curve == 0)) {
						std::cout << setprecision(10) << res_vec[i].number << std::setw(20) << res_vec[i].x << std::setw(20) << res_vec[i].h << std::setw(20) << res_vec[i].row.a << std::setw(20) << res_vec[i].row.b << std::setw(16) << u[i].a << std::setw(16) << u[i].b << std::setw(25) << res_vec[i].row.a - u[i].a << std::setw(20) << res_vec[i].row.b - u[i].b << endl;
						curve *= 2;
					}
					if (max_not_pogran < abs(res_vec[i].row.a - u[i].a)) {
						max_not_pogran = abs(res_vec[i].row.a - u[i].a);
					}
			}
			std::cout << setprecision(10) << res_vec[res_vec.size() - 1].number << std::setw(20) << res_vec[res_vec.size() - 1].x << std::setw(20) << res_vec[res_vec.size() - 1].h << std::setw(20) << res_vec[res_vec.size() - 1].row.a << std::setw(20) << res_vec[res_vec.size() - 1].row.b << std::setw(16) << u[res_vec.size() - 1].a << std::setw(16) << u[res_vec.size() - 1].b << std::setw(25) << res_vec[res_vec.size() - 1].row.a - u[res_vec.size() - 1].a << std::setw(20) << res_vec[res_vec.size() - 1].row.b - u[res_vec.size() - 1].b << endl;
			std::cout << "\nМаксимальная погрешность на погран. слое: " << max_pogran<<endl;
			std::cout << "Максимальная погрешность остальном участке: " << max_not_pogran << endl;
			std::cout << "Задача была решена с погрешностью " << max(max_pogran, max_not_pogran) << " за " << time / CLOCKS_PER_SEC << "секунд "<<endl;
		}
		else {
			std::cout << "Введите шаг: ";
			std::cin >> h;
			if (h <= 0) { throw 1; }

			int count;
			std::cout << "Введите максимальное  количество шагов: ";
			std::cin >> count;

			int tCount;
			std::cout << "Введите количество первых значений в таблице: ";
			std::cin >> tCount;

			int interval;
			std::cout << "Введите интервал вывода промежуточных значений";
			std::cin >> interval;

			vector<Row2> u;
			for (int i = 1; i <= count; ++i) {
				temp = temp * (E + A * h + A.pow(2) * (h * h * 0.5));
				Row2 current = temp * v0;
				Row2 perfect = { -3 * exp(-1000 * i*h) + 10 * exp(-0.01 * i*h),3 * exp(-1000 * i*h) + 10 * exp(-0.01 * i*h) };
				u.push_back(perfect);
				res_vec.push_back({ i,i*h, h, {current.a,current.b} });
				
			}

			std::cout << setw(60) << "Таблица" << endl;
			std::cout << setw(66) << "Явный метод РК - II, h = " << h << endl;
			std::cout << endl;
			std::cout << setprecision(10) << "x" << std::setw(20) << "v1" << std::setw(20) << "v2" << std::setw(16) << "u1" << std::setw(16) << "u2" << std::setw(25) << "Гл. погрешность(1)" << std::setw(20) << "Гл.погрешность(2)" << endl;
			for (int i = 0; i <= tCount; i++) {
				std::cout << setprecision(10) << res_vec[i].x << std::setw(20) << res_vec[i].row.a << std::setw(20) << res_vec[i].row.b << std::setw(16) << u[i].a << std::setw(16) << u[i].b << std::setw(25) << res_vec[i].row.a - u[i].a << std::setw(20) << res_vec[i].row.b - u[i].b << endl;
			}
			std::cout << setprecision(10) << res_vec[res_vec.size()-1].x << std::setw(20) << res_vec[res_vec.size() - 1].row.a << std::setw(20) << res_vec[res_vec.size() - 1].row.b << std::setw(16) << u[res_vec.size() - 1].a << std::setw(16) << u[res_vec.size() - 1].b << std::setw(25) << res_vec[res_vec.size() - 1].row.a - u[res_vec.size() - 1].a << std::setw(20) << res_vec[res_vec.size() - 1].row.b - u[res_vec.size() - 1].b << endl;

		}
		/*
		

		vector<Row2> rows;
		rows.push_back({ 7,13 });
		Row2 v1 = (E + A * h + A.pow(2)*h*h*0.5)*v0; // явный РК порядка 2 формула (16.4)
		for (int i = 1; i <= count; i++) {
			temp = temp * (E + A * h + A.pow(2)*(h*h*0.5));
			Row2 current = temp * v0;
			if (i <= tCount) {
				rows.push_back(current);
			}  else if (i % interval == 0 ) {
				rows.push_back(current);
			}
		
		}
		char a;
		std::cout << "Подсчет окончен. Вывести таблицу? (y/n) ";
		std::cin >> a;
		
		if (a == 'y')
		{
			std::cout << "Добавить точное решение?  (y/n) ";
			char b;
			std::cin >> b;
			if (b == 'y') {
				vector<Row2> u;
				u.push_back({ 7,13 });
				for (int i = 1; i <= tCount; i++) {
					u.push_back({ -3 * exp(-1000 * i * h) + 10 * exp(-0.01 * i * h),3 * exp(-1000 * i * h) + 10 * exp(-0.01 * i * h) });
				}
				
				system("cls");
				std::cout << setw(60) << "Таблица" << endl;
				std::cout << setw(66) << "Явный метод РК - II, h = " << h << endl;
				std::cout << endl;
				std::cout << setprecision(10) << "x" << std::setw(20) << "v1" << std::setw(20) << "v2" << std::setw(16) << "u1" << std::setw(16) << "u2" << std::setw(25)<<"Гл. погрешность(1)"<< std::setw(20)<<"Гл.погрешность(2)"<< endl;
				for (int i = 0; i <= tCount; i++) {
					std::cout << (i)*h << std::setw(20) << std::right << rows[i].a << std::setw(20) << std::right << rows[i].b << std::setw(16)<<u[i].a<< std::setw(16) <<u[i].b<< std::setw(20)<< rows[i].a- u[i].a<< std::setw(20)<< rows[i].b - u[i].b<< endl;
				}
			}
			else {
			system("cls");
			std::cout << setw(36) << "Таблица" << endl;
			std::cout << setw(42) << "Явный метод РК - II, h = " << h << endl;
			std::cout << endl;
			std::cout << setprecision(14) << "x" << std::setw(30) << "v1" << std::setw(30) << "v2" << endl;
			for (int i = 0; i <=tCount; i++) {
				std::cout << (i) * h << std::setw(30) << std::right << rows[i].a << std::setw(30) << std::right << rows[i].b << endl;
			}
		
		}
		}
		*/
	}