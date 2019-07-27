/*
 * heap.h
 *
 *  Created on: 2019. 7. 27.
 *      Author: dwkang
 */
#include <algorithm>
using namespace std;

#ifndef HEAP_H_
#define HEAP_H_

namespace heapfunc{
template <typename T>
void swap(T &a, T &b){
	T t=a;
	a=b;
	b=t;
}
}

template <typename T>
class heap{
public:
	T * data;
	int * index;//heap index to data index
	int heapsize;
	const int maxsize;

	inline int parent(int index){
		return index/2;
	}
	inline int leftc(int index){
		return index*2;
	}
	inline int rightc(int index){
		return index*2+1;
	}

//public:
	heap(int maxsize):maxsize(maxsize), heapsize(0){
		data = new T[maxsize+1];
		index = new int[maxsize+1];
	}
	~heap(){
		delete data;
		delete index;
//		delete ditohi;
//		delete hitodi;
	}
	inline void relax(int i){
		//up
		while(data[index[parent(i)]] < data[index[i]] && i>1){
			heapfunc::swap(index[parent(i)], index[i]);
		}
		//down
		int lrmax;
		while(i*2 <= heapsize){
			if( data[leftc(i)] < data[rightc(i)] ){
				lrmax=rightc(i);
			}else lrmax=leftc(i);
			if(data[index[i]] >= data[index[lrmax]]) break;
			heapfunc::swap(index[i], index[lrmax]);
			i=lrmax;
		}
	}
	inline int push(const T &x){
		heapsize++;
		int now;
		now = heapsize;
		data[now] = x;
		index[now] = heapsize;
		while(data[index[parent(now)]] < data[index[now]] && now>1){
			heapfunc::swap(index[parent(now)], index[now]);
		}
		return heapsize;
	}
	inline void pop(){
		index[1]=index[heapsize--];
		int now=1;
		int lrmax;
		while(now*2 <= heapsize){
			if( data[leftc(index[now])] < data[rightc(index[now])] ){
				lrmax=rightc(now);
			}else lrmax=leftc(now);
			if(data[index[now]] >= data[index[lrmax]]) break;
			heapfunc::swap(index[now], index[lrmax]);
			now=lrmax;
		}
	}
	inline T top(){
		return data[index[1]];
	}
};

#endif /* HEAP_H_ */
