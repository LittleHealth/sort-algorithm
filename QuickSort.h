#pragma once

template<typename T>
int Partition(T *array, int start, int end) {
	T pivot = array[end];
	int move = start;
	for (int i = start; i < end; i++) {
		if (array[i] < pivot) {
			T temp = array[i];
			array[i] = array[move];
			array[move] = temp;
			move++;
		}
	}
	array[end] = array[move];
	array[move] = pivot;

	return move;
}

template<typename T>
void QuickSort(T *array, int start, int end) {
	if (start < end) {
		int index = Partition(array, start, end);

		QuickSort(array, start, index-1);
		QuickSort(array, index + 1, end);
	}
}
