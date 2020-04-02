The most commomly used sort-algorithms implemented in C++
## 排序算法比较(sort-algorithm-compare)

### 1.算法分析

#### 1.1 插入排序

```c++
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
```

可以看出，有双重循环，最坏情况下的算法复杂度为$\Theta(n^2)$，而最好情况下的算法复杂度为$\Theta(n)$。

在空间上不需要额外的空间。

#### 1.2 希尔排序

```c++
int gaps[] = { 0, 1, 8, 23, 77, 281, 1073, ...};
while (gap > 0) {
	insertionsort()
    index--;
    gap = gaps[index];
}
```

希尔排序是实质上是分组插入排序，而其算法复杂度比较依赖于增量序列。

我们这里使用Sedgewick增量序列，$4*4^i + 3*2^i+1$，理论分析上按照此序列的算法最坏时间复杂度是$O(n^(4/3))$。

空间上希尔排序同插入排序一致，不需要额外的辅助空间。

#### 1.3 快速排序

```c++
void QuickSort(unsigned *array, int start, int end) {
	if (start < end) {
		int index = Partition(array, start, end);
		QuickSort(array, start, index-1);
		QuickSort(array, index + 1, end);
	}
}
```

使用分治法的思想，一般情况下，快排的算法复杂度的表达式可以表示为：
$$
T(n) = 2T(n/2)+\Theta(n)
$$
根据主定理，可以求出$T(n) = \Theta(nlgn)$。

最坏情况下，我们可以通过随机选择主元($pivot$)来保证快速排序在排好序的情况下(本次实验不会出现排好序的情况)不会太糟糕。因此算法复杂度$T(n)=O(nlgn)$。

在空间上，快速排序只需要在原有数组的存储空间中操作数据，不会提高空间复杂度。

#### 1.4 归并排序

```c++
void MergeSort(unsigned *a, int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		MergeSort(a, start, mid);
		MergeSort(a, mid + 1, end);
		Merge(a, start, mid, end);
	}
}
```

时间复杂度的分析同快速排序。同时归并排序即使在最坏情况下，也能保证有$\Theta(nlgn)$的稳定算法。

归并排序最大的缺点便是需要借助额外的辅助空间。


#### 1.5 基数排序

```c++
for (int bits = 0; bits < max_bits; bits++) {
	countingsort(array, len, bits);
    //对数组按照bits位上的数字，进行计数排序，算法复杂度很低
}
```

利用计数排序可以实现对每对应的bits上的线性时间排序，若考虑的二进制表示中此bits对应于$r$位的二进制，则其时间复杂度为$\Theta(n+2^r)$。我们实验当中排序无符号整型，有32位，$b=32$。所以对应的时间复杂度为
$$
T(n,b)=\Theta(\frac{b}{r}(n+2^r))
$$

此公式在$r = lgn$时有极值，故复杂度最小为$T(n,b)=\Theta(bn/lgn)$。

### 2. 实验环境

 Operating System: Windows 10 家庭中文版 64-bit

Processor: Intel(R) Core(TM) i5-7200U CPU @ 2.50GHz (4 CPUs), ~2.7GHz 为基于x64的处理器。

Memory: 8192MB RAM  Available OS Memory: 8090MB RAM

VS2017

### 3. 实验数据

以下时间为数组大小为$size$时的排序运行时间，在$size<=10^4$时，均为10或100次运行时间的平均值；在$size>=10^5$，视情况增加一定运行次数求平均值。

| size   | insert | shell | quick | merge | radix |
| ------ | ------ | ----- | ----- | ----- | ----- |
| $10$ | 0.00013 | 0.00012 | 0.00012 | 0.00182 | 0.00416 |
| $10^2 $ | 0.00382 | 0.00459 | 0.00704 | 0.04147 | 0.0102  |
| $10^3 $ | 0.169   | 0.2033  | 0.0504  | 0.2689  | 0.0452  |
| $10^4 $ | 15.26   | 18.336  | 0.612   | 2.773   | 0.375   |
| $10^5 $ | 1565.7  | 1856.1  | 6.796   | 27.888  | 2.534   |
| $10^6 $ | timeout | timeout | 173.51  | 313.94  | 34.03   |
| $10^7 $ | ...     | ...     | 15027.8 | 4545.1  | 1044.4  |
| $10^8 $ | ...     | ...     | 1777220 | 58482.2 | 20126.3 |
| $2*10^8 $ | ...     | ...     | timeout | 124018  | 63784.6 |

<img src="sac.png" style="zoom:150%;" />

### 4.实验结果分析

#### 4.1 插入排序和希尔排序

​	插入排序和希尔排序的运行时间几乎差不多，但是按照理论分析希尔排序对于插入排序是存在一定程度上的优化的，这显然与理论不符合。

​	实际上，我连续设计了`希尔增量`，`Sedgewick增量`优化希尔排序，却未能见效，也就是说最终的运行时间都与插入排序一致。

#### 4.2 快速排序和归并排序

​	快速排序和归并排序的理论时间复杂度均为$\Theta(nlgn)$，而两者也均都能够较插入/希尔排序能够较快运行在$size>=10^6$下的情况。这也验证了我们的理论分析。

​	在$size<=10^6$时，由于归并排序需要更多的内存空间，在内存上有更多的操作，所以较快速排序消耗更多的时间。而后由于$size$过大，出现快速排序较归并排序的时间的情况，这一点我却暂时未能理解

​	在实验中，我原本考虑数组原本便是随机产生，因此快速排序无需进行随机化选择$pivot$，但是考虑到$size> 10^6$时，归并快于快排，因此我试图增加随机化代码，如`三数取中划分`，最终仍是归并更快。

#### 4.3 基数排序

​	我实现了两种基数排序，一种基于桶排序的，一种基于计数排序的，但考虑到桶排序算法需要更多的空间上的操作，因此舍弃（代码保留在`RadixSort.h`）。

​	我们通过实验数据可以看出，基数排序的运行时间较前四种排序的时间要好，验证了我们前面的理论分析$T(n,b) = \Theta(bn/lgn)$的理论分析。

#### 4.4 比较总结

+ 数据量较小，插入排序和希尔排序较好；实现起来简单，空间上也无额外消耗。

+ 数据量较大，快速排序和归并排序较好；
	
	+ 快速排序无需额外空间辅助，唯一缺点便是不稳定
	
	+ 归并排序稳定排序，但需要额外空间
	
+ 排序的数组有稳定的大小范围：基数排序最好；时间复杂度极低，空间消耗也较低。  

### 5. 其他的总结

#### 5.1 随机数的生成

```c++
bin[0] = 1;
for (int i = 1; i < 32; i++)
	bin[i] = bin[i - 1] * 2;
for (int j = 0; j < 32; j++) 
	array[i] += (rand() % 2) * bin[j];
```

​	利用$\sum_{i=0}^{31} rand(0,1)* 2^i$ 来生成从$[0,2^{32}-1]$范围内的大小随机数,这样可以保证随机数在该范围能真正地做到等概率地产生

#### 5.2希尔排序中的$Sedgewick$增量

$Sedgewick$增量的表达式为$4*4^i+3*2^i+1\quad i=0,1,\dots$。可以直接存储为数组，依次至$gap=1$即可

```c++
int gaps[] = { 0, 1, 8, 23, 77, 281, 1073, 4193, 16577, 65921, 262913,
	1050113, 4197377, 16783361, 67121153};
```

#### 5.3随机快排的实现

由于我们这里的数据为完全随机的数组，所以这里不需要实现随机快排，若是要实现随机快排则只需添加如下代码：

```c++
#include <ctime>
#include <cstdlib>
...
srand(time(0));
int index = rand() % (end-start)+start;
unsigned temp = array[index];
array[index] = array[end];
array[end] = temp;
```

若是不嫌复杂，也可以随机选取三个随机数，去对应数组中的中位数作为$pivot$更好。但这都避免不了最坏情况，我们只能优化，平均情况为$\Theta(nlgn)$。

#### 5.4 基数排序中的计数排序

按照理论分析，取$r=lgn$能得到最好的结果，同时对应的$passes$次数应当为$ \lceil\frac{32}{r}\rceil$

创建新数组存储对应$bits$位上的数字，只需要额外开辟与$array$等大的存储空间。

```c++
void RadixSort(unsigned* array, int len) {
	unsigned r = log2(len);
	unsigned base = 1 << r;
	int passes = ceil(UNSIGNED_BIT / r);
    ...
	unsigned* bit_array = new unsigned[len];
	...
}
```



