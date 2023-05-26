

#include <iostream>
#include <vector>
#define min(a,b) a>b ? b : a
#define INF 100000000
using namespace std;


typedef struct roadsAndImm
{
	vector<int> roads;
	bool isImm;
}roadsAndImm;

roadsAndImm* roadsandimm;
int* intermediate;
int S, E, K, N;
bool* visitedRoads;
int ans;
//vector<int> s;

void DFS(int currentPlace, int currentSum)
{
	if (currentSum > K)
		return;

	if (currentPlace == E)
	{
		if(currentSum == K)
			ans++;
		return;
	}
	else
	{
		for (int i = 0; i < roadsandimm[currentPlace].roads.size(); i++)
		{
			if (!visitedRoads[roadsandimm[currentPlace].roads[i]])
			{
				/*bool flag = true;
				for (int j = 0; j < K; j++)
				{
					if (intermediate[j] == i)
					{
						DFS(N, i, visitedNum + 1);
						visitedRoads[i] = false;
						flag = false;
						break;
					}
				}
				if (flag)
				{
					DFS(N, i, visitedNum);
					visitedRoads[i] = false;
				}
				*/
				//s.push_back(roadsandimm[currentPlace].roads[i]);
				visitedRoads[roadsandimm[currentPlace].roads[i]] = true;

				if(roadsandimm[currentPlace].isImm == true)
					DFS(roadsandimm[currentPlace].roads[i],currentSum+1);
				else
					DFS(roadsandimm[currentPlace].roads[i], currentSum);

				//s.pop_back();
				visitedRoads[roadsandimm[currentPlace].roads[i]] = false;
			}
		}
	}
	return;
}

int main(void)
{
	int T;
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		//s.clear();
		int M;
		cin >> N >> M;
		roadsandimm = new roadsAndImm[N];
		visitedRoads = new bool[N];
		for (int j = 0; j < N; j++)
		{
			visitedRoads[j] = false;
			roadsandimm[j].isImm = false;
		}


		for (int j = 0; j < M; j++)
		{
			int a, b;
			cin >> a >> b;
			roadsandimm[a].roads.push_back(b);
		} 

		cin >> S >> E >> K;

		intermediate = new int[K];
		// 도착 전에 K개의 교차점을 지나야 한다.
		for (int j = 0; j < K; j++)
		{
			cin >> intermediate[j];
			roadsandimm[intermediate[j]].isImm = true;
		} 

		ans = 0;

		visitedRoads[S] = true;
		//s.push_back(S);

		DFS(S,0);

		cout << ans % 20230419 << endl;
	}

}