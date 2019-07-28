//#ifndef STATE_H_INCLUDED
//#define STATE_H_INCLUDED
//
////HEADER START
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>
//#include <memory.h>
//#include <malloc.h>
//#include <math.h>
//#include <unordered_map>
//#include <unordered_set>
//
//#include <queue>
//#include <vector>
//#include <iostream>
//#include <algorithm>
//
//#include "heap.h"
//#include "astar.h"
//#include "input.h"
//
//using namespace std;
////HEADER END
//
//namespace statefunc{
//inline void hashbyte(std::size_t &h, uint8_t byte){
//	h ^= std::hash<int>{}(byte)  + 0x9e3779b9 + (h << 6) + (h >> 2);
//}
//inline void hashdata(std::size_t &h, void * data, size_t size){
//	for(uint32_t i=0; i<size; i++){
//		hashbyte(h, ((uint8_t *)data)[i]);
//	}
//}
//}
//using namespace statefunc;
//
//struct state{
//    struct car_data{
//        int car_FT;
//        int car_n;
//        car_data(int car_FT=0, int car_n=0){
//            this->car_FT = car_FT;
//            this->car_n = car_n;
//        }
//
//        bool operator < (const car_data &b) const{
//            return (car_FT)>(b.car_FT);
//        }
//    };
//    heap<car_data> car_FT;
//    int * carV;
//    int * carFV;
//    double * carT;
//    int carN;
//    double nowT;
//
////    static input * data;
//    state(int carN): \
//    		nowT(0), carN(carN), car_FT(carN),\
//			carV(new int[carN]), carFV(new int[carN]), carT(new double[carN]){}
//    ~state(){
//    	delete carV;
//    	delete carFV;
//    	delete carT;
//    }
//
//    static int h(state &now, state &end);
//    static int nextsize(state &now);
//    static Astar<state>::road a(int a);
//
////    bool operator
//};
////state::data=   ;
////input * state::data;
//namespace std {
//template <>
//struct hash<state> {
//	size_t operator()(const state& s) const {//hash {v, fv, (t-ft.top())}
//		std::size_t h = 0;
//		hashdata(h, s.carV, sizeof(int)*s.carN);	//hash v
//		hashdata(h, s.carFV, sizeof(int)*s.carN);	//hash fv
//		for(int i=0; i<s.carN; i++){				//hash (t-ft.top()
//			hashbyte(h, s.carT[i] - s.car_FT.top().car_FT);
//		}
//		return h;
//	}
//};
//}  // namespace std
//
////int state::h(state &now, state &end){
////    double distance=0.0;
////    for(int car_n=0;car_n<data->C;car_n++){
////        distance+=(sqrt(pow((data->v_xy[now.carFV[car_n]][0])-(data->v_xy[end.carFV[car_n]][0]), 2)\
////                    +pow((data->v_xy[now.carFV[car_n]][1])-(data->v_xy[end.carFV[car_n]][1]), 2)))/(data->c_speed[car_n]);
////    }
////    int distance2;
////    distance2=(int)(distance*100);
////    return distance2;
////}
////int state::nextsize(state &now){
////    car_data a;
////    a=now.car_FT.top();
////    int number=data->g[now.carFV[a.car_n]].size();
////    return number;
////}
////Astar<state>::road & state::nexti(state &now, int i){
////    state next;
////    memcpy(next.car_FT.data+1, now.car_FT.data+1, sizeof(car_data)*now.car_FT.heapsize);
////    memcpy(next.car_FT.index+1, now.car_FT.index+1, sizeof(int)*now.car_FT.heapsize);
////    next.car_FT.heapsize=now.car_FT.heapsize;
////    for(int car_n=0; car_n<data->C; car_n++){
////        next.carV[car_n]=now.carV[car_n];
////        next.carFV[car_n]=now.carV[car_n];
////        next.carT[car_n]=now.carT[car_n];
////    }
////
////    car_data a=next.car_FT.top();
////    edge FuV=data->g[next.carFV[a.car_n]][i];
////    int flowV=FuV.to;
////
////    next.carV[a.car_n]=now.carFV[a.car_n];
////    next.carFV[a.car_n]=flowV;
////    next.carT[a.car_n]=a.car_FT;
////    next.nowT=a.car_FT;
////    next.carN=now.carN;
////    if(next.carFV[a.car_n]==data->car_road[a.car_n][1]){
////        next.carN--;
////        next.car_FT.pop();
////    }
////
////    double flowtime=(FuV.len)/(data->c_speed[a.car_n]);
////    int flowtime2=(int)(100*flowtime);
////    for(int car_n=0;car_n<data->C;car_n++){
////        if(car_n!=a.car_n){
////            if(next.carV[car_n]==next.carV[a.car_n]){
////                if(next.carFV[car_n]==next.carFV[a.car_n]){
////                    if(next.car_FT.data[car_n+1].car_FT>next.carT[a.car_n]+flowtime2){
////                        flowtime2=next.car_FT.data[car_n+1].car_FT-next.carT[a.car_n];
////                    }
////                }
////            }
////        }
////    }
////    next.car_FT.data[a.car_n+1].car_FT+=flowtime2;
////
////    Astar<state>::road todis;
////    todis.first.carV=next.carV;
////    todis.first.carFV=next.carFV;
////    todis.first.carT=next.carT;
////    todis.first.nowT=next.nowT;
////    todis.first.car_FT.data=next.car_FT.data;
////    todis.first.car_FT.index=next.car_FT.index;
////    todis.first.car_FT.heapsize=next.car_FT.heapsize;
////    todis.first.carN=next.carN;
////    todis.second=flowtime2;
////    return todis;
////}
//
//#endif // STATE_H_INCLUDED

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
    state(int carN): \
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
    int number=data->g[now.carFV[a.car_n]].size();
    return number;
}
Astar<state>::road & state::nexti(state &now, int i){
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
    return todis;
}
namespace std {
template <>
struct hash<state> {
	size_t operator()(const state& s) const {//hash {v, fv, (t-ft.top())}
		std::size_t h = 0;
		hashdata(h, s.carV, sizeof(int)*s.carN);	//hash v
		hashdata(h, s.carFV, sizeof(int)*s.carN);	//hash fv
		for(int i=0; i<s.carN; i++){				//hash (t-ft.top()
			hashbyte(h, s.carT[i] - s.car_FT.top().car_FT);
		}
		return h;
	}
};
}  // namespace std
//state::data=   ;

#endif // _STATE_H_
