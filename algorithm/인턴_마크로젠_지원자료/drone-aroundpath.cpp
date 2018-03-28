#include <vector>
#include <fstream>
#define Weight second.second
#define X first.first
#define Y first.second
#define Int2pairs pair<pair<int, int>,pair<int, int>>
using namespace std;

int maxValue = 0;
int n;
vector<Int2pairs> Orders;
Int2pairs Order;


ifstream in("drone.inp");
ofstream out("drone.out");

int minEnergy = 999999999;
int dist(int x1, int y1, int x2, int y2) { return abs(x2 - x1) + abs(y2 - y1); }

int Factorial(vector<Int2pairs> Orders, int maxWeight, int Energy, int l, int r)
{
	int tempEnergy;
	int tempWeight;
	if (l <= r)
	{

		for (int i = l; i <= r; i++)
		{

			swap((Orders[l]), (Orders[i]));


			tempEnergy = maxWeight * dist(Orders[l - 1].X, Orders[l - 1].Y, Orders[l].X, Orders[l].Y);
			tempWeight = Orders[l].Weight;
			Energy += tempEnergy;
			maxWeight -= tempWeight;


			if (Energy < minEnergy)
			{

				Factorial(Orders, maxWeight, Energy, l + 1, r);
			}
		
			Energy -= tempEnergy;
			maxWeight += tempWeight;
			swap((Orders[l]), (Orders[i])); //backtrack
		}
	}
	else
	{
		Energy += dist(Orders[n - 1].X, Orders[n - 1].Y, Orders[0].X, Orders[0].Y);

		if (minEnergy > Energy)
			minEnergy = Energy;
	}
	return 0;
}
int main()
{
	int h, w, x, y;
	int maxWeight = 1;
	in >> n;
	Orders.push_back(make_pair(make_pair(0, 0), make_pair(0, 0)));
	for (int i = 0; i < n; i++)
	{
		in >> h >> w >> x >> y;
		if (h == 1)
		{
			Orders[0]=(make_pair(make_pair(x, y),make_pair(h, w)));
		}
		else
			Orders.push_back(make_pair(make_pair(x, y),make_pair(h, w)));
		maxWeight += w;
	}

	Factorial(Orders, maxWeight, 0, 1, n-1);
	out << minEnergy;

	in.close();
	out.close();
}