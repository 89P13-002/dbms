#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    FILE *fp1,*fp2,*fp3;
    fp1 = fopen("hss_courses.csv","r");
    fp2 = fopen("hss_electives.csv","r");
    fp3 = fopen("task6.sql","w");
    if(fp1 == NULL || fp2 == NULL){
        printf("Check for file\n");
    }
    else{
        fprintf(fp3,"USE week04;\n");
        fprintf(fp3,"CREATE table hss_course01 (\n\tcid char(10),\n\tcname char(60),\tPRIMARY KEY(cid)\n);\n");
        while(!feof(fp1)){
            char id[11];
            char name[61];
            fscanf(fp1,"%[^,],%[^\n]\n",id,name);
            fprintf(fp3,"INSERT INTO hss_course01 (cid,cname) VALUES (\"%s\",\"%s\");\n",id,name); 
        }
        fclose(fp1);
        printf("Done\n");
    }
    


    return 0;
}
