#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *strins (char *s, char *s0, char c) {
int slen=strlen(s);
int s0len=strlen(s0);
int i,j;
for (i=0; i<slen; i++) {
if (s[i]==c) {
for (j=slen; j>=i; j--) s[j+s0len]=s[j];
for (j=0; j<s0len; j++) s[i+j]=s0[j];
slen+=s0len; i+=s0len;
}
}
return s;
}
int main (){
char c='\n';
const int SIZE=256;
char *s = (char *)malloc(SIZE*sizeof(char));
strcpy(s,"lol, Hello, i'm test string! \nla-la-l");
char *s0 = "l";
char *ptr = strins(s,s0,c);
puts(ptr);
fflush (stdin);
getchar ();
return 0;
}