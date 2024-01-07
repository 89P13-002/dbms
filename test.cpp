#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){

    // time_t t = time(NULL);
    // struct tm date = *localtime(&t);
    // // printf("Current date and time is %s\n",ctime(&t));
    // // ctime(&t) == asctime(localtime(&t))
    // // printf("Current date and time is %s\n",asctime(&date));

    // // Format string
    // char dateString[200];
    // strftime(dateString,200,"%Y-%m-%d",&date);

    // printf("Current date and time is %s\n",dateString);

// Take input from user
    time_t t = time(NULL);
    struct tm date = *localtime(&t);
    int year;
    int month;
    int day;
    int hour;
    int mint;

    scanf("%d",&year);
    scanf("%d",&month);
    scanf("%d",&day);

    date.tm_year = year - 1900;
    date.tm_mon = month -1;
    date.tm_mday = day ;
    date.tm_hour = 0;
    date.tm_min = 0;



    char dateString[200];
    strftime(dateString,200,"%Y-%b-%d %I:%M%p",&date);
    printf("Your Date and Time %s",dateString);


    return 0;
}