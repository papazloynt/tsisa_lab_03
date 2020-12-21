#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <utility>

using std::cout;

const double A = 9.;
const double B = 14.;

double func(const double x) {
	return (x * x) * exp(sin(x));
}

double multi_func(const double x) {
	return func(x) * sin(5 * x);
}

double random(const double A, const double B) {
	return A + rand() * 1. / RAND_MAX * (B - A);
}

void print_arg(const int num, const double T,
	const double value, const double function) {
	cout << "| " << std::setw(4) << num << "| " << std::setw(10) << T
		<< "| " << std::setw(11) << value << "| " << std::setw(13) <<
		function << "|" << std::endl;
}

std::pair<double, double> SA(double(*f)(const double x)) {
	
	cout << "| " << std::setw(4) << "N" << "| " << std::setw(10) << "T"
	<< "| " << std::setw(11) << "x" << "| " << std::setw(13) << "f(x)" << "|" << std::endl;

	const double T_min = 0.01;
	double T_i = 10000.0;
	double x_i = random(A, B);
	int i = 0;
	while (T_i > T_min) {
		++i;
		double x_new = random(A, B);
		double delta = f(x_new) - f(x_i);
		if (delta <= 0) {
			x_i = x_new;
		}
		else {
			double rand_probob = random(0, 1);
			double probob = exp(-delta / T_i);
			if (rand_probob < probob) {
				x_i = x_new;
			}
		}
		print_arg(i, T_i, x_i, f(x_i));
		T_i *= 0.95;
	}

	return std::pair<double,double>{ x_i, f(x_i) };
}


int main() {

	srand(time(nullptr));

	cout << "Function 1, interval: [" << A << " " << B << "]" << std::endl;
	
	std::pair<double, double> res1 = SA(func);
	
	cout << "Res: X_min = " << res1.first << " , Fmin = " << res1.second << std::endl;

	cout << "Function 2, interval: [" << A << " " << B << "]" << std::endl;
	
	std::pair<double, double> res2 = SA(multi_func);
	
	cout << "Res: X_min = " << res2.first << " , Fmin = " << res2.second << std::endl;
}

