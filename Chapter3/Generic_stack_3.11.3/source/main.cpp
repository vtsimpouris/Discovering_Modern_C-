// Generic_Stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>

template <typename T>
class stack_member {
public:
	stack_member(const T& data) : data(data), previous(nullptr) {}
	stack_member(const T& data, stack_member<T>* previous) : data(data), previous(previous) {}
	T data;
	stack_member<T>* previous;
};

template <typename T>
class stack {
public:
	stack() : n(0), max(10000000), top_element(nullptr) {}
	~stack() {};

	void push(const T& data) {
		try {
			if (n + 1 > max) {
				throw std::length_error("Error:stack overflow");
			}
			if (n > 0) {
				top_element = new stack_member<T>(data, top_element);
			}
			else
			{
				top_element = new stack_member<T>(data);
			}
		}
		catch (std::length_error& e) {
			std::cerr << e.what() << "\n";
		}
		n += 1;
	}
	
	void pop() {
		try {
			if (top_element == nullptr) {
				throw std::out_of_range("Error:empty stack");
			}
			temp = top_element;
			top_element = top_element->previous;
			delete temp;
			n -= 1;
		}
		catch (std::out_of_range& e) {
			std::cerr << e.what() << "\n";
		}
	}
	T top() {
		try {
			if (top_element == nullptr) {
				throw std::out_of_range("Error:empty stack");
			}
			return top_element->data;
		}
		catch (std::out_of_range& e) {
			std::cerr << e.what() << "\n";
		}
	}
	void clear() {
		try {
			if (top_element == nullptr) {
				throw std::out_of_range("Error:empty stack");
			}
			for (int i = 0; i < n; i++) {
				temp = top_element;
				top_element = top_element->previous;
				delete temp;
			}
			top_element = nullptr;
			n = 0;
		}
		catch (std::out_of_range& e) {
			std::cerr << e.what() << "\n";
		}

	}
	bool full() {
		return n == max;
	}
	bool empty() {
		return n == 0;
	}
	bool size() {
		return n;
	}
	int n;
private:
	stack_member<T>* temp;
	stack_member<T>* top_element;
	
	int max;
};

template <>
class stack<bool> {
public:
	stack() : n(0), max(8), s(0) {}
	~stack() {};
	int n;

	void push(bool data) {
		try {
			if (n + 1 > max) {
				throw std::length_error("Error:stack overflow");
			}
			unsigned char a = (int)data;
			a = a << n;
			s = s | a;
			n += 1;
		}
		catch (std::length_error& e) {
			std::cerr << e.what() << "\n";
		}
		
	}

	void pop() {
		try {
			if (n == 0) {
				throw std::out_of_range("Error:empty stack");
			}
			unsigned char a = 0;
			for (int i = 0; i < n-1; i++) {
				a = a << 1;
				a = a | 1;	
			}
			s = s & a;
			n -= 1;
		}
		catch (std::out_of_range& e) {
			std::cerr << e.what() << "\n";
		}
	}

	bool top() {
		try {
			if (n == 0) {
				throw std::out_of_range("Error:empty stack");
			}
			unsigned r = 0;
			r = 1 & (s >> n - 1);
			return r;
		}
		catch (std::out_of_range& e) {			
			std::cerr << e.what() << "\n";
		}
	}

	void clear() {
		s = 0;
		n = 0;
	}
	bool full() {
		return n == max;
	}
	bool empty() {
		return n == 0;
	}
	bool size() {
		return n;
	}

private:
	int max;
	unsigned char s;
};

int main()
{
	std::cout << "Generic stack:" << "\n";
	std::cout << "\n";
	stack<double> a;
	std::cout << "Push 3 and 7, pop and print top element:" << "\n";
	a.push(3.0);
	a.push(7.0);
	a.pop();
	std::cout << a.top() << "\n";
	std::cout << "Push 3 and 7, clear and print top element (error expected):" << "\n";
	a.push(3.0);
	a.push(7.0);
	a.clear();
	std::cout << "Push 7 fifty times and print top element:" << "\n";
	for (int i = 0; i < 50; i++) {
		a.push(7.0);
	}
	std::cout << a.top() << "\n";
	std::cout << "Check if full() func gives 0 with empty stack  " << "\n";
	a.clear();
	std::cout << "is full: " << a.full() << "\n";
	std::cout << "Clear and already empty stack (error expected) and check if empty() func works" << "\n";
	a.clear();
	std::cout << "is empty: " << a.empty() << "\n";


	std::cout << "\n" << "\n" << "\n";
	std::cout << "Bool specialization for previous stack:" << "\n";
	std::cout << "\n";
	stack<bool> b;
	std::cout << "Push 0 1 1 1 at this order, print top element each time" << "\n";
	b.push(0);
	std::cout << b.top() << "\n";
	b.push(1);
	std::cout << b.top() << "\n";
	b.push(1);
	std::cout << b.top() << "\n";
	b.push(1);
	std::cout << b.top() << "\n";
	std::cout << "Pop and print top element until empty stack error is produced" << "\n";
	b.pop();
	std::cout << b.top() << "\n";
	b.pop();
	std::cout << b.top() << "\n";
	b.pop();
	std::cout << b.top() << "\n";
	b.pop();
	b.pop();
	std::cout << "Clear the stack of bool and pop (error expected)" << "\n";
	b.push(1);
	b.clear();
	b.pop();
	

}
