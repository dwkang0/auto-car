#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <vector>
#include <math.h>
using namespace std;
#define MAX_V 100
#define MAX_CAR 100
#define INF ((int)((((unsigned int)0)-((unsigned int)1))/2)-1)

#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
struct edge{
    int to;
    double len;
    edge(int to=0, double len=0.0){
        this->to = to;
        this->len = len;
    }
    bool operator < (const edge &b) const{
        return (this->len)>(b.len);
    }
};
// edge e(1, 2)

struct input{
    int V, E, C;
    int * data_v;
    int * data_c;
    float * c_speed;
    vector<edge> *g;

    ~input(){
        free(data_v);
        free(data_c);
        delete(g);
    }
};
#endif // INPUT_H_INCLUDED
