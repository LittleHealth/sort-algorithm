#pragma once

void CountingSort(unsigned* array, int len, int bound = 10) {
	// bound是array数组当中所有数的上界,上界应当远小于len
	int* count_array = new int[bound];
	unsigned* sorted_array = new unsigned[len];
	int i;

	for (i = 0; i < bound; i++)
		count_array[i] = 0;
	for (i = 0; i < len; i++)
		count_array[array[i]]++;
	for (i = 1; i < bound; i++)
		count_array[i] = count_array[i] + count_array[i - 1];
	for (i = len - 1; i >= 0; i--)
		sorted_array[--count_array[array[i]]] = array[i];
	for (i = 0; i < len; i++)
		array[i] = sorted_array[i];
	delete[] sorted_array;
	delete[] count_array;
}