#include <string.h>
#include <stdio.h>
// лаба 14----------------------------------------------------
int main(void){
int n;
scanf("%d", &n);
int m[n][n];
for(int i=0; i!=n; ++i){
for(int j=0; j!=n; ++j){
scanf("%d", &m[i][j]);
}
}
int i;
int j;
i=0;
j=3;
printf("%d ", m[i][j]);
--j;
printf("%d ", m[i][j]);
while(j<n){
++i;
++j;
printf("%d ", m[i][j]);
if(j==n-1){
++i;
printf("%d ", m[i][j]);
while(i!=0){
--i;
--j;
printf("%d ", m[i][j]);
}
--j;
printf("%d ", m[i][j]);
while(j<n && i<n){
++i;
++j;
printf("%d ", m[i][j]);
if(i==3 && j==3){
break;
}
}
--j;
while(i!=0){
printf("%d ", m[i][j]); --i; --j;
}
++i;
while(i!=n-1){
++i;
++j;
printf("%d ", m[i][j]);
}
printf("%d ", m[i][j-1]);
break;
}

}
}