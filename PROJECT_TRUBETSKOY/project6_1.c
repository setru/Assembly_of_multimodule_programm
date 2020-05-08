#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>

double f1(double);
double f2(double);
double f3(double);

int k;

double root(double f(double x), double g(double x), double a, double b, double eps1) {
    k++;
    double x;
    double c = a - ((f(a) - g(a)) * (b - a)) / ((f(b) - g(b)) - (f(a) - g(a)));
    int flag;
    if (f(a) - g(a) < 0) flag = -1;
    else flag = 1;
    if (f(c) - g(c) > 0) flag *= -1;
    if (flag == 1) {
        if ((f(c) - g(c)) * (f(c - eps1) - g(c - eps1)) < 0)
            return c;
        x = root(f, g, a, c, eps1);
    } else {
        if ((f(c) - g(c)) * (f(c + eps1) - g(c + eps1)) < 0)
            return c;
        x = root(f, g, c, b, eps1);
    }
    return x;
}

double integral(double f(double x), double a, double b, double eps2) {
    double in1 = 0, in2 = 0, h1, h2, n = 1, step;
    while (fabs(in1 - in2) * 3 > eps2 || in1 == 0) {
        in1 = in2;
        in2 = 0;
        n *= 2;
        step = (b - a) / n;
        h1 = f(a);
        for (int i = 1; i < n; i++) {
            h2 = f(a + step * i);
            in2 += (h1 + h2) / 2 * step;
            h1 = h2;
        }
    }
    return in2;
}
int main(int argc, char *argv[]) {
    double (*f[])(double) = {f1, f2, f3};
    int root_value = 0, iter = 0;
    for (int i = 1; i < argc; i++) {
        if (!strncmp(argv[i], "-help", 6)) {
            printf("-print_root (print the root of intersection of functions)\n");
            printf("-print_iter (print the number of iterations)\n");
            printf("-test_root (test function 'root')\n");
            printf("-test_integral (test function 'integral')\n");
            return 0;
        }
        else if (!strncmp(argv[i], "-print_root", 12)) {
            root_value = 1;
        }
        else if (!strncmp(argv[i], "-print_iter", 12)) {
            iter = 1;
        }
        else if (!strncmp(argv[i], "-test_root", 11)) {
            double a, b, eps1;
            int j, k;
            printf("test function 'root'\n");
            printf("enter function numbers:\n");
            scanf("%d%d", &j, &k);
            printf("enter the segment [a, b] where the supposed root is:\n");
            scanf("%lf%lf", &a, &b);
            printf("enter epsilon:\n");
            scanf("%lf", &eps1);
            printf("Function result: %lf\n", root(f[j - 1], f[k - 1], a, b, eps1));
            return 0;
        }
        else if (!strncmp(argv[i], "-test_integral", 15)) {
            double x1, x2, eps2;
            int j;
            printf("test function 'integral'\n");
            printf("enter function number:\n");
            scanf("%d", &j);
            printf("enter integration limits x1, x2:\n");
            scanf("%lf%lf", &x1, &x2);
            printf("enter epsilon:\n");
            scanf("%lf", &eps2);
            printf("Function result: %lf\n", integral(f[j - 1], x1, x2, eps2));
            return 0;
        }
    }
    k = 0;
    double x12 = root(f1, f2, 0.5, 2, 0.00001);
    if (iter) {
        printf("the number of iterations for root1: %d\n", k);
        k = 0;
    }
    double x13 = root(f1, f3, -2, -1, 0.00001);
    if (iter) {
        printf("the number of iterations for root2: %d\n", k);
        k = 0;
    }
    double x23 = root(f2, f3, 0, 2, 0.00001);
     if (iter) {
        printf("the number of iterations for root3: %d\n", k);
        k = 0;
    }
    if (root_value) {
        printf("root1 = %lf\nroot2 = %lf\nroot3 = %lf\n", x12, x13, x23);
    }
    double s1 = integral(f1, x13, x12, 0.0001);
    double s2 = -integral(f2, x23, x12, 0.0001);
    double s3 = -integral(f3, x13, x23, 0.0001);
    double s = s1 + s2 + s3;
    printf("The square is: S = %lf\n", s);
    return 0;
}