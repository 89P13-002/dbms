#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct date{
    int day;
    char mon[4];
    int year;
    
}date;


typedef struct product
{
    char name[20];
    char region[10];
    date dat[10];
    void (*printData)(struct product *);
} product;


void swapDates(date *a, date *b) {
    date temp = *a;
    *a = *b;
    *b = temp;
}



int getMonthValue(const char *month) {
    // Map month names to numerical values
    if (strcmp(month, "Jan") == 0) return 1;
    if (strcmp(month, "Feb") == 0) return 2;
    if (strcmp(month, "Mar") == 0) return 3;
    if (strcmp(month, "Apr") == 0) return 4;
    if (strcmp(month, "May") == 0) return 5;
    if (strcmp(month, "Jun") == 0) return 6;
    if (strcmp(month, "Jul") == 0) return 7;
    if (strcmp(month, "Aug") == 0) return 8;
    if (strcmp(month, "Sep") == 0) return 9;
    if (strcmp(month, "Oct") == 0) return 10;
    if (strcmp(month, "Nov") == 0) return 11;
    if (strcmp(month, "Dec") == 0) return 12;
    return 0;  // Invalid month
}



void printDataFunction(product *p) {
    printf("%s ", p->name);
    for (int i = 0; i < 10; i++) {
        printf("%d %s %d ", p->dat[i].day, p->dat[i].mon, p->dat[i].year);
    }
    printf("%s", p->region);
}



void sort_in(product *p,int c,int e){
    int i,j;
    for (int i = c; i < e; i++) {
        for (int j = i + 1; j < e; j++) {
            if (p->dat[i].year > p->dat[j].year ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) > getMonthValue(p->dat[j].mon)) ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) == getMonthValue(p->dat[j].mon) && p->dat[i].day > p->dat[j].day)) {
                swapDates(&p->dat[i], &p->dat[j]);
            }
        }
    }
}



void sort_de(product *p,int c,int e){
    int i,j;
    for (int i = c; i < e; i++) {
        for (int j = i + 1; j < e; j++) {
            if (p->dat[i].year < p->dat[j].year ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) < getMonthValue(p->dat[j].mon)) ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) == getMonthValue(p->dat[j].mon) && p->dat[i].day < p->dat[j].day)) {
                swapDates(&p->dat[i], &p->dat[j]);

                // Swap dates[i] and dates[j]
                // int y = p->dat[i].year;
                // int d = p->dat[i].day;
                // char m[4] ;
                // strcpy(m,p->dat[i].mon);
                // p->dat[i] = p->dat[j];
                // p->dat[j].day = d;
                // p->dat[j].year = y;
                // strcpy(p->dat[j].mon , m);
            }
        }
    }
}



void sort_in_de(product *p,int c){
    int i,j;
    int k =0;
    for(i=5;i<c;i++){
        if(p->dat[i].year == p->dat[4].year && getMonthValue(p->dat[i].mon) == getMonthValue(p->dat[4].mon) && p->dat[i].day == p->dat[4].day){
            k++;
        }
        else{
            break;
        }
    }

    sort_in(p,0,10);
    sort_de(p,5+k,10);
    
}



void sort_de_in(product *p,int c){
    int i,j,k;
    k =0;
    for(i=5;i<c;i++){
        if(p->dat[i].year == p->dat[4].year && getMonthValue(p->dat[i].mon) == getMonthValue(p->dat[4].mon) && p->dat[i].day == p->dat[4].day){
            k++;
        }
        else{
            break;
        }
    }

    sort_de(p,0,10);
    sort_in(p,5+k,10);


}

int main()
{

    FILE *fp;
    // product *entry;
    fp = fopen("week01.csv", "r");
    char line[300];
    int i = 0;
    
    product* entry;

    entry = (product*)calloc(15000,sizeof(product));
    int count;
    while (fgets(line, 300, fp)  && i<15000)
    {
        sscanf(line, " %[^,],"
                     "%d-%[^-]-%d,"
                     "%d-%[^,-]-%d,"
                     "%d-%[^,-]-%d,"
                     "%d-%[^,-]-%d,"
                     "%d-%[^,-]-%d,"
                     "%d-%[^,-]-%d,"
                     "%d-%[^,-]-%d,"
                     "%d-%[^,-]-%d,"
                     "%d-%[^,-]-%d,"
                     "%d-%[^,-]-%d,"
                     "%[^\n]",

               entry[i].name,
               &entry[i].dat[0].day, entry[i].dat[0].mon, &entry[i].dat[0].year,
               &entry[i].dat[1].day, entry[i].dat[1].mon, &entry[i].dat[1].year,
               &entry[i].dat[2].day, entry[i].dat[2].mon, &entry[i].dat[2].year,
               &entry[i].dat[3].day, entry[i].dat[3].mon, &entry[i].dat[3].year,
               &entry[i].dat[4].day, entry[i].dat[4].mon, &entry[i].dat[4].year,
               &entry[i].dat[5].day, entry[i].dat[5].mon, &entry[i].dat[5].year,
               &entry[i].dat[6].day, entry[i].dat[6].mon, &entry[i].dat[6].year,
               &entry[i].dat[7].day, entry[i].dat[7].mon, &entry[i].dat[7].year,
               &entry[i].dat[8].day, entry[i].dat[8].mon, &entry[i].dat[8].year,
               &entry[i].dat[9].day, entry[i].dat[9].mon, &entry[i].dat[9].year,
               entry[i].region);
        
        entry[i].printData = printDataFunction;

        // entry[i].printData(&entry[i]);
        i++;
    }


    fclose(fp);
    count =i;



    for(i=0;i<count;i++){
        if(strcmp(entry[i].region , "North")==0){
            sort_in(&entry[i],0,10);
            
        }
        else if(strcmp(entry[i].region , "South")==0){
            sort_de(&entry[i],0,10);
        }
        else if(strcmp(entry[i].region , "East")==0){
            sort_in_de(&entry[i],10);
        }
        else if(strcmp(entry[i].region , "West")==0){
            sort_de_in(&entry[i],10);
        }
    }

    // entry[0].printData(&entry[0]);
    // entry[1].printData(&entry[1]);

    FILE *fp1;
    fp1 = fopen("Output1.csv","w");
    for(i=0;i<count;i++){
        fprintf(fp1," %s,"
                     "%d-%s-%d,"
                     "%d-%s-%d,"
                     "%d-%s-%d,"
                     "%d-%s-%d,"
                     "%d-%s-%d,"
                     "%d-%s-%d,"
                     "%d-%s-%d,"
                     "%d-%s-%d,"
                     "%d-%s-%d,"
                     "%d-%s-%d,"
                     "%s\n",
                     entry[i].name,
                     entry[i].dat[0].day, entry[i].dat[0].mon, entry[i].dat[0].year,
               entry[i].dat[1].day, entry[i].dat[1].mon, entry[i].dat[1].year,
               entry[i].dat[2].day, entry[i].dat[2].mon, entry[i].dat[2].year,
               entry[i].dat[3].day, entry[i].dat[3].mon, entry[i].dat[3].year,
               entry[i].dat[4].day, entry[i].dat[4].mon, entry[i].dat[4].year,
               entry[i].dat[5].day, entry[i].dat[5].mon, entry[i].dat[5].year,
               entry[i].dat[6].day, entry[i].dat[6].mon, entry[i].dat[6].year,
               entry[i].dat[7].day, entry[i].dat[7].mon, entry[i].dat[7].year,
               entry[i].dat[8].day, entry[i].dat[8].mon, entry[i].dat[8].year,
               entry[i].dat[9].day, entry[i].dat[9].mon, entry[i].dat[9].year,
               entry[i].region);
    }
    fclose(fp1);

    printf("%s","Written");
    return 0;
}
