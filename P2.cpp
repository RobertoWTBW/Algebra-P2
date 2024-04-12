#include <iostream>
#include <fstream>

#pragma GCC optimize ("Ofast") 

using namespace std;

ifstream fin("input1.in");
ofstream fout("output1.out");

void print_operation(int operation[9][9], int n) {
	/**
	* It prints the table of the generated operation
	*@param n - the size of the binary set
	* operation - operation to print
	* @return output needed
	*/
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			fout << "a" << operation[i][j] << " ";
		fout << '\n';
	}
}

bool is_solution(int n, int operation[9][9]) { // i wanted to do this check with light's associative test by only checking the tables for the generative elements, but I could not find the error, as it always gave me a small delta 
	/**
	* It checks if the current operation is associative
	*@param n - the size of the binary set
	* operation - operation to check for associativity
	* @return true if operation is associative
	*/
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				if (operation[i][operation[j][k]] != operation[operation[i][j]][k])
					return 0;
			}
		}
	}
	return 1;
}

void generate(int n, int& res, int operation[9][9], bool option, int i = 1, int j = 1) {
	/**
	* It generates all of the possible operations on the binary set
	*@param n - the size of the binary set
	*res - the number of solutions found
	*operation - operation being constructed
	*option - if we want to print or not the tables found
	*i - the first index (first element in the operation)
	*j - the second index (second element of the operation)
	*@return output needed
	*/
	if (n == 0)
		return;
	if (i == n + 1) {
		if (is_solution(n, operation)) {
			res++;
			if (option)
				print_operation(operation, n), fout << '\n';
		}
	}
	else {
		for (int c = 1; c <= n; c++) {
			operation[i][j] = c;
			if (j < n)
				generate(n, res, operation, option, i, j + 1);
			else
				generate(n, res, operation, option, i + 1, 1);
		}
	}
}

void print_number_of_solutions(int n, int nr_of_solutions) {
	/**
	* It prints the output needed for the first statement
	*@param n - the size of the binary set
	* nr_of_solutions - the number of solutions found
	* @return output needed
	*/
	fout << "1. The number of associative operations on a set A = {";
	if (n > 0)
		cout << "a1";
	for (int i = 2; i <= n; i++) {
		fout << ",a" << i;
	}
	fout << "} is " << nr_of_solutions << "\n";
}

void print_explanation(int n) {
	/**
	* It prints the output needed for the second statement
	* @param n - the size of the binary set
	* @return output needed
	*/
	fout << "2. Identifying an operation table by a matrix, the operation tables of the associative operations on A = {";
	if (n > 0)
		fout << "a1";
	for (int i = 2; i <= n; i++) {
		fout << ",a" << i;
	}
	fout << "} are given by the matrices: \n\n";
}

int main() {
	int n, nr_of_solutions = 0;
	int operation[9][9];
	fin >> n;
	generate(n, nr_of_solutions, operation, 0); //we input 0 as option because we do not want the function to print the operations
	print_number_of_solutions(n, nr_of_solutions);
	print_explanation(n);
	generate(n, nr_of_solutions, operation, 1); //we input 0 as option because we do not want the function to print the operations
	return 0;
}