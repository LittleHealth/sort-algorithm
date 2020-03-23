#pragma once

void InsertSort(unsigned *array, int len) {
	int i, j = 0;
	// 前n个元素已经排好序，此时将第n+1个元素插入到现有的有序数列当中
	for (i = 1; i < len; i++) {
		// 此时array(0,i-1)为有序数列，待插入array[i];
		unsigned value = array[i];
		for (j = i-1; j >= 0; j--) {
			// 从i-1开始向前，若比value大，则向后挪；否则即为value插入的位置
			if (array[j] > value)
				array[j + 1] = array[j];
			else break;
		}
		array[j + 1] = value;
	}
}
