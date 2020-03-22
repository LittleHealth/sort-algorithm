#pragma once
//#include <iostream>
//using namespace std;

template<typename T>
void ShellSort(T* array, int len) {
	for (int gap = len / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < len; i += gap) {
			T temp = array[i];
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
	}
}