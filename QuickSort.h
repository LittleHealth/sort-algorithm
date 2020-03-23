#pragma once

int Partition(unsigned *array, int start, int end) {
	// 由于我们这里的数据为完全随机的数组，所以这里不需要实现随机快排
	/*
	若是要实现随机快排则只需添加如下代码
		#include <ctime>
		#include <cstdlib>

		srand(time(0));
		int index = rand() % (end-start)+start;
		unsigned temp = array[index];
		array[index] = array[end];
		array[end] = temp;
	*/
	unsigned pivot = array[end];
	int move = start;
	for (int i = start; i < end; i++) {
		if (array[i] < pivot) {
			unsigned temp = array[i];
			array[i] = array[move];
			array[move] = temp;
			move++;
		}
	}
	array[end] = array[move];
	array[move] = pivot;

	return move;
}

void QuickSort(unsigned *array, int start, int end) {
	if (start < end) {
		int index = Partition(array, start, end);

		QuickSort(array, start, index-1);
		QuickSort(array, index + 1, end);
	}
}
