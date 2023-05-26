#include <iostream>
#include <stack>

using namespace std;

//다리를 폭파함으로서 적의 진격을 방해함으로서,
// 다리 하나를 날려서 추격을 따돌릴 방법을 찾는 프로그램
// 다리 : 두 개의 섬과 다리의 길이로 표현, 섬을 분리할 수 있는 방법이 많다면, 가장 짧은 다리를 폭파해야 함. 다리의 길이 출력
// 가능한 다리가 없다면, -1을 출력한다.

bool dfs(int** bridge, int N, int M, int start, int end,int mindest)
{
	// 해당 간선을 삭제하고도 갈 수 있는가

	stack<int> s;
	bool* visited = new bool[N];

	for (int i = 0; i < N; i++)
		visited[i] = false;

	s.push(start);
	
	while (!s.empty())
	{
		int v = s.top();
		s.pop();
		if (!visited[v])
		{
			visited[v] = true;
			for (int i = 0; i < N; i++)
			{
				if (bridge[v][i] != 0)
				{
					s.push(i);
					if (i == end)
						return false;
				}
			}
		}
	}
	return true;
}


int main(void)
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		int N, M; // N은 섬의 수, M은 다리의 수
		// 인접 행렬로 다리...
		cin >> N >> M;

		int** bridge = new int* [N];

		for (int j = 0; j < N; j++)
		{

			bridge[j] = new int[N];
		}

		for (int j = 0; j < M; j++)
		{
			int U, V, L;
			cin >> U >> V >> L;
			bridge[U][V] = L;
			bridge[V][U] = L;
		}

		int mindist = 2147483647;


		
	}
}