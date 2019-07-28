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

	inline int parent(const int index) const{
		return index/2;
	}
	inline int leftc(const int index) const{
		return index*2;
	}
	inline int rightc(const int index) const{
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
	}
	inline void relax(int i){
//		printf("asd");
		//up
		while(data[index[parent(i)]] < data[index[i]] && i>1){
			heapfunc::swap(index[parent(i)], index[i]);
		}
		//down
		int lrmax;
//		printf("asd,%d][]",i);
		while(rightc(i) <= heapsize){
//			printf("asd");
			if( data[leftc(i)] < data[rightc(i)] ){
				lrmax=rightc(i);
			}else lrmax=leftc(i);
			if(!(data[index[lrmax]] < data[index[i]])) break;
			heapfunc::swap(index[i], index[lrmax]);
			i=lrmax;
		}
//		printf("i=%d\n", i);
		lrmax=leftc(i);
		if(lrmax == heapsize){
			if(!(data[index[lrmax]] < data[index[i]])){
				heapfunc::swap(index[i], index[lrmax]);
//				printf("!!!");
			}
		}
	}
	inline int push(const T &x){
		heapsize++;
		int now;
		now = heapsize;
		data[now] = x;
		index[now] = heapsize;
		while(now>1 && data[index[parent(now)]] < data[index[now]]){
			heapfunc::swap(index[parent(now)], index[now]);
		}
		return heapsize;
	}
	inline void pop(){
		index[1]=index[heapsize--];
		int now=1;
		int lrmax;
		while(rightc(now) <= heapsize){
//			printf("now=%d\n",now);
			if( data[leftc(index[now])] < data[rightc(index[now])] ){
				lrmax=rightc(now);
			}else lrmax=leftc(now);
//			printf("goto=>%d\n",lrmax);
			if(!(data[index[lrmax]] < data[index[now]])) break;
			heapfunc::swap(index[now], index[lrmax]);
			now=lrmax;
		}
//		printf("now=%d\n", now);
		lrmax=leftc(now);
		if(lrmax == heapsize){
//			printf("???, %d\n", lrmax);
			if(!(data[index[lrmax]] < data[index[now]])){
//				printf("222");
				heapfunc::swap(index[now], index[lrmax]);
			}
		}
	}
	inline T top() const{
		return data[index[1]];
	}
};

#endif /* HEAP_H_ */
