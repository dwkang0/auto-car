/*
 * heap.h
 *
 *  Created on: 2019. 7. 27.
 *      Author: dwkang
 */
#ifndef HEAP_H_
#define HEAP_H_

#include <algorithm>
#include "log.h"
using namespace std;

namespace heapfunc{
template <typename T>
void swap(T &a, T &b){
	T t=a;
	a=b;
	b=t;
}
template <typename T>
struct defaultcmd{
	bool operator()(const T&a, const T&b){
		return a<b;
	}
};
}
template <typename T, typename cmp = heapfunc::defaultcmd<T> >
class heap{
public:
	cmp cp;

	T * data;
	int * index;//heap index to data index
	int * nextq, qhead, qtail;
	int heapsize;
	int maxsize;


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
	heap(int maxsize):maxsize(maxsize), heapsize(0), cp(),\
			data(new T[maxsize+1]), index(new int[maxsize+1]),\
			nextq(new int[maxsize+1]), qhead(0), qtail(0){}
	~heap(){
//		delete data;
//		delete index;
//		delete nextq;
	}
	inline void nqpush(int i){
		nextq[(qtail++)%(maxsize+1)]=i;
	}
	inline int nqpop(){
//		printf("h:%d, t:%d\n",qhead, qtail);
		return qhead<qtail ? nextq[(qhead++)%(maxsize+1)] : -1;
	}
	inline void relax(int i){
		log("relax:");

		//up
		while(i>1 && cp(data[index[parent(i)]], data[index[i]])){
			heapfunc::swap(index[parent(i)], index[i]);
			i=parent(i);
		}
		//down
		int lrmax;
//		printf("asd,%d][]",i);
		while(rightc(i) <= heapsize){
//			printf("asd");
			if( cp(data[index[leftc(i)]] , data[index[rightc(i)]]) ){
				lrmax=rightc(i);
			}else lrmax=leftc(i);
			if(cp(data[index[lrmax]] , data[index[i]])) break;
			heapfunc::swap(index[i], index[lrmax]);
			i=lrmax;
		}
//		printf("i=%d\n", i);
		lrmax=leftc(i);
		if(lrmax == heapsize){
			if(!cp(data[index[lrmax]] , data[index[i]])){
				heapfunc::swap(index[i], index[lrmax]);
//				printf("!!!");
			}
		}

		log("relax end\n");
	}
	inline int push(const T &x){
	    log("push:");
		heapsize++;
		int now, dindex;
		now=heapsize;
		dindex = nqpop();
//		printf("hs:%d\n",heapsize);
		dindex = dindex==-1 ? heapsize : dindex;
//		printf("now:%d, dindex:%d\n",now, dindex);
		data[dindex] = x;
		index[now] = dindex;
		log("now:%d, index[now]:%d, data[now]:%d",now, index[now],data[index[now]]);
//		log("%d < %d?",data[index[parent(now)]], data[index[now]]);
		while(now>1 && cp(data[index[parent(now)]] , data[index[now]])){
			log("index[now]:%d",index[now]);
			heapfunc::swap(index[parent(now)], index[now]);
			now = parent(now);
			log("%d < %d?",data[index[parent(now)]], data[index[now]]);
		}
		log("push end\n");
		return heapsize;
	}
	inline void pop(){
		log("pop:");
		nqpush(index[1]);
//		printf("-==%d\n",index[1]);
		index[1]=index[heapsize--];
//		data[index[1]] = data[index[heapsize--]];
		int now=1;
		int lrmax;
		while(rightc(now) <= heapsize){
//			printf("now=%d\n",now);
			if( cp(data[index[leftc(now)]] , data[index[rightc(now)]]) ){
				lrmax=rightc(now);
			}else lrmax=leftc(now);
//			printf("goto=>%d\n",lrmax);
			if(cp(data[index[lrmax]] , data[index[now]])) break;
			heapfunc::swap(index[now], index[lrmax]);
			now=lrmax;
		}
//		printf("now=%d\n", now);
		lrmax=leftc(now);
		if(lrmax == heapsize){
//			printf("???, %d\n", lrmax);
			if(!cp(data[index[lrmax]] , data[index[now]])){
//				printf("222");
				heapfunc::swap(index[now], index[lrmax]);
			}
		}
		log("pop end\n");
	}
	inline T top() const{
		log("top:");
		log("index[1]:%d, heapsize:%d", index[1], heapsize);
		T out = data[index[1]];
		log("top end\n");
		return out;
	}
};

#endif /* HEAP_H_ */
