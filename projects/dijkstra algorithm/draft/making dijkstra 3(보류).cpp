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
vector<edge> *g;

int * file_output(void *, void *);
void dijkstra_first(int, int, void *, void *);
int main()
{
    void * data_v = malloc(4*MAX_V*2);
    void * data_c = malloc(4*MAX_CAR*2);
    int * VC=file_output(data_v, data_c);//int (* road)[V] = (int (*)[V])data; //int road[V][V]; ���� ���� ���� �� : -1, ������ ����� �� : �� �� ������ �Ÿ� // ���ͽ�Ʈ�� �̿��� �׷���
    int V=VC[0]; int C=VC[1];
    free(VC);
    dijkstra_first(V, C, data_v, data_c);
    return 0;
}
int * file_output(void * data_v, void *data_c){
	FILE *fp;
	fp=fopen("road.txt", "rt");
	if (fp!=NULL) {}
	else {
		puts("���� ���� ����\n");
		return 0;
	}
    int V; //������ ����
    fscanf(fp, "%d", &V);
    int E; //��������Ʈ ��
    fscanf(fp, "%d", &E);
    int C; //�� ��
    fscanf(fp, "%d", &C);
    int (* data_v2)[2] = (int (*)[2])data_v;    //ptr[10] => *(ptr+10)
	for(int i=0;i<V;i++){
        fscanf(fp, "%*d %d %d", &data_v2[i][0], &data_v2[i][1]);//i���� ���� ��ǥ(x,y)
        if (feof(fp))
            break;
	}
	int (* data_c2)[2]=(int (*)[2])data_c;
	for(int i=0;i<C;i++){
        fscanf(fp, "%*d %d %d", &data_c2[i][0], &data_c2[i][1]);//i��° �� : (0)������ (1)������ �̵�
        if(feof(fp))
            break;
	}
    g = (vector<edge> *) malloc(sizeof(vector<edge>)*V);
	int k1, k2; double dis_p2p;
	for(int i=0;i<E;i++){
        fscanf(fp, "%d %d", &k1, &k2);
        dis_p2p=sqrt(pow((data_v2[k1][0]-data_v2[k2][0]), 2)+pow((data_v2[k1][1]-data_v2[k2][1]), 2));
        g[k1].push_back(edge(k2, dis_p2p));
        g[k2].push_back(edge(k1, dis_p2p));
	}
	fclose(fp);
	//���� ���� ����
	int * returnal = (int *)malloc(sizeof(int)*2);
	returnal[0]=V; returnal[1]=C;
	return returnal;
}
void dijkstra_first(int V, int C, void * data_v, void * data_c){
    int (* car_road)[2]=(int (*)[2])data_c;
    double roadtotal[V];                             int check[V];                         int link[V];
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
            if(check[u]==0){
                for(int i=0; i<g[u].size(); i++){
                    int v=g[u][i].to;
                    if(check[v]==0){
                        if(roadtotal[u]<roadtotal[v]-g[u][i].len){
                            roadtotal[v]=roadtotal[u]+g[u][i].len;
                            road_t_q.push(edge(v, roadtotal[v]));
                            link[v]=u;
                            printf("%d -> %d : %f\n", u, v, roadtotal[v]);
                        }
                    }
                }
                check[u]=1;
            }
        }
        int car_roadtotal;    int data_link[V];
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
        printf("��%d�� �Ÿ�:%d\n��%d�� �̵����:", (car_n+1), car_roadtotal, (car_n+1));
        for(int i=0;i<linking;i++){
            printf("%d ", car_link[i]);
        }
        printf("\n");
    }
}

