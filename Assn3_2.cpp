#include <iostream>
#include <stack>

using namespace std;

//�ٸ��� ���������μ� ���� ������ ���������μ�,
// �ٸ� �ϳ��� ������ �߰��� ������ ����� ã�� ���α׷�
// �ٸ� : �� ���� ���� �ٸ��� ���̷� ǥ��, ���� �и��� �� �ִ� ����� ���ٸ�, ���� ª�� �ٸ��� �����ؾ� ��. �ٸ��� ���� ���
// ������ �ٸ��� ���ٸ�, -1�� ����Ѵ�.

bool dfs(int** bridge, int N, int M, int start, int end,int mindest)
{
	// �ش� ������ �����ϰ� �� �� �ִ°�

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
		int N, M; // N�� ���� ��, M�� �ٸ��� ��
		// ���� ��ķ� �ٸ�...
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