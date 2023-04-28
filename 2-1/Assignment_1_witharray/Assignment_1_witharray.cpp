#define _CRT_SECURE_NO_WARNINGS
#include <iostream>;
using namespace std;
const int MAX = 100;
int arr[MAX];
int check = -1;

void push(int num) {
	if (check == MAX - 1)//stack full
		return;
	check++;
	arr[check] = num;
}

void pop() {
	if (check == -1)//stack empty
		return;
	check--;
}

void top() {
	if (check == -1)//stack empty
		return;
	cout << arr[check] << endl;
}

void print() {
	if (check == -1)//stack empty
		return;
	for (int i = 0; i <= check; i++)
		cout << arr[i] << "\t";
	cout << endl;
}

void empty() {
	if (check == -1)//stack empty
		cout << "1" << endl;
	else
		cout << "0" << endl;
}

int main() {
	char input[100]{};
	int num = 0;

	while (1) {
		cin >> input;
		if (strcmp(input, "push") == 0) {
			cin >> num;
			push(num);
		}
		else if (strcmp(input, "pop") == 0) {
			pop();
		}
		else if (strcmp(input, "top") == 0) {
			top();
		}
		else if (strcmp(input, "print") == 0) {
			print();
		}
		else if (strcmp(input, "empty") == 0) {
			empty();
		}
		else if (strcmp(input, "exit") == 0) {
			break;
		}
	}
	return 0;
}