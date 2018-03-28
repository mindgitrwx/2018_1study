#include <vector>
#include <fstream>
#include <algorithm>
#define MaxCost second.first
#define MinDay second.second
using namespace std;
int main()
{
	int n;
	int b, e, c;
	vector<pair<pair<int, int>, 
		   pair<int, int>>> Orders;

	ifstream in("freelance.inp");
	ofstream out("freelance.out");

	in >> n;

	for (int i = 0; i < n; i++)
	{
		in >> b >> e >> c;
		Orders.push_back (make_pair(make_pair(b, e),
			                        make_pair(c, e - b + 1)));
	}

	sort(Orders.begin(), Orders.end());

	for (int i = n-2; i >= 0; i--)
	{
		for (int j = i+1; j < n; j++)
		{
			if (Orders[i].first.second < Orders[j].first.first)
			{
				Orders[i].MaxCost += Orders[j].MaxCost - 10;
				Orders[i].MinDay += Orders[j].MinDay;
				break;
			}
		}
		if (Orders[i].MaxCost < Orders[i + 1].MaxCost || 
			Orders[i].MaxCost == Orders[i + 1].MaxCost && Orders[i].MinDay > Orders[i + 1].MinDay)
			swap(Orders[i], Orders[i + 1]);
	}

	out << Orders[0].MaxCost << " " << Orders[0].MinDay << endl;
	in.close();
	out.close();
}