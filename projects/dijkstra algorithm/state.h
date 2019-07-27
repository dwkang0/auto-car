#include "heap.h"
#include "astar.h"

#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
struct state{
    struct car_data{
        double car_FT;
        state(double car_FT=0.0){
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

    static input * data;

    static int h(state &now, state &end);
    static int nextsize(state &now);
    static Astar<state>::road& nexti(state &now, int i);
};
//state::data=   ;

#endif // STATE_H_INCLUDED
