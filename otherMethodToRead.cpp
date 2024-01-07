#include<stdio.h>

typedef struct{
    char name[50];
    int  age;
    float grade;
}student;

int main(){

    FILE *fp;
    fp = fopen("test.csv","r");

    if(fp == NULL){
        perror("Error in opening file"); // perror is a standard library function that is used to print a description for the last error that occurred as void perror(const char *s);
        return 1;
    }

    student s[3];
    // while(fread(&s,sizeof(student),1,fp)){
    //     printf("%s%d%f",s.name,s.age,s.grade);
    // }
    int i=0;
    while(fscanf(fp,"%[^,],%d,%d\n",s[i].name,&s[i].age,&s[i].grade)==3){
        // Process the read record
        
        printf("Name: %s Age: %d Grade: %d\n", s[i].name, s[i].age, s[i].grade);
        i++;
    }
    
    fclose(fp);
    printf("%d",s[0].age+s[1].age+s[2].age);
    return 0;
}



// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_NAME_LENGTH 50
// #define MAX_LINE_LENGTH 100

// // Define a structure to store CSV data
// struct Person {
//     char name[MAX_NAME_LENGTH];
//     int age;
//     float salary;
// };

// int main() {
//     FILE *file;
//     char line[MAX_LINE_LENGTH];
//     struct Person people[100];  // Assuming a maximum of 100 people in the CSV file

//     // Open the CSV file for reading
//     file = fopen("example.csv", "r");

//     if (file == NULL) {
//         perror("Error opening file");
//         return 1;
//     }

//     int count = 0;

//     // Read each line from the file
//     while (fgets(line, sizeof(line), file) != NULL) {
//         // Parse the line using sscanf and store data in the structure
//         sscanf(line, "%49[^,],%d,%f", people[count].name, &people[count].age, &people[count].salary);
//         count++;

//         // You may want to add additional checks to handle errors or incomplete data
//     }

//     // Close the file
//     fclose(file);

//     // Now, 'people' array contains the data from the CSV file in the 'Person' structure

//     // Print the data as an example
//     for (int i = 0; i < count; i++) {
//         printf("Person %d:\n", i + 1);
//         printf("Name: %s\n", people[i].name);
//         printf("Age: %d\n", people[i].age);
//         printf("Salary: %.2f\n", people[i].salary);
//         printf("\n");
//     }

//     return 0;
// }



// For tab separated
// while (fscanf(fp, "%[^\t]\t%d\t%d\n", s.name, &s.age, &s.grade) == 3) {
//         // Process the read record
//         printf("Name: %s, Age: %d, Grade: %d\n", s.name, s.age, s.grade);
//     }