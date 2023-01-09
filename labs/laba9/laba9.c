#include <stdio.h>

int min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}
int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}
int abs(int a, int b) {
	int c = a - b;
	if (c < 0)
		return c * -1;
	else
		return c;
}
int sign(int a) {
	if (a > 0)
		return 1;
	else if (a = 0)
		return 0;
	else
		return -1;
}

int check(int a, int b, int c) {
	if (a == 10 && b == -10 && c == 10) {
		return 1;
	}
	else
		return 0;
}
struct delta {
	int i, j, l;
};

int main() {
	int a, b, c;
	struct delta d = { 24, -14,9 };
	for (int k = 0; k < 50; ++k) {
		a = d.i;
		b = d.j;
		c = d.l;
		d.i = (a + k)*(b - k)*(c + k) % 25;
		d.j = min(a + k, max(b - k, c - k)) % 30;
		d.l = abs(b, c) * sign(a) - abs(a, c) * sign(b);
		if (check(d.i, d.j, d.l) == 1) {
			printf("yes\n");
			printf("i=%d.i", d.i);
			printf("j=%d.j", d.j);
			printf("l=%d.l", d.l);
			printf("k=%k", k);
			return 0;
		}

	}
	printf("no\n");
	printf("i=%d\n", d.i);
	printf("j=%d\n", d.j);
	printf("l=%d\n", d.l);
	printf("k=50\n");
}