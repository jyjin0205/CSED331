#include<iostream>
#include<algorithm>

using namespace std;

typedef struct course
{
	int s;
	int e;
}course;

bool compare(course a, course b)
{
	if (a.e < b.e)
		return true;
	else
		return false;
}
int main(void)
{
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		int n;
		cin >> n;
		
		course* c = new course[n];
		for (int j = 0; j < n; j++)
		{
			cin >> c[j].s >> c[j].e;
		}
		sort(c, c+n, compare);

		int flag = 0;
		int ans = 0;
		for (int j = 0; j < n; j++)
		{
			if (c[j].s >= flag)
			{
				ans++;
				flag = c[j].e;
			}
		}
		cout << ans << endl;
	}
}