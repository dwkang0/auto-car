#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // INT_MAX에 이용

#define MAX_V 100
#define MAX_CAR 100
#define INF ((int)((((unsigned int)0)-((unsigned int)1))/2)-1)

/*
int minDistance(int dist[V], bool sptSet[V])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
    {
        if (!sptSet[v] && min > dist[v])
        {
            min_index = v;
            min = dist[v];
        }
    }

    return min_index;
}


// 시작점에서 그 정점까지의 최단 거리를 출력해준다.
void printSolution(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}
*/

int * file_output(void *, void *);
int dijkstra_first(int, int, void *, void *);
//void main_dijkstra(int, int, int, void *, void *);
//void dijkstra(int [V][V], int);
int main()
{
    void * data = malloc(MAX_V^2);
    void * data_c = malloc(MAX_CAR*2);
    int * VC=file_output(data, data_c);//int (* road)[V] = (int (*)[V])data; //int road[V][V]; 연결 되지 않은 길 : -1, 나머지 연결된 길 : 두 점 사이의 거리 // 다익스트라를 이용할 그래프
    int V=VC[0]; int C=VC[1]; int k=VC[2];
    free(VC);
    // main_dijkstra(정점 수, 최단 거리를 구하고자 하는 그래프(포인터));
    //main_dijkstra(V, C, k, data, data_c);
    int road=dijkstra_first(V, C, data, data_c);

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
int dijkstra_first(int V, int C, void * data, void * data_c){
    int (* car_road)[2]=(int (*)[2])data_c;
    int (* road)[V]=(int (*)[V])data;
    int roadtotal[V];
    memset(roadtotal, INF, sizeof(int));
    roadtotal[car_road[0][1]]=0;
    for(int i=0; i<V;i++){

    }
    return 0;
}
/*
void main_dijkstra(int V, int C, int k, void * data, void * data_c){
    int shortest[C];
}
*/
/*
void dijkstra(int graph[V][V], int src){
    int dist[V]; // 최단 거리를 파악하는 배열
    bool sptSet[V]; // 방문 했는지 체크 하는 bool형 배열

    for (int i = 0; i<V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // 초기 조건 설정.
    dist[src] = 0;

    // V-1번 루프를 수행한다는 것은 첫 src노드를 제외한 모든 노드들에 접근을 해 계산을 한다는 의미.
    for (int count = 0; count < V - 1; count++)
    {
        // 최단거리 정보를 알고 있는 노드들 중 가장 거리가 짧은 노드의 인덱스를 가져온다.
        int u = minDistance(dist, sptSet);

        // 그래프 상의 모든 노드들을 탐색하며 u 노드의 주변 정보를 갱신한다.
        for (int v = 0; v < V; v++)
        {
            // 1. 아직 처리가 되지 않은 노드이어야 하며 (무한루프 방지)
            // 2. u-v 간에 edge가 존재하고
            // 3. src부터 u까지의 경로가 존재하고
            // 4. 기존의 v노드까지의 최단거리 값보다 새로 계산되는 최단거리가 더 짧을 경우
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[v] > dist[u] + graph[u][v])
            {
                // 최단거리를 갱신해준다.
                dist[v] = dist[u] + graph[u][v];
            }
        }

        // 이제 이 노드(u)는 접근할 일이 없다. 플래그를 true로 설정.
        sptSet[u] = true;

        // 현재까지의 최단 거리를 출력해준다.
        printSolution(dist, V);
    }
}
*/

