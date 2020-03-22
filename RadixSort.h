#pragma once
#include <iostream>
using namespace std;
/*
��������Ͱ����ʵ��RadixSort
*/
static int decimal = 10;

// Return the nth bit of number
// for example: 9283, the 2th is 8 and the 4th is 9
int bit(unsigned num, int n) {
	while (n > 0) {
		// ��decimalΪ2�ı��������Ըĳ� num >> 
		num /= decimal;

		n--;
	}
	return num % decimal;
}


void RadixSort(unsigned* array, int len) {
	// create the buckets
	int **bucket = new int*[decimal];
	int *bucket_index = new int[decimal];
	for (int i = 0; i < decimal; i++) {
		bucket_index[i] = 0;
		bucket[i] = new int[len];
	}

	bool next = true;
	int bits = 0;
	int number;
	int max = 1;

	while (next) {
		next = false;
		max = max * decimal;

		for (int j = 0; j < len; j++) {
			number = bit(array[j], bits);
			if (!next && array[j] >= max) {
				next = true;
			}
			// ��array[j]���յ�bitsλ�����ַ����Ӧ��Ͱ��,ͬʱ���±��һ
			bucket[number][bucket_index[number]++] = array[j];
		}

		//cout << "׼�������ַ���Ͱ��, bits=" << bits << endl;
		//for (int i = 0; i < decimal; i++) {
		//	cout << "bucket[" << i << "]:" ;
		//	for (int j = 0; j < bucket_index[i]; j++) {
		//		cout << bucket[i][j] << " ";
		//	}
		//	cout << endl;
		//}
		 // Ȼ���ٽ�Ͱ�е�����ȫ���Ż�array 
		int index = 0;
		for (int i = 0; i < decimal; i++) {
			int l = bucket_index[i];
			for (int j = 0; j < l; j++) {
				array[index++] = bucket[i][j];
			}
			bucket_index[i] = 0;
		}

		bits++;
		//for(int i = 0; i < len; i++) {
		//	cout << array[i] << " ";
		//}
		//cout << endl;
	} // endwhile

	  // free up the buckets
	for (int i = 0; i < decimal; i++) {
		delete[] bucket[i];
	}
	delete[] bucket;
	delete[] bucket_index;
}

void CountingSort(unsigned* array, int len, int bound=10) {
	// bound��array���鵱�����������Ͻ�,�Ͻ�Ӧ��ԶС��len
	int* count_array = new int[bound];
	int* sorted_array = new int[len+1];
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
