#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct student{
    int roll_num;
    char name[20];
    struct subject{
        int sub_code;
        char sub_name[20];
        int mark;
    }sub[3];
    int total;
    float per;
}student;

void create();
void display();
void append();
void record_num();
void search();
void update();
void delete_rec();
void sort_total_on_screen();
void sort_total_in_file();
void sort_name_on_screen();

int main(){
    int choice;
    do{
        printf("\n1.CREATE");
        printf("\n2.DISPLAY");
        printf("\n3.APPEND");
        printf("\n4.NO OF RECORDS");
        printf("\n5.SEARCH A RECORDS");
        printf("\n6.UPDATE");
        printf("\n7.DELETE");
        printf("\n8.Sort BY TOTAL DESC - ON SCREEN");
        printf("\n9.Sort BY TOTAL DESC - IN FILE");
        printf("\n10.SORT BY NAME ON SCREEN");
        printf("\n0.EXIT");

        printf("\nEnter Your Choice : ");
        scanf("%d",&choice);


        switch(choice){
            case 1:
                create();
                break;
            case 2:
                display();
                break;
            case 3:
                append();
                break;
            case 4:
                record_num();
                break;
            case 5:
                search();
                break;
            case 6:
                update();
                break;
            case 7:
                delete_rec();
                break;
            case 8:
                sort_total_on_screen();
                break;
            case 9:
                sort_total_in_file();
                break;
            case 10:
                sort_name_on_screen();
                break;   
                
        }


    }while(choice != 0);


    return 0;
}


void create(){
    FILE *fp;
    fp = fopen("mystudent.txt","w");

    student *s;
    int n,i,j;
    printf("Enter how many students you want : ");
    scanf("%d",&n);

    s = (student*)calloc(n,sizeof(student));

    for(i=0;i<n;i++){
        s[i].total = 0;
        s[i].per = 0;
        printf("Enter RollNo : ");
        scanf("%d",&s[i]);
        fflush(stdin);
        printf("Enter Name : ");
        scanf("%s",s[i].name);
        scanf("%[^\n]s",s[i].name);
        for(j=0;j<3;j++){
            printf("Enter Marks of Subject %d :",j+1);
            scanf("%d",&s[i].sub[j].mark);
            s[i].total += s[i].sub[j].mark;
        }
        s[i].per = s[i].total / 3.0 ;

        fwrite(&s[i],sizeof(student),1,fp);
    }
    fclose(fp);
}


void display(){
    student s1;
    FILE *fp;
    int j;
    fp = fopen("mystudent.txt","r");

    while(fread(&s1,sizeof(student),1,fp)){
        printf("\n%-5d%-20s",s1.roll_num,s1.name);
        for(j=0;j<3;j++){
            printf("%4d",s1.sub[j].mark);
        }
        printf("%5d %7.2f",s1.total,s1.per);

    }
}


void append(){
    FILE *fp;
    fp = fopen("mystudent.txt","a");

    student *s;
    int n,i,j;
    printf("Enter how many students you want : ");
    scanf("%d",&n);

    s = (student*)calloc(n,sizeof(student));

    for(i=0;i<n;i++){
        s[i].total = 0;
        s[i].per = 0;
        printf("Enter RollNo : ");
        scanf("%d",&s[i]);
        fflush(stdin);
        printf("Enter Name : ");
        scanf("%[^\n]s",s[i].name);
        for(j=0;j<3;j++){
            printf("Enter Marks of Subject %d :",j+1);
            scanf("%d",&s[i].sub[j].mark);
            s[i].total += s[i].sub[j].mark;
        }
        s[i].per = s[i].total / 3.0 ;

        fwrite(&s[i],sizeof(student),1,fp);
    }
    fclose(fp);
}




void record_num(){
    student s1;
    FILE *fp;
    fp = fopen("mystudent.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(student);
    printf("\n\nNo of Record = %d",n);
    fclose(fp);
}

void search(){
    student s1;
    FILE *fp;
    int j,roll;
    bool found = false;
    fp = fopen("mystudent.txt","r");
    printf("Enter roll num to search :");
    scanf("%d",&roll);
    while(fread(&s1,sizeof(student),1,fp)){
        if(s1.roll_num == roll){
            found = true;
            printf("\n%-5d%-20s",s1.roll_num,s1.name);
            for(j=0;j<3;j++){
                printf("%4d",s1.sub[j].mark);
            }
            printf("%5d %7.2f",s1.total,s1.per);
        }
    }
    if(!found){
        printf("\nRecord not found\n");
    }
}


void update(){
    student s1;
    FILE *fp,*fp1;
    int j,roll;
    bool found = false;
    fp = fopen("mystudent.txt","r");
    fp = fopen("temp.txt","w");
    printf("Enter roll num to update :");
    scanf("%d",&roll);
    while(fread(&s1,sizeof(student),1,fp)){
        if(s1.roll_num == roll){
            found = true;
            s1.total = 0;
            s1.per = 0;
            printf("Enter New Name : ");
            scanf("%[^\n]s",s1.name);
            for(j=0;j<3;j++){
                printf("Enter New Marks of Subject %d :",j+1);
                scanf("%d",&s1.sub[j].mark);
                s1.total += s1.sub[j].mark;
            }
            s1.per = s1.total / 3.0 ;
        }
        fwrite(&s1,sizeof(student),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1 = fopen("temp.txt","r");
        fp = fopen("mystudent.txt","w");

        while(fread(&s1,sizeof(student),1,fp1)){
            fwrite(&s1,sizeof(student),1,fp);
        }

        fclose(fp1);
        fclose(fp);
    }
    else{
        printf("\nRecord not found\n");
    }
}



void delete_rec(){
    student s1;
    FILE *fp,*fp1;
    int j,roll;
    bool found = false;
    fp = fopen("mystudent.txt","r");
    fp = fopen("temp.txt","w");
    printf("Enter roll num to delete :");
    scanf("%d",&roll);
    while(fread(&s1,sizeof(student),1,fp)){
        if(s1.roll_num == roll){
            found = true;
        }
        else{
            fwrite(&s1,sizeof(student),1,fp1);
        }
        
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1 = fopen("temp.txt","r");
        fp = fopen("mystudent.txt","w");

        while(fread(&s1,sizeof(student),1,fp1)){
            fwrite(&s1,sizeof(student),1,fp);
        }

        fclose(fp1);
        fclose(fp);
    }
    else{
        printf("\nRecord not found\n");
    }
}



void sort_total_on_screen(){
    student *s,s1;
    FILE *fp;
    fp = fopen("mystudent.txt","r");

    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(student);

    s = (student*)calloc(n,sizeof(student));
    int i,j;
    rewind(fp); // move curser back to initial pos

    for(i=0;i<n;i++){
        fread(&s[i],sizeof(student),1,fp);
    }

    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(s[i].total<s[j].total){
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
            }
        }
    }


    for(i=0;i<n;i++){
        printf("\n%-5d%-20s",s[i].roll_num,s[i].name);
        for(j=0;j<3;j++){
            printf("%4d",s[i].sub[j].mark);
        }
        printf("%5d %7.2f",s[i].total,s[i].per);
    }
    fclose(fp);
}



void sort_total_in_file(){
    student *s,s1;
    FILE *fp;
    fp = fopen("mystudent.txt","r");

    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(student);

    s = (student*)calloc(n,sizeof(student));
    int i,j;
    rewind(fp); // move curser back to initial pos

    for(i=0;i<n;i++){
        fread(&s[i],sizeof(student),1,fp);
    }

    fclose(fp);
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(s[i].total<s[j].total){
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
            }
        }
    }

    fp = fopen("mystudent.txt","w");
    for(i=0;i<n;i++){
        printf("\n%-5d%-20s",s[i].roll_num,s[i].name);
        for(j=0;j<3;j++){
            printf("%4d",s[i].sub[j].mark);
        }
        printf("%5d %7.2f",s[i].total,s[i].per);

        fwrite(&s[i],sizeof(student),1,fp);
    }
    fclose(fp);
}

void sort_name_on_screen(){
    student *s,s1;
    FILE *fp;
    fp = fopen("mystudent.txt","r");

    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(student);

    s = (student*)calloc(n,sizeof(student));
    int i,j;
    rewind(fp); // move curser back to initial pos

    for(i=0;i<n;i++){
        fread(&s[i],sizeof(student),1,fp);
    }

    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(strcmp(s[i].name,s[j].name)>0){
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
            }
        }
    }


    for(i=0;i<n;i++){
        printf("\n%-5d%-20s",s[i].roll_num,s[i].name);
        for(j=0;j<3;j++){
            printf("%4d",s[i].sub[j].mark);
        }
        printf("%5d %7.2f",s[i].total,s[i].per);
    }
    fclose(fp);
}