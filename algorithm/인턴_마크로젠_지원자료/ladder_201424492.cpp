#include <fstream>
int main()
{
	int lad[11][100] = {0},k,n,i=0,j,x,y,t;
	std::ifstream in("ladder.inp"); std::ofstream out("ladder.out");
	in >> k >> n;
	for (; i < n; i++){
		in >> x >> y;
		lad[x    ][y] =  1;
		lad[x + 1][y] = -1;
	}
	for (i = 1; (t = i) <= k; i++){
		for (j = 1; j <= 100; j++)
			t += lad[t][j];
		out << char(64 + t) << " ";
	}
}
