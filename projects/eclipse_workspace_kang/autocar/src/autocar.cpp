#include "astar.h"
#include "heap.h"
#include "state.h"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int V, E;
vector<pair<int, int> > graph[1000];//pair(toNode, edgeLenth)
int carN;
int car[100][2];//[0]: start node, [1]: end node
int carSpeed[100];
int path[1000][1000][100];
int maxT[100];
int dis[1000][1000];
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

void autoFill();
void makeEdge(int v1, int v2, int edgeLen);

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
	cars[1].speed=2;

	cars[2].start=6;
	cars[2].end=4;
	cars[2].speed=3;
}


void makeEdge(int v1, int v2, int edgeLen){
	graph[v1].push_back(make_pair(v2, edgeLen));
	graph[v2].push_back(make_pair(v1, edgeLen));
}

int nextsize(int &v){
	return graph[v].size();
}
Astar<int>::road & nexti(int &v, int i){
	return graph[v][i];
}
int h(int &now, int &end){
	return 0;
}

class as{
public:
	void execute(){
		input();

		Astar<int> astar = Astar<int>(1, 5, nexti, nextsize, h);
//		Astar<int> a2 = Astar<int>(1, 5, NULL, NULL, NULL);
		printf("%d", astar.findpath());

//		printf("%d", astar.findpath());
//		printf("issame? %d", s1==s2);
	}
};

int main(){
//	state *s = (state *)malloc(sizeof(state(10)));
//	state &s2(*(state*)malloc(sizeof(state)));
//	state &s3 = *s;
//	state s4(10);
//	state &s5=s4;
//	heap<int> a(10);
//	a.push(30);
//	a.push(10);
//	int index =a.push(20);
//
//	a.data[index]=5;
//	a.relax(index);
//	printf("%d %d %d\n", a.data[1], a.data[2], a.data[3]);
//	printf("%d\n", a.top()); a.pop();
//	printf("%d\n", a.top()); a.pop();
//	printf("%d\n", a.top()); a.pop();
	heap<state::car_data> a(10);
	a.push(state::car_data(7, 2));
	a.push(state::car_data(5, 2));
	a.push(state::car_data(10, 3));
	printf("%d\n", a.top().car_FT); a.pop();
	printf("%d\n", a.top().car_FT); a.pop();
	printf("%d\n", a.top().car_FT); a.pop();

//	state s(2);
//	s.carV[0]=0; s.carV[1]=10;
//	s.carFV[0]=1; s.carFV[1]=11;
//	s.carT[0]=5; s.carT[1]=15;
//	s.car_FT.push(15);
//
//	hash<state> h;
//	cout<< h(s);


}
