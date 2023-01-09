double fun(double x)
{
    return cos(x)/(2*sin(x));
}

double F1(double x) {
    return (2*x*sin(x)-cos(x));
}

double F2(double x) {
    return cos(x) - exp(-pow(x, 2) / 2) + x - 1;
}

double f1(double x) {

    return cos(x)/(2*sin(x));
}

double f2(double x) {
    return 1 + exp(-pow(x, 2) / 2) - cos(x);
}

double F1_1(double x) {
    return (3*sin(x)+2*x*cos(x));
}

double F2_1(double x) {
    return -sin(x) + x * exp(-pow(x, 2) / 2) + 1;
}

double dth(double f(double), double a, double b, double eps) {
    double x;
    while (fabs(a - b) > eps) {
        x = (a + b) / 2;
        if (f(x) * f(a) < 0) {
            b = x;
        } else {
            a = x;
        }
    }
    return (a+b)/2;
}

double itter(double f(double), double a, double b, double eps) {
    double x = (a + b) / 2;
    while (fabs(f(x) - x) > eps) {
        x = f(x);
    }
    return x;
}

double newton(double F(double), double F1(double), double a, double b, double eps) {
    double x = (a + b / 2);
    while (fabs(F(x) / F1(x)) > eps) {
        x -= F(x)/F1(x);
    }
    return x;
}
void ans(double F(double), double F1(double), double f(double), double a, double b, double eps){
    printf("Корень, полученный методом дихотомии: %11.7f\n", dth(F, a, b, eps));
    printf("Корень, полученный методом Ньютона: %11.7f\n", newton(F, F1, a, b, eps));
}
int main() {
    double eps = 1;
    while (1 + eps/2 > 1){
        eps /= 2;
    }
    printf("Функция exp(x) + ln(x) - 10x\n");
    ans(F1, F1_1, f1, 0.4, 1.0, eps);

{
    double a = 0.4, b = 1.0, r = 0.6532712, eps = 1.0, x = (a + b) / 2, c = fun(x);
    int k = 0;
    while (1.0 + eps > 1.0)
        eps /= 2.0;
    eps *= 100;
    while (fabs(x - c) >= eps)
    {
        k++;
        x = c;
        c = fun(x);
        if(fabs(x-r)<=1e-7){
        printf("Корень, полученный методом итераций: %11.7f\n", x);
        return 0;   
    }
    }
    return 0;

}
}