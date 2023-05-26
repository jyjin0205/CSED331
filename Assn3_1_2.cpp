//VIP는 고속을 좋아하므로, 최대 속도를 구해야 한다.
//벌금 없이 최고 속도

//tuple 개념 : https://notepad96.tistory.com/37


#include <iostream>
#include <stack>
//#include <tuple>
#include <vector>
#include <queue>

typedef struct qElement {
	int x;
	int y;
	long long int value;
}qElement;


struct cmp {
	bool operator()(qElement n1, qElement n2)
	{
		return n1.value < n2.value;
	}
};


using namespace std;



long long int DFS(long long int** arr,bool** visited, int N, int M)
{
	//stack<qElementPair> s;
	priority_queue<qElement, vector<qElement>, cmp> pq;
	qElement start{ 0,0, arr[0][0] };
	pq.push(start);
	visited[0][0] = true;
	long long int speed = arr[0][0];

	qElement output;
	
	while (1)
	{
		if (!pq.empty())
		{
			output = pq.top();
			pq.pop();

			if (output.value != speed)
				speed = output.value;
		}
		else
			return -1;

		visited[output.y][output.x] = true;

		//queue push phase
		if (output.x == M - 1 && output.y == N - 1)
		{
			return speed;
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
					if (n.value>= speed)
					{
						visited[n.y][n.x] = true;

						if (n.x == M - 1 && n.y == N - 1)
						{
							return speed;
						}
					}
					pq.push(n);
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

						if(n.x == M - 1 && n.y == N - 1)
						{
							return speed;
						}
					}
					//s.push(n);
					pq.push(n);
				}
			}
			if (output.y != 0) // 위
			{
				if (!visited[output.y - 1][output.x])
				{
					qElement n;
					n.x = output.x;
					n.y = output.y - 1;
					n.value = arr[output.y-1][output.x];
					if (n.value >= speed)
					{
						visited[n.y][n.x] = true;

						if (n.x == M - 1 && n.y == N - 1)
						{
							return speed;
						}
					}
					pq.push(n);
				}
			}
			if (output.y < N - 1) // 아래
			{
				if (!visited[output.y + 1][output.x])
				{
					qElement n;
					n.x = output.x;
					n.y = output.y + 1;
					n.value = arr[output.y+1][output.x];
					if (n.value >= speed)
					{
						visited[n.y][n.x] = true;

						if (n.x == M - 1 && n.y == N - 1)
						{
							return speed;
						}
					}
					pq.push(n);
				}
			}
		}
	}
}
int main(void)
{
	ios_base::sync_with_stdio(false);
		cin.tie(NULL);
		cout.tie(NULL);

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

		for (int i = 0; i < N; i++)
		{
			arr[i] = new long long int[M];
			visited[i] = new bool[M];
			for (int j = 0; j < M; j++)
			{
				cin >> arr[i][j];
				visited[i][j] = false;
			}
		}

		cout << DFS(arr,visited, N, M) << endl;

		/*
		for (int i = 0; i < N; i++)
		{
			delete[] arr[i];
			delete[] visited[i];
		}

		delete[] arr;
		delete[] visited;
		*/
	}
}