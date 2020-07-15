
#include <iostream>
#include <math.h> 

int main()
{
	auto func = [](double x) {return 2 * cos(x) + std::pow(x,2);  };
	double h = 0.000000001;
	auto der = [&h](double (*f)(double), double x) {return (f(x + h) - f(x)) / h; };
	auto second_der = [&h,&der](double(*f)(double), double x) {return (der(f, x + h) - der(f, x))/h; };
	std::cout << "derivative of 2cos(pi) + pi^2 = " << der(func, 3.14) << "\n";
	std::cout << "second derivative of 2cos(pi) + pi^2 = " << second_der(func, 3.14) << "\n";
}


