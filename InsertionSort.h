#pragma once

template<typename T>
void InsertSort(T *array, int len) {
	int i, j;
	// ǰn��Ԫ���Ѿ��ź��򣬴�ʱ����n+1��Ԫ�ز��뵽���е��������е���
	for (i = 0; i < len; i++) {
		// ��ʱarray(0,i-1)Ϊ�������У�������array[i];
		T value = array[i];
		for (j = i; j > 0; j--) {
			// ��i-1��ʼ��ǰ������value�������Ų������Ϊvalue�����λ��
			if (array[i] < array[i - 1])
				array[j] = array[j - 1];
			else break;
		}
		array[j] = value;
	}
}
