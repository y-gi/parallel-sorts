#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

#include "selection_sort.cpp"
#include "insertion_sort.cpp"


template<typename RandomAccessIterator>
void print(RandomAccessIterator first, RandomAccessIterator last);


int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Usage: sort [n]\n";
		std::cout << "\tn - integer for the size of container\n";
		exit(1);
	}

	int n = atoi(argv[1]);

	// Populate vector with random numbers
	std::random_device rd;
	std::mt19937 mersenne_engine{rd()};
	std::uniform_int_distribution<int> dist{0, 99};
	auto gen = [&dist, &mersenne_engine]() {
		return dist(mersenne_engine);
	};

	std::vector<int> v1(n);
	std::generate(v1.begin(), v1.end(), gen);
	std::vector<int> v2 = v1;

	// Selection Sort
	std::cout << "Selection Sort\n";
	std::cout << '\t';
	print(v1.begin(), v1.end());
	double time = selection_sort(v1.begin(), v1.end(), std::less<int>{});
	std::cout << '\t';
	print(v1.begin(), v1.end());
	std::cout << "Selection sort completed in " << time << " seconds\n";

	std::cout << '\n';
	
	// Insertion Sort
	std::cout << "Insertion Sort\n";
	std::cout << '\t';
	print(v2.begin(), v2.end());
	time = selection_sort(v2.begin(), v2.end(), std::less<int>{});
	std::cout << '\t';
	print(v2.begin(), v2.end());
	std::cout << "Insertion sort completed in " << time << " seconds\n";
}


template<typename RandomAccessIterator>
void print(RandomAccessIterator first, RandomAccessIterator last) {
	std::cout << "[ ";

	while (first != last) {
		std::cout << *first;
		first++;

		if (first != last) {
			std::cout << ", ";
		} else {
			std::cout << " ";
		}
	}

	std::cout << "]\n";
}
