
#include <iostream>
#include <stack>
//#include <tuple>
#include <vector>
#include <queue>
#include <algorithm>

typedef struct qElement {
	int x;
	int y;
	long long int value;
}qElement;


using namespace std;

void visitedClear(bool** visited, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			visited[i][j] = false;
		}
	}
	return;
}

bool DFS(long long int** arr, bool** visited, long long int speed, int N, int M)
{
	//stack<qElementPair> s;
	queue<qElement> q;
	qElement start{ 0,0, arr[0][0] };
	q.push(start);

	if (arr[0][0] < speed)
		return false;
	visited[0][0] = true;

	qElement output;

	while (!q.empty())
	{
		output = q.front();
		q.pop();

		visited[output.y][output.x] = true;

		if (output.x == M - 1 && output.y == N - 1)
		{
			visitedClear(visited, N, M);
			return true;
		}
		else
		{
			// 속도 제한이 있는 애들이라도 일단 넣는다
			if (output.x != 0) // 왼쪽
			{
				if (!visited[output.y][output.x - 1])
				{
					qElement n;
					n.x = output.x - 1;
					n.y = output.y;
					n.value = arr[output.y][output.x - 1];
					if (n.value >= speed)
					{
						visited[n.y][n.x] = true;

						if (n.x == M - 1 && n.y == N - 1)
						{
							visitedClear(visited, N, M);
							return true;
						}
						q.push(n);
					}
				}
			}
			if (output.x < M - 1) // 오른쪽
			{
				if (!visited[output.y][output.x + 1])
				{
					qElement n;
					n.x = output.x + 1;
					n.y = output.y;
					n.value = arr[output.y][output.x + 1];
					if (n.value >= speed)
					{
						visited[n.y][n.x] = true;

						if (n.x == M - 1 && n.y == N - 1)
						{
							visitedClear(visited, N, M);
							return true;
						}
						q.push(n);
					}
				}
			}
			if (output.y != 0) // 위
			{
				if (!visited[output.y - 1][output.x])
				{
					qElement n;
					n.x = output.x;
					n.y = output.y - 1;
					n.value = arr[output.y - 1][output.x];
					if (n.value >= speed)
					{
						visited[n.y][n.x] = true;

						if (n.x == M - 1 && n.y == N - 1)
						{
							visitedClear(visited, N, M);
							return true;
						}
						q.push(n);
					}
				}
			}
			if (output.y < N - 1) // 아래
			{
				if (!visited[output.y + 1][output.x])
				{
					qElement n;
					n.x = output.x;
					n.y = output.y + 1;
					n.value = arr[output.y + 1][output.x];
					if (n.value >= speed)
					{
						visited[n.y][n.x] = true;

						if (n.x == M - 1 && n.y == N - 1)
						{
							visitedClear(visited, N, M);
							return true;
						}
						q.push(n);
					}
				}
			}
		}
	}
	visitedClear(visited, N, M);
	return false;
}


long long int speedDivide(long long int** arr, bool** visited,int N, int M, long long int start, long long int end)
{
	long long int mid = (start+end)/2;
	bool beforeDFS = false;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (DFS(arr, visited, mid, N, M)) // mid를 올려서 봐야 한다.
		{

			start = mid + 1;
			beforeDFS == true;
		}
		else // mid를 내려서 봐야 한다
		{
			start = start - 1;
			end = mid - 1; 
			beforeDFS = false;
		}
	}
	return mid;
}


int main(void)
{

	int t;
	cin >> t;

	for (int i = 0; i < t; i++)
	{
		int N, M;
		cin >> N >> M;
		long long int** arr;
		bool** visited;
		arr = new long long int* [N];
		visited = new bool* [N];
		//long long int* speeds = new long long int[N * M];
		long long int maxSpeed = -1;

		for (int i = 0; i < N; i++)
		{
			arr[i] = new long long int[M];
			visited[i] = new bool[M];
			for (int j = 0; j < M; j++)
			{
				cin >> arr[i][j];
				visited[i][j] = false;
				if (arr[i][j] > maxSpeed)
					maxSpeed = arr[i][j];
			}
		}

		cout << speedDivide(arr,visited, N, M, 1, maxSpeed) << endl;
		
	}
}