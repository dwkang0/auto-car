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

using namespace std;

//HEADER END

//CLASS START
template <typename VT>
class Astar{
public:
	typedef pair<VT, int> road; // first: to, second: cost

	VT &startV;
	VT &endV;

	int (*nextsize)(VT &now);
	road& (*nexti)(VT &now, int i);
	int (*h)(VT &now, VT &end);

	Astar(VT startV, VT endV, \
			road& (*nexti)(VT &now, int i),int (*nextsize)(VT &now), \
			int (*h)(VT &now, VT &end)):\
			startV(*(VT*)malloc(sizeof(VT))), endV(*(VT*)malloc(sizeof(VT))),nexti(nexti), nextsize(nextsize), h(h)\
			{
		this->startV = startV;
		this->endV = endV;
			}
	~Astar(){
		free(&startV);
		free(&endV);
	}

	int findpath();
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
int Astar<VT>::findpath(){
	printf("aaa\n");
	unordered_map<VT, int> dis;
	unordered_set<VT> visit;
	priority_queue<road, vector<road>, Astar::roadcmp > q;

	dis.insert(road(startV, 0));
	q.push(road(startV, 0));

	road now, next;
	int i;
	while(!q.empty()){
		now = q.top(); q.pop();
		printf("%d %d\n",now.first, now.second);
		if(visit.find(now.first) != visit.end()) continue;
		if(now.first == endV){
			return now.second;
		}
		visit.insert(now.first);

		for(i=0; i<nextsize(now.first); i++){
			next = nexti(now.first, i);
			auto iter = dis.find(next.first);
			if(iter==dis.end()){
				dis.insert(road(next.first, now.second+next.second));
				q.push(road(next.first, now.second+next.second+h(next.first, endV)));
			}else{
				if(iter->second > now.second+next.second){
					iter->second = now.second+next.second;
					q.push(road(next.first, now.second+next.second+h(next.first, endV)));
				}
			}
		}
	}
	return -1;
}
//FUNCTION END

#endif
