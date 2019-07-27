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

    static int h(state &now, state &end);
    static int nextsize(state &now);
//    static Astar11<state>::roadve& nexti(state &now, int i);
    static Astar<state>::road a(int a);
};
//state::data=   ;
namespace std {
template <>
struct hash<state> {
  size_t operator()(const state& s) const {//hash v, fv, (t-ft.top())
//	        std::size_t h = 0;
//	        for (int i= 0; i<10; i++) {
//	        	h ^= std::hash<int>{}(((unsigned char *)&a)[i])  + 0x9e3779b9 + (h << 6) + (h >> 2);
//	        }
//	        return h;
  }
};
}  // namespace std

#endif // STATE_H_INCLUDED
