#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(){
    FILE * fp1,*fp2;
    fp1 = fopen("hss_electives.csv","r");
    fp2 = fopen("task2b.sql","w");
    fprintf(fp2,"USE week04;\n");
    while(!feof(fp1)){
        int a,b;
        char name[50];
        char code[10];
        char sub[60];
        fscanf(fp1,"%d,%d,%[^,],%[^,],%[^\n]\n",&a,&b,name,code,sub);
        fprintf(fp2,"INSERT INTO hss_table05 (sno,roll_number,sname,cid,cname) VALUES (%d,%d,\"%s\",\"%s\",\"%s\");\n",a,b,name,code,sub);
    }
    fclose(fp1);
    fclose(fp2);
    printf("Done\n");
    return 0;
}
