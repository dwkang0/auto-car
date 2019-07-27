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
namespace astar{
int VTsize=4;
}
template <typename VT>
class Astar{
public:
	typedef pair<VT, int> road; // first: to, second: cost

	int VTsize;

	VT &startV;
	VT &endV;

	int (*nextsize)(VT &now);
	road& (*nexti)(VT &now, int i);
	int (*h)(VT &now, VT &end);

	Astar(int VTsize, VT startV, VT endV, \
			road& (*nexti)(VT &now, int i),int (*nextsize)(VT &now), \
			int (*h)(VT &now, VT &end)):\
			VTsize(VTsize), startV(startV), endV(endV),nexti(nexti), nextsize(nextsize), h(h)\
			{}

	int findpath();
	struct roadcmp{
		bool operator()(const road & a, const road & b) const
		{
			return a.second > b.second;
		}
	};

	struct hashVT {
	    std::size_t operator()(const VT & a) const{
	        std::size_t h = 0;
	        for (int i= 0; i<astar::VTsize; i++) {
	        	h ^= std::hash<int>{}(((unsigned char *)&a)[i])  + 0x9e3779b9 + (h << 6) + (h >> 2);
	        }
	        return h;
	    }
	};
};
//CLASS END

#endif
