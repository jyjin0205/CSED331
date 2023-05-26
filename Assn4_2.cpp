#include<iostream>
#include<queue>
#include<vector>
#include<tuple>
#define INF 2147483647

using namespace std;

int ans;

int* dist;

vector<pair<int, int>>* nonExpress;
int N;
vector<pair<int, int>>* Express;
//vector<pair<int, int>> ExpressLineNum;
int s, t;

//start : ������, diststart : ���������� �Ÿ�
void dijkstra(vector<pair<int, int>>* lines, int start, int diststart)
{
	for (int i = 0; i < N; i++)
		dist[i] = INF;

	if (start >= N)
	{
		while (1);
	}
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> PQ;

	PQ.push(make_pair(diststart,start));
	dist[start] = diststart;

	while (!PQ.empty())
	{
		pair<int,int> u = PQ.top();
		PQ.pop();
		
		for (int i = 0; i < lines[u.second].size(); i++)
		{
			int v = lines[u.second][i].first;
			int l = lines[u.second][i].second;

			if (dist[v] > dist[u.second] + l)
			{
				dist[v] = dist[u.second] + l;
				PQ.push(make_pair(dist[v],v));
			}
		}
	}	
}

void takeExpressTrain()
{
	vector<pair<int, int>> ExpressGoal;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < Express[i].size(); j++)
		{
			int u = i;
			int v = Express[i][j].first;
			int l = Express[i][j].second;

			if (dist[u] <= s)
			{
				if (s + l <= t)
				{
					ExpressGoal.push_back(make_pair(s + l, v));
				}
			}
			else if (dist[u] != INF)
			{
				if (dist[u] + l <= t)
				{
					ExpressGoal.push_back(make_pair(dist[u] + l, v));
				}
			}
		}
	}
		
	for (int i = 0; i < ExpressGoal.size(); i++)
	{
		// �׷���, ���� �� �ð��� �̹� ������ ans���� ũ�� �����Ѵ�.
		if (ExpressGoal[i].first >= ans && ans != -1)
			continue;

		
		dijkstra(nonExpress, ExpressGoal[i].second, ExpressGoal[i].first);
		// �������������� ���ͽ�Ʈ�� �Ѵ�

		if (dist[N - 1] != INF && ans > dist[N - 1])
			ans = dist[N - 1];

		
		takeExpressTrain();
	}
}

int main(void)
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		int M;
		cin >> N >> M; // N�� ���� ��, M�� ������ ��

		nonExpress = new vector<pair<int, int>>[N];
		Express = new vector<pair<int, int>>[N];
		dist = new int [N];

		for (int j = 0; j < N; j++)
		{
			dist[j] = INF;
		}

		cin >> s >> t; // express edge�� s���� t���� ���� �� �ִ�.
		
		for (int j = 0; j < M; j++)
		{
			int u, v, l, e; // u, v�� �� �� ��, l�� ����. e�� Ÿ��
			cin >> u >> v >> l >> e; 

			if (e == 1)
			{
				Express[u].push_back(make_pair(v,l));
				//ExpressLineNum.push_back(make_pair(u,v)); // �������� �� ���� �� ����
			}
			else
			{
				nonExpress[u].push_back(make_pair(v, l));
			}
		}

		ans = -1;
		dijkstra(nonExpress, 0, 0);
		
		if (dist[N - 1] != INF)
			ans = dist[N - 1];

		takeExpressTrain();

		cout << ans << endl;
	}
}