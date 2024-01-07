#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random date between two given dates
char* generateRandomDate(const char *startDate, const char *endDate) {
    struct tm start_tm = {0};
    struct tm end_tm = {0};

    // Parse the start and end dates using sscanf
    sscanf(startDate, "%d-%3s-%d", &start_tm.tm_mday, start_tm.tm_mon, &start_tm.tm_year);
    sscanf(endDate, "%d-%3s-%d", &end_tm.tm_mday, end_tm.tm_mon, &end_tm.tm_year);

    // Adjust month value to be 0-based (January is 0)
    start_tm.tm_mon -= 1;
    end_tm.tm_mon -= 1;

    // Convert dates to time_t (seconds since epoch)
    start_tm.tm_year -= 1900; // Adjust for year (years since 1900)
    end_tm.tm_year -= 1900;

    time_t start_time = mktime(&start_tm);
    time_t end_time = mktime(&end_tm);

    // Generate a random number of seconds between the two dates
    time_t random_seconds = start_time + rand() % (end_time - start_time + 1);

    // Convert the random time_t back to a struct tm
    struct tm *random_tm = localtime(&random_seconds);

    // Convert the struct tm to a string in the specified format
    static char buffer[12];
    strftime(buffer, sizeof(buffer), "%d-%b-%Y", random_tm);

    return buffer;
}

int main() {
    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));

    // Start and end dates
    const char *startDate = "15-Aug-1947";
    const char *endDate = "01-Jan-2023";

    // File path
    const char *filename = "random_dates.txt";

    // Open the file for writing
    FILE *file = fopen(filename, "w");

    // Check if the file is opened successfully
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1;
    }

    // Generate and write random dates to the file
    for (int i = 0; i < 10000; ++i) {
        fprintf(file, "%s\n", generateRandomDate(startDate, endDate));
    }

    // Close the file
    fclose(file);

    printf("Random dates between %s and %s have been written to %s successfully.\n", startDate, endDate, filename);

    return 0;
}
