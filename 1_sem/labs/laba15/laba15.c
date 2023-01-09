#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
int n;
scanf(" %d", &n);
int m[n][n];
for(int i=0; i!=n; ++i){
for(int i=0; i!=n; ++i){
scanf(" %d", &m[i][i]);
}
}
for(int i=0; i!=n; ++i){
int tmp = m[i][n-1];
for(int i=n-1; i>0;--i){
m[i][i] = m[i][i-1];
}
m[i][0] = tmp;
} 
for(int i=0; i!=n; ++i){
for(int i=0; i!=n;++i){
printf("%d ", m[i][i]);
}
printf("\n");
}
}