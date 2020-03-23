/* 
	Author: 张小健 Date: 2020-03-19
	对32位无符号整数的排序效果对比；
	输入数据随机产生，数据范围为[0, 2^32-1]
	输入数据量分别为10~10^9
*/
#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <typeinfo>
#include "InsertionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "ShellSort.h"
#include "RadixSort.h"
using namespace std;

unsigned bin[32];

void genRandom(unsigned* array, int len) {
	srand((unsigned)time(0));
	for (int i = 0; i < len; i++) {
		array[i] = 0;
		for (int j = 0; j < 32; j++) {
			array[i] += (rand() % 2) * bin[j];
		}
	}
}

int main() {
	//利用\sum_{i=0}^{31} (0|1)* 2^i 来生成从0~2^32-1范围内的大小随机数
	bin[0] = 1;
	for (int i = 1; i < 32; i++)
		bin[i] = bin[i - 1] * 2;

	unsigned a[10] = { 2, 9, 8, 0, 1, 3, 6, 5, 7, 4 };
	RadixSort(a, 10);

	for (int i = 0; i < 10; i++) {
		cout << a[i] << " ";
	}

	while (true) {
		int LEN, ipow;
		cin >> ipow;
		if (ipow >= 10 || ipow < 0) break;
		LEN = (int)pow(10, ipow);
		cout << "LEN:" << LEN << endl;
		unsigned *a = new unsigned[LEN];
		unsigned *b = new unsigned[LEN];
		unsigned *c = new unsigned[LEN];
		genRandom(a, LEN);
		for (int i = 0; i < LEN; i++)
			b[i] = a[i];
		auto start = chrono::steady_clock::now();
		if(ipow < 6) InsertSort(b, LEN);
		else cout << "insertionsort timeout: ";
		auto end = chrono::steady_clock::now();
		auto duration = std::chrono::duration<float, std::milli>(end - start);
		cout << "The time of insertionsort is " << duration.count() << "ms" << endl;
		for (int i = 0; i < LEN; i++) {
			c[i] = b[i];
		}

		for (int i = 0; i < LEN; i++)
			b[i] = a[i];
		start = chrono::steady_clock::now();
		QuickSort(b, 0, LEN - 1);
		end = chrono::steady_clock::now();
		duration = std::chrono::duration<float, std::milli>(end - start);
		cout << "The time of quicksort is " << duration.count() << "ms" << endl;
		//bool sorted = true;
		//for (int i = 0; i < LEN; i++) {
		//	if (b[i] != c[i]) {
		//		sorted = false;
		//		break;
		//	}
		//}
		//if (sorted) cout << "sorted correctly" << endl;
		//else cout << "sorted error" << endl;


		for (int i = 0; i < LEN; i++)
			b[i] = a[i];
		start = chrono::steady_clock::now();
		MergeSort(b, 0, LEN - 1);
		end = chrono::steady_clock::now();
		duration = std::chrono::duration<float, std::milli>(end - start);
		cout << "The time of mergesort is " << duration.count() << "ms" << endl;
		//sorted = true;
		//for (int i = 0; i < LEN; i++) {
		//	if (b[i] != c[i]) {
		//		sorted = false;
		//		break;
		//	}
		//}
		//if (sorted) cout << "sorted correctly" << endl;
		//else cout << "sorted error" << endl;


		for (int i = 0; i < LEN; i++)
			b[i] = a[i];
		start = chrono::steady_clock::now();
		ShellSort(b, LEN);
		end = chrono::steady_clock::now();
		duration = chrono::duration<float, milli>(end - start);
		cout << "The time of shellsort is " << duration.count() << "ms" << endl;
		//sorted = true;
		//for (int i = 0; i < LEN; i++) {
		//	if (b[i] != c[i]) {
		//		sorted = false;
		//		break;
		//	}
		//}
		//if (sorted) cout << "sorted correctly" << endl;
		//else cout << "sorted error" << endl;

		for (int i = 0; i < LEN; i++)
			b[i] = a[i];
		start = chrono::steady_clock::now();
		RadixSort(b, LEN);
		end = chrono::steady_clock::now();
		duration = chrono::duration<float, milli>(end - start);
		cout << "The time of radixsort is " << duration.count() << "ms" << endl;
		bool sorted = true;
		for (int i = 0; i < LEN; i++) {
			if (b[i] != c[i]) {
				sorted = false;
				break;
			}
		}
		if (sorted) cout << "sorted correctly" << endl;
		else cout << "sorted error" << endl;

		delete[] a;
		delete[] b;
	}
	return 0;
}
