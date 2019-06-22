#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_V 100
#define MAX_CAR 100
#define INF ((int)((((unsigned int)0)-((unsigned int)1))/2)-1)

int * file_output(void *, void *);
void dijkstra_first(int, int, void *, void *);
int main()
{
    void * data = malloc(MAX_V^2);
    void * data_c = malloc(MAX_CAR*2);
    int * VC=file_output(data, data_c);//int (* road)[V] = (int (*)[V])data; //int road[V][V]; 연결 되지 않은 길 : -1, 나머지 연결된 길 : 두 점 사이의 거리 // 다익스트라를 이용할 그래프
    int V=VC[0]; int C=VC[1]; int k=VC[2];
    free(VC);
    // main_dijkstra(정점 수, 최단 거리를 구하고자 하는 그래프(포인터));
    //main_dijkstra(V, C, k, data, data_c);
    dijkstra_first(V, C, data, data_c);
    return 0;
}
int * file_output(void * data, void *data_c){
	FILE *fp;
	fp=fopen("road.txt", "rt");
	if (fp==NULL) {}
	else {
		puts("파일 오픈 실패\n");
		return 0;
	}
    int V; //교차로 개수
    fscanf(fp, "%d", V);
    int C; //차 수
    fscanf(fp, "%d", C);
    int k; //k번째 값
    fscanf(fp, "%d", k);
    int (* data2)[V] = (int (*)[V])data;
    //ptr[10] => *(ptr+10)
	for (int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            fscanf(fp, "%d", data2[i][j]);//i점에서 j점까지의 거리
            if(data2[i][j]==-1){
                data2[i][j]=INF;
            }
            if (feof(fp))
                break;
        }
	}
	int (* data_c2)[2]=(int (*)[2])data_c;
	for (int i=0;i<C;i++){
        for(int j=0;j<2;j++){
            fscanf(fp, "%d", data_c2[i][j]);//차 : i점에서 j점으로 이동
            if(feof(fp))
                break;
        }
	}
	fclose(fp);
	//파일 정보 참조
	int * returnal = (int *)malloc(sizeof(int)*3);
	returnal[0]=V; returnal[1]=C; returnal[2]=k;
	return returnal;
}
void dijkstra_first(int V, int C, void * data, void * data_c){
    int (* car_road)[2]=(int (*)[2])data_c;
    int (* road)[V]=(int (*)[V])data;
    int roadtotal[V];                       int check[V];                       int link[V];
    memset(roadtotal, INF, sizeof(int));    memset(check, 0, sizeof(int));      memset(link, -1, sizeof(int));
    roadtotal[car_road[0][1]]=0;
    link[car_road[0][1]]=car_road[0][1];
    int u; int u_n;
    for(int c=0; c<V-1; c++){
        u_n=INF;
        u=-1;
        for(int i=0; i<V; i++){
            if((check[i]==0)&&(roadtotal[i]<u_n)){
                u=i;
                u_n=roadtotal[i];
            }
        }
        if(u>-1){
            for(int v=0; v<V; v++){
                if((check[v]==0)&&(road[u][v]>=0)){
                    if(roadtotal[u]<roadtotal[v]-road[u][v]){
                        roadtotal[v]=roadtotal[u]+road[u][v];
                        link[v]=u;
                    }
                }
            }
            check[u]=1;
        }
    }
    int car_roadtotal;    int data_link[V];
    car_roadtotal=roadtotal[car_road[0][2]];
    memset(data_link, -1, sizeof(int));
    data_link[0]=car_road[0][2];
    int linking;
    for(int i=1;i<V;i++){
        data_link[i]=link[data_link[i-1]];
        if(data_link[i]==car_road[0][1]){
            linking=i+1;
            break;
        }
    }
    int car_link[linking];
    for(int i=0;i<linking;i++){
        car_link[linking-i-1]=data_link[i];
    }
    printf("차1의 거리:%d\n차1의 이동경로:", car_roadtotal);
    for(int i=0;i<linking;i++){
        printf("%d ", car_link[i]);
    }
}
