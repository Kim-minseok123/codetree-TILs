#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <memory.h>
#include <queue>

using namespace std;

static void Init()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
}
void Rotation(vector<deque<int>>& dart, int i,int d)
{
	if (d == 0)
	{
		dart[i].push_front(dart[i].back());
		dart[i].pop_back();
	}
	else if(d == 1)
	{
		dart[i].push_back(dart[i].front());
		dart[i].pop_front();
	}
}
bool RemoveAdjacent(vector<deque<int>>& dart)
{
	vector<deque<int>> temp(dart.size(), deque<int>(dart[0].size(), 0));
	int rows = dart.size();
	int cols = dart[0].size();

	bool IsRemove = false;

	auto isAdjacentEqual = [&](int y, int x, int val) -> bool
		{
			int up = y - 1;
			int down = y + 1;
			int left = (x == 0) ? cols - 1 : x - 1;
			int right = (x == cols - 1) ? 0 : x + 1;

			if (y == 0)
				return (dart[down][x] == val || dart[y][left] == val || dart[y][right] == val);
			else if (y == rows - 1)
				return (dart[up][x] == val || dart[y][left] == val || dart[y][right] == val);
			else
				return (dart[up][x] == val || dart[down][x] == val || dart[y][left] == val || dart[y][right] == val);
		};

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (isAdjacentEqual(y, x, dart[y][x]))
			{
				temp[y][x] = 0;
				IsRemove = true;
			}
			else
				temp[y][x] = dart[y][x];
		}
	}

	dart = temp;
	return IsRemove;
}
void Normalization(vector<deque<int>>& dart)
{
	int cnt = 0;
	int sum = 0;
	for (auto row : dart)
		for (auto col : row)
			if (col != 0)
			{
				sum += col;
				cnt += 1;
			}

	int avg = sum / cnt;

	for (auto row : dart)
		for (auto col : row)
			if (col > avg)
				col -= 1;
			else if (col < avg)
				col += 1;
}
int main()
{
	Init();

	int n, m, q;
	cin >> n >> m >> q;
	vector<deque<int>> dart(n, deque<int>(m, 0));

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			cin >> dart[y][x];
		}
	}

	while (q--)
	{
		int x, d, k;
		cin >> x >> d >> k;
		for (int i = x; i <= n; i *= 2)
		{
			for (int j = 0; j < k; j++)
			{
				Rotation(dart, i - 1, d);
			}
		}
		auto trigger = RemoveAdjacent(dart);
		if(trigger == false)
			Normalization(dart);
	}

	int sum = 0;

	for (auto row : dart)
		for (auto col : row)
			sum += col;

	cout << sum;

	return 0;
}