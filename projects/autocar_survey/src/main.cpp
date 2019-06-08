//============================================================================
// Name        : car.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define INF 987654321

int V, E;
vector<pair<int, int> > graph[1000];//pair(toNode, edgeLenth)
int carN;
int car[100][2];//[0]: start node, [1]: end node
int carSpeed[100];
int path[1000][1000][100];
int maxT[100];
int dis[1000][1000];

void input();
void autoFill();
void makeEdge(int v1, int v2, int edgeLen);
void dijkstra();
vector<int> dijkstra_maxT();

struct comp
{
	bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b)
	{
		return a.second > b.second;
	}
};
std::priority_queue< std::pair<int, int>, std::vector<  std::pair<int, int> >, comp > q; //���ͽ�Ʈ�� �˰�������
std::priority_queue<int> paths[1111];

int main() {
	input();

	return 0;
}

vector<int> dijkstra_maxT(int K){
	vector<int> s,d;
	s.assign(V,false);
	d.assign(V,INF);
	d[K-1] = 0;
	while(true)
	{
		int m = INF, N=-1;
		for(int j=0;j<V; j++)
		{
			if(!s[j] && (m>d[j]))
			{
				m = d[j];
				N = j;
			}
		}
		if(m == INF)
			break;
		s[N] = true; // N��° ���带 �湮.
		for(int j=0;j<V;j++)
		{
			if(s[j]) continue;
			unsigned int via = d[N] + graph[N][j];
			if(d[j] > via)
				d[j] = via;
		}
	}
	return d;
}

void dijkstra(unsigned int k){
	q.push(std::make_pair(1,0));
	paths[1].push(0);
	while (!q.empty())
	{
		int vertex = q.top().first;
		int time = q.top().second;
		q.pop();

		for (auto next : graph[vertex])
		{
			if (paths[next.first].size() < k)
				paths[next.first].push(time + next.second);
			else if (paths[next.first].top() > time + next.second)
			{
				paths[next.first].pop();
				paths[next.first].push(time + next.second);
			}
			else
				continue;

			q.push(std::make_pair(next.first, time + next.second));
		}
	}
}

void input(){
	autoFill();
}

void autoFill(){
	V=5;
	E=7;
	makeEdge(0, 1, 4);
	makeEdge(0, 3, 3);
	makeEdge(0, 4, 2);
	makeEdge(3, 4, 3);
	makeEdge(3, 5, 2);
	makeEdge(2, 4, 5);
	makeEdge(1, 2, 7);

	carN=3;
	car[0][0]=0;
	car[0][1]=2;
	carSpeed[0]=1;

	car[1][0]=1;
	car[1][1]=3;
	carSpeed[1]=2;

	car[2][0]=0;
	car[2][1]=1;
	carSpeed[2]=3;
}

void makeEdge(int v1, int v2, int edgeLen){
	graph[v1].push_back(make_pair(v2, edgeLen));
	graph[v2].push_back(make_pair(v1, edgeLen));
}
