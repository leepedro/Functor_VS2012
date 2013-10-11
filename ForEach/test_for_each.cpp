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
	FunctorAdd(int b) : b_(b) {}

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

class FunctorReturn
{
public:
	void operator()(int n)
	{
		std::cout << n << std::endl;
		// TODO: How to take an argument and return a value?
	}
};

int main(void)
{
	std::vector<int> i_1(5);
	std::iota(i_1.begin(), i_1.end(), 0);
	//std::array<int, 5> i_1 = {1, 2, 3, 4, 5};
	int n(0);

	// Print elements.
	// function.
	std::for_each(i_1.begin(), i_1.end(), FunctionPrint);
	//n = std::for_each(i_1.begin(), i_1.end(), FunctionReturn());
	std::cout << std::endl;

	// function object.
	FunctorReturn functorRet;
	std::for_each(i_1.begin(), i_1.end(), functorRet);
	//n = std::for_each(i_1.begin(), i_1.end(), functorRet);
	std::cout << std::endl;

	// Change elements by increasing.
	// function.
	std::for_each(i_1.begin(), i_1.end(), FunctionIncrease);
	std::cout << std::endl;

	// function object.
	FunctorIncrease functor2;
	std::for_each(i_1.begin(), i_1.end(), functor2);
	std::cout << std::endl;

	// Change elements by adding the given parameter to it.
	// function.
	//std::for_each(i_1.begin(), i_1.end(), FunctionAdd(2));	// Compile error.

	// function object.
	FunctorAdd functor3(2);
	std::for_each(i_1.begin(), i_1.end(), functor3);
}
