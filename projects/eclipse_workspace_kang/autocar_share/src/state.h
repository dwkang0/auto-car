#ifndef _STATE_H_
#define _STATE_H_

//HEADER START

#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>
#include <malloc.h>
#include <unordered_map>
#include <unordered_set>

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

#include "heap.h"
#include "input.h"
#include "astar.h"
#include "log.h"

using namespace std;
//HEADER END

namespace statefunc{
inline void hashbyte(std::size_t &h, uint8_t byte){
	h ^= std::hash<int>{}(byte)  + 0x9e3779b9 + (h << 6) + (h >> 2);
}
inline void hashdata(std::size_t &h, void * data, size_t size){
	for(uint32_t i=0; i<size; i++){
		hashbyte(h, ((uint8_t *)data)[i]);
	}
}
}
using namespace statefunc;

struct state{
	struct car_data{
		int car_FT;
		int car_n;
		car_data(int car_FT=0, int car_n=0){
			this->car_FT = car_FT;
			this->car_n = car_n;
		}

		bool operator < (const car_data &b) const{
			return (car_FT)>(b.car_FT);
		}
	};
	heap<car_data> car_FT;
	int * carV;
	int * carFV;
	int * carT;
	int carN;
	int nowT;
	static input * data;

	void destruction(){
		delete carV;
		delete carFV;
		delete carT;
		delete car_FT.index;
		delete car_FT.data;
	}
	void deep_copy(const state &from){//보통은 destroction, 메모리 할당 필요
		memcpy(this->car_FT.data, from.car_FT.data, sizeof(car_data)*(from.car_FT.heapsize+1));
		memcpy(this->car_FT.index, from.car_FT.index, sizeof(int)*(from.car_FT.heapsize+1));
		this->car_FT.heapsize = from.car_FT.heapsize;
		this->car_FT.maxsize = from.car_FT.maxsize;

		memcpy(this->carV, from.carV, sizeof(int)*carN);
		memcpy(this->carFV, from.carFV, sizeof(int)*carN);
		memcpy(this->carT, from.carT, sizeof(int)*carN);

		this->carN = from.carN;
		this->nowT = from.nowT;
	}
	state(const state &s):\
			nowT(s.nowT), carN(s.carN), car_FT(s.carN),\
			carV(new int[s.carN]), carFV(new int[s.carN]), carT(new int[s.carN]) {
		deep_copy(s);
	}
	state(int carN=0): \
			nowT(0), carN(carN), car_FT(carN),\
			carV(new int[carN]), carFV(new int[carN]), carT(new int[carN]){}
	~state(){
		delete carV;
		delete carFV;
		delete carT;
	}

	static int h(state &now, state &end);
	static int nextsize(state &now);
	static Astar<state>::road & nexti(state &now, int i);

	state & operator = (const state & b){
		destruction();
		nowT=b.nowT;
		carN=b.carN;
		car_FT.data = new car_data[b.carN+1];
		car_FT.index = new int[b.carN+1];
		car_FT.heapsize=b.car_FT.heapsize;
		car_FT.maxsize=b.car_FT.maxsize;
		carV =new int[b.carN];
		carFV =new int[b.carN];
		carT =new int[b.carN];
		deep_copy(b);
//		memcpy(this, &b, sizeof(state));
		return *this;
	}
	bool operator == (const state &b) const;
};
input* state::data;
int state::h(state &now, state &end){
	double distance=0.0;
	for(int car_n=0;car_n<data->C;car_n++){
		distance+=(sqrt(pow((data->v_xy[now.carFV[car_n]][0])-(data->v_xy[end.carFV[car_n]][0]), 2)\
				+pow((data->v_xy[now.carFV[car_n]][1])-(data->v_xy[end.carFV[car_n]][1]), 2)))/(data->c_speed[car_n]);
	}
	int distance2;
	distance2=(int)(distance*100);
	return distance2;
}
int state::nextsize(state &now){
	car_data a;
	a=now.car_FT.top();
	log("%d, %d][][]", now.carFV[a.car_n], a.car_n);
	int number=data->g[now.carFV[a.car_n]].size();
	return number;
}
Astar<state>::road & state::nexti(state &now, int i){
	log("nexti:");
	car_data a=now.car_FT.top();
	edge FuV=data->g[now.carFV[a.car_n]][i];
	int flowV=FuV.to;

	int carnumber=now.carN;
	if(flowV==data->car_road[a.car_n][1]){
		carnumber--;
	}

	state next(carnumber);
	memcpy(next.car_FT.data+1, now.car_FT.data+1, sizeof(car_data)*now.car_FT.heapsize);
	memcpy(next.car_FT.index+1, now.car_FT.index+1, sizeof(int)*now.car_FT.heapsize);
	next.car_FT.heapsize=now.car_FT.heapsize;
	for(int car_n=0; car_n<data->C; car_n++){
		next.carV[car_n]=now.carV[car_n];
		next.carFV[car_n]=now.carFV[car_n];
		next.carT[car_n]=now.carT[car_n];
	}

	next.carV[a.car_n]=now.carFV[a.car_n];
	next.carFV[a.car_n]=flowV;
	next.carT[a.car_n]=a.car_FT;
	next.nowT=a.car_FT;
	next.carN=carnumber;
	if(next.carN!=now.carN){
		next.car_FT.pop();
	}

	double flowtime=(FuV.len)/(data->c_speed[a.car_n]);
	int flowtime2=(int)(100*flowtime);
	for(int car_n=0;car_n<data->C;car_n++){
		if(car_n!=a.car_n){
			if(next.carV[car_n]==next.carV[a.car_n]){
				if(next.carFV[car_n]==next.carFV[a.car_n]){
					if(next.car_FT.data[car_n+1].car_FT>next.carT[a.car_n]+flowtime2){
						flowtime2=next.car_FT.data[car_n+1].car_FT-next.carT[a.car_n];
					}
				}
			}
		}
	}
	next.car_FT.data[a.car_n+1].car_FT+=flowtime2;

	Astar<state>::road todis(next, flowtime2);
	log("nexti end");
	return todis;
}
namespace std {
template <>
struct hash<state> {
	size_t operator()(const state& s) const {//hash {v, fv, (t-ft.top())}
		printf("hash:\n");
		std::size_t h = 0;
		unsigned int temp, t2;
		hashdata(h, s.carV, sizeof(int)*s.carN);	//hash v
		hashdata(h, s.carFV, sizeof(int)*s.carN);	//hash fv
		for(int i=0; i<s.carN; i++){				//hash (t-ft.top()
			temp = s.carT[i];
			int t2=s.car_FT.top().car_FT;
			temp-=t2;
			//            s.car_FT.top();
			hashbyte(h, temp&(0xff));
			hashbyte(h, (temp&(0xff00))>>8);
			hashbyte(h, (temp&(0xff0000))>>16);
			hashbyte(h, (temp&(0xff000000))>24);

		}
		printf("hash end\n\n");
		return h;
	}
};
}  // namespace std

bool state::operator == (const state &b) const{
	hash<state> h;
	return h(*this) == h(b);
}

//state::data=   ;

#endif // _STATE_H_
