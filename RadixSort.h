#pragma once
#include <iostream>
using namespace std;
static double UNSIGNED_BIT = 32;
static unsigned decimal = 8;
// 8进制情况下，对于无符号整型，需要11次循环，ceil(lg2(2^32-1)/log8)
static int max_bits = 11;

int bit(unsigned num, int n, unsigned dec = decimal) {
	while (n > 0) {
		// 若decimal为2的倍数，可以改成 num >> 
		num /= dec;
		n--;
	}
	return num % dec;
}


void RadixSort_Bucket(unsigned* array, int len) {
	// 构建buckets
	unsigned **bucket = new unsigned*[decimal];
	int *bucket_index = new int[decimal];
	for (unsigned i = 0; i < decimal; i++) {
		bucket_index[i] = 0;
		bucket[i] = new unsigned[len];
	}

	unsigned number;
	//cout << oct;
	for (int bits = 0; bits < max_bits; bits++) {

		for (int j = 0; j < len; j++) {
			number = bit(array[j], bits);
			// 将array[j]按照第bits位的数字放入对应的桶中,同时将下标加一
			bucket[number][bucket_index[number]++] = array[j];
		}

		int index = 0;
		for (unsigned i = 0; i < decimal; i++) {
			int l = bucket_index[i];
			//cout << "bucket[" << i << "]:";
			for (int j = 0; j < l; j++) {
				//cout << bucket[i][j] << " ";
				array[index++] = bucket[i][j];
			}
			//cout << endl;
			bucket_index[i] = 0;
		}
	}

	for (unsigned i = 0; i < decimal; i++)
		delete[] bucket[i];
	delete[] bucket;
	delete[] bucket_index;
}

void CountingSort(unsigned* array, int len, int bits, int bound=10) {
	// bound是array数组当中所有数的上界,上界应当远小于len
	int* count_array = new int[bound];
	unsigned* sorted_array = new unsigned[len + 1];
	unsigned* bit_array = new unsigned[len + 1];
	int i;
	
	for (i = 0; i < bound; i++)
		count_array[i] = 0;
	for (i = 0; i < len; i++) {
		bit_array[i] = bit(array[i], bits);
		count_array[bit_array[i]]++;
	}
	for (i = 1; i < bound; i++)
		count_array[i] = count_array[i] + count_array[i - 1];
	for (i = len - 1; i >= 0; i--)
		sorted_array[--count_array[array[i]]] = array[i];
	for (i = 0; i < len; i++)
		array[i] = sorted_array[i];
	delete[] sorted_array;
	delete[] count_array;
	delete[] bit_array;
}

void RadixSort(unsigned* array, int len) {
	unsigned r = log2(len);
	unsigned base = 1 << r;
	int passes = ceil(UNSIGNED_BIT / r);
	//cout << "len=" << len << " r=" << r << "  log2(len)" << log2(len) << "  base="<< base << "  pass=" << passes << "  floor"<<floor(UNSIGNED_BIT/r) << endl;
	
	int* count_array = new int[base];
	unsigned* sorted_array = new unsigned[len];
	unsigned* bit_array = new unsigned[len];
	
	for (int pass = 0; pass < passes; pass++) {
		int i;
		for (i = 0; i < base; i++)
			count_array[i] = 0;
		for (i = 0; i < len; i++) {
			bit_array[i] = bit(array[i], pass, base);
			count_array[bit_array[i]]++;
		}
		for (i = 1; i < base; i++)
			count_array[i] = count_array[i] + count_array[i - 1];
		for (i = len - 1; i >= 0; i--)
			sorted_array[--count_array[bit_array[i]]] = array[i];
		for (i = 0; i < len; i++)
			array[i] = sorted_array[i];
	}
	delete[] sorted_array;
	delete[] count_array;
	delete[] bit_array;
}
