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
void dijkstra_first(input *, double *);
void ClearQueue(priority_queue<edge> &);
int main(int argc, char* argv[])
{
	log("startProgram");
    log
    ("%d   ", argc);
    log("%s", argv[1]);
	input * data=file_output(argv[1]);
	log("inputEND\n");

    double * traffic;
    traffic=(double *)malloc(8*data->V*data->V);
    dijkstra_first(data, traffic);

	state Start_ST(data->C), End_ST(data->C);

	End_ST.nowT=INF;

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
        printf("차 %d 이동경로 : \n", c);
//        for(int i=0;i<linking+1;i++){
//            printf("%d ", linkingdata[linking-i-1]);
//        }
        printf("이동 시간 : %d\n\n", result.first.carT[c]);
    }
    printf("%d", result.second);

	log("endProgram");
	return 0;
}
void ClearQueue(priority_queue<edge> &someQueue){
    priority_queue<edge> empty;
    swap(someQueue, empty);
}
void dijkstra_first(input * data, double * traffic2){
    int (* v_xy)[2]=(int (*)[2])data->data_v;
    int (* car_road)[2]=(int (*)[2])data->data_c;
    int V=data->V;  int C=data->C;
    float * speed=data->c_speed;
    double roadtotal[V];     int check[V];     int link[V];
    priority_queue<edge> road_t_q;      edge road_t;
    double (* traffic)[V]=(double (*)[V])traffic2;
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            traffic[i][j]=0.0;
        }
    }

    for(int car_n=0;car_n<C;car_n++){
        for(int i=0;i<V;i++){
            roadtotal[i]=INF;
            check[i]=0;
            link[i]=-1;
        }
        roadtotal[car_road[car_n][0]]=0;
        road_t_q.push(edge(car_road[car_n][0], 0));
        link[car_road[car_n][0]]=car_road[car_n][0];
        int u;
        while(!road_t_q.empty()){
            road_t=road_t_q.top(); road_t_q.pop();
            u=road_t.to;
            if(u==car_road[car_n][1]){
                break;
            }
            if(check[u]==0){
                for(int i=0; i<data->g[u].size(); i++){
                    int v=data->g[u][i].to; double h;
                    if(check[v]==0){
                        if(roadtotal[u]<roadtotal[v]-data->g[u][i].len){
                            roadtotal[v]=roadtotal[u]+data->g[u][i].len;
                            h=sqrt(pow((v_xy[v][0]-v_xy[car_road[car_n][1]][0]), 2)+pow((v_xy[v][1]-v_xy[car_road[car_n][1]][1]), 2));
                            road_t_q.push(edge(v, roadtotal[v]+h));
                            link[v]=u;
                        }
                    }
                }
                check[u]=1;
            }
        }
        ClearQueue(road_t_q);

        int data_link[V];
        for(int i=0;i<V;i++){
            data_link[i]=-1;
        }
        data_link[0]=car_road[car_n][1];
        int linking=V;
        for(int i=1;i<V;i++){
            data_link[i]=link[data_link[i-1]];
            if(data_link[i]==car_road[car_n][0]){
                linking=i+1;
                break;
            }
        }
        int car_link[linking];
        for(int i=0;i<linking;i++){
            car_link[linking-i-1]=data_link[i];
        }
        for(int i=0;i<linking-1;i++){
            traffic[car_link[i]][car_link[i+1]]+=1.0;
            for(int j=0;j<V;j++){
                if(j!=car_link[i+1]){
                    traffic[j][car_link[i]]+=(1.0/(double)(data->g[i].size()));
                }
                if(j!=car_link[i]){
                    traffic[car_link[i+1]][j]+=(1.0/(double)(data->g[i+1].size()));
                }
            }
        }
    }
    for(int i=0; i<V;i++){
        for(int j=0; j<V;j++){
            if(traffic[i][j]<1.0){
                traffic[i][j]=1.0;
            }
        }
    }
}

