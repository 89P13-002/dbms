#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    // Random int 
    // int num;
    // int lower = 23,upper = 45;

    // srand(time(NULL));
    // // for b/w 0 to n : num = rand()%n;
    // num =(rand()%(upper-lower+1) +lower);

    // printf("%d\n",num);

    // Random float

    srand(time(NULL));
    int a=12,b=20;
    float num ;
    num = (((float)rand() / ((float)RAND_MAX))*(float)(b-a)) + a;
    printf("%f",num);
}