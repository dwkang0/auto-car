//============================================================================
// Name        : ttt.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
#include "state.h"
#include "heap.h"
using namespace std;

struct roadcmp{
	bool operator()(const pair<state, int> & a, const pair<state, int> & b) const
	{
		return a.second > b.second;
	}
};

int main() {
//	heap<pair<state, int>, roadcmp> q(100);
//	pair<state, int> a(3, 2);
//	a.first.car_FT.push(state::car_data(1, 2));
//	a.first.car_FT.push(state::car_data(2, 3));
//	a.first.car_FT.push(state::car_data(-1, 2));
//	a.first.ts=10;
//	q.push(a);
//	state b(a.first);
//	printf("%d, %d\n", a.first.ts, q.top().first.ts);
//	printf("%d, %d\n", a.first.car_FT.index[2],q.top().first.car_FT.index[2]);
////	printf("%d\n", a.first.car_FT.index[1]);
////	printf("%d\n", a.first.car_FT.top().car_FT);  a.first.car_FT.pop();
////	printf("%d\n", a.first.car_FT.top().car_FT);  a.first.car_FT.pop();
////	printf("%d\n", a.first.car_FT.top().car_FT);  a.first.car_FT.pop();
////	q.push(state(0));

	heap<int> a(100);

	a.push(10);
	a.push(9);
	a.push(15);
	a.push(15);
	a.push(24);
	a.push(1);
	a.push(30);
	a.push(2);

//	a.pop();
//	a.pop();
//	a.pop();
//	a.pop();
//	a.pop();
//	a.pop();
//	a.pop();
//	a.pop();
	while(a.heapsize!=0){
		printf("%d\n", a.top()); a.pop();
	}
	return 0;
}
