#include <iostream>

using namespace std;

int midofn(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		int min = i;
		for (int j = i+1; j < n; j++)
		{
			if (a[min] > a[j])
			{
				min = j;
			}
		}
		int flag = a[i];
		a[i] = a[min];
		a[min] = flag;
	}

	return a[n/2];
}

int divide5andfind(int* arr, int arrlen)
{
	//arr을 5개 element로 나눈다
	int* oldarr = new int[arrlen];
	int* newarr = new int[arrlen];
	for (int i = 0; i < arrlen; i++)
	{
		oldarr[i] = arr[i];
	}

	while (1)
	{
		if (arrlen == 1)
			return oldarr[0];

		int f;
		if (arrlen % 5 == 0)
			f = arrlen / 5;
		else
			f = arrlen / 5 + 1;

		int j = 0;

		for (int i = 0; i < arrlen; i = i + 5)
		{
			if (i + 5 < arrlen)
			{
				newarr[j] = midofn(oldarr + i, 5);
				j++;
			}
			else if (i == arrlen - 1) // 1개 남음
			{
				newarr[j] = oldarr[i];
				j++;
			}
			else if (i == arrlen - 2)
			{
				if (oldarr[i] < oldarr[i + 1])
				{
					newarr[j] = oldarr[i];
				}
				else
				{
					newarr[j] = oldarr[i + 1];
				}
				j++;
			}
			else if (i == arrlen - 3)
			{
				newarr[j] = midofn(oldarr + i, 3);
				j++;
			}
			else
			{
				newarr[j] = midofn(oldarr + i, 4);
				j++;
			}

			for (int i = 0; i < j; i++)
				oldarr[i] = newarr[i];

			arrlen = j;
		}
	}
}

int kthElement(int* arr, int arrlen, int k)
{
	int M = divide5andfind(arr, arrlen);
	
	int* A1 = new int[arrlen];
	int A1len = 0;
	int* A2 = new int[arrlen];
	int A2len = 0;
	int Mlen = 0;

	for (int i = 0; i < arrlen; i++)
	{
		if (arr[i] < M)
		{
			A1[A1len++] = arr[i];
		}
		else if (arr[i] > M)
		{
			A2[A2len++] = arr[i];
		}
		else
		{
			Mlen++;
		}
	}

	if (A1len <= k && k < A1len + Mlen)
	{
		// M이 k번째로 작은 원소이다
		return M;
	}
	else if (k < A1len)
	{
		// k가 A1에 있다
		return kthElement(A1, A1len, k);
	}
	else
	{
		// k가 A2에 있다
		return kthElement(A2, A2len, k - A1len - Mlen);
	}
}

int main(void)
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		int n;
		cin >> n;
		int *input = new int[n];
		for (int j = 0; j < n; j++)
		{
			cin >> input[j];
		}
		if(n%2 == 0)
			cout << kthElement(input, n, n / 2-1) << "\n";
		else
			cout << kthElement(input, n, n / 2) << "\n";
	}
	return 0;
}