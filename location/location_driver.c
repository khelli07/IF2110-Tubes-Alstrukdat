#include<stdio.h>
#include<stdlib.h>
#include "location.h"

int main(){
	Location loc[5];
	int i=0;
	for(i=0;i<5;i++){
		CreateLocation(&loc[i],i*3,i+2,(char)'A'+i);
	}
	for(int i=0;i<5;i++){
		DisplayLocation(loc[i]);
		printf("\n");
	}
}
