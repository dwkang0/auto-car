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
    input * data=file_output();//int (* road)[V] = (int (*)[V])data; //int road[V][V]; 연결 되지 않은 길 : -1, 나머지 연결된 길 : 두 점 사이의 거리 // 다익스트라를 이용할 그래프
    state Start_ST, End_ST;
    Start_ST.carV=(int *)malloc(4*data->C);
    Start_ST.carFV=(int *)malloc(4*data->C);
    Start_ST.carT=(double *)malloc(8*data->C);
    End_ST.carV=(int *)malloc(4*data->C);
    End_ST.carFV=(int *)malloc(4*data->C);
    End_ST.carT=(double *)malloc(8*data->C);

    Start_ST.carN=data->C;
    Start_ST.nowT=0.0;
    End_ST.carN=data->C;
    Start_ST.nowT=(double)INF;

    for(int car_n=0;car_n<data->C;car_n++){
        Start_ST.carV[car_n]=data->car_road[car_n][0];
        Start_ST.carFV[car_n]=data->car_road[car_n][0];
        Start_ST.carT[car_n]=0.0;
        Start_ST.car_FT.push(state::car_data(0.0, car_n));
        End_ST.carFV=data->car_road[car_n][1];
    }
    Start_ST.data=data;
    End_ST.data=data;
    Astar<state> astar = Astar<state>(sizeof(state), Start_ST, End_ST, state::nexti, state::nextsize, state::h);
    return 0;
}

