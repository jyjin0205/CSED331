#include <iostream>

//convolution : 두 함수를 연산해서 세번째 함수를 만듬
// 두 개의 input(n, m,d), d*d kernel
using namespace std;
int main(void)
{
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		int N, M, d;
		cin >> N >> M >> d;

		long long int** I = new long long int* [N];
		
		for (int j = 0; j < N; j++)
		{
			I[j] = new long long int[M];
			for (int k = 0; k < M; k++)
			{
				cin >> I[j][k];
			}
		}

		long long int** DP = new long long int* [N];
		for (int j = 0; j < N; j++)
		{
			DP[j] = new long long int[M - d + 1];
			DP[j][0] = 0;
			for (int k = 0; k < d; k++)
			{
				DP[j][0] += I[j][k];
			}

			for (int k = 1; k < M - d + 1; k++)
			{
				DP[j][k] = DP[j][k - 1] - I[j][k-1] + I[j][k+d-1];
			}
		}

		long long int** ANS = new long long int* [N - d + 1];
		for (int j = 0; j < N - d + 1; j++)
		{
			ANS[j] = new long long int[M - d + 1];
		}
			
		for (int j = 0; j < M - d + 1; j++)
		{
			ANS[0][j] = 0;
			for (int k = 0; k < d; k++)
			{
				ANS[0][j] += DP[k][j];
			}

			for (int k = 1; k < N - d + 1; k++)
			{
				ANS[k][j] = ANS[k - 1][j] - DP[k - 1][j] + DP[k + d - 1][j];
			}
		}

		for (int j = 0; j < N - d + 1; j++)
		{
			for (int k = 0; k < M - d + 1; k++)
			{
				cout << ANS[j][k] << " ";
			}
			cout << "\n";
		}
		
		
	}
}