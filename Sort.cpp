#include <iostream>
#define DATANUM 100

using namespace std;

class Sort {
private:
	int testData[DATANUM];
	int _count;
	int cmpK;
	int transK;
public:
	Sort() {
		for (int i = 0; i < DATANUM; i++) {
			testData[i] = rand();
		}
		
		_count = 0;
		cmpK = 0;
		transK = 0;
	}

	void resetK() {
		cmpK = 0;
		transK = 0;
	}

	void printK() {
		cout << "关键字的比较次数为：" << cmpK << endl;
		cout << "关键字的移动次数为：" << transK << endl;
	}

	void printResult() {
		for (int i = 0; i < DATANUM; i++) {
			cout << testData[i] << "	";
		}
		cout << endl;
	}

	void resetTestData() {
		for (int i = 0; i < DATANUM; i++) {
			testData[i] = rand();
		}
	}

	int calIndex(int i) {
		return i % DATANUM;
	}

	//直接插入排序
	void InsertionSort() {
		int tmp = 0;
		for (int i = 0; i < DATANUM; i++) {
			tmp = testData[i];
			for (int j = 0; j < i; j++) {
				if (tmp < testData[j]) {
					for (int m = i; m > j; m--) {
						testData[m] = testData[m - 1];
						/**/transK++;
					}
					testData[j] = tmp;
					break;
				}
				/**/cmpK++;
			}
		}
		printResult();
	}

	//折半插入排序
	void HalfInsertionSort() {
		int tmp = 0;
		for (int i = 0; i < DATANUM; i++) {
			tmp = testData[i];
			int j = halfSearch(0, i, tmp);
			if (tmp < testData[j]) {
				for (int m = i; m > j; m--) {
					testData[m] = testData[m - 1];
					/**/transK++;
				}
				testData[j] = tmp;
			}
			/**/cmpK++;
		}
		printResult();
	}

	int halfSearch(int min, int max, int num) {
		while (true) {
			/**/cmpK++;
			int half = (max + min) / 2;
			if (testData[half] == num) {
				return half;
			}
			else if (testData[half] < num) {
				if (half != max) {
					min = half + 1;
				}
				else {
					return max;
				}
				half = (max + min) / 2;
			}
			else if (testData[half] > num) {
				if (half != min) {
					max = half - 1;
				}
				else {
					return min;
				}
				half = (max + min) / 2;
			}
			if (min == max) {
				if (testData[half] < num) {
					return half + 1;
				}
				else{
					return half;
				}
			}
		}
	}

	//二路插入排序
	void BinaryInsertionSort() {
		int n = DATANUM;
		int first, last;
		first = last = 0;
		int *b = new int[n];
		b[0] = testData[0];
		for (int i = 1; i < n; i++) {
			/**/cmpK++;
			if (testData[i] < b[first]) {
				first = (first - 1 + n) % n;
				b[first] = testData[i];
				/**/transK++;
			}
			else if (testData[i] >= b[last]) {
				last++;
				b[last] = testData[i];
				/**/transK++;
			}
			else {
				int k;
				for (k = last + 1; testData[i] < b[(k - 1 + n) % n]; k = (k - 1 + n) % n) {
					b[k] = b[(k - 1 + n)%n];
					/**/transK++;
				}
				b[k] = testData[i];
				last++;
			}
		}
		for (int i = 0; i < n; i++) {
			testData[i] = b[(i + first) % n];
		}
		printResult();
		delete[]b;
	}

	//希尔排序
	void ShellSort() {
	    int i, j, gap;
		int n = DATANUM;
	    for (gap = n / 2; gap > 0; gap /= 2) {
			for (i = 0; i < gap; i++) {
				for (j = i + gap; j < n; j += gap) {
					/**/cmpK++;
					if (testData[j] < testData[j - gap]) {
						int temp = testData[j];
						int k = j - gap;
						while (k >= 0 && testData[k] > temp) {
							transK++;
							testData[k + gap] = testData[k];
							k -= gap;
						}
						testData[k + gap] = temp;
					}
				}
			}
        }
		printResult();
	}

	//冒泡排序
	void swap(int array[], int i, int j) {
		/**/transK = transK + 3;
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}

	void BubbleSort() {
		int n = DATANUM;
		for (int i = 0; i < n - 1; i++) {
			for (int j = n - 1; j >= i;j--) {
				/**/cmpK++;
				if (testData[j - 1] > testData[j]) {
					swap(testData, j, j - 1);
				}
			}
		}
		printResult();
	}
	
	//快速排序
	void QuickSort() {
		quickSortF(testData, 0, DATANUM - 1);
		printResult();
	}

	void quickSortF(int arr[], int left, int right) {
		if (left < right) {
			int key = arr[left];
			int i = left, j = right;
			while (i < j) {
				while (arr[j] > key && j > i) {
					/**/cmpK++;
					j--;
				}
				if (i < j) {
					/**/transK++;
					arr[i++] = arr[j];
				}
				while (arr[i] < key && i < j) {
					/**/cmpK++;
					i++;
				}
				if (i < j) {
					/**/transK++;
					arr[j--] = arr[i];
				}
			}
			/**/transK++;
			arr[i] = key;
			quickSortF(arr, left, i - 1);
			quickSortF(arr, i + 1, right);
		}
	}

	//简单选择排序
	void SelectSort() {
		int size = DATANUM;
	    for(int i = 0 ; i < size - 1; ++i) {
	        int index = i;
	        for(int j = i + 1; j < size; ++j) {
				if (testData[j] < testData[index]) {
	                index = j;
					/**/cmpK++;
				}
	        }
	        if(index != i) {
	            int temp = testData[i];
	            testData[i] = testData[index];
	            testData[index] = temp;
				/**/transK = transK + 3;
	        }
	    }
		printResult();
	}

	//堆排序
	void HeapAdjust (int data[], int length, int k) {
		int tmp = data[k];
		int i = 2 * k + 1;
		while (i<length) {
			if (i + 1 < length && data[i] < data[i + 1]) {
				/**/cmpK++;
				i++;
			}
			if (tmp > data[i]) {
				break;
			}
			/**/transK++;
			data[k] = data[i];
			k = i;
			i = 2 * k + 1;
		}
		data[k] = tmp;
	}
	 
	void HeapSort () {
		int length = DATANUM;
		for (int i=length/2-1; i>=0; --i) {
			HeapAdjust(testData, length, i);
		}
		for (int i=length-1; i>=0; --i) {
			transK = transK + 3;
			std::swap(testData[0], testData[i]);
			HeapAdjust(testData, i, 0);
		}
		printResult();
	}

	//归并排序
	void Merge(int a[],int left,int mid,int right) {
		int length1 = mid - left + 1;
		int length2 = right - mid;
		int *l1 = new int[length1];
		int *l2 = new int[length2];
		for (int i = 0; i < length1; ++i) {
			/**/transK++;
			l1[i] = a[left + i];
		}
		for (int j = 0; j < length2; ++j) {
			/**/transK++;
			l2[j] = a[j + mid + 1];
		}
		int i = 0,j = 0;
		int k = length1;
		while (i<length1 && j<length2) {
			cmpK++;
			if (l1[i] < l2[j]) {
				/**/transK++;
				a[left++] = l1[i++];
			}
			else {
				/**/transK++;
				a[left++] = l2[j++];
				if (l2[j] > l1[i]) {
					_count += length1 - i + 1;
				}		
			}
		}
		while (i<length1) {
			/**/transK++;
			a[left++] = l1[i++];
		}
		while (j<length2) {
			/**/transK++;
			a[left++] = l2[j++];
		}
		delete[] l1;
		delete[] l2;
	}

	void MergeSortF(int a[],int left,int right) {
		if (left < right) {
			int mid = (left + right) / 2;
			MergeSortF(a, left, mid);
			MergeSortF(a, mid + 1, right);
			Merge(a, left, mid, right);

		}
	}

	void MergeSort() {
		MergeSortF(testData, 0, DATANUM - 1);
		printResult();
	}


};

int main() {
	Sort sort = Sort();
	cout << "直接插入排序：" << endl;
	sort.InsertionSort();
	sort.printK();
	sort.resetK();
	sort.resetTestData();
	cout << endl;

	cout << "折半插入排序：" << endl;
	sort.HalfInsertionSort();
	sort.printK();
	sort.resetK();
	sort.resetTestData();
	cout << endl;

	cout << "二路插入排序：" << endl;
	sort.BinaryInsertionSort();
	sort.printK();
	sort.resetK();
	sort.resetTestData();
	cout << endl;

	cout << "希尔排序：" << endl;
	sort.ShellSort();
	sort.printK();
	sort.resetK();
	sort.resetTestData();
	cout << endl;

	cout << "冒泡排序：" << endl;
	sort.BubbleSort();
	sort.printK();
	sort.resetK();
	sort.resetTestData();
	cout << endl;

	cout << "快速排序：" << endl;
	sort.QuickSort();
	sort.printK();
	sort.resetK();
	sort.resetTestData();
	cout << endl;

	cout << "简单选择排序：" << endl;
	sort.SelectSort();
	sort.printK();
	sort.resetK();
	sort.resetTestData();
	cout << endl;

	cout << "堆排序：" << endl;
	sort.HeapSort();
	sort.printK();
	sort.resetK();
	sort.resetTestData();
	cout << endl;

	cout << "归并排序：" << endl;
	sort.MergeSort();
	sort.printK();
	sort.resetK();
	sort.resetTestData();
	cout << endl;

	while (true);
	return 0;
}
