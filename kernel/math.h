#ifndef MATH_H
#define MATH_H

#define E 2.71828
#define PI 3.14159265358979323846264338327950

double abs(double x) {
    return x < 0.0 ? -x : x;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a,int b) {
    return a < b ? a : b;
}

double fmod(double x, double m) {
    double result;
    asm("1: fprem\n\t"
        "fnstsw %%ax\n\t"
        "sahf\n\t"
        "jp 1b"
        : "=t"(result) : "0"(x), "u"(m) : "ax", "cc");
    return result;
}

double sin(double x) {
    double result;
    asm("fsin" : "=t"(result) : "0"(x));
    return result;
}

double cos(double x) {
    return sin(x + PI / 2.0);
}

// black magic
double pow(double x, double y) {
    double out;
    asm(
            "fyl2x;"
            "fld %%st;"
            "frndint;"
            "fsub %%st,%%st(1);"
            "fxch;"
            "fchs;"
            "f2xm1;"
            "fld1;"
            "faddp;"
            "fxch;"
            "fld1;"
            "fscale;"
            "fstp %%st(1);"
            "fmulp;" : "=t"(out) : "0"(x),"u"(y) : "st(1)" );
    return out;
}

#endif
