#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <vector>
#include <math.h>
using namespace std;

#include "input.h"
#include "heap.h"
#include "astar.h"

input * file_output();
void ClearQueue(priority_queue<edge> &);
void dijkstra_first(input *);
int main()
{
    input * data=file_output();//int (* road)[V] = (int (*)[V])data; //int road[V][V]; ���� ���� ���� �� : -1, ������ ����� �� : �� �� ������ �Ÿ� // ���ͽ�Ʈ�� �̿��� �׷���
    state Start_ST, End_ST;
    Start_ST.carV=(int *)malloc(4*C);
    Start_ST.carFV=(int *)malloc(4*C);
    Start_ST.carT=(int *)malloc(4*C);
    End_ST.carV=(int *)malloc(4*C);
    End_ST.carFV=(int *)malloc(4*C);
    End_ST.carT=(int *)malloc(4*C);

    Start_ST.carN=data->C;
    Start_ST.nowT=0.0;
    End_ST.carN=data->C;
    End_ST.nowT=0.0;

    for(int car_n=0;car_n<C;car_n++){
        Start_ST.carV=data->
    }

    Astar<int> astar = Astar<int>(Start_ST, End_ST, state::nexti, state::nextsize, state::h);
    dijkstra_first(data);
    return 0;
}

void ClearQueue(priority_queue<edge> &someQueue){
    priority_queue<edge> empty;
    swap(someQueue, empty);
}
void dijkstra_first(input * data){
    int (* v_xy)[2]=(int (*)[2])data->data_v;
    int (* car_road)[2]=(int (*)[2])data->data_c;
    int V=data->V;  int C=data->C;
    float * speed=data->c_speed;
    double roadtotal[V];     int check[V];     int link[V];
    priority_queue<edge> road_t_q;      edge road_t;
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

        double car_roadtotal;    int data_link[V];
        car_roadtotal=roadtotal[car_road[car_n][1]];
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
        printf("��%d�� �Ÿ�:%.3f\n��%d�� �̵����:", (car_n+1), car_roadtotal/speed[car_n], (car_n+1));
        for(int i=0;i<linking;i++){
            printf("%d ", car_link[i]);
        }
        printf("\n");
    }
}

