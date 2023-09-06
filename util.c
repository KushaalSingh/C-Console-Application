#include "core.h"   

/* This function clears the input buffer by reading characters from the standard input stream until a newline character is encountered.
   The purpose of this function is to discard any characters left in the input buffer after a previous input operation. */

void clearInputBuffer(void) {
    char ch = 'x';
    while (ch != '\n') {
        ch = getchar();
    }
}

/* The function pauses the program's execution until the user presses the "Enter" key.
   It achieves this by displaying a prompt, clearing the input buffer to remove any characters left in it. */

void suspend(void) {
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

/* This function reads from the standard input and validates whether the user only entered an integer. If not the user must enter a new
   value again. */

int inputInt(void) {
    int num;        // To store user input.
    int done = 1;
    char nextChar;  // To check if the value of 'num' is followed by an newline character or not.   

    while (done) {
        int return_value = scanf("%d%c", &num, &nextChar);  // 'return_value' stores the result of scaning 'num' & 'nextChar' by checking if they are true (1) or false (0).
        if (return_value == 0) {
            printf("Error! Input a whole number: ");
        }
        else if (return_value == 2) {
            if (nextChar == '\n') {
                done = 0;
            }
            else {
                printf("Error! Input a whole number: ");
                clearInputBuffer();
            }
        }
        if (nextChar != '\n') {
            clearInputBuffer();
        }
    }
    return num;
}

/* This function does the same thing as the inputInt function above, however, the value entered must also be positive.
   If not the user will be asked to enter a new value again. */

int inputIntPositive(void) {
    int num;
    int done = 1;
    char nextChar;

    while (done) {
        int return_value = scanf("%d%c", &num, &nextChar);
        if (return_value == 0) {
            printf("Error! Input a whole number: ");
        }
        else if (return_value == 2) {
            if (nextChar == '\n') {
                if (num > 0) {          // This 'if' statement makes sure that the value is positive.
                    done = 0;
                }
                else {
                    printf("ERROR! Value must be > 0: ");
                }
            }
            else {
                printf("Error! Input a whole number: ");
                clearInputBuffer();
            }
        }
        if (nextChar != '\n') {
            clearInputBuffer();
        }
    }
    return num;
}

/* The following function validates the user input to see if it is within a rage or not. The range is passed as a parameters as 'lower' & 'upper' */

int inputIntRange(int lower, int upper) {
    int num;
    int done = 1;
    char next_char;

    while (done) {
        int return_value = scanf("%d%c", &num, &next_char);
        if (return_value == 0) {
            printf("Error! Input a whole number: ");
        }
        else if (return_value == 2) {
            if (next_char == '\n') {
                if (num > upper || num < lower) {          // This 'if' statement checks if the user input is within the specified range or not.
                    printf("ERROR! Value must be between %d and %d inclusive: ", lower, upper);
                }
                else {
                    done = 0;
                }
            }
            else {
                printf("Error! Input a whole number: ");
                clearInputBuffer();
            }
        }
        if (next_char != '\n') {
            clearInputBuffer();
        }
    }
    return num;
}

/* This function reads a character input from the user and validate whether the entered character is one of the allowed options specified in the character_array. */

char inputCharOption(char character_array[]) {
    int i;
    int done = 1;
    char firstChar = '\0';
    char nextChar;
    int array_length = (int)strlen(character_array); // Length of 'character_array' is stored in 'array_length' by the virtue of 'strlen' function.

    while (done) {
        int checker = 0;
        int return_value = scanf(" %c%c", &firstChar, &nextChar);
        if (return_value != 2) {
            clearInputBuffer();
            printf("ERROR: Character must be one of [%s]: ", character_array);
        }
        else if (return_value == 2) {
            for (i = 0; i < array_length; i++) {    // The 'for' loop traversel the entier 'character_array'.                
                if ((firstChar == character_array[i]) && (nextChar == '\n')) {    // This 'if' statement checks if the current value of 'character_array' is equal to the user input.
                    checker++;
                }
            }
            if (checker == 1) {
                done = 0;
            }
            else {
                clearInputBuffer();
                printf("ERROR: Character must be one of [%s]: ", character_array);
            }
        }
    }
    return firstChar;
    clearInputBuffer();
}

/* Take a string input from the user and validate it on it's length. the range for the length is passed as an parameter.
   If not then the must re-enter the string. */

void inputCString(char cString[], int min, int max) {
    int done = 1;

    while (done) {
        char userCString[256];
        userCString[0] = '\0';
        scanf(" %[^\n]", userCString);
        int string_length = (int)strlen(userCString);

        if (string_length < min || string_length > max) {
            if (min == max) {
                printf("Invalid %d-digit number! Number: ", max);
            }
            else if (min == 0) {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
            else if (string_length > max) {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
            else {
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }
        }
        else {
            cString[0] = '\0';
            strcpy(cString, userCString);
            done = 0;
        }
    }
}

/* This function that takes a pointer to a null-terminated string (const char* str) as input and formats it as a phone number. */

void displayFormattedPhone(const char* str) {
    int len = 0;
    const char* tmp = str;
    int val = 1;
    int done = 1;

    if (str == NULL) {          // It checks if the input string is NULL. If it is, it prints a default phone number format and returns.
        printf("(___)___-____");
        return;
    }

    while ((*tmp != '\0') && (done)) {
        if (!(*tmp >= '0' && *tmp <= '9')) {
            val = 0;
            done = 0;
        }

        ++len;
        ++tmp;
    }

    if (!val || len != 10) {
        printf("(___)___-____");
    }
    else {
        printf("(%c%c%c)%c%c%c-%c%c%c%c", str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7], str[8], str[9]);
    }
}

int daysByYearAndMonth(int year, int month) {
    int numDays = 0;
    if (year % 4 == 0) {
        if (month == 2) {
            numDays = 29;
        }
        else if (month % 2 != 0) {
            numDays = 31;
        }
        else if (month % 2 == 0) {
            numDays = 30;
        }
    }
    else if (year % 4 != 0) {
        if (month == 2) {
            numDays = 28;
        }
        else if (month % 2 != 0) {
            numDays = 31;
        }
        else if (month % 2 == 0) {
            numDays = 30;
        }
    }
    return numDays;
}