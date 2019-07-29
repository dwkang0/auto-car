//============================================================================
// Name        : file_IO_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main() {
	FILE *fp;
	fp=fopen("road.txt", "rt");
	if (fp!=NULL) {}
	else {
		puts("파일을 찾을 수 없습니다.\n");
		return 0;
	}
	char a='a';
	fscanf(fp, "%c", &a);

	printf("%c", a);

	return 0;
}
