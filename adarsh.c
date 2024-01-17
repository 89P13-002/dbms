#include <stdio.h>
#include <string.h>

typedef int (*CompareFunction)(const void *, const void *);

typedef struct {
    int day;
    char month[4]; 
    int year;
} Date;


int getmonth(const char* month){
    if(strcmp(month, "Jan") == 0){
        return 1;
    }else if(strcmp(month, "Feb") == 0){
        return 2;
    }else if(strcmp(month, "Mar") == 0){
        return 3;
    }else if(strcmp(month, "Apr") == 0){
        return 4;
    }else if(strcmp(month, "May") == 0){
        return 5;
    }else if(strcmp(month, "Jun") == 0){
        return 6;
    }else if(strcmp(month, "Jul") == 0){
        return 7;
    }else if(strcmp(month, "Aug") == 0){
        return 8;
    }else if(strcmp(month, "Sep") == 0){
        return 9;
    }else if(strcmp(month, "Oct") == 0){
        return 10;
    }else if(strcmp(month, "Nov") == 0){
        return 11;
    }else if(strcmp(month, "Dec") == 0){
        return 12;
    } 
    return -1;
}

int comparedates(Date* date1, Date* date2){
    if(date1->year == date2->year){
        if(getmonth(date1->month) == getmonth(date2->month)){
            if(date1->day == date2->day){
                return 1;
            }
        }
    }
    return -1;
}

void bubbleSortNorth(Date arr[], int size, CompareFunction compare) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compare(&arr[j], &arr[j + 1]) > 0) {
                // Swap arr[j] and arr[j+1]
                Date temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubbleSortSouth(Date arr[], int size, CompareFunction compare) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compare(&arr[j], &arr[j + 1]) < 0) {
                // Swap arr[j] and arr[j+1]
                Date temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void bubbleSortEast(Date arr[], int size, CompareFunction compare) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            //Initially sorting east in descending order
            if (compare(&arr[j], &arr[j + 1]) < 0) {
                // Swap arr[j] and arr[j+1]
                Date temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // After sorting in descending order we need to first find the extent of the first partition and then reverse the first partition.
    int k = 5;
    while(comparedates(&arr[4], &arr[k]) == 1){
        k++;
        if(k == 10){
            break;
        }
    }
    k--;
    //Now k is the last position at which date is same as date[4] i.e. 5th date

    //Atmax 10 dates to reverse
    Date datestemp[10];
    for (int i = 0; i <= k; i++)
    {
        datestemp[i] = arr[i];
    }

    for (int i = 0; i <= k; i++)
    {
        arr[i] = datestemp[k-i];
    }
}

void bubbleSortWest(Date arr[], int size, CompareFunction compare) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            //Initially sorting west in descending order
            if (compare(&arr[j], &arr[j + 1]) < 0) {
                // Swap arr[j] and arr[j+1]
                Date temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    //After sorting in descending order we need to first find till where the border extends
    int k = 5;
    while(comparedates(&arr[4], &arr[k]) == 1){
        k++;
        if(k == 10){
            break;
        }
    }

    //Now k-1 is the last element which is equal to 5th date, so we need to make all elements from k+1 to 10 in reverse order.

    //Atmax 5 dates to be reversed
    Date tempdates[5];
    int i = 0;
    for (int l = k; l < size; l++)
    {
        tempdates[i] = arr[l];
        i++;
    }
    i = 0;
    for (int l = k; l < size; l++)
    {
        arr[l] = tempdates[size - k - i - 1];
        // printf("%02d-%s-%d\n", arr[l].day, arr[l].month, arr[l].year);
        i++;
    }
}

int compareDates(const void *a, const void *b) {
    const Date *dateA = (const Date *)a;
    const Date *dateB = (const Date *)b;

    if (dateA->year != dateB->year) {
        return dateA->year - dateB->year;
    }

    if(getmonth(dateA->month) != getmonth(dateB->month)){
        return getmonth(dateA->month) - getmonth(dateB->month);
    }

    return dateA->day - dateB->day;
}

void printDatesToFile(const char* Region,const char* ID,Date arr[], int size, const char *filename) {
    FILE *file = fopen(filename, "a");
    char temp[10];
    sprintf(temp, "%s,", ID);
    fputs(temp, file);
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d-%s-%d,", arr[i].day, arr[i].month, arr[i].year);
    }
    *temp = '\0';
    sprintf(temp, "%s", Region);
    fputs(temp, file);
    fclose(file);
}

void printDates(Date arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%02d-%s-%d\n", arr[i].day, arr[i].month, arr[i].year);
    }
    printf("\n");
}



int main()
{
	FILE* fp = fopen("week01.csv", "r");
    FILE* output;

    char buffer[1024];
    char ID[10];
    char Region[10];
    int numsteps = 10;

    int row = 0;
    int column = 0;

    Date dates[10];

    FILE* temp;

    printf("Currently Processing Input Please Wait...\n");

    while (fgets(buffer, 1024, fp)) {
        column = 0;
        row++;

        if ((row == 1)){
            output = fopen("output.txt", "w");
            fputs(buffer, output);
            fclose(output);
            continue;
        }

        temp = fopen("temp.txt", "w");
        char* value = strtok(buffer, ", ");
        while (value) {
            if(column==0){
                strcpy(ID, value);
                // printf("ID: %s \n", ID);
            }else if( column <= 10){
                fprintf(temp, "%s\n", value);
                // printf("Step: %s \n", value);
            }else{
                strcpy(Region, value);
                // printf("Region: %s", Region);
            }
            value = strtok(NULL, ", ");
            column++;
        }
        fclose(temp);

        // We have stored the dates cooresponding to 1 ID in the file temp.txt
        // Now we will open the file and store the dates in the array dates


        // The Dates are stored in an array of dates size 10 one at a time.
        temp = fopen("temp.txt", "r");
        for (int i = 0; i < numsteps; i++) {
            fscanf(temp, "%d-%3s-%d", &dates[i].day, dates[i].month, &dates[i].year);
        }



        if(strcmp(Region, "West\n") == 0){
            bubbleSortWest(dates, numsteps, compareDates);
        }else if(strcmp(Region, "North\n") == 0){
            bubbleSortNorth(dates, numsteps, compareDates);
        }else if(strcmp(Region, "South\n") == 0){
            bubbleSortSouth(dates, numsteps, compareDates);
        }else if(strcmp(Region, "East\n") == 0){
            bubbleSortEast(dates, numsteps, compareDates);
        }

        fclose(temp);
        printDatesToFile(Region, ID, dates, numsteps, "output.txt");
        // printf("\n");
    }

    fclose(fp);
    printf("Done Processing Input.\n");

    // TASK 04
    char input[50];
    printf("Enter Product Number or quit to quit: ");
    scanf("%s", input);
    

    // printf("%d", strcmp(input, "quit"));

    while(strcmp(input, "quit") != 0){
        printf("Displaying results for %s\n", input);

        row = column = 0;
        fp = fopen("week01.csv","r");
        int found = 0;

        while (fgets(buffer, 1024, fp)) {
            column = 0;
            row++;

            if ((row == 1)){
                continue;
            }

            temp = fopen("temp.txt", "w");
            char* value = strtok(buffer, ", ");
            while (value) {
                if(column==0){
                    strcpy(ID, value);
                    // printf("%d", strcmp(ID, input));
                    if(strcmp(ID, input) == 0){
                        printf("Before Sorting \n");
                        found = 1;
                    }
                    // printf("ID: %s \n", ID);
                }else if(column <= 10){
                    if(found == 1){
                        fprintf(temp, "%s\n", value);
                        printf("%s\n", value);
                    }
                    // printf("Step: %s \n", value);
                }else{
                    if(found == 1){
                        strcpy(Region, value);
                    }
                    // strcpy(Region, value);
                    // printf("Region: %s", Region);
                }
                value = strtok(NULL, ", ");
                column++;
            }
            if(found == 1) break;
            found = 0;
            fclose(temp);
            // We have stored the dates cooresponding to 1 ID in the file temp.txt
            // Now we will open the file and store the dates in the array dates
        }



        // The Dates are stored in an array of dates size 10 one at a time.
        temp = fopen("temp.txt", "r");
        for (int i = 0; i < numsteps; i++) {
            fscanf(temp, "%d-%3s-%d", &dates[i].day, dates[i].month, &dates[i].year);
        }

        if(strcmp(Region, "West\n") == 0){
            // printf("West region");
            bubbleSortWest(dates, numsteps, compareDates);
        }else if(strcmp(Region, "North\n") == 0){
            bubbleSortNorth(dates, numsteps, compareDates);
        }else if(strcmp(Region, "South\n") == 0){
            bubbleSortSouth(dates, numsteps, compareDates);
        }else if(strcmp(Region, "East\n") == 0){
            bubbleSortEast(dates, numsteps, compareDates);
        }

        fclose(temp);
        // printDatesToFile(Region, ID, dates, numsteps, "output.txt");
        // printf("\n");
        printf("\nAfter Sorting: \n");
        printDates(dates, numsteps);
        fclose(fp);


        printf("Enter next product number or quit to quit: ");
        scanf("%s", input);
    }

	return 0;
}
