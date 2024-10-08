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
void Rotation(vector<deque<int>>& dart, int i, int d, int k)
{
	if (d == 0)  
		rotate(dart[i].rbegin(), dart[i].rbegin() + k, dart[i].rend());
	else if (d == 1)  
		rotate(dart[i].begin(), dart[i].begin() + k, dart[i].end());
}

bool RemoveAdjacent(vector<deque<int>>& dart)
{
	bool IsRemove = false;
	int rows = dart.size();
	int cols = dart[0].size();
	vector<vector<bool>> toRemove(rows, vector<bool>(cols, false));

	auto markForRemoval = [&](int y, int x, int ny, int nx)
		{
			if (dart[y][x] == dart[ny][nx] && dart[y][x] != 0)
			{
				toRemove[y][x] = true;
				toRemove[ny][nx] = true;
			}
		};

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			int left = (x == 0) ? cols - 1 : x - 1;
			int right = (x == cols - 1) ? 0 : x + 1;
			markForRemoval(y, x, y, left);   
			markForRemoval(y, x, y, right);  

			if (y > 0)
			{
				markForRemoval(y, x, y - 1, x);  
			}
			if (y < rows - 1)
			{
				markForRemoval(y, x, y + 1, x); 
			}
		}
	}

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (toRemove[y][x])
			{
				dart[y][x] = 0;
				IsRemove = true;
			}
		}
	}

	return IsRemove;
}

void Normalization(vector<deque<int>>& dart)
{
	int sum = 0, cnt = 0;

	for (const auto& row : dart)
	{
		for (const auto& col : row)
		{
			if (col > 0)
			{
				sum += col;
				cnt++;
			}
		}
	}

	if (cnt == 0) return;  

	int avg = sum / cnt;

	for (auto& row : dart)
	{
		for (auto& col : row)
		{
			if (col > 0)
			{
				if (col > avg) col -= 1;
				else if (col < avg) col += 1;
			}
		}
	}
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
		for (int i = x; i <= n; i += x)
		{
			Rotation(dart, i - 1, d, k % m);  
		}

		bool removed = RemoveAdjacent(dart);
		if (!removed)
		{
			Normalization(dart);
		}
	}

	int sum = 0;
	for (const auto& row : dart)
	{
		for (const auto& col : row)
		{
			sum += col;
		}
	}

	cout << sum << "\n";

	return 0;
}