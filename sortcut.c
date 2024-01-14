#include <stdio.h>
#include <string.h>

int main() {
    char input[] = "P001,22-Mar-2024,24-Mar-2024,31-Mar-2024,22-Mar-2024,23-Mar-2024,23-Mar-2024,22-Mar-2024,22-Mar-2024,25-Mar-2024,28-Mar-2024,West";
    
    // Tokenize the input string
    char *token = strtok(input, ",-");

    // Iterate through the tokens
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",-");
    }

    return 0;
}


//
