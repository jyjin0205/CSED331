//VIP는 고속을 좋아하므로, 최대 속도를 구해야 한다.
//벌금 없이 최고 속도

//tuple 개념 : https://notepad96.tistory.com/37


#include <iostream>
#include <stack>
//#include <tuple>
#include <vector>

typedef struct qElement {
	int x;
	int y;
	long long int value;
}qElement;

using namespace std;


long long int DFS(long long int** arr,bool** visited,int N,int M)
{
	stack<qElement> s;
	qElement start{ 0,0,arr[0][0] };
	s.push(start);
	visited[0][0] = true;
	long long int speed = arr[0][0];
	long long int unvisitedMax = -1;

	vector<qElement>* unvisited = new vector<qElement>;
	
	while (1)
	{
		qElement output;


		if (!s.empty())
		{
			output = s.top();
			s.pop();
		}
		else // stack이 비었을 경우에는 speed를 한 단계 조정, unvisited 원소들을 
		{
			long long int newMax = -1;
			vector<qElement>* newunvisited = new vector<qElement>;

			for (int i = 0; i < (*unvisited).size(); i++)
			{
				if (unvisitedMax == (*unvisited)[i].value)
					s.push((*unvisited)[i]);
				else
				{
					if (newMax < (*unvisited)[i].value)
					{
						newMax = (*unvisited)[i].value;
					}
					(*newunvisited).push_back((*unvisited)[i]);
				}
			}

			if (s.size() == 0)
				return 1;

			output = s.top();
			s.pop();
			speed = unvisitedMax;

			//unvisited.clear();
			(*unvisited).clear();
			unvisited = newunvisited;
			unvisitedMax = newMax;
		}

		visited[output.y][output.x] = true;
		if (unvisited == NULL)
			break;

		//queue push phase
		if (output.x == M-1 && output.y == N-1)
		{
			return speed;
		}
		else
		{
			// 속도 제한이 있는 애들이라도 일단 넣는다
			if (output.x != 0) // 왼쪽
			{
				if (!visited[output.y][output.x-1])
				{
					qElement* n = new qElement;
					n->x = output.x-1;
					n->y = output.y;
					n->value = arr[output.y][output.x-1];
					if (arr[output.y][output.x-1] >= speed)
					{
						visited[output.y][output.x-1] = true;

						s.push(*n);
					}
					else
					{
						if (arr[output.y][output.x - 1] > unvisitedMax)
						{
						 	unvisitedMax = arr[output.y][output.x - 1];

						}
						(*unvisited).push_back(*n);
					}
				}
			}
			if (output.x != M - 1) // 오른쪽
			{
				if(!visited[output.y][output.x+1])
				{
					qElement* n = new qElement;
					n->x = output.x+1;
					n->y = output.y;
					n->value = arr[output.y][output.x+1];
					if (arr[output.y][output.x+1] >= speed)
					{
						visited[output.y][output.x+1] = true;

						s.push(*n);
					}
					else
					{
						if (arr[output.y][output.x+1] > unvisitedMax)
						{
							unvisitedMax = arr[output.y][output.x+1];

						}
						(*unvisited).push_back(*n);

					}
				}
			}
			if (output.y != 0) // 위
			{
				if (!visited[output.y-1][output.x])
				{
					qElement* n = new qElement;
					n->x = output.x;
					n->y = output.y - 1;
					n->value = arr[output.y-1][output.x];
					if (arr[output.y-1][output.x] >= speed)
					{
						visited[output.y-1][output.x] = true;

						s.push(*n);
					}
					else
					{
						if (arr[output.y-1][output.x] > unvisitedMax)
						{
							unvisitedMax = arr[output.y-1][output.x];
						}
						(*unvisited).push_back(*n);
					}
				}
			}
			if (output.y != N - 1) // 아래
			{
				if (!visited[output.y+1][output.x])
				{
					qElement* n = new qElement;
					n->x = output.x;
					n->y = output.y + 1;
					n->value = arr[output.y+1][output.x];
					if (arr[output.y+1][output.x] >= speed)
					{
						visited[output.y+1][output.x] = true;

						s.push(*n);
					}
					else
					{
						if (arr[output.y+1][output.x ] > unvisitedMax)
						{
							unvisitedMax = arr[output.y+1][output.x];

						}
						(*unvisited).push_back(*n);
					}
				}
			}
		}
	}
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

		cout << DFS(arr, visited, N, M) << endl;
	}
}