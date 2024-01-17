#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct date {
    int day;
    char mon[4];
    int year;
} Date;

typedef struct product {
    char name[20];
    Date dat[10];
    char region[10];
} Product;

int getMonthValue(const char *month) {
    if (strcmp(month, "Jan") == 0) return 1;
    if (strcmp(month, "Feb") == 0) return 2;
    if (strcmp(month, "Mar") == 0) return 3;
    if (strcmp(month, "Apr") == 0) return 4;
    if (strcmp(month, "May") == 0) return 5;
    if (strcmp(month, "Jun") == 0) return 6;
    if (strcmp(month, "Jul") == 0) return 7;
    if (strcmp(month, "Aug") == 0) return 8;
    if (strcmp(month, "Sep") == 0) return 9;
    if (strcmp(month, "Oct") == 0) return 10;
    if (strcmp(month, "Nov") == 0) return 11;
    if (strcmp(month, "Dec") == 0) return 12;
    return 0;  // Invalid month
}

void swapDates(Date *a, Date *b) {
    Date temp = *a;
    *a = *b;
    *b = temp;
}

void sort_in(Product *p) {
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (p->dat[i].year > p->dat[j].year ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) > getMonthValue(p->dat[j].mon)) ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) == getMonthValue(p->dat[j].mon) && p->dat[i].day > p->dat[j].day)) {
                swapDates(&p->dat[i], &p->dat[j]);
            }
        }
    }
}

void sort_de(Product *p) {
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (p->dat[i].year < p->dat[j].year ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) < getMonthValue(p->dat[j].mon)) ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) == getMonthValue(p->dat[j].mon) && p->dat[i].day < p->dat[j].day)) {
                swapDates(&p->dat[i], &p->dat[j]);
            }
        }
    }
}

void sort_in_de(Product *p) {
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (p->dat[i].year > p->dat[j].year ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) > getMonthValue(p->dat[j].mon)) ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) == getMonthValue(p->dat[j].mon) && p->dat[i].day > p->dat[j].day)) {
                swapDates(&p->dat[i], &p->dat[j]);
            }
        }
    }

    int k = 0;
    for (int i = 9; i >= 5; i--) {
        if (p->dat[i].year == p->dat[4].year && getMonthValue(p->dat[i].mon) == getMonthValue(p->dat[4].mon) && p->dat[i].day == p->dat[4].day) {
            swapDates(&p->dat[i], &p->dat[4 + k + 1]);
            k++;
        }
    }

    for (int i = 5 + k; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (p->dat[i].year < p->dat[j].year ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) < getMonthValue(p->dat[j].mon)) ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) == getMonthValue(p->dat[j].mon) && p->dat[i].day < p->dat[j].day)) {
                swapDates(&p->dat[i], &p->dat[j]);
            }
        }
    }
}

void sort_de_in(Product *p) {
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (p->dat[i].year < p->dat[j].year ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) < getMonthValue(p->dat[j].mon)) ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) == getMonthValue(p->dat[j].mon) && p->dat[i].day < p->dat[j].day)) {
                swapDates(&p->dat[i], &p->dat[j]);
            }
        }
    }

    int k = 0;
    for (int i = 5; i < 10; i++) {
        if (p->dat[i].year == p->dat[4].year && getMonthValue(p->dat[i].mon) == getMonthValue(p->dat[4].mon) && p->dat[i].day == p->dat[4].day) {
            swapDates(&p->dat[i], &p->dat[4 + k + 1]);
            k++;
        }
    }

    for (int i = 5 + k; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (p->dat[i].year > p->dat[j].year ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) > getMonthValue(p->dat[j].mon)) ||
                (p->dat[i].year == p->dat[j].year && getMonthValue(p->dat[i].mon) == getMonthValue(p->dat[j].mon) && p->dat[i].day > p->dat[j].day)) {
                swapDates(&p->dat[i], &p->dat[j]);
            }
        }
    }
}

int main() {
    FILE *fp;
    fp = fopen("week01.csv", "r");
    if (fp == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    char line[300];
    int count = 0;
    Product entry[150];

    while (fgets(line, sizeof(line), fp)) {
        int index = 0;

        // Read name
        int charIndex = 0;
        while (line[index] != ',') {
            entry[count].name[charIndex++] = line[index++];
        }
        entry[count].name[charIndex] = '\0';
        index++;  // Move past ','

        // Read dates
        for (int i = 0; i < 10; i++) {
            sscanf(&line[index], "%d-%3[^-]-%d,", &entry[count].dat[i].day, entry[count].dat[i].mon, &entry[count].dat[i].year);
            index += 12;  // Move past date and ','
        }

        // Read region
        charIndex = 0;
        while (line[index] != '\n' && line[index] != '\0') {
            entry[count].region[charIndex++] = line[index++];
        }
        entry[count].region[charIndex] = '\0';

        count++;
    }

    fclose(fp);

    for (int i = 0; i < count; i++) {
        if (strcmp(entry[i].region, "North") == 0) {
            sort_in(&entry[i]);
        } else if (strcmp(entry[i].region, "South") == 0) {
            sort_de(&entry[i]);
        } else if (strcmp(entry[i].region, "East") == 0) {
            sort_in_de(&entry[i]);
        } else if (strcmp(entry[i].region, "West") == 0) {
            sort_de_in(&entry[i]);
        }
    }

    FILE *fp1;
    fp1 = fopen("Output1.csv", "w");
    if (fp1 == NULL) {
        printf("Error opening the file for writing.\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp1, " %s,"
                      "%d-%s-%d,"
                      "%d-%s-%d,"
                      "%d-%s-%d,"
                      "%d-%s-%d,"
                      "%d-%s-%d,"
                      "%d-%s-%d,"
                      "%d-%s-%d,"
                      "%d-%s-%d,"
                      "%d-%s-%d,"
                      "%d-%s-%d,"
                      "%s\n",
                entry[i].name,
                entry[i].dat[0].day, entry[i].dat[0].mon, entry[i].dat[0].year,
                entry[i].dat[1].day, entry[i].dat[1].mon, entry[i].dat[1].year,
                entry[i].dat[2].day, entry[i].dat[2].mon, entry[i].dat[2].year,
                entry[i].dat[3].day, entry[i].dat[3].mon, entry[i].dat[3].year,
                entry[i].dat[4].day, entry[i].dat[4].mon, entry[i].dat[4].year,
                entry[i].dat[5].day, entry[i].dat[5].mon, entry[i].dat[5].year,
                entry[i].dat[6].day, entry[i].dat[6].mon, entry[i].dat[6].year,
                entry[i].dat[7].day, entry[i].dat[7].mon, entry[i].dat[7].year,
                entry[i].dat[8].day, entry[i].dat[8].mon, entry[i].dat[8].year,
                entry[i].dat[9].day, entry[i].dat[9].mon, entry[i].dat[9].year,
                entry[i].region);
    }

    fclose(fp1);
    printf("Written to Output1.csv\n");

    return 0;
}
