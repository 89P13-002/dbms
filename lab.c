#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct product
{
    char name[20];
    struct date
    {
        int day;
        char mon[4];
        int year;
    } dat[10];
    char region[10];
    void (*printData)(struct product *);
} product;

void printDataFunction(product *p) {
    printf("%s ", p->name);
    for (int i = 0; i < 10; i++) {
        printf("%d %s %d ", p->dat[i].day, p->dat[i].mon, p->dat[i].year);
    }
    printf("%s", p->region);
}


void sort_in(product *p){
    int i,j;
    for(i=0;i<10;i++){
        for(j=i+1;j<10;j++){
            int t = 0;
            if(p->dat[i].year > p->dat[j].year){
                t = 1;
            }
            else if (p->dat[i].year == p->dat[j].year){
                if(strcmp(p->dat[i].mon , p->dat[j].mon)>0){
                    t = 1;
                }
                else if(strcmp(p->dat[i].mon, p->dat[j].mon)==0){
                    if((p->dat[i].mon > p->dat[j].mon)){
                        t = 1;
                    }
                }
            }
        }
    }
}


int main()
{

    FILE *fp;
    // product *entry;
    fp = fopen("tt.csv", "r");
    char line[300];
    int i = 0;
    // entry = (product*)calloc(1000,sizeof(product));
    product entry[1000];
    int count;
    while (fgets(line, 300, fp))
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
                     "%[^,]",

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
        
        // sscanf(line, " %[^,-],
        //             %[^,-]-%[^-]-%d,
        //             %d-%[^-]-%d,
        //             %d-%[^-]-%d,
        //             %d-%[^-]-%d,
        //             %d-%[^-]-%d,
        //             %d-%[^-]-%d,
        //             %d-%[^-]-%d,
        //             %d-%[^-]-%d,
        //             %d-%[^-]-%d,
        //             %[^,]",

        //    entry.name,
        //    entry.dat[0].day, entry.dat[0].mon, entry.dat[0].year,
        //    entry.dat[1].day, entry.dat[1].mon, entry.dat[1].year,
        //    entry.dat[2].day, entry.dat[2].mon, entry.dat[2].year,
        //    entry.dat[3].day, entry.dat[3].mon, entry.dat[3].year,
        //    entry.dat[4].day, entry.dat[4].mon, entry.dat[4].year,
        //    entry.dat[5].day, entry.dat[5].mon, entry.dat[5].year,
        //    entry.dat[6].day, entry.dat[6].mon, entry.dat[6].year,
        //    entry.dat[7].day, entry.dat[7].mon, entry.dat[7].year,
        //    entry.dat[8].day, entry.dat[8].mon, entry.dat[8].year,
        //    entry.dat[9].day, entry.dat[9].mon, entry.dat[9].year,
        //    entry.region);

        // sscanf(line, "%9[^,],%11[^,],%11[^,],%11[^,],%11[^,],%11[^,],%11[^,],%11[^,],%11[^,],%11[^,],%11[^,],%19[^,]",
        //    entry.name, entry.date[0], entry.date[1], entry.date[2], entry.date[3], entry.date[4],
        //    entry.date[5], entry.date[6], entry.date[7], entry.date[8], entry.date[9], entry.region);
        // sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
        //    entry.name, entry.date[0], entry.date[1], entry.date[2], entry.date[3], entry.date[4],
        //    entry.date[5], entry.date[6], entry.date[7], entry.date[8], entry.date[9], entry.region);

        entry[i].printData = printDataFunction;

        // entry[i].printData(&entry[i]);
        i++;
    }
    fclose(fp);
    count =i;
    for(i=0;i<count;i++){
        if(strcmp(entry[i].region , "West\n")==0){
            printf("%d ",i+1);
            
        }
        else if(strcmp(entry[i].region , "East\n")==0){

        }
        else if(strcmp(entry[i].region , "West\n")==0){

        }
        else{

        }
    }
    return 0;
}