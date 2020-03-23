#pragma once
#include <iostream>
using namespace std;

int gaps[] = { 0, 1, 8, 23, 77, 281, 1073, 4193, 16577, 65921, 262913,
	1050113, 4197377, 16783361, 67121153};

void ShellSort(unsigned* array, int len) {
	int index = 0;
	int gap = len / 4;
	while (true) {
		if (gaps[index] > gap) break;
		index++;
	}

	while (gap > 0) {
		//cout << "index=" << index << "  gap=" << gap << endl;
		for (int i = gap; i < len; i += gap) {
			unsigned temp = array[i];
			int j = i - gap;
			while (j >= 0 && temp < array[j]) {
				array[j + gap] = array[j];
				//cout << "array[" << j + gap <<"]=" << array[j + gap] << " " << endl;
				j -= gap;
			}
			array[j + gap] = temp;
			/*for (int k = 0; k <= 9; k++) {
				cout << array[k] << " ";
			}
			cout << endl;*/
		}
		index--;
		gap = gaps[index];
	}
}