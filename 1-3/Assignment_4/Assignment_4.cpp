#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

int cnt=0;

void quick_sort(int arr_copy[],int start, int end)
{
	if (start >= end) {//분할 계산 완료
		return;
	}

	int pivot = start;
	int i = pivot + 1; // 왼쪽 출발 지점 
	int j = end; // 오른쪽 출발 지점
	int temp;

	while (i <= j) {//엇갈릴 때까지
		while (i <= end && arr_copy[i] <= arr_copy[pivot]) {
			i++;
		}
		while (j > start && arr_copy[j] >= arr_copy[pivot]) {
			j--;
		}

		if (i > j) {
			// 엇갈림
			temp = arr_copy[j];
			arr_copy[j] = arr_copy[pivot];
			arr_copy[pivot] = temp;
			break;
		}
		else {
			// i번째와 j번째를 스왑
			temp = arr_copy[i];
			arr_copy[i] = arr_copy[j];
			arr_copy[j] = temp;
		}
	}

	cnt++;
	//분할 계산
	quick_sort(arr_copy, start, j - 1);
	quick_sort(arr_copy, j + 1, end);
}

void merge(int sorted[], int arr_copy[], int left, int mid, int right) {
	int i, j, k;
	i = left;//왼
	j = mid + 1;//오
	k = left;//전체

	while (i <= mid && j <= right) {//나눴던 배열 2개에서 작은 수를 파악해 sorted 배열에 저장
		if (arr_copy[i] <= arr_copy[j]) {
			sorted[k] = arr_copy[i];
			i++;
		}
		else {
			sorted[k] = arr_copy[j];
			j++;
		}
		k++;
	}//인덱스값을 매개변수로 전해주기 때문에 sorted배열에 arr_copy배열 안의 숫자가 동일한 자리에 저장됨
	
	//앞 배열 다 저장했으면, 뒷배열에 남아있는 모든 숫자 순차적으로 저장 (이미 정렬 완료되어있음)
	if (i > mid) {
		for (int l = j; l <= right; l++) {
			sorted[k] = arr_copy[l];
			k++;
		}
	}
	//뒷배열 다 저장했으면, 앞배열에 남아있는 모든 숫자 순차적으로 저장 (이미 정렬 완료되어있음)
	else {
		for (int l = i; l <= mid; l++) {
			sorted[k] = arr_copy[l];
			k++;
		}
	}

	//arr_copy로 정렬되어있는 배열 복사
	for (int l = left; l <= right; l++) {
		arr_copy[l] = sorted[l];
	}
}

void merge_division(int sorted[], int arr_copy[], int left, int right)
{
	int middle;//배열 분할

	if (left < right) {
		middle = (left + right) / 2;//배열 분할
		merge_division(sorted, arr_copy, left, middle);//앞부분 정렬 (재귀 호출)
		merge_division(sorted, arr_copy, middle + 1, right);//뒷부분 정렬
		merge(sorted, arr_copy, left, middle, right);//병합
		cnt++;
	}
	//else 배열 크기 1 or 2
}

int main()
{
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	int num;
	cin >> num;

	int *arr = new int[num];
	int* arr_copy = new int[num];

	for (int i = 0; i < num; i++)
		cin >> arr[i];

	int temp,count;
	
	//bubble sort
	count = 0;
	for (int i = 0; i < num; i++)//배열 복사
		arr_copy[i] = arr[i];

	cout << "Bubble Sort : " << endl;

	QueryPerformanceCounter(&start);

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num - 1; j++) {
			if (arr_copy[j] >= arr_copy[j + 1]) {
				temp = arr_copy[j];
				arr_copy[j] = arr_copy[j + 1];
				arr_copy[j + 1] = temp;
			}
			count++;
		}
	}

	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;

	cout << "Sorted order : ";
	for (int i = 0; i < num; i++)
		cout << arr_copy[i] << "   ";
	cout << endl << "Median number : " << arr_copy[num / 2];
	cout << endl << "Number of Repetition : " << count;
	cout << endl << "Time spend : " << diff.QuadPart;
	cout << endl << endl << endl;
	///////////////////////////////////////////
	
	//insertion sort
	count = 0;
	for (int i = 0; i < num; i++)//배열 복사
		arr_copy[i] = arr[i];

	cout << "Insertion Sort : " << endl;

	QueryPerformanceCounter(&start);

	for (int i = 0; i < num; i++) {
		int smallest = i;
		for (int j = i + 1; j < num; j++) {
			if (arr_copy[j] <= arr_copy[smallest])
				smallest = j;
			count++;
		}
		temp = arr_copy[i];
		arr_copy[i] = arr_copy[smallest];
		arr_copy[smallest] = temp;
	}

	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;

	cout << "Sorted order : ";
	for (int i = 0; i < num; i++)
		cout << arr_copy[i] << "   ";
	cout << endl << "Median number : " << arr_copy[num / 2];
	cout << endl << "Number of Repetition : " << count;
	cout << endl << "Time spend : " << diff.QuadPart;
	cout << endl << endl << endl;
	///////////////////////////////////////////

	//quick sort
	for (int i = 0; i < num; i++)//배열 복사
		arr_copy[i] = arr[i];

	cout << "Quick Sort : " << endl;

	QueryPerformanceCounter(&start);

	quick_sort(arr_copy, 0, num-1);
	//count = cnt;

	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;

	cout << "Sorted order : ";
	for (int i = 0; i < num; i++)
		cout << arr_copy[i] << "   ";
	cout << endl << "Median number : " << arr_copy[num / 2];
	cout << endl << "Number of Repetition : " << cnt;
	cout << endl << "Time spend : " << diff.QuadPart;
	cout << endl << endl << endl;
	///////////////////////////////////////////

	//merge sort
	cnt = 0;
	for (int i = 0; i < num; i++)//배열 복사
		arr_copy[i] = arr[i];

	cout << "Merge Sort : " << endl;

	int* sorted = new int[num];//정렬할 것 저장할 배열
	for (int i = 0; i < num; i++)
		sorted[i] = 0;

	QueryPerformanceCounter(&start);

	merge_division(sorted, arr_copy, 0, num - 1);//함수 호출

	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;

	cout << "Sorted order : ";
	for (int i = 0; i < num; i++)
		cout << arr_copy[i] << "   ";
	cout << endl << "Median number : " << arr_copy[num / 2];
	cout << endl << "Number of Repetition : " << cnt;
	cout << endl << "Time spend : " << diff.QuadPart;
	cout << endl << endl << endl;

	delete[] arr;
	delete[] arr_copy;

	return 0;
}