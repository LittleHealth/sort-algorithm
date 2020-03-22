/* 
	Author: ��С�� Date: 2020-03-19
	��32λ�޷�������������Ч���Աȣ�
	��������������������ݷ�ΧΪ[0, 2^32-1]
	�����������ֱ�Ϊ10~10^9
*/
#include <iostream>
#include "InsertionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "ShellSort.h"
#include "RadixSort.h"
using namespace std;

const int LEN = 10;

bool compare(unsigned x, unsigned y) {
	return x < y;
}


int main() {
	unsigned b[] = { 1, 3, 4, 5, 8, 2, 3, 9, 8, 0};
	unsigned a[LEN] = { 210, 178, 256, 987, 422, 81, 865, 712, 592, 320};
	//insertSort(a, LEN);
	//quickSort<unsigned>(a, 0, LEN - 1, compare);
	//mergeSort(a, 0, LEN - 1);
	//ShellSort(a, LEN);
	//CountingSort(b,10,10);
	cout << bit(210, 1) << endl;
	RadixSort(a, 10);
	for (int i = 0; i < LEN; i++) {
		cout << a[i] << " ";
	}

	return 0;
}
