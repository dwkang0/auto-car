#include "astar.h"
#include "heap.h"
#include <stdio.h>
#include <vector>

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



//class state{
//public:
//	int *carv;
//	int *cart;
//	int nowt;
//	int carn;
//	state(int carn){
//		this->carn = carn;
//		carv = new int[carn];
//		cart = new int[carn];
//		nowt=0;
//	}
//	~state(){
//		delete carv;
//	}
//	bool operator == (const state & b) const{
//		for(int i=0; i<carn; i++){
//			if(carv[i] != b.carv[i]) return 0;
//		}
//		return 1;
//	}
//	static int nextsize(state &v){
//		int min=0;
//		for(int i=1; i<v.carn; i++){
//			if(v.cart[min] > v.cart[i]) min = i;
//		}
//		return graph[v.carv[min]].size();
//	}
//
//	static Astar<state>::road & nexti(state &v, int i){
//		int min=0;
//		for(int i=1; i<v.carn; i++){
//			if(v.cart[min] > v.cart[i]) min = i;
//		}
//		return ;
//	}
//};

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

//		state s1(3);
//		s1.carv[0]=1; s1.carv[1]=2; s1.carv[2]=10;
//		state s2(3);
//		s2.carv[0]=1; s2.carv[1]=2; s2.carv[2]=10;
//		printf("asdasd");
		Astar<int> astar = Astar<int>(sizeof(int), 1, 5, nexti, nextsize, h);
//		Astar<int>::hashVT h;
		printf("%d", astar.findpath());

//		printf("%d", astar.findpath());
//		printf("issame? %d", s1==s2);
	}
};

int main(){

//	as as;
//	as.execute();
	heap<int> a(10);
	a.push(30);
	a.push(10);
	int index =a.push(20);

	a.data[index]=5;
	a.relax(index);

	printf("%d\n", a.top()); a.pop();
	printf("%d\n", a.top()); a.pop();
	printf("%d\n", a.top()); a.pop();

}
