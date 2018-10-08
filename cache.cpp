
#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include <iterator>

using namespace std;

const int L1 = 131072; // Размер в байтах
const int L2 = 524288;
const int L3 = 3145728;

int main()
{
#ifdef WIN32
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif
	srand(time(NULL));
	ofstream toFile("time.txt");
	int temp;
	for (int exp = 0; exp < 2; ++exp) {
		toFile << endl << "Эксперимент №" << exp + 1 << "\n\n";
		int size = L1 / 2;
		while (size <= (1.5*L3)) {
			toFile << "Размер массива: " << size / 1024 << " Кбайт" << endl;
			int *array = new int[size / sizeof(int)];
			for (size_t i = 0; i < (size / sizeof(int)); ++i) { // прогрев кэша
				array[i] = i + 1;
			}
			for (size_t i = 0; i < (size / sizeof(int)); ++i) {
				temp = array[i];
			}

			size_t counter = 0;
			auto startTime = chrono::high_resolution_clock::now();
			while (counter != 1000) {
				for (size_t i = 0; i < (size / sizeof(int)); ++i) {
					temp = array[i];
				}
				++counter;
			}
			auto endTime = chrono::high_resolution_clock::now();
			auto diff = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

			toFile << "Проход массива занял: " << diff << " миллисекунд" << endl << endl;
			delete[] array;
			size *= 2;
		}
	}


	for (int exp = 0; exp < 2; ++exp) {
		toFile << endl << "Обратный обход эксперимент №" << exp + 1 << endl;
		int size = L1 / 2;
		while (size <= (1.5*L3)) {
			toFile << "Размер массива: " << size / 1024 << " Кбайт" << endl;
			int *array = new int[size / sizeof(int)];
			for (size_t i = 0; i < (size / sizeof(int)); ++i) { // прогрев кэша
				array[i] = i + 1;
			}
			for (size_t i = 0; i < (size / sizeof(int)); ++i) {
				temp = array[i];
			}

			size_t counter = 0;
			auto startTime = chrono::high_resolution_clock::now();
			while (counter != 1000) {
				for (size_t i = (size / sizeof(int)); i >0; --i) {
					temp = array[i-1];
				}
				++counter;
			}
			auto endTime = chrono::high_resolution_clock::now();
			auto diff = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
			toFile << "Проход массива занял: " << diff << " миллисекунд" << endl << endl;
			delete[] array;
			size *= 2;
		}
	}

	for (int exp = 0; exp < 2; ++exp) {
		toFile << endl << "Случайный обход эксперимент №" << exp + 1 << endl;
		int size = L1 / 2;
		while (size <= (1.5*L3)) {
			{
				toFile << "Размер массива: " << size / 1024 << " Кбайт" << endl;
				int *array = new int[size / sizeof(int)];
				int *random_array = new int[size / sizeof(int)];
				for (size_t i = 0; i < (size / sizeof(int)); ++i) { // прогрев кэша
					array[i] = i + 1;
				}
				for (size_t i = 0; i < (size / sizeof(int)); ++i) {
					temp = array[i];
				}
				vector<int> vec(size / sizeof(int));
				for (size_t i = 0; i < (size / sizeof(int)); ++i) {
					vec[i] = i;
				}
				random_device rd;
				mt19937 g(rd());
				shuffle(vec.begin(), vec.end(), g);
				for (size_t i = 0; i < (size / sizeof(int)); ++i) {
					random_array[i] = vec[i];
				}

				size_t counter = 0;
				auto startTime = chrono::high_resolution_clock::now();
				while (counter != 1000) {
					for (size_t i = 0; i < (size / sizeof(int)); ++i) {
						temp = array[random_array[i]];
					}
					++counter;
				}
				auto endTime = chrono::high_resolution_clock::now();
				auto diff = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
				toFile << "Проход массива занял: " << diff << " миллисекунд" << endl << endl;
				delete[] array;
				delete[] random_array;
				size *= 2;
			}
		}
	}
	toFile.close();	
    return 0;
}

