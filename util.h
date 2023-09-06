/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Kushaal Singh
Student ID#: 1153020228
Email      : kna28@myseneca.ca
Section    : NRB

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// Fail-Guards : Prevents the complier from making multiple copies of the header files.
#ifndef CORE_H
#define CORE_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// Reads through the 'stdin' until a newline character is found.
void clearInputBuffer(void);

// Pauses the program until the user presses the enter key to continue.
void suspend(void);

// Takes an integer as an input from the user.
int inputInt(void);

// Takes a positive integer as an input from the user.
int inputIntPositive(void);

// Takes an integer input from the user which must be within a rage.
int inputIntRange(int lower, int upper);

// Takes a character input from the user which must be one of the elements of 'character_array'.
char inputCharOption(char character_array[]);

// The user inputs a string which must be in a certain range.
void inputCString(char cString[], int min, int max);

// Takes an integer as an argument and prints it in a formatted way.
void displayFormattedPhone(const char* str);

// Returns the number of days in the month depending upon the year.
int daysByYearAndMonth(int year, int month);

#endif