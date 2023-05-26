#include<iostream>
#include<algorithm>
using namespace std;

typedef struct lowhull {
	int l, r, y;
}lowhull;

typedef struct tophull {
	int l, r, y, idx; // lowhull에서의 idx
};

bool compare1(const tophull& h1, const tophull& h2)
{
	if (h1.y > h2.y)
		return true;
	return false;
}

long long int greedy(lowhull* hull,int hullidx, int mainidx, int height, int beforeleft, int beforeheight)
{
	long long int ans = 0;

	for (; mainidx < hullidx; mainidx++)
	{
		height = hull[mainidx].y;

		if (height > beforeheight)
		{
			long long int heightnotchange = (long long int)beforeheight * (hull[mainidx].r - beforeleft);
			long long int heightchange = (long long int)height * (hull[mainidx].r - hull[mainidx].l);

			if (heightnotchange > heightchange) // 안 바꾸는 게 더 낫다
			{
				//beforeright = hull[mainidx].r;

				if (ans < heightnotchange)
					ans = heightnotchange;
			}
			else if (heightnotchange < heightchange) // 바꾸는 게 더 낫다
			{
				beforeleft = hull[mainidx].l;
				beforeheight = height;

				if (ans < heightchange)
					ans = heightchange;
			}
			else
			{
				long long int ans1 = greedy(hull, hullidx, mainidx, height, beforeleft, beforeheight);
				long long int ans2 = greedy(hull, hullidx, mainidx, height, hull[mainidx].l, height);

				if (ans < ans1)
					ans = ans1;
				if (ans < ans2)
					ans = ans2;
			}
		}
		else // 높이가 낮아짐
		{
			long long int heightchange = (long long int)height * (hull[mainidx].r - beforeleft);

			beforeheight = height;
			if (ans < heightchange)
			{
				ans = heightchange;
			}
		}
	}
	return ans;
}

int main(void)
{
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		int n, w;
		cin >> n >> w;

		lowhull* hull = new lowhull[n];

		lowhull* oldhull = new lowhull[n];

		for (int j = 0; j < n; j++)
		{
			int l, r, y;
			cin >> l >> r >> y;
			oldhull[j].l = l;
			oldhull[j].r = r;
			oldhull[j].y = y;

		}

		int flagheight = oldhull[0].y;
		int flaglft = oldhull[0].l;
		int hullidx = 0;
		for (int j = 0; j < n; j++)
		{
			flagheight = oldhull[j].y;
			if (j == n - 1)
			{
				hull[hullidx].l = flaglft;
				hull[hullidx].r = oldhull[j].r;
				hull[hullidx].y = flagheight;
				hullidx++;
			}
			else if (flagheight == oldhull[j + 1].y)
			{
				
			}
			else
			{
				hull[hullidx].l = flaglft;
				hull[hullidx].r = oldhull[j].r;
				hull[hullidx].y = flagheight;

				flaglft = oldhull[j+1].l;
				hullidx++;
			}
		}

		long long int ans = greedy(hull, hullidx, 0, hull[0].y, 0, hull[0].y);
		cout << ans << endl;
	}
}