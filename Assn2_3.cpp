#include <iostream>
#include <vector>
#include <tuple>

//merge�� �ؾ� �Ѵ�

using namespace std;

typedef struct lineseg
{
	int l;
	int r;
	int y;
}lineseg;

typedef vector<tuple<int, int, int>> MyLineseg;

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

void mergeSort(lineseg* dots, lineseg* temp, int L, int R)
{
	if (L >= R)
		return;

	int M = (L + R) / 2;

	mergeSort(dots, temp, L, M);
	mergeSort(dots, temp, M + 1, R);

	//sorting - L���� M������ M+1���� R������ ��� ���ĵǾ� �ִٰ� ����

	int sortFlag1 = L; // M�� �Ǹ� ����
	int sortFlag2 = M + 1; // R�� �Ǹ� ����


	for (int i = L; i <= R; i++)
	{
		if (sortFlag1 > M)
		{
			temp[i] = dots[sortFlag2];
			sortFlag2++;
		}
		else if (sortFlag2 > R)
		{
			temp[i] = dots[sortFlag1];
			sortFlag1++;
		}
		else
		{
			if (dots[sortFlag1].l < dots[sortFlag2].l)
			{
				temp[i] = dots[sortFlag1];
				sortFlag1++;
			}
			else
			{
				temp[i] = dots[sortFlag2];
				sortFlag2++;
			}
		}
	}

	for (int i = L; i <= R; i++)
	{
		dots[i] = temp[i];
	}
}

MyLineseg lineMergeSort(lineseg* lines, int L, int R)
{
	if (L > R)
	{
		MyLineseg v;
		return v;
	}
	else if (L == R)
	{
		MyLineseg v;
		int l = lines[L].l;
		int r = lines[L].r;
		int y = lines[L].y;
		v.push_back(make_tuple(l, r, y));
		return v;
	}

	int M = (L + R) / 2;

	MyLineseg A = lineMergeSort(lines, L, M);
	MyLineseg B = lineMergeSort(lines, M + 1, R);

	MyLineseg ANS;
	
	if (A.size() == 0)
		return B;
	if (B.size() == 0)
		return A;
	
	int sortFlag1 = 0;
	int sortFlag2 = 0;

	while(1)
	{
		if (sortFlag1 >= A.size() && sortFlag2 >= B.size())
			break;
		else if (sortFlag1 >= A.size())
		{
			ANS.push_back(B[sortFlag2]);
			sortFlag2++;

		}
		else if (sortFlag2 >= B.size())
		{
			ANS.push_back(A[sortFlag1]);
			sortFlag1++;
		}
		else
		{
			tuple<int, int, int> compareofB = B[sortFlag2];
			tuple<int, int, int> lastofA = A[sortFlag1];

			if (get<0>(compareofB) > get<1>(lastofA)) // A�� Ȯ���ϰ� �տ� ����
			{ 
				ANS.push_back(lastofA);
				sortFlag1++;
			}
			else if (get<0>(lastofA) > get<1>(compareofB)) // B�� Ȯ���ϰ� �տ� ����
			{
				ANS.push_back(compareofB);
				sortFlag2++;
			}
			else
			{
				if (get<2>(compareofB) < get<2>(lastofA)) // A�� ���� ���� ���
				{
					if (get<1>(compareofB) < get<1>(lastofA)) // B�� r�� A�� r���� ���ʿ� ���� ��� 
					{
						if (get<0>(compareofB) < get<0>(lastofA)) // i
						{
							int l = get<0>(compareofB);
							int r = get<0>(lastofA);
							int y = get<2>(compareofB);
							if(l != r)
								ANS.push_back(make_tuple(l, r, y));

							sortFlag2++;
						}
						else // ii
						{
							sortFlag2++;
						}
					}
					else // iii
					{
						ANS.push_back(lastofA);
						sortFlag1++;
						
						int l = get<1>(lastofA);
						int r = get<1>(compareofB);
						int y = get<2>(compareofB);
						if (l != r)
							B[sortFlag2] = make_tuple(l, r, y); // �ǳ�
						else
							sortFlag2++;
					}
				}
				else 
				{
					if (get<1>(compareofB) < get<1>(lastofA))
					{
						if (get<0>(compareofB) < get<0>(lastofA)) //iv 
						{
							ANS.push_back(compareofB);
							sortFlag2++;
						}
						else // v
						{
							int l = get<0>(lastofA);
							int r = get<0>(compareofB);
							int y = get<2>(lastofA);
							if(l != r)
								ANS.push_back(make_tuple(l, r, y));
							
							ANS.push_back(compareofB);
							sortFlag2++;
						}

						int l = get<1>(compareofB);
						int r = get<1>(lastofA);
						int y = get<2>(lastofA);
						if (l != r)
							A[sortFlag1] = make_tuple(l, r, y); // �ǳ�
						else
							sortFlag2++;
					}
					else
					{
						int l = get<0>(lastofA);
						int r = get<0>(compareofB);
						int y = get<2>(lastofA);
						if(l != r)
							ANS.push_back(make_tuple(l, r, y));
						sortFlag1++;
					}
				}
				

			}
		}
	}

	MyLineseg real_ANS;

	int i;
	for (i = 0; i < ANS.size()-1; i++)
	{
		if ( get<1>(ANS[i]) == get<0>(ANS[i + 1]) && get<2>(ANS[i]) == get<2>(ANS[i+1]))
		{
			int l = get<0>(ANS[i]);
			int r = get<1>(ANS[i + 1]);
			ANS[i + 1] = make_tuple(l, r, get<2>(ANS[i]));
		}
		else
		{
			real_ANS.push_back(ANS[i]);
		}
	}
	real_ANS.push_back(ANS[i]);

	return real_ANS;
}

int main(void)
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		int n;
		cin >> n;
		lineseg* lines = new lineseg[n];
		lineseg* temp = new lineseg[n];

		for (int i = 0; i < n; i++)
		{
			cin >> lines[i].l >> lines[i].r >> lines[i].y;
		}

		mergeSort(lines, temp, 0, n - 1);


		MyLineseg ANS = lineMergeSort(lines, 0, n - 1);

		for (int i = 0; i < ANS.size(); i++)
		{
			cout << get<0>(ANS[i]) << " " << get<1>(ANS[i]) << " " << get<2>(ANS[i]) << "\n";
		}
	}
}