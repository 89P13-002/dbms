#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(){
    // Generate int
    FILE *fp1;
    // fp1 = fopen("i10k.txt","w");
    // if(fp1 == NULL){
    //     perror("File can't opened\n");
    //     return 1;
    // }
    // int i;
    // srand(time(NULL));
    // for(i=0;i<10000;i++){
    //     int num = rand()%1000000;
    //     fprintf(fp1,"%d\n",num);
    // }
    // fclose(fp1);

    fp1 = fopen("i10k.txt","r");
    int i;
    // // Read the file line by line and count items to get total items
    // int itemCount = 0;
    // char buffer[100000];  // Adjust the buffer size as needed

    // while (fgets(buffer, sizeof(buffer), fp1) != NULL) {
    //     itemCount++;
    // }
    int arr[10000];
    
    //  while (fgets(dateBuffer, sizeof(dateBuffer), file) != NULL)
    i=0;
    clock_t t1 = clock();
    for(i=0;i<10000;i++){
        fscanf(fp1,"%d",&arr[i]);
    }
    clock_t t2 = clock();
    double t = ((double)(t2-t1))/CLOCKS_PER_SEC; 
    for(i=0;i<10;i++){
        printf("%d ",arr[i]);
    }
    fclose(fp1);
    printf("%f",t);
/*
    // Generate date

    FILE *fp2;
    int i;
    // time_t t = time(NULL);

    // struct tm date1 = *localtime(&t);
    // date1.tm_year = 1947 - 1900;
    // date1.tm_mon = 7;
    // date1.tm_mday = 15;

    // struct tm date2 = *localtime(&t);
    // date2.tm_year = 2023 - 1900;
    // date2.tm_mon = 0;
    // date2.tm_mday = 1;


    // // char dateString1[200];
    // // char datestring2[200];
    // // strftime(dateString1,200,"",&date1);
    // // strftime(datestring2,200,"",&date2);
    const char *startDate = "15-Aug-1947";
    const char *endDate = "01-Jan-2023";

    struct tm start_tm, end_tm;

    // // Parse the start and end dates using sscanf
    // sscanf(startDate, "%d-%3s-%d", &start_tm.tm_mday, start_tm.tm_mon, &start_tm.tm_year);
    // sscanf(endDate, "%d-%3s-%d", &end_tm.tm_mday, end_tm.tm_mon, &end_tm.tm_year);

    // // Adjust month value to be 0-based (January is 0)
    // start_tm.tm_mon -= 1;
    // end_tm.tm_mon -= 1;

    start_tm.tm_year = 1947-1900;
    start_tm.tm_mon = 7;
    start_tm.tm_mday = 15;

    end_tm.tm_year = 2023-1900;
    end_tm.tm_mon = 0;
    end_tm.tm_mday = 1;
    // Convert dates to time_t (seconds since epoch)
    time_t start_time = mktime(&start_tm);
    time_t end_time = mktime(&end_tm);

    srand((unsigned int)time(NULL));
    fp2 = fopen("d10k.txt","w");

    for(i=0;i<10000;i++){
        time_t rand_sec = start_time + rand() % (end_time - start_time + 1);

        struct tm *rand_time = localtime(&rand_sec);
        static char randDateString[200];
        strftime(randDateString,200,"%d-%b-%Y",rand_time);
        fprintf(fp2,"%s\n",randDateString);
    }
    fprintf(fp2,"%s\n","asfef");
    fclose(fp2);

    */
    return 0;
}