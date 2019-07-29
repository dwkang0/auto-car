#ifndef _ASTAR_H_
#define _ASTAR_H_

//HEADER START

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>
#include <malloc.h>
#include <unordered_map>
#include <unordered_set>

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>


#include "log.h"
class state;

#include "state.h"
#include "input.h"

using namespace std;

//HEADER END

struct turn{
    int *data_link;
    int V;
    turn (int C, int V):\
        data_link((int *)malloc(4*C*V)), V(V)\
        {
            memset(data_link, -1, sizeof(int)*C*V);
        }

    int &link(int i, int j){
        return data_link[i*V+j];
    }
};

//CLASS START
template <typename VT>
class Astar{
public:
	typedef pair<VT, int> road; // first: to, second: cost

	VT *startV;
	VT *endV;

	int (*nextsize)(VT &now);
	road& (*nexti)(VT &now, int i);
	int (*h)(VT &now, VT &end);
	input * data;

	Astar(VT &startV, VT &endV, \
			road& (*nexti)(VT &now, int i),int (*nextsize)(VT &now), \
			int (*h)(VT &now, VT &end), input *data):\
			startV((VT*)malloc(sizeof(VT))), endV((VT*)malloc(sizeof(VT))),nexti(nexti), nextsize(nextsize), h(h), data((input*)malloc(sizeof(input)))\
			{
		log("Astar():");
		memcpy(this->startV, &startV, sizeof(VT));
		memcpy(this->endV, &endV, sizeof(VT));
		memcpy(&this->data, &data, sizeof(input));

		log("index,,%d",this->startV->car_FT.index[1]);
		log("Astar() end\n");
			}
	~Astar(){
		free(startV);
		free(endV);
	}

	road findpath(turn *);
	struct roadcmp{
		bool operator()(const road & a, const road & b) const
		{
			return a.second > b.second;
		}
	};

//	struct hashVT {
//	    std::size_t operator()(const VT & a) const{
//	        std::size_t h = 0;
//	        for (int i= 0; i<astar::VTsize; i++) {
//	        	h ^= std::hash<int>{}(((unsigned char *)&a)[i])  + 0x9e3779b9 + (h << 6) + (h >> 2);
//	        }
//	        return h;
//	    }
//	};
};
//CLASS END

//FUNCTION START
template <typename VT>

typename Astar<VT>::road Astar<VT>::findpath(turn * turn_data){
	log("in findPath:");
	unordered_map<VT, int> dis;
	unordered_set<VT> visit;
//	priority_queue<road, vector<road>, Astar::roadcmp > q;
	heap<road, Astar::roadcmp > q(1000000);
	log("in findpath: index[1]:%d",startV->car_FT.index[1]);

	dis.insert(road(*startV, 0));
	q.push(road(*startV, 0));
	road now, next;

	int i;
	while(q.heapsize){
		now = q.top(); q.pop();
		log("inwhile: %p, index[1]: %d",&now.first, now.first.car_FT.index[1]);
		if(visit.find(now.first) != visit.end()) continue;
		if(now.first == *endV){
			return now;
		}
        now.first.printstate();
        printf("point:%d\n", now.second);
		visit.insert(now.first);
		now.second = dis.find(now.first)->second;
		printf("total:%d\n", now.second);

		for(i=0; i<nextsize(now.first); i++){
			next = nexti(now.first, i);
			printf("add next to queue:\n");
//			next.first.printstate();
			auto iter = dis.find(next.first);
			if(iter==dis.end()){
                int carnumber;
                for(carnumber=0;carnumber<data->C;carnumber++){
                    if(next.first.carT[carnumber]==next.first.nowT)
                        break;
                }
                turn_data->link(carnumber, next.first.carFV[carnumber])=next.first.carV[carnumber];
				dis.insert(road(next.first, now.second+next.second));
				q.push(road(next.first, now.second+next.second+h(next.first, *endV)));
			}else{
				if(iter->second > now.second+next.second){
				    int carnumber;
                    for(carnumber=0;carnumber<data->C;carnumber++){
                        if(next.first.carT[carnumber]==next.first.nowT)
                            break;
                    }
                    turn_data->link(carnumber, next.first.carFV[carnumber])=next.first.carV[carnumber];
					iter->second = now.second+next.second;
					q.push(road(next.first, now.second+next.second+h(next.first, *endV)));
				}
			}
		}
	}
	return road(*startV, -1);
}
//FUNCTION END
#endif
