//다익스트라 알고리즘
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

#define pp pair<int,int>
using namespace std;
class little
{
public:
	int operator() (const pair<int, int>& p1, const pair<int, int>& p2)
	{return p1.second < p2.second;}
};
int main()
{
	vector< pp > G[30 + 1];
	int d[60 + 1];                              // 거리 저장
	int max = 0;

	int i, n, first;
	int e, u, v, distance;

	ifstream in("rumor.inp");
	ofstream out("rumor.out");
	
	in >> n;
	in >> first;

	priority_queue<pp, vector<pp >, little > Q;
	
	for (int k = 0; k < n; k++){
		in >> u >> e;                           // 간선의 수
		for ( i = 0; i < e; i++){
			in >> v >> distance;                // distance는 거리 
			G[u].push_back(pp(v, distance));    // u와 v 의 위치에 v와 u가 연결되어있음을 저장
			G[v].push_back(pp(u, distance));
		}
	}

	for (i = 1; i <= n; i++) d[i] = 999;   // 거리 max로 설정하기
	d[first] = 0;                          // 출발하는 위치는 0으로

	Q.push(pp(first, d[first]));
	while (!Q.empty()){                    
		u = Q.top().first;
		Q.pop();
		int size = G[u].size();
		for (int i = 0; i < size; i++){
			v = G[u][i].first;
			distance = G[u][i].second;

			if (d[v] > d[u] + distance){   // 지금까지 저장된 v에서 first로 가는 방법이  
				d[v] = d[u] + distance;    // u를 거쳐 가는 것보다 크면 u를 거쳐가는게 이득이므로 바꿔줌
				Q.push(pp(v, d[v]));
			}
		}
	}
	for (i = 1; i <= n; i++)
		if (d[i] > max) max = d[i];        // 최대 출력

	out << max << "\n";
	for (i = 1; i <= n; i++)
		if (max == d[i]) out << i << "\n"; // 최대에 해당하는 위치 출력
	
	return 0;
}