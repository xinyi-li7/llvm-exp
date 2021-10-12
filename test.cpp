#include <stdio.h>
#include <stdlib.h> 

double add_f(double x, double y) {
    return x+y;
}

int main() {
    double x, y;
    x = 1;
    y = 4;
    double z = 5;
    z += add_f(x, y);
    // double *arr = (double*) malloc(sizeof(double)*z);
    // for(int i = 0; i<z; i++){
    //     *(arr+i) = 0; 
    // }
    // z = *arr;
    //double *t=&z;
    printf("hello world %f\n",z);
    return 0;
}