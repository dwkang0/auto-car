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

    int (* v_xy)[2];
    int (* car_road)[2];

    ~input(){
        free(data_v);
        free(data_c);
        delete(g);
    }
};

input * file_output(){
	FILE *fp;
	fp=fopen("road.txt", "rt");
	if (fp!=NULL) {}
	else {
		puts("파일을 찾을 수 없습니다.\n");
		return 0;
	}

    input * data=(input *)malloc(sizeof(input));

    int V=9; //������ ����
    fscanf(fp, "%d", &V);   data->V=V;
    int E; //��������Ʈ ��
    fscanf(fp, "%d", &E);   data->E=E;
    int C; //�� ��
    fscanf(fp, "%d", &C);   data->C=C;

    data->data_v=(int *)malloc(4*V*2);
    data->data_c=(int *)malloc(4*C*2);
    data->c_speed=(float *)malloc(4*C);

    int (* data_v2)[2] = (int (*)[2])data->data_v;    //ptr[10] => *(ptr+10)
    int (* data_c2)[2]=(int (*)[2])data->data_c;

	for(int i=0;i<V;i++){
        fscanf(fp, "%*d %d %d", &data_v2[i][0], &data_v2[i][1]);//i���� ���� ��ǥ(x,y)
        if (feof(fp))
            break;
	}

	for(int i=0;i<C;i++){
        fscanf(fp, "%*d %d %d %f", &data_c2[i][0], &data_c2[i][1], &data->c_speed[i]);//i��° �� : (0)������ (1)������ �̵�
        if(feof(fp))
            break;
	}

	vector<int> * g = new vector<int>[3];
    data->g = new vector<edge>[V];
	int k1, k2; double dis_p2p;
	for(int i=0;i<E;i++){
        fscanf(fp, "%d %d", &k1, &k2);
        dis_p2p=sqrt(pow((data_v2[k1][0]-data_v2[k2][0]), 2)+pow((data_v2[k1][1]-data_v2[k2][1]), 2));
        data->g[k1].push_back(edge(k2, dis_p2p));
        data->g[k2].push_back(edge(k1, dis_p2p));
	}
	fclose(fp);
    data->v_xy=(int (*)[2])data->data_v;
    data->car_road=(int (*)[2])data->data_c;
	//���� ���� ����
	return data;
}

#endif // INPUT_H_INCLUDED
