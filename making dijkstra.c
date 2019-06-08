#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // INT_MAX�� �̿�

#define MAX_V 100
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


// ���������� �� ���������� �ִ� �Ÿ��� ������ش�.
void printSolution(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}
*/
void dijkstra(int graph[V][V], int src)
{
    int dist[V]; // �ִ� �Ÿ��� �ľ��ϴ� �迭
    bool sptSet[V]; // �湮 �ߴ��� üũ �ϴ� bool�� �迭

    for (int i = 0; i<V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // �ʱ� ���� ����.
    dist[src] = 0;

    // V-1�� ������ �����Ѵٴ� ���� ù src��带 ������ ��� ���鿡 ������ �� ����� �Ѵٴ� �ǹ�.
    for (int count = 0; count < V - 1; count++)
    {
        // �ִܰŸ� ������ �˰� �ִ� ���� �� ���� �Ÿ��� ª�� ����� �ε����� �����´�.
        int u = minDistance(dist, sptSet);

        // �׷��� ���� ��� ������ Ž���ϸ� u ����� �ֺ� ������ �����Ѵ�.
        for (int v = 0; v < V; v++)
        {
            // 1. ���� ó���� ���� ���� ����̾�� �ϸ� (���ѷ��� ����)
            // 2. u-v ���� edge�� �����ϰ�
            // 3. src���� u������ ��ΰ� �����ϰ�
            // 4. ������ v�������� �ִܰŸ� ������ ���� ���Ǵ� �ִܰŸ��� �� ª�� ���
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[v] > dist[u] + graph[u][v])
            {
                // �ִܰŸ��� �������ش�.
                dist[v] = dist[u] + graph[u][v];
            }
        }

        // ���� �� ���(u)�� ������ ���� ����. �÷��׸� true�� ����.
        sptSet[u] = true;

        // ��������� �ִ� �Ÿ��� ������ش�.
        printSolution(dist, V);
    }
}

int pile_output(void * data){
	FILE *fp;
	fp=fopen("road.txt", "rt");
	if (fp==NULL) {}
	else {
		puts("���� ���� ����\n");
		return 0;
	}
    int V; //������ ����
    fscanf(fp, "%d", V);
    int (* input2)[V] = (int (*)[V])data;
    //ptr[10] => *(ptr+10)
	int road[V][V]; //���� ���� ���� �� : -1, ������ ����� �� : �� �� ������ �Ÿ� // ���ͽ�Ʈ�� �̿��� �׷���
	for (int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            fscanf(fp, "%d", input2[i][j]);//i������ j�������� �Ÿ�
            if (feof(fp))
                break;
        }
	}
	fclose(fp);
	//���� ���� ����
	return V;
}

int main()
{
    void * data = malloc(MAX_V^2);
    int V=pile_output(data);//int road[V][V] = (int (*)[V])data;

    // dijkstra(�ִ� �Ÿ��� ���ϰ��� �ϴ� �׷���(������), ���� �ϰ��� �ϴ� ����);
    dijkstra(road, 0);

    return 0;
}
