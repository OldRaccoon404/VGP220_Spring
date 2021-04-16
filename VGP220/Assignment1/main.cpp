#include <iostream>
#include <assert.h>

//Name:			Artem Sviatenko
//StudentId:	204-2594

int RecursiveMultiplication(int a, int b);
int NonRecursiveFibonacci(int n);
int PrintFibonacciLessThan15(int n);
int printRecursiveFactorialLessThan50(int n);
int DynamicProgrammingFunc(int n);

int main(int argc, char* argv[])
{
	//Tests:
	std::cout << RecursiveMultiplication(2, 5) << std::endl; // Expected result: 10

	std::cout << NonRecursiveFibonacci(5) << std::endl; //Expected result: 5

	PrintFibonacciLessThan15(7); //Expected result: 0 1 1 2 3 5 8 13

	std::cout << std::endl;// ->Adding an extra line

	printRecursiveFactorialLessThan50(10);//Expected result: 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1

	return 0;
}

int RecursiveMultiplication(int a, int b)
{
	//TODO: Write a recursive function to multiply two positive integers
	//without using the operator *
	//You can use addition(+), subtraction(-) and bitShifting(<< or >>), but you
	//should minimize the number of those operations.
	assert(a != 0 && b != 0);

	if (a > b && b > 1)
	{
		--b;
		return a + RecursiveMultiplication(a, b);
	}
	else if (b > a && a > 1)
	{
		--a;
		return b + RecursiveMultiplication(a, b);
	}
	else if (a == 1)
	{
		return b;
	}
	else if (b == 1)
	{
		return a;
	}

}

int NonRecursiveFibonacci(int n)
{
	//TODO: Convert the recursive fibonacci that we did in class
	//to a non recursive method, using a bottom-up approach.
	assert(n >= 0);

	//in a bottom up approach we start from first two numbers than we can assign them
	int number1 = 0;
	int number2 = 1;
	int nextNumber = 0;

	for (int i = 0; i < n - 1; ++i)
	{
		nextNumber = number1 + number2;
		number1 = number2;
		number2 = nextNumber;
	}



	return nextNumber;
}

int PrintFibonacciLessThan15(int n)
{
	//TODO: Create a method that will print all the fibonacci sequence
	//less than 15. The way that you should print is:
	//PrintFibonacciLessThan15(7) -> "0 1 1 2 3 5 8 13". You just need to print what is between "".
	//Don't forget that is less than 15, so use assert if the method is being used outside the
	//boundaries of the function.
	assert(n < 15);
	int number1 = 0;
	int number2 = 1;
	int nextNumber = number1 + number2;

	if (n >= 0) std::cout << number1 << " ";
	if (n >= 1)	std::cout << number2 << " ";

	for (int i = 0; i < n - 1; ++i)
	{
		nextNumber = number1 + number2;
		number1 = number2;
		number2 = nextNumber;
		std::cout << nextNumber << " ";
	}



	return 0;
}

int printRecursiveFactorialLessThan50(int n)
{
	//TODO: Create a method that will print recursive
	//the factorial multiplication format of a number that is less than 50.
	//ASSERT that this function will be used in a correct way.
	//As an example:
	//printRecursiveFactorialLessThan50(10) -> "10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1"
	//The function just prints what is between "".

	assert(n < 50);

	if (n > 0)
	{
		if (n > 1)
		{
			std::cout << n << " * ";
		}
		else
		{
			std::cout << n;

		}
		--n;
		printRecursiveFactorialLessThan50(n);
	}

	return 0;
}

//TODO: Show with dynamic programming, the results and calls for DynamicProgrammingFunc(10)
//Identify repeated calls. This question you can do in a piece of paper drawing the calls
//and results and saving an image on your git repo.
int DynamicProgrammingFunc(int n)
{
	if (n < 5)
	{
		return n - 2;
	}

	return DynamicProgrammingFunc(n - 3) - (DynamicProgrammingFunc(n - 1) * DynamicProgrammingFunc(n - 2));
}