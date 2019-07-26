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
#define INF 2147483647

int V, E;
vector<pair<int, int> > graph[1000];//pair(toNode, edgeLenth)
int carN;
int car[100][2];//[0]: start node, [1]: end node
int carSpeed[100];
int path[1000][1000][100];
int maxT[100];
int dis[1000][1000];

int * doAll();

//아이디어: 그리드 컴퓨팅(Car 하나마다 프로세서가 있으므로 그걸 이용?)
class Road{
public:
	int roadStart, roadEnd;
	Road(int s, int e): roadStart(s), roadEnd(e){}
	Road(){}
};
class Loc: public Road{
public:
	int movedInRoad;
	Loc(int s, int e, int movedInRoad): Road(s, e), movedInRoad(movedInRoad) {}
	Loc(){}
};

class Car
{
private:
	static int _ID;//다음 차의 ID
public:
	int start, end;
	Loc now;
	int speed;
	const int id;

	int shortest[100];

	Car(): id(_ID++), speed(0){}
	Car(int start, int to): id(_ID++), start(start), end(to), speed(0){}
	void reTo(int newTo){start=now.roadStart, end=newTo;}
};
int Car::_ID = 0;

Car cars[100];

void input();
void autoFill();
void makeEdge(int v1, int v2, int edgeLen);
std::priority_queue<int> & dijkstra_k(unsigned int k, Car &car);
//vector<int> dijkstra_maxT();

struct comp
{
	bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b)
	{
		return a.second > b.second;
	}
};
std::priority_queue< std::pair<int, int>, std::vector<  std::pair<int, int> >, comp > q;
std::priority_queue<int> paths[1111];

/////////////////////////////////////////////////////////////
//                    int main()                           //
/////////////////////////////////////////////////////////////
int main() {
	printf("start...\n");

	input();
// = dijkstra_k(5, cars[i])
	int k=5;
	for(int i=0; i<carN; i++){
		priority_queue<int> &path= dijkstra_k(k, cars[i]);
		Car &car=cars[i];
		printf("id:%d, start %d, end:%d:\n	", car.id, car.start, car.end);
			for(int j=0; j<k; j++){
				car.shortest[k-j-1]=path.top();
				path.pop();
			}
			for(int j=0; j<k; j++){
				printf("%d ",car.shortest[j]);
			}
			printf("\n");
//		printf("\n");
	}



	return 0;
}

std::priority_queue<int> & dijkstra_k(unsigned int k, Car &car){
	std::priority_queue< std::pair<int, int>, std::vector<  std::pair<int, int> >, comp > q;
	std::priority_queue<int> * paths = new std::priority_queue<int>[1111];

	q.push(std::make_pair(car.start,0));
	paths[car.start].push(0);
	while (!q.empty())
	{
		int vertex = q.top().first;
		int time = q.top().second;
		q.pop();

		//printf("(vertex, time): (%d, %d)\n", vertex, time);

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

	return paths[car.end];
}



/*
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
		s[N] = true;
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
*/
//int * doall(){
//
//}

void input(){
	autoFill();
}

void autoFill(){
	V=5;
	E=7;
	makeEdge(1, 2, 7);
	makeEdge(1, 3, 9);
	makeEdge(1, 6, 14);
	makeEdge(2, 3, 10);
	makeEdge(2, 4, 15);
	makeEdge(3, 4, 11);
	makeEdge(3, 6, 2);
	makeEdge(4, 5, 6);
	makeEdge(5, 6, 9);

	carN=3;
	cars[0].start=1;
	cars[0].end=4;
	cars[0].speed=1;

	cars[1].start=2;
	cars[1].end=5;
	cars[1].speed=1;

	cars[2].start=6;
	cars[2].end=4;
	cars[2].speed=1;
}

void makeEdge(int v1, int v2, int edgeLen){
	graph[v1].push_back(make_pair(v2, edgeLen));
	graph[v2].push_back(make_pair(v1, edgeLen));
}
