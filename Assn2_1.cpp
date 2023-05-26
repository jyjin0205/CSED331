#include <iostream>
#include <vector>
#include <math.h>


using namespace std;

// mergesort

typedef struct dot
{
	long long int x, y;
}dot;

dot* dots;
dot* temp;

void mergeSort(dot* dots, dot* temp, int L, int R)
{
	if (L >= R)
		return;

	int M = (L + R) / 2;

	mergeSort(dots, temp, L, M);
	mergeSort(dots, temp, M + 1, R);

	//sorting - L부터 M까지와 M+1부터 R까지는 모두 정렬되어 있다고 가정

	int sortFlag1 = L; // M이 되면 끝남
	int sortFlag2 = M + 1; // R이 되면 끝남


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
			if (dots[sortFlag1].x < dots[sortFlag2].x)
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

void mergeSortV(vector<dot>* dots, int L, int R)
{
	if (L >= R)
		return;

	int M = (L + R) / 2;

	vector<dot> temp;
	mergeSortV(dots,  L, M);
	mergeSortV(dots,  M + 1, R);

	//sorting - L부터 M까지와 M+1부터 R까지는 모두 정렬되어 있다고 가정

	int sortFlag1 = L; // M이 되면 끝남
	int sortFlag2 = M + 1; // R이 되면 끝남


	for (int i = L; i <= R; i++)
	{
		if (sortFlag1 > M)
		{
			(temp).push_back((*dots)[sortFlag2]);
			sortFlag2++;
		}
		else if (sortFlag2 > R)
		{
			(temp).push_back((*dots)[sortFlag1]);
			sortFlag1++;
		}
		else
		{
			if ((*dots)[sortFlag1].y < (*dots)[sortFlag2].y)
			{
				(temp).push_back((*dots)[sortFlag1]);
				sortFlag1++;
			}
			else
			{
				(temp).push_back((*dots)[sortFlag2]);
				sortFlag2++;
			}
		}
	}

	for (int i = L; i <= R; i++)
	{
		(*dots)[i] = (temp)[i-L];
	}
}

long long int calcDist(dot A, dot B)
{
	long long int ans = 0;
	if (A.x > B.x)
		ans += (long long)(A.x) - (long long)(B.x);
	else
		ans += (long long)(B.x) - (long long)(A.x);

	if (A.y > B.y)
		ans += (long long)(A.y) - (long long)(B.y);
	else
		ans += (long long)(B.y) - (long long)(A.y);

	return ans;
}

// 최소 거리
long long int DivideConquer(int L,int R) 
{
	int median = (L + R) / 2;

	if (L > R)
	{
		return (long long)(pow(2,34));
	}
	if (L == R)
	{
		return (long long)(pow(2,34));
	}
	if (R == L + 1)
	{
		return calcDist(dots[L], dots[R]);
	}
	
	long long int LeftMin = DivideConquer(L, median-1);
	long long int RightMin = DivideConquer(median + 1, R);

	long long int sigma = LeftMin;
	if (sigma > RightMin)
		sigma = RightMin;

	vector<dot> AlignY;

	int alignnum = 0;
	for (int i = L; i <= R; i++)
	{
		if (dots[i].x > dots[median].x - sigma && dots[i].x < dots[median].x + sigma)
		{
			AlignY.push_back(dots[i]);
			alignnum++;
		}
	} // median 근처 점들을 다시 잡고 생각

	mergeSortV(&AlignY, 0, alignnum - 1);

	
		int i = 0;
		
		for (i = 0; i < alignnum - 13; i++)
		{
			for (int j = i + 1; j < i + 13; j++)
			{
				long long int tmp = calcDist(AlignY[i], AlignY[j]);
				if (tmp < sigma)
					sigma = tmp;
			}
		}

		for (; i < alignnum; i++)
		{
			for (int j = i + 1; j < alignnum; j++)
			{
				long long int tmp = calcDist(AlignY[i], AlignY[j]);
				if (tmp < sigma)
					sigma = tmp;
			}
		}


	return sigma;

}

int main(void)
{
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		int N;
		cin >> N;
		dots = new dot[N];
		temp = new dot[N];
		for (int j = 0; j < N; j++)
		{
			cin >> dots[j].x >> dots[j].y;
		}
		mergeSort(dots, temp, 0, N - 1);

		long long int ans = DivideConquer(0, N - 1);

		cout << ans << "\n";
	}
}