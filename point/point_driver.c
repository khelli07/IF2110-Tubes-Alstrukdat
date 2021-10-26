#include<stdio.h>
#include<stdlib.h>
#include "point.h"

int main(){
	Point p[5];
	int i=0;
	for(i=0;i<5;i++)CreatePoint(&p[i],i*2,i+7);
	for(i=0;i<5;i++)printf("(%d,%d)\n",p[i].x,p[i].y);
}
