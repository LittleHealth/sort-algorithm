#pragma once

void InsertSort(unsigned *array, int len) {
	int i, j = 0;
	// ǰn��Ԫ���Ѿ��ź��򣬴�ʱ����n+1��Ԫ�ز��뵽���е��������е���
	for (i = 1; i < len; i++) {
		// ��ʱarray(0,i-1)Ϊ�������У�������array[i];
		unsigned value = array[i];
		for (j = i-1; j >= 0; j--) {
			// ��i-1��ʼ��ǰ������value�������Ų������Ϊvalue�����λ��
			if (array[j] > value)
				array[j + 1] = array[j];
			else break;
		}
		array[j + 1] = value;
	}
}
