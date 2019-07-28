#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

//HEADER START

#include <stdio.h>
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
#include "astar.h"

using namespace std;
//HEADER END

namespace statefunc{
inline void hashbyte(std::size_t &h, uint8_t byte){
	h ^= std::hash<int>{}(byte)  + 0x9e3779b9 + (h << 6) + (h >> 2);
}
inline void hashdata(std::size_t &h, void * data, size_t size){
	for(uint i=0; i<size; i++){
		hashbyte(h, ((uint8_t *)data)[i]);
	}
}
}
using namespace statefunc;

struct state{
    struct car_data{
        double car_FT;
        car_data(double car_FT=0.0): car_FT(car_FT){
            this->car_FT = car_FT;
        }

        bool operator < (const car_data &b) const{
            return (car_FT)>(b.car_FT);
        }
    };
    heap<car_data> car_FT;
    int * carV;
    int * carFV;
    double * carT;
    int carN;
    double nowT;

//    static input * data;
    state(int carN): \
    		nowT(0), carN(carN), car_FT(carN),\
			carV(new int[carN]), carFV(new int[carN]), carT(new double[carN]){}

    static int h(state &now, state &end);
    static int nextsize(state &now);
    static Astar<state>::road a(int a);
};
//state::data=   ;
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

#endif // STATE_H_INCLUDED
