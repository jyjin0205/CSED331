#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef struct edge {
	int node1, node2;
	int length;
}edge;

bool compare(const edge& e1, const edge& e2)
{
	if (e1.length < e2.length)
		return true;
	else
		return false;
}

struct cmp {
	bool operator()(const edge& e1, const edge& e2)
	{
		return e1.length > e2.length;
	}
};

int main(void)
{
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		int I, P, B;
		cin >> I >> P >> B;
		/* I는 섬의 총 개수
		 P는 처음에 포탈이 있던 섬의 개수
		 B는 다리 후보지 수

		포털이 있는 섬에서 인접한 섬으로 가는 다리를 만들고, 아직 없는 경우 포털을 설정
		다리 건설 비용을 최소화

		가장 비싼 연결을 위한 다리 건설 비용!!

		교량 건설 비용을 최소화해서 다리는 이미 건설되어 있음
		*/

		int* parent = new int[I];
		int portalconnum = 0;		
		bool* isportalcon = new bool[I];
		bool* isgroupcon = new bool[I];
		int groupnum = I;

		vector<edge>* ad = new vector<edge>[I];

		for (int j = 0; j < I; j++)
		{
			parent[j] = j;
			isportalcon[j] = false;
			isgroupcon[j] = false;
		}

		for (int j = 0; j < P; j++)
		{
			int portal;
			cin >> portal;
			isportalcon[portal] = true;
			portalconnum++;
		}
		
		edge* bridges = new edge[B];

		for (int j = 0; j < B; j++)
		{
			int i1, i2, c;
			cin >> i1 >> i2 >> c;
			bridges[j].length = c;
			bridges[j].node1 = i1;
			bridges[j].node2 = i2;
		}

		sort(bridges, bridges + B, compare);

		int bridgesidx = 0;
		while (portalconnum != I) // island만큼 다 골라짐
		{
			edge e = bridges[bridgesidx];

			if (isportalcon[e.node1] && isportalcon[e.node2]) // 둘다 다른 포탈과 연결되었다면
			{
			}
			else if(isportalcon[e.node1]) // node1만 포탈에 연결되었다면
			{
				int parentnode2 = parent[e.node2];
				for (int j = 0; j < I; j++)
				{
					if (parent[j] == parentnode2 && isportalcon[j] == false)
					{
						isportalcon[j] = true;
						portalconnum++;
					}
				}

				if (parent[e.node1] > parent[e.node2])
				{
					int beforeparent = parent[e.node1];
					for (int j = 0; j < I; j++)
					{
						if (parent[j] == beforeparent)
							parent[j] = parent[e.node2];
					}
				}
				else
				{
					int beforeparent = parent[e.node2];
					for (int j = 0; j < I; j++)
					{
						if (parent[j] == beforeparent)
							parent[j] = parent[e.node1];
					}
				}

			}
			else if (isportalcon[e.node2]) // node2만 포탈에 연결되었다면
			{
				// node1과 parent가 같은 아이들 처리
				int parentnode1 = parent[e.node1];
				for (int j = 0; j < I; j++)
				{
					if (parent[j] == parentnode1 && isportalcon[j] == false)
					{
						isportalcon[j] = true;
						portalconnum++;
					}
				}

				if (parent[e.node1] > parent[e.node2])
				{
					int beforeparent = parent[e.node1];
					for (int j = 0; j < I; j++)
					{
						if (parent[j] == beforeparent)
							parent[j] = parent[e.node2];
					}
				}
				else
				{
					int beforeparent = parent[e.node2];
					for (int j = 0; j < I; j++)
					{
						if (parent[j] == beforeparent)
							parent[j] = parent[e.node1];
					}
				}
			}
			else // 모두 포탈에 연결되어 있지 않다면
			{
				if (parent[e.node1] > parent[e.node2])
				{
					int beforeparent = parent[e.node1];
					for (int j = 0; j < I; j++)
					{
						if (parent[j] == beforeparent)
							parent[j] = parent[e.node2];
					}
				}
				else
				{
					int beforeparent = parent[e.node2];
					for (int j = 0; j < I; j++)
					{
						if (parent[j] == beforeparent)
							parent[j] = parent[e.node1];
					}
				} // parent를 최소가 되게 바꾸어 준다


			}
			bridgesidx++;
		}

		int cntgroup = 0;
		int ans = 0;
		bridgesidx = B - 1; // 다리 중 제일 긴 것부터


		while (1)
		{
			edge e = bridges[bridgesidx];

			if (parent[e.node1] != parent[e.node2])
			{
				ans += e.length;

				if (parent[e.node1] > parent[e.node2])
				{
					int beforeparent = parent[e.node1];
					for (int j = 0; j < I; j++)
					{
						if (parent[j] == beforeparent)
							parent[j] = parent[e.node2];
					}
				}
				else
				{
					int beforeparent = parent[e.node2];
					for (int j = 0; j < I; j++)
					{
						if (parent[j] == beforeparent)
							parent[j] = parent[e.node1];
					}
				}
			}
			bridgesidx--;

			int flag = parent[0];
			for (int j = 0; j < I; j++)
			{
				if (flag != parent[j])
				{
					flag = -1;
					break;
				}
			}
			if (flag != -1)
				break;
		}

		cout << ans << endl;
	}
}