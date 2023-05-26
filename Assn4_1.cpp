

#include <iostream>
#define min(a,b) a>b ? b : a
#define INF 100000000
using namespace std;



int** roads;
int* intermediate;
int S, E, K;
bool* visitedRoads;
int ans;

void DFS(int N, int currentPlace, int visitedNum)
{
	visitedRoads[currentPlace] = true;

	if (currentPlace == E)
	{
		if (visitedNum == K)
			ans++;
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			if (roads[currentPlace][i] == 1)
			{
				bool flag = true;
				for (int j = 0; j < K; j++)
				{
					if (intermediate[j] == i)
					{
						DFS(N, i, visitedNum + 1);
						flag = false;
					}
				}
				if (flag)
					DFS(N, i, visitedNum);
			}
		}
	}
}

int main(void)
{
	int T;
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		int N, M;
		cin >> N >> M;
		roads = new int* [N];
		visitedRoads = new bool[N];
		for (int j = 0; j < N; j++)
		{
			roads[j] = new int[N];
			visitedRoads[j] = false;
			for (int k = 0; k < N; k++)
			{
				if (j != k)
					roads[j][k] = INF;
				else
					roads[j][j] = 0;
			}
		}


		for (int j = 0; j < M; j++)
		{
			int a, b;
			cin >> a >> b;
			roads[a][b] = 1;
			//roads[b][a] = 1;
		}

		//int S, K, E;
		cin >> S >> E >> K;

		intermediate = new int[K];
		// 도착 전에 K개의 교차점을 지나야 한다.
		for (int j = 0; j < K; j++)
		{
			cin >> intermediate[j];
		}

		ans = 0;

		DFS(N, S, 0);
		
		cout << ans % 20230419 << endl;
	}

}