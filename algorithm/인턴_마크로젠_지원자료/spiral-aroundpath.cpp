#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

#define COLLINEAR 0
#define CLOCK 1
#define COUNTERCLOCK 2

ifstream in("spiral.inp");
ofstream out("spiral.out");

struct point
{
	int x, y, index;
	point() : x(0), y(0), index(0){}
};


int distSquare(point a, point b)
{
	return pow((a.x - b.x),2) + pow((a.y - b.y),2);
}

int FindDirection(point p, point q, point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
			  (q.x - p.x) * (r.y - q.y);

	if (val == COLLINEAR) return COLLINEAR;
	return (val > 0) ? CLOCK : COUNTERCLOCK;
}

void CovexAntiSpiral(vector<point> points)
{
	vector<point> spiral;
	while (!points.empty())
	{
		int next = 1 % points.size();
		for (int i = 1; i < points.size(); i++)
		{
			int direction = FindDirection(points[0], points[i], points[next]);
			
			if (direction == COUNTERCLOCK ||
			   (direction == COLLINEAR && (distSquare(points[0], points[i]) < distSquare(points[0], points[next]))))
				next = i;

		}
		spiral.push_back(points[0]);
		swap(points[0], points[next]);

		points.erase(points.begin() + next);

	} 

	for (int i = 1; i < spiral.size(); i++)
		 out << spiral[i].index << " ";
}

int main()
{
	vector<point> points;
	point point;
	points.push_back(point);
	
	int n;
	in >> n;

	for (int i = 1; i <= n; i++)
	{
		in >> point.x >> point.y; point.index = i;
		points.push_back(point);
	}

	CovexAntiSpiral(points);

	in.close();
	out.close();
	
	return 0;
}