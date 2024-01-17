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


typedef struct subject {
    char sub_name[100];
    char sub_code[10];
    char sub_grade[3];
    int s_semester;
    int s_credit;
}subject; 

typedef struct student {
    int s_roll_num;
    char s_name[100];
    int total_sub;
    subject subjects[65];
     // Assuming a maximum of 100 subjects per student
} student;


void quickSort_name(student arr[], int low, int high);
void quickSort_credit(student arr[], int low, int high);
void quickSort_grade(student arr[], int low, int high);

void bubbleSort_name(student arr[], int n);
void bubbleSort_credit(student arr[], int n);
// void bubbleSort_grade(student arr[], int n);

void printSortedData(student arr[], int student_num, char *filename);

int partition_name(student arr[], int low, int high);
int partition_credit(student arr[], int low, int high);
int partition_grade(student arr[], int low, int high);

void swap(student *a, student *b);
void swap2(subject *a, subject *b);


// Function to perform Quick Sort based on credit in descending order and grade in ascending order
void quickSort_credit_grade(student arr[], int low, int high);

// Function to partition the array for Quick Sort based on credit in descending order and grade in ascending order
int partition_credit_grade(student arr[], int low, int high);


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


    // printf("%d %d %d\n",student_num,course_num,grade_total);


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



   
    // // Task 2a: Sorting based on student names in ascending order
    // quickSort(students, 0, student_num - 1);
    // // Task 2b: Sorting based on credits in descending order within Task 2a sorting
    // quickSort(students, 0, student_num - 1);  // Assuming the credits field is at index 2
    // // printSortedData(students, student_num, "output_task2b.csv");
    // // Task 2c: Sorting based on grade in ascending order within Task 2b sorting
    //   // Assuming the grades field is at index 3
    



    quickSort_name(students, 0, student_num - 1);
    for(i=0;i<student_num;i++){
        quickSort_credit_grade(&students[i], 0,students[i].total_sub-1 );
    }
    // for(i=0;i<student_num;i++){
    //     quickSort_grade(&students[i], 0, students[i].total_sub-1);
    // }
    printSortedData(students, student_num, "quick_sort.csv");



    bubbleSort_name(students, student_num);        // Assuming the student names field is at index 4
    for(i=0;i<student_num;i++){
        bubbleSort_credit(&students[i], students[i].total_sub);
    }
    // bubbleSort_grade(students, student_num);        // Assuming the student names field is at index 4
    // printSortedData(students, student_num, "bubble_sort.csv");




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

*/
    return 0;
}




void printSortedData(student arr[], int student_num, char *filename) {
    FILE *fp_sorted = fopen(filename, "w");

    for (int i = 0; i < student_num; i++) {
        // fprintf(fp_sorted, "Student Roll Number: %d\n", arr[i].s_roll_num);
        // fprintf(fp_sorted, "Student Name: %s\n", arr[i].s_name);
        // fprintf(fp_sorted, "Total Subjects: %d\n", arr[i].total_sub);

        for (int j = 0; j < arr[i].total_sub; j++) {
            fprintf(fp_sorted, "%s,%s,%s,%d,%s\n",
                    arr[i].s_name,
                    arr[i].subjects[j].sub_name,
                    arr[i].subjects[j].sub_code,
                    arr[i].subjects[j].s_credit,
                    arr[i].subjects[j].sub_grade);
        }

        // fprintf(fp_sorted, "\n");
    }

    fclose(fp_sorted);
    printf("%s\n", "Write successful to sorted file.");
}



/*
// Function to print the sorted data to a file
void printSortedData(student arr[], int student_num, char *filename) {
    FILE *fp_sorted = fopen(filename, "w");

    for (int i = 0; i < student_num; i++) {
        fprintf(fp_sorted, "Student Roll Number: %d\n", arr[i].s_roll_num);
        fprintf(fp_sorted, "Student Name: %s\n", arr[i].s_name);
        fprintf(fp_sorted, "Total Subjects: %d\n", arr[i].total_sub);

        for (int j = 0; j < arr[i].total_sub; j++) {
            fprintf(fp_sorted, "Subject Name: %s, Subject Code: %s, Grade: %s, Semester: %d, Credit: %d\n",
                    arr[i].subjects[j].sub_name, arr[i].subjects[j].sub_code,
                    arr[i].subjects[j].sub_grade, arr[i].subjects[j].s_semester,
                    arr[i].subjects[j].s_credit);
        }

        fprintf(fp_sorted, "\n");
    }

    fclose(fp_sorted);
    printf("%s\n", "Write successful to sorted file.");
}

*/

// Function to perform Quick Sort based on a specific field
void quickSort_name(student arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition_name(arr, low, high);
        quickSort_name(arr, low, pivotIndex - 1);
        quickSort_name(arr, pivotIndex + 1, high);
    }
}


// Function to partition the array for Quick Sort
int partition_name(student arr[], int low, int high) {
    

    int i = (low - 1);
    char nm[100];
    strcpy(nm,arr[high].s_name);
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j].s_name,nm)<0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}



// Function to perform Bubble Sort based on a specific field
void bubbleSort_name(student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[i].s_name,arr[j].s_name)>0) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void quickSort_credit(student* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition_credit(arr, low, high);
        quickSort_credit(arr, low, pivotIndex - 1);
        quickSort_credit(arr, pivotIndex + 1, high);
    }
}

// Function to partition the array for Quick Sort based on credit in decreasing order and grade in increasing order
int partition_credit(student* arr, int low, int high) {
    int i = low - 1;
    int k = arr->subjects[high].s_credit;
    for (int j = low; j <= high - 1; j++) {
        if (arr->subjects[j].s_credit > k) {
            i++;
            // subject t = arr->subjects[i];
            // arr->subjects[i] = arr->subjects[j];
            // arr->subjects[j] = t;
            swap2(&arr->subjects[i], &arr->subjects[j]);
        }
    }

    // subject t = arr->subjects[i+1];
    // arr->subjects[i+1] = arr->subjects[high];
    // arr->subjects[high] = t;
    swap2(&arr->subjects[i + 1], &arr->subjects[high]);
    return (i + 1);
}

void quickSort_grade(student* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition_grade(arr, low, high);
        quickSort_grade(arr, low, pivotIndex - 1);
        quickSort_grade(arr, pivotIndex + 1, high);
    }
}

// Function to partition the array for Quick Sort based on credit in decreasing order and grade in increasing order
int partition_grade(student* arr, int low, int high) {
    int i = low - 1;
    char ch[3];
    strcpy(ch,arr->subjects[high].sub_grade);
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(ch,arr->subjects[j].sub_grade)>0) {
            i++;
            swap2(&arr->subjects[i], &arr->subjects[j]);
        }
    }

    swap2(&arr->subjects[i + 1], &arr->subjects[high]);
    return (i + 1);
}

// Function to perform Bubble Sort based on credit in decreasing order and grade in increasing order
void bubbleSort_credit(student* arr, int n) {
    for (int i = 0; i < n ; i++) {
        for (int j = i+1; j < n ; j++) {
            if (arr->subjects[i].s_credit < arr->subjects[j].s_credit) {
                swap2(&arr->subjects[i], &arr->subjects[j]);
            }
        }
    }
}

void swap2(subject *a, subject *b) {
    subject temp = *a;
    *a = *b;
    *b = temp;
}


// Function to swap two student elements
void swap(student *a, student *b) {
    student temp = *a;
    *a = *b;
    *b = temp;
}




// Function to perform Quick Sort based on credit in descending order and grade in ascending order
void quickSort_credit_grade(student* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition_credit_grade(arr, low, high);
        quickSort_credit_grade(arr, low, pivotIndex - 1);
        quickSort_credit_grade(arr, pivotIndex + 1, high);
    }
}

// Function to partition the array for Quick Sort based on credit in descending order and grade in ascending order
int partition_credit_grade(student* arr, int low, int high) {
    int i = low - 1;
    int k = arr->subjects[high].s_credit;

    for (int j = low; j <= high - 1; j++) {
        if (arr->subjects[j].s_credit > k) {
            i++;
            swap2(&arr->subjects[i], &arr->subjects[j]);
        } else if (arr->subjects[j].s_credit == k) {
            // If credits are the same, compare by grades in ascending order
            if (strcmp(arr->subjects[j].sub_grade, arr->subjects[high].sub_grade) < 0) {
                i++;
                swap2(&arr->subjects[i], &arr->subjects[j]);
            }
        }
    }

    swap2(&arr->subjects[i + 1], &arr->subjects[high]);
    return (i + 1);
}
