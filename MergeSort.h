#pragma once

void Merge(unsigned* array, int start, int mid, int end) {
 	int n1 = mid - start + 1;
	int n2 = end - mid;
	unsigned *Left = new unsigned[n1 + 1];
	unsigned *Right = new unsigned[n2 + 1];
	for (int i = 0; i < n1; i++)
		Left[i] = array[start + i];
	for (int i = 0; i < n2; i++)
		Right[i] = array[mid + 1 + i];
	Left[n1] = 0xffffffff;
	Right[n2] = 0xffffffff; // 无符号整型的最大值
	int i = 0, j = 0;
	for (int k = start; k <= end; k++) {
		if (Left[i] < Right[j])
			array[k] = Left[i++];
		else
			array[k] = Right[j++];
	}
	delete[] Left; delete[] Right;
}

void MergeSort(unsigned *a, int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		MergeSort(a, start, mid);
		MergeSort(a, mid + 1, end);
		Merge(a, start, mid, end);
	}
}