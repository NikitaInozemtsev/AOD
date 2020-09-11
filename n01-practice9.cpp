
#include <iostream>
#include <math.h>
#include <queue>
#include <ctime>
#include <windows.h>


using namespace std;

int getMax(int arr[], int n) {
	int max = arr[0];
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}

void cousort(int* arr, int n, int mnoj) {
	if (*arr == NULL)
		return;

	int* out = new int[n];
	int i, count[10] = { 0 };

	for (i = 0; i < n; i++)
	{
		count[(arr[i] / mnoj) % 10]++;
	}

	for (i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}

	for (i = n-1; i >= 0; i--)
	{
		out[count[(arr[i] / mnoj) % 10] - 1] = arr[i];
		count[(arr[i] / mnoj) % 10]--;
	}

	for (i = 0; i < n; i++)
	{
		arr[i] = out[i];
	}

}

void startSort(int arr[], int n) {
	int m = getMax(arr, n);
	for (int i = 1; m / i > 0; i *= 10)
	{
		cousort(arr, n, i);
	}
}

int retInt(queue<int> b, int k) {
	int ty = -1;
	queue<int> c = b;
	for (int i = -1; i < k; i++)
	{
		ty = c.front();
		c.pop();
	}
	return ty;
}

queue<int> delInt(queue<int> b, int k) {
	int ty;
	queue<int> a;
	for (int i = 0; i < a.size(); i++)
	{
		int z = b.front();
		if (z != k) {
			a.push(z);
		}
		b.pop();
	}
	return a;
}

bool emp(queue<int> b) {
	return b.empty();
}

bool nEmp(queue<int> b) {
	return !b.empty();
}



queue<int> dob(queue<int> b, int k) {
	b.push(k);
	return b;
}


int main()
{
	srand(time(NULL));

	int i, j;

	queue<queue<int>> a;

	int n;

	for (i = 0; i < 10; i++)
	{
		queue<int> v;
		n = rand() % 100;
		
		for ( j = 0; j < n; j++)
		{
			v.push(rand() % 1000);
		}
		Sleep(1000);
		a.push(v);
	}

	int* x = new int[10];

	for (i = 0; i < 10; i++)
	{
		x = new int[10];
		for ( j = 0; j < 10; j++)
		{
			x[j] = retInt(a.front(), j);
		}

		startSort(x, 10);

		for (int k = 0; k < 10; k++)
		{
			cout << x[k] << endl;
		}
		cout << endl;
	}

	

	return 0;
}
