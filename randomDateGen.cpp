#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to generate random integers and write them to a file
void generateIntegers(int size, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; ++i) {
        fprintf(file, "%d\n", rand() % 1000001);
    }

    fclose(file);
}

// Function to generate random dates and write them to a file
void generateDates(int size, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; ++i) {
        int day = rand() % 31 + 1;
        int month = rand() % 12 + 1;
        int year = rand() % (2023 - 1947 + 1) + 1947;
        fprintf(file, "%02d-%s-%04d\n", day, (month == 1) ? "Jan" : (month == 2) ? "Feb" : /* ... */ "Dec", year);
    }

    fclose(file);
}

// Function to generate random date and time stamps and write them to a file
void generateDateTimeStamps(int size, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; ++i) {
        int day = rand() % 31 + 1;
        int month = rand() % 12 + 1;
        int year = rand() % (2023 - 1947 + 1) + 1947;
        int hour = rand() % 24;
        int minute = rand() % 60;
        int second = rand() % 60;
        fprintf(file, "%02d-%s-%04d %02d:%02d:%02d\n", day, (month == 1) ? "Jan" : (month == 2) ? "Feb" : /* ... */ "Dec", year, hour, minute, second);
    }

    fclose(file);
}

// Function to read integers from a file
int* readIntegers(const char *filename, int size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int *array = malloc(size * sizeof(int));
    if (array == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; ++i) {
        if (fscanf(file, "%d", &array[i]) != 1) {
            fprintf(stderr, "Error reading from file");
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
    return array;
}

// Function to read dates from a file
char** readDates(const char *filename, int size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char **array = malloc(size * sizeof(char*));
    if (array == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; ++i) {
        array[i] = malloc(12); // Assuming maximum date length of 12 characters
        if (array[i] == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        if (fscanf(file, "%s", array[i]) != 1) {
            fprintf(stderr, "Error reading from file");
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
    return array;
}

// Function to read date and time stamps from a file
char** readDateTimeStamps(const char *filename, int size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char **array = malloc(size * sizeof(char*));
    if (array == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; ++i) {
        array[i] = malloc(20); // Assuming maximum date and time stamp length of 20 characters
        if (array[i] == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        if (fscanf(file, "%s", array[i]) != 1) {
            fprintf(stderr, "Error reading from file");
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
    return array;
}

// Function to perform Quick Sort on integers
void quickSortIntegers(int *arr, int low, int high) {
    if (low < high) {
        int pi = partitionIntegers(arr, low, high);

        quickSortIntegers(arr, low, pi - 1);
        quickSortIntegers(arr, pi + 1, high);
    }
}

// Function to perform Quick Sort on dates
void quickSortDates(char **arr, int low, int high) {
    if (low < high) {
        int pi = partitionDates(arr, low, high);

        quickSortDates(arr, low, pi - 1);
        quickSortDates(arr, pi + 1, high);
    }
}

// Function to perform Quick Sort on date and time stamps
void quickSortDateTimeStamps(char **arr, int low, int high) {
    if (low < high) {
        int pi = partitionDateTimeStamps(arr, low, high);

        quickSortDateTimeStamps(arr, low, pi - 1);
        quickSortDateTimeStamps(arr, pi + 1, high);
    }
}

// Function to partition integers for Quick Sort
int partitionIntegers(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swapIntegers(&arr[i], &arr[j]);
        }
    }

    swapIntegers(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Function to partition dates for Quick Sort
int partitionDates(char **arr, int low, int high) {
    char* pivot = arr[high];
    int
