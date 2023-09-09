#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
char a[8] = {1,1,1,0,0,1,1,0};
int tmp = a[8-1];
for(int i=0; i<8;++i){
scanf(" %s", &a[i]);
}
for(int i=8-1;i>0;--i){
a[i]=a[i-1];
}
a[0]=tmp;
for(int i=0;i<8;++i){
printf("%d", a[i]);
}
}
