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
		/* I�� ���� �� ����
		 P�� ó���� ��Ż�� �ִ� ���� ����
		 B�� �ٸ� �ĺ��� ��

		������ �ִ� ������ ������ ������ ���� �ٸ��� �����, ���� ���� ��� ������ ����
		�ٸ� �Ǽ� ����� �ּ�ȭ

		���� ��� ������ ���� �ٸ� �Ǽ� ���!!

		���� �Ǽ� ����� �ּ�ȭ�ؼ� �ٸ��� �̹� �Ǽ��Ǿ� ����
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
		while (portalconnum != I) // island��ŭ �� �����
		{
			edge e = bridges[bridgesidx];

			if (isportalcon[e.node1] && isportalcon[e.node2]) // �Ѵ� �ٸ� ��Ż�� ����Ǿ��ٸ�
			{
			}
			else if(isportalcon[e.node1]) // node1�� ��Ż�� ����Ǿ��ٸ�
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
			else if (isportalcon[e.node2]) // node2�� ��Ż�� ����Ǿ��ٸ�
			{
				// node1�� parent�� ���� ���̵� ó��
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
			else // ��� ��Ż�� ����Ǿ� ���� �ʴٸ�
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
				} // parent�� �ּҰ� �ǰ� �ٲپ� �ش�


			}
			bridgesidx++;
		}

		int cntgroup = 0;
		int ans = 0;
		bridgesidx = B - 1; // �ٸ� �� ���� �� �ͺ���


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