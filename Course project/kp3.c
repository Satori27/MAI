#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef long double real;

real func(real x) {
    return sin(x)*sin(x);
}
real eps(real x) {
    x = x > 0 ? x : -x;
    real eps = x;
    while (1) {
        if (x == (x + eps))
            return eps;
        eps /= 2;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    printf("___________________________________________________________________\n");
    printf("|   x  |         sum         |        f(x)         |число итераций |\n");
    printf("_________________________________________________________________\n");
    for (real x = 0.0; x <= 1.0; x += 0.01) {
        x = round(x * 1000) / 1000;
        real func_res = func(x);
        real ryad_res = 0;
        real cur = x*x;
        int n;
        for (n = 1; n < 100; n++) {
            ryad_res += cur;
            cur *= ((-1)*(2*x*x)/(2*n*n+3*n+1));
            if(ryad_res + cur == ryad_res)
                break;
        }
        printf("| %.2Lf | %.16Lf | %.16Lf |      %d       |\n", x, ryad_res, func_res, n);
        printf("___________________________________________________________________\n");
    }
}