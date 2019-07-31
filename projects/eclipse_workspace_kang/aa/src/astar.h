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
	//typename unordered_map<VT,int>::iterator;
	vector<VT> findpath();
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
vector<VT> Astar<VT>::findpath(){
	log("in findPath:");
	unordered_map<VT, int> dis;
	unordered_set<VT> visit;
//	typename unordered_map<VT,int>::iterator a;
	unordered_map<VT, VT> path_before;//<now, before>
	heap<road, Astar::roadcmp > q(1000000);
	log("in findpath: index[1]:%d",startV->car_FT.index[1]);

	dis.insert(road(*startV, 0));
	path_before.insert(pair<VT, VT>(*startV, *startV));
	q.push(road(*startV, 0));
	road now, next;

	int i;
	while(q.heapsize){
		now = q.top(); q.pop();
		log("inwhile: %p, index[1]: %d",&now.first, now.first.car_FT.index[1]);
		if(visit.find(now.first) != visit.end()) continue;
		if(nextsize(now.first)==0){
//		if(now.first == *endV){////////////todo
			VT *nowVt = new VT(dis.find(*endV)->first);
			vector<VT *> _path;
			printf("resault:\n");
			while(!(*nowVt == *startV)){
				nowVt->printstate();
				nowVt= &(path_before.find(*nowVt)->second);
				_path.push_back(nowVt);
			}
			vector<VT> path;
			for(int i=_path.size()-1; i>=0; i--){
				path.push_back(*_path[i]);
			}
			return path;
		}
//		printf("\n\n\n\n");
//      now.first.printstate();
//      printf("point:%d\n", now.second);
		visit.insert(now.first);
		now.second = dis.find(now.first)->second;
//		printf("total:%d\n", now.second);

		for(i=0; i<nextsize(now.first); i++){
			next = nexti(now.first, i);
//			printf("add next to queue:\n");
//			next.first.printstate();
			auto iter = dis.find(next.first);
			if(iter==dis.end()){
				dis.insert(road(next.first, now.second+next.second));
				path_before.insert(pair<VT, VT>(next.first, now.first));
				q.push(road(next.first, now.second+next.second+h(next.first, *endV)));
			}else{
				if(iter->second > now.second+next.second){
					iter->second = now.second+next.second;
					auto iter_path = path_before.find(next.first);
					iter_path->second = now.first;
					q.push(road(next.first, now.second+next.second+h(next.first, *endV)));
				}
			}
		}
	}

	return vector<VT>();
}
//FUNCTION END
#endif
