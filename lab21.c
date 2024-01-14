#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student_name_roll{
    char name[100];
    int roll_num;
}student_name_roll;

typedef struct course{
    int semester;
    char course_num[10];
    char course_name[100];
    int lec_hour;
    int tut;
    int practical;
    int credit;

}course;

typedef struct grade{
    int g_roll_num;
    char g_course_num[10];
    char grad[3];
}grade;

typedef struct student {
    int s_roll_num;
    char s_name[100];
    int total_sub;
    struct subject {
        char sub_name[100];
        char sub_code[10];
        char sub_grade[3];
        int s_semester;
        int s_credit;
    } subjects[65];  // Assuming a maximum of 100 subjects per student
} student;


int main(){
    FILE *fp1,*fp2,*fp3,*fp4;
    student_name_roll student1[200];
    course course1[100];
    grade grade1[10000];
    student students[200];
    int i,j,k;
    int student_num = 0,course_num = 0,grade_total = 0;



    fp1 = fopen("students01.csv","r");
    i=0;
    while(!feof(fp1) ){
        fscanf(fp1,"%[^,],%d\n",student1[i].name,&student1[i].roll_num);
        i++;
    }
    student_num = i;
    fclose(fp1);


    fp2 = fopen("courses01.csv","r");
    i=0;
    while(!feof(fp2) ){
        fscanf(fp2,"%d,%[^,],%[^,],%d,%d,%d,%d\n",&course1[i].semester,course1[i].course_num,
        course1[i].course_name,&course1[i].lec_hour,&course1[i].tut,&course1[i].practical,
        &course1[i].credit);
        i++;   
    }
    course_num = i;
    fclose(fp2);


    fp3 = fopen("grades01.csv","r");
    i=0;
    while(!feof(fp3) ){
        fscanf(fp3,"%d,%[^,],%[^\n]\n",&grade1[i].g_roll_num,grade1[i].g_course_num,grade1[i].grad);
        i++;   
    }
    fclose(fp3);
    grade_total = i;

    printf("%d %d %d\n",student_num,course_num,grade_total);


    // for(i=0;i<10;i++){
    //     printf("%s %d\n",student1[i].name,student1[i].roll_num);
    //     printf("%d %s %s %d %d %d %d\n",course1[i].semester,course1[i].course_num,course1[i].course_name,course1[i].lec_hour,course1[i].tut,course1[i].practical,course1[i].credit);
    //     printf("%d %s %s\n",grade1[i].g_roll_num,grade1[i].g_course_num,grade1[i].grade);
    // }

    // Combine data into the 'students' array
    for (i = 0; i < student_num ; i++) {
        students[i].s_roll_num = student1[i].roll_num;
        strcpy(students[i].s_name, student1[i].name);
        students[i].total_sub = 0;  // Initialize the total subjects for each student

        for (j = 0; j < grade_total; j++) {
            if (grade1[j].g_roll_num == students[i].s_roll_num) {
                // Add course information to the subjects array
                // strcpy(students[i].subjects[students[i].total_sub].sub_name, course1[j].course_name);
                strcpy(students[i].subjects[students[i].total_sub].sub_code, grade1[j].g_course_num);
                strcpy(students[i].subjects[students[i].total_sub].sub_grade, grade1[j].grad);
                // students[i].subjects[students[i].total_sub].semester = course1[j].semester;
                // students[i].subjects[students[i].total_sub].credit = course1[j].credit;
                // grade1[j].g_roll_num = -1;
                // Increment the total subjects for the current student
                for(k=0;k<course_num;k++){
                    if(strcmp(students[i].subjects[students[i].total_sub].sub_code,course1[k].course_num)==0){
                        strcpy(students[i].subjects[students[i].total_sub].sub_name,course1[k].course_name);
                        students[i].subjects[students[i].total_sub].s_semester = course1[k].semester;
                        students[i].subjects[students[i].total_sub].s_credit = course1[k].credit;
                        // can add tut ,pracctical time etc
                        break;
                    }
                }
                (students[i].total_sub)++;
            }
        }
    }

/*
    for (i = 0; i < student_num && i<10; i++) {
        printf("Student Roll Number: %d\n", students[i].s_roll_num);
        printf("Student Name: %s\n", students[i].s_name);
        printf("Total Subjects: %d\n", students[i].total_sub);

        for (j = 0; j < students[i].total_sub; j++) {
            printf("Subject Name: %s, Subject Code: %s, Grade: %s, Semester: %d, Credit: %d\n",
                   students[i].subjects[j].sub_name, students[i].subjects[j].sub_code,
                   students[i].subjects[j].sub_grade, students[i].subjects[j].s_semester,
                   students[i].subjects[j].s_credit);
        }

        printf("\n");
    }

   */

    // Printing the combined data
    fp4 = fopen("output.csv","w");
    for (i = 0; i < student_num ; i++) {
        fprintf(fp4,"Student Roll Number: %d\n", students[i].s_roll_num);
        fprintf(fp4,"Student Name: %s\n", students[i].s_name);
        fprintf(fp4,"Total Subjects: %d\n", students[i].total_sub);

        for (j = 0; j < students[i].total_sub; j++) {
            fprintf(fp4,"Subject Name: %s, Subject Code: %s, Grade: %s, Semester: %d, Credit: %d\n",
                   students[i].subjects[j].sub_name, students[i].subjects[j].sub_code,
                   students[i].subjects[j].sub_grade, students[i].subjects[j].s_semester,
                   students[i].subjects[j].s_credit);
        }

        fprintf(fp4,"\n");
    }

    fclose(fp4);

  
    printf("%s\n","Write succes");


    return 0;
}