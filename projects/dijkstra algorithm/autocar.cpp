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

input * file_output(char*);
//void dijkstra_first(input *);
int main(int argc, char* argv[])
{
	log("startProgram");
    log
    ("%d   ", argc);
    log("%s", argv[1]);
	input * data=file_output(argv[1]);
	log("inputEND\n");
	//    printf("dd");
	state Start_ST(data->C), End_ST(data->C);

	End_ST.nowT=INF;
	//    printf("asd");

	for(int car_n=0;car_n<data->C;car_n++){
		Start_ST.carV[car_n]=data->car_road[car_n][0];
		Start_ST.carFV[car_n]=data->car_road[car_n][0];
		Start_ST.carT[car_n]=0;
		Start_ST.car_FT.push(state::car_data(0, car_n));
		End_ST.carFV[car_n]=data->car_road[car_n][1];
	}
	log("start.index[1]:%d", Start_ST.car_FT.index[1]);
//	log("%p,%p,%p,%p",&Start_ST.car_FT.index, &Start_ST, &End_ST.car_FT.index, &End_ST);
//	log("size:%d",sizeof(state));
//	log("%p| start_ST.index... :%p",&Start_ST, &Start_ST.car_FT.index);

	state::data=data;

//	log("%p| start_ST.index... :%d\n",&Start_ST, Start_ST.car_FT.index[1]);
//	log("%p| start_ST.index... :%d\n",&Start_ST, Start_ST.car_FT.index[1]);
//	log("%p| size:%d, carN:%d, index,,%d\n",index,sizeof(state), s->carN, Start_ST.car_FT.index[1]);

	Astar<state> astar = Astar<state>(Start_ST, End_ST, state::nexti, state::nextsize, state::h, data);
//	log("%p| start_ST.index... :%d\n",&Start_ST, Start_ST.car_FT.index[1]);

    turn * turn_data=new turn(data->C, data->V);
    Astar<state>::road result=astar.findpath(turn_data);
    int linkingdata[data->V];
    int linking;
    for(int c=0;c<data->C;c++){
        linkingdata[0]=data->car_road[c][1];
        for(int i=1;i<data->V;i++){
            linkingdata[i]=turn_data->link(c, linkingdata[i-1]);
            if(linkingdata[i]==data->car_road[c][0]){
                linking=i+1;
                break;
            }
        }
        printf("�� %d �̵���� : \n", c);
//        for(int i=0;i<linking+1;i++){
//            printf("%d ", linkingdata[linking-i-1]);
//        }
        printf("�̵� �ð� : %d\n\n", result.first.carT[c]);
    }
    printf("%d", result.second);

	log("endProgram");
	return 0;
}
