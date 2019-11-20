#include <iostream>
#include "flush_finder.h"

int main() 
{
	int nPairs;
	
	std::cout << "Amount of flush pairs to find:\n";
	std::cin >> nPairs;
	std::cout << "Enable verbose? (y/N)\n";
	std::cin.ignore();
	bool verbose = (std::cin.get() == 'y');

	FlushFinder finder(nPairs, verbose);
	finder.Start();
}