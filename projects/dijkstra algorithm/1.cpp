#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <vector>
#include <math.h>
using namespace std;

#include "input.h"
#include "heap.h"
#include "state.h"
#include "astar.h"

input * file_output();
void dijkstra_first(input *);
int main()
{
    input * data=file_output();
    state Start_ST(data->C), End_ST(data->C);

    End_ST.carN=0;
    End_ST.nowT=INF;

    for(int car_n=0;car_n<data->C;car_n++){
        Start_ST.carV[car_n]=data->car_road[car_n][0];
        Start_ST.carFV[car_n]=data->car_road[car_n][0];
        Start_ST.carT[car_n]=0;
        Start_ST.car_FT.push(state::car_data(0, car_n));
        End_ST.carFV[car_n]=data->car_road[car_n][1];
    }
    state::data=data;
    Astar<state> astar = Astar<state>(Start_ST, End_ST, state::nexti, state::nextsize, state::h, data);

    turn * turn_data=new turn(data->C, data->V);
    Astar<state>::road result=astar.findpath(turn_data);
    printf("%d", result.second);
    return 0;
}

