// This example presents how to use std::for_each() function with function and function
// object (functor).
// Note that the 3rd argument of for_each() must be a function or the operator() of a
// function object with a single argument, so it can be given WITHOUT an argument inside
// of for_each().

#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <iostream>

void FunctionPrint(int n)
{
	std::cout << n << std::endl;
}

class FunctorPrint
{
public:
	void operator()(int n)
	{
		std::cout << n << std::endl;
	}
};

void FunctionIncrease(int &n)
{
	++n;
	std::cout << n << std::endl;
}

class FunctorIncrease
{
public:
	void operator()(int &n)
	{
		++n;
		std::cout << n << std::endl;
	}
};

void FunctionAdd(int &n, int b)
{
	n = n + b;
	std::cout << n << std::endl;
}

class FunctorAdd
{
public:
	explicit FunctorAdd(int b) : b_(b) {}

	void operator()(int &n)
	{
		n += this->b_;
		std::cout << n << std::endl;
	}

protected:
	int b_;
};

int FunctionReturn(int n)
{
	std::cout << n << std::endl;
	return n;
}

class FunctorReturnMean
{
public:
	explicit FunctorReturnMean() : sum_(0), no_(0) {}

	// Operator which runs repeatedly with the implicit argument.
	void operator()(int n)
	{
		this->sum_ += n;
		this->no_++;
		std::cout << n << std::endl;
	}

	// Return operator which runs only once at the end.
	operator double()
	{
		std::cout << "Functor is returning a value. ";
		return static_cast<double>(this->sum_) / static_cast<double>(this->no_);
	}

protected:
	int sum_;
	unsigned int no_;
};

int main(void)
{
	std::vector<int> i_1(5);
	std::iota(i_1.begin(), i_1.end(), 0);
	//std::array<int, 5> i_1 = {1, 2, 3, 4, 5};
	int n(0);

	// Do something without changing source data; print elements.
	std::cout << "Printing elements" << std::endl;
	// function.
	std::for_each(i_1.begin(), i_1.end(), FunctionPrint);
	std::cout << std::endl;

	// function object.
	FunctorPrint functorPrint;
	std::for_each(i_1.begin(), i_1.end(), functorPrint);
	std::for_each(i_1.begin(), i_1.end(), FunctorPrint());
	std::cout << std::endl;

	// Do something while changing source data; increase elements.
	std::cout << "Increasing elements" << std::endl;

	// function.
	std::for_each(i_1.begin(), i_1.end(), FunctionIncrease);
	std::cout << std::endl;

	// function object.
	FunctorIncrease functorInc;
	std::for_each(i_1.begin(), i_1.end(), functorInc);
	std::for_each(i_1.begin(), i_1.end(), FunctorIncrease());
	std::cout << std::endl;

	// Do something while taking input argument while changing source data; add a preset value to elements.
	std::cout << "Adding a preset value to elements" << std::endl;

	// function.
	//std::for_each(i_1.begin(), i_1.end(), FunctionAdd(2));	// Compile error.

	// function object.
	FunctorAdd functorAdd(2);
	std::for_each(i_1.begin(), i_1.end(), functorAdd);
	std::for_each(i_1.begin(), i_1.end(), FunctorAdd(2));
	std::cout << std::endl;

	// Do something while returning a result at the end of the elements.
	std::cout << "Returning a result at the end of the elements" << std::endl;

	// function object.
	FunctorReturnMean functorMean;
	std::cout << std::for_each(i_1.begin(), i_1.end(), functorMean) << std::endl;
	std::cout << std::for_each(i_1.begin(), i_1.end(), FunctorReturnMean()) << std::endl;
}
