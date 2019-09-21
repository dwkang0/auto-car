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
//void dijkstra_first(input *);
int main(){
	log("startProgram");

	input * data=file_output("road_40.txt");
	log("inputEND\n");
	//    printf("dd");
	state Start_ST(data->C), End_ST(data->C);

	End_ST.carN=0;
	End_ST.nowT=INF;
	//    printf("asd");

	for(int car_n=0;car_n<data->C;car_n++){
		Start_ST.carV[car_n]=data->car_road[car_n][0];
		Start_ST.carFV[car_n]=data->car_road[car_n][0];
		Start_ST.carT[car_n]=0;
		Start_ST.car_FT.push(state::car_data(0, car_n));
		End_ST.carFV[car_n]=data->car_road[car_n][1];
		End_ST.carV[car_n]=data->car_road[car_n][1];
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

//	turn * turn_data=new turn(data->C, data->V);
//	Astar<state>::road result=astar.findpath(turn_data);
	vector<state> path=astar.findpath();
	vector<int> pathforcar[data->C];

	int moveCar;
	printf("\n###############################\ncar move tracker\n");
	for(int i=0; i<path.size()-1; i++){
		moveCar = path[i].car_FT.data[path[i].car_FT.index[1]].car_n;
		pathforcar[moveCar].push_back( path[i+1].carFV[moveCar] );
		printf("car %d: ",moveCar);
		if(pathforcar[moveCar].size() == 1){
			printf("%d",path[0].carV[moveCar]);
		}else{
			printf("%d",pathforcar[moveCar][pathforcar[moveCar].size()-2]);
		}
		printf(" -> %d\n",pathforcar[moveCar][pathforcar[moveCar].size()-1]);
	}
	printf("\n\npaths for all cars:\n");
	for(int i=0; i<data->C; i++){
		printf("car %d | %d ",i, path[0].carV[i]);
		for(int j=0; j<pathforcar[i].size()-1; j++){
			printf("-> %d", pathforcar[i][j]);
		}
		printf("\n");
	}

//	printf("%d", result.second);



	return 0;
}

