#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
int ascii;
char string[30] = "hello lehho leho";
// Extract the first token
char * token = strtok(string, " ");
// loop through the string to extract all other tokens
int size = sizeof(token);
unsigned int set; 
unsigned int res_set; 
unsigned int set1; 
unsigned int res_set1; 
unsigned int set2; 
unsigned int res_set2; 
unsigned int res3_set; 
for(int i = 0; i<size; ++i) {
for(int i = 0; token[i] != '\0'; ++i){
if (i+1%3==1){
ascii = token[i];
set = 1u<<(token[i]-'a');
res_set | set;

}
}

for(int i = 0; token[i] != '\0'; ++i) {
if (i+1%3==2){
ascii = token[i];
set1 = 1u<<(token[i]-'a');
res_set1 | set1;
}
}

for(int i = 0; token[i] != '\0'; ++i) {
// printf(" %d", token[i]);
if (i+1%3==0){
ascii = token[i];
set2 = 1u<<(token[i]-'a');
res_set2 | set2;
res3_set = res_set & res_set1 & res_set2;
if(res3_set != 0){
printf("1");
}
}
}
}
token = strtok(NULL, " ");

}