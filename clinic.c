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

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt) {    // Take the 'patient' struct as parameter, max number of patients and the format in which the output must be printed.
    int i = 0;
    if (fmt == 1) {
        for (i = 0; i < max; i++) {
            if (patient[i].patientNumber == 0) continue;                       // Traverses through the entire struct and printers their info.
            displayPatientData(&patient[i], fmt);
        }
    }
    else if (fmt == 2) {
        displayPatientTableHeader();

        for (i = 0; i < max; i++) {
            if (patient[i].patientNumber == 0) continue;
            displayPatientData(&patient[i], fmt);
        }
    }
    putchar('\n');
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max) {               // Users inputs an integer corresponding to the the numbers in the menu.
    int done = 1;
    while (done) {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");

        int choice = inputIntRange(0, 2);
        putchar('\n');

        switch (choice) {
        case 0:                                                                 // If the user inputs 0, the function returns back to the 'menuMain' function.
            done = 0;
            break;
        case 1:                                                                 // If the users inputs 1, 'searchPatientByPatientNumber' is called.
            searchPatientByPatientNumber(patient, max);
            break;
        case 2:                                                                 // If the users inputs 2, 'searchPatientByPhoneNumber' is called.
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        default:
            break;
        }
    }
    return;
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max) {                            // This functions primary role is to validate if the number of patients are at it max capacity or not.
    int i = 0;
    int full = 1;

    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == 0) {                                    // Traverses the entier array looking for any empty sport.
            full = 0;                                                           // If the statement is true, full is set to zero.
            break;
        }
    }
    if (full) {                                                                 // If the full is not zero, the functoin prints an error message and returns to 'menuPatien'.
        printf("ERROR: Patient listing is FULL!\n\n");
        return;
    }
    for (i = 0; i < max; i++) {                                                 // The 'patientNumber' which is zero is identified.
        if (patient[i].patientNumber == 0) {
            patient[i].patientNumber = nextPatientNumber(patient, max);         // However, if the full is set zero, the 'patientNumber' that is zero get's assigned a new patient number.
            inputPatient(&patient[i]);                                          // Patient is made to input thier details.
            inputPhoneData(&(patient[i].phone));                                // Then a phone numbers needs to be entered. 
            printf("\n*** New patient record added ***\n\n");
            break;
        }
    }
}


// Edit a patient record from the patient array
void removePatient(struct Patient patient[], int max) {
    printf("Enter the patient number: ");
    int num = inputIntPositive();                                               // User is prompted to enter the their patient number.
    int index = findPatientIndexByPatientNum(num, patient, max);                // the patient number is passed to 'findPatientIndexByPatientNum' to identify user info in the struct.
    putchar('\n');
    char options[3] = { 'y', 'n' };
    if (index > -1) {
        displayPatientData(&patient[index], 1);                                 // Patient index number is passed to 'displayPatientData' to be printed in fmt format 1.
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        char choice = inputCharOption(options);
        if (choice == 'y') {                                                    // If the user selects y, all the user info in the struct corresponding to their index number is set to empty.
            patient[index].patientNumber = 0;
            patient[index].name[0] = '\0';
            patient[index].phone.description[0] = '\0';
            patient[index].phone.number[0] = '\0';
            printf("Patient record has been removed!\n");
        }
        else {
            printf("Operation aborted.\n");
        }

        putchar('\n');
    }
    else {
        printf("ERROR: Patient record not found!\n\n");
    }
}


void editPatient(struct Patient patient[], int max) {
    int done = 1;
    printf("Enter the patient number: ");
    int num = inputIntPositive();
    putchar('\n');
    int index = findPatientIndexByPatientNum(num, patient, max);

    if (index > -1)
    {
        while (done) {
            printf("Edit Patient (0%d)\n", patient[index].patientNumber);
            printf("=========================\n");
            printf("1) NAME : %s\n", patient[index].name);                              // User's name is printed by the index number.
            printf("2) PHONE: "); displayFormattedPhone(patient[index].phone.number);   // Formated phone number is printed from 'displayFormattedPhone' in core.c.
            putchar('\n');
            printf("-------------------------\n");
            printf("0) Previous menu\n");
            printf("-------------------------\n");
            printf("Selection: ");

            int choice = inputIntRange(0, 2);

            if (choice == 0) {
                putchar('\n');
                done = 0;
                return;
            }
            else if (choice == 1) {                                                     // If the user chooses 1, name input is taken.
                printf("\nName  : ");
                inputCString(patient[index].name, 0, NAME_LEN);
                printf("\nPatient record updated!\n\n");
            }
            else if (choice == 2) {                                                     // If the user chooses 2, phone number input is taken.
                inputPhoneData(&patient[index].phone);
                printf("\nPatient record updated!\n\n");
            }
        }
        return;
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data) {
    int i, count;
    displayScheduleTableHeader(&data->appointments->date, 1);
    sortAppointmentsByAscendingOrder(data);
    for (i = 0; i < data->maxAppointments; i++) {
        for (count = 0; count < data->maxPatient; count++) {
            if (data->patients[count].patientNumber == data->appointments[i].patientNum) {      // If patient's number has an equal in appointments struct, the next line executes.
                displayScheduleData(&data->patients[count], &data->appointments[i], 1);         // Scheduled data is displayed.
            }
        }
    }
    putchar('\n');
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data) {
    int index;
    int i = 0;
    int count = 0;
    int noApp = 0;

    int year, month, day;
    printf("Year        : ");
    year = inputIntPositive();
    printf("Month (1-12): ");
    month = inputIntRange(1, 12);
    int daysInMonth = daysByYearAndMonth(year, month);                                                                                                  // The number of days depending on the user's input are calculated.
    printf("Day (1-%d)  : ", daysInMonth);
    day = inputIntRange(1, daysInMonth);
    struct Date date;                                                                                                                                   // Create a Date struct to represent the selected date.
    date.year = year;
    date.month = month;
    date.day = day;
    putchar('\n');
    displayScheduleTableHeader(&date, 0);
    struct ClinicData patData;
    struct Patient patient[20];                                                                                                                         // Array to store matching patients.
    struct Appointment appointment[50];                                                                                                                 // Array to store matching appointments.
    for (i = 0; i < data->maxAppointments; i++) {
        if ((data->appointments[i].date.year == year) && (data->appointments[i].date.month == month) && (data->appointments[i].date.day == day)) {      // Check if the appointment's date matches the selected date.
            index = findPatientIndexByPatientNum(data->appointments[i].patientNum, data->patients, data->maxPatient);                                   // Find the index of the patient associated with the appointment.
            patient[count] = data->patients[index];                                                                                                     // Store the matching patient and appointment data.
            appointment[count] = data->appointments[i];
            noApp++;
            count++;
        }
    }
    patData.appointments = appointment;                                                                                                                 // Update the patData struct with the matching patient and appointment data.
    patData.patients = patient;
    patData.maxAppointments = count;
    patData.maxPatient = data->maxPatient;
    sortAppointmentsByAscendingOrder(&patData);
    for (i = 0; i < count; i++) {
        displayScheduleData(&patData.patients[i], &patData.appointments[i], 0);                                                                         // Display the schedule data for each matching appointment.
    }
    putchar('\n');
    if (noApp == 0) {
        printf("*** No appointments found ***\n");
    }
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appointment, int maxAppts, struct Patient* patients, int maxPatient) {
    int patient_num = 0;
    int year = 0; int month = 0; int day = 0; int hr = 0; int min = 0;
    int index = 0;
    int empty_appointment = 0;
    int i;
    for (i = 0; i < maxAppts; i++) {                                                                                                    // Find an empty appointment slot or determine that none are available.
        if (appointment[i].patientNum < 1) {
            empty_appointment += 1;
            index = i;
        }
    }
    int done = 1;
    if (empty_appointment) {
        while (done) {
            printf("Patient Number: ");
            patient_num = inputIntPositive();
            for (i = 0; i < maxPatient; i++) {                                                                                         // Check if the entered patient number matches an existing patient record.
                if (patients[i].patientNumber == patient_num) {
                    done = 0;
                }
            }
            if (done) {
                printf("ERROR: Patient record not found!\n");
            }
        }
    }
    else {
        printf("ERROR: No more available time slots\n");
    }
    int select_time = 1;
    int check = 0;
    while (select_time) {
        if (check == 1) {
            select_time = 0;
        }
        printf("Year        : ");
        year = inputIntPositive();
        printf("Month (1-12): ");
        month = inputIntRange(0, 12);
        int daysInMonth = daysByYearAndMonth(year, month);
        printf("Day (1-%d)  : ", daysInMonth);
        day = inputIntRange(0, daysInMonth);
        done = 1;
        while (done) {
            printf("Hour (0-23)  : ");
            hr = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            min = inputIntRange(0, 59);
            if ((min % HOURINTERVAL != 0) || (min + hr > ENDHOUR) || (hr < STARTHOUR) || (hr > ENDHOUR)) {                             // Check if the entered time meets the criteria.
                printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", STARTHOUR, ENDHOUR, HOURINTERVAL);
            }
            else {
                check = 1;
                done = 0;
            }
        }
        for (i = 0; i < maxAppts; i++) {                                                                                               // Check if the entered appointment time conflicts with existing appointments.
            int isYearEqual = appointment[i].date.year == year ? 1 : 0;
            int isMonthEqual = appointment[i].date.month == month ? 1 : 0;
            int isDayEqual = appointment[i].date.day == day ? 1 : 0;
            int isHourEqual = appointment[i].time.hour == hr ? 1 : 0;
            int isMinEqual = appointment[i].time.min == min ? 1 : 0;

            if (isYearEqual && isMonthEqual && isDayEqual && isHourEqual && isMinEqual) {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
        }
    }
    appointment[index].patientNum = patient_num;                                                                                        // Set the appointment details for the selected slot.
    appointment[index].date.year = year;
    appointment[index].date.month = month;
    appointment[index].date.day = day;
    appointment[index].time.hour = hr;
    appointment[index].time.min = min;
    printf("\n*** Appointment scheduled! ***\n\n");
}


// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appointment, int maxAppts, struct Patient* patients, int maxPatient) {
    int patient_num = 0;
    int year = 0; int month = 0; int day = 0; int i = 0;
    int index;
    char sel;
    char options[3] = { 'y', 'n' };
    printf("Patient Number: ");
    patient_num = inputIntPositive();
    index = findPatientIndexByPatientNum(patient_num, patients, maxPatient);

    if (index > -1) {
        printf("Year        : ");                                                               // Prompt for the year, month, and day of the appointment.
        year = inputIntPositive();
        printf("Month (1-12): ");
        month = inputIntRange(0, 12);
        int daysInMonth = daysByYearAndMonth(year, month);
        printf("Day (1-%d)  : ", daysInMonth);
        day = inputIntRange(0, daysInMonth);
        putchar('\n');
        displayPatientData(&patients[index], 1);                                                // Display patient data and confirm appointment removal.
        printf("Are you sure you want to remove this appointment (y,n): ");
        sel = inputCharOption(options);
        putchar('\n');
        if (sel == 'y') {                                                                       // Find and remove the appointment based on patient number and date.
            for (i = 0; i < maxAppts; i++) {
                int isPatNumEqual = appointment[i].patientNum == patient_num ? 1 : 0;
                int isYearEqual = appointment[i].date.year == year ? 1 : 0;
                int isMonthEqual = appointment[i].date.month == month ? 1 : 0;
                int isDayEqual = appointment[i].date.day == day ? 1 : 0;

                if (isPatNumEqual && isYearEqual && isMonthEqual && isDayEqual) {
                    appointment[i].patientNum = 0;                                              // Mark the appointment slot as available.
                }
            }
            printf("Appointment record has been removed!\n\n");
        }
        else {
            printf("Operation aborted\n\n");
        }
    }
    else {
        printf("ERROR: Patient record not found!\n\n");
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    printf("Search by patient number: ");

    int choice = inputIntPositive();
    int index = findPatientIndexByPatientNum(choice, patient, max);         // Find the index of the patient in the patient array using their patient number.

    if (index > -1) {                                                       // If the patient is found in the array.
        putchar('\n');
        displayPatientData(&patient[index], 1);                             // Display the patient's data.
        putchar('\n');
        suspend();
    }
    else {
        printf("\n*** No records found ***\n\n");
        suspend();
    }
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    printf("Search by phone number: ");
    char ph[PHONE_LEN + 1];                                     // Declare a character array to store the phone number.
    inputCString(ph, 10, 10);
    int hasData = 0;
    putchar('\n');
    displayPatientTableHeader();
    int i;
    for (i = 0; i < max; i++) {
        if (strcmp(patient[i].phone.number, ph) == 0) {         // Compare the phone number in the patient record with the input phone number.
            hasData = 1;
            displayPatientData(&patient[i], 2);                 // Display the patient's data using a different format.
        }
    }
    clearInputBuffer();
    putchar('\n');

    if (!hasData) {
        printf("*** No records found ***\n");
        putchar('\n');
    }
}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max) {
    int i;
    int maxNum = -1;                                            // Initialize a variable to keep track of the maximum patient number.
    for (i = 0; i < max; i++) {                                 // Iterate through the patient array to find the highest patient number.
        if (patient[i].patientNumber > maxNum) {
            maxNum = patient[i].patientNumber;                  // Update the maximum patient number if a higher number is found.
        }
    }
    return maxNum + 1;                                          // Return the next available patient number by adding 1 to the maximum patient number.
}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) {      // This function finds the index of a patient in the patient array based on the patient number.
    int i;
    for (i = 0; i < max; i++) {                                                                     // Iterate through the patient array to find the patient with the specified patient number.
        if (patient[i].patientNumber == patientNumber) {                                            // Compare the patient's number with the specified patient number.
            return i;
        }
    }
    return -1;
}


// Sort the patients appointments from the earliest date and time to the latest date and time.
void sortAppointmentsByAscendingOrder(struct ClinicData* data) {
    int i;
    int sort;
    struct Appointment sortedApoint = { 0 };
    for (i = data->maxAppointments - 1; i > 0; i--) {                                                                           // Iterate through the appointments array using bubble sort algorithm.
        for (sort = 0; sort < i; sort++) {

            int isYearEqual = data->appointments[sort].date.year == data->appointments[sort + 1].date.year ? 1 : 0;             // Compare the date and time components of appointments.
            int isMonthEqual = data->appointments[sort].date.month == data->appointments[sort + 1].date.month ? 1 : 0;
            int isDayEqual = data->appointments[sort].date.day == data->appointments[sort + 1].date.day ? 1 : 0;

            if (data->appointments[sort].date.year > data->appointments[sort + 1].date.year) {                                  // Check for the need to swap appointments based on date and time comparisons.
                sortedApoint = data->appointments[sort];
                data->appointments[sort] = data->appointments[sort + 1];
                data->appointments[sort + 1] = sortedApoint;
            }
            else if (isYearEqual && data->appointments[sort].date.month > data->appointments[sort + 1].date.month) {
                sortedApoint = data->appointments[sort];
                data->appointments[sort] = data->appointments[sort + 1];
                data->appointments[sort + 1] = sortedApoint;
            }
            else if (isYearEqual && isMonthEqual && data->appointments[sort].date.day > data->appointments[sort + 1].date.day) {
                sortedApoint = data->appointments[sort];
                data->appointments[sort] = data->appointments[sort + 1];
                data->appointments[sort + 1] = sortedApoint;
            }
            else if (isYearEqual && isMonthEqual && isDayEqual && data->appointments[sort].time.hour > data->appointments[sort + 1].time.hour) {
                sortedApoint = data->appointments[sort];
                data->appointments[sort] = data->appointments[sort + 1];
                data->appointments[sort + 1] = sortedApoint;
            }
            else if (isYearEqual && isMonthEqual && isDayEqual && data->appointments[sort].time.hour == data->appointments[sort + 1].time.hour && data->appointments[sort].time.min > data->appointments[sort + 1].time.min) {
                sortedApoint = data->appointments[sort];
                data->appointments[sort] = data->appointments[sort + 1];
                data->appointments[sort + 1] = sortedApoint;
            }
        }
    }
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient) {
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: 0%d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 3, NAME_LEN);           // Call a function to input a fixed-size character array (C-string) and store it in the 'name' field of the patient structure.
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone) {
    printf("\nPhone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");

    int choice = inputIntRange(1, 4);                   // Get user's choice for contact type using the inputIntRange function.

    if (choice >= 1 && choice <= 3) {
        putchar('\n');
        switch (choice) {
        case 1:                                         // If user chooses 'Cell', set the description and display it.
            strcpy(phone->description, "CELL");
            printf("Contact: CELL\n");
            break;
        case 2:                                         // If user chooses 'Home', set the description and display it,
            strcpy(phone->description, "HOME");
            printf("Contact: HOME\n");
            break;
        case 3:                                         // If user chooses 'Work', set the description and display it.
            strcpy(phone->description, "WORK");
            printf("Contact: WORK\n");
            break;
        }
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        clearInputBuffer();
    }
    else {                                              // If user chooses 'TBD' or an invalid choice, set description to 'TBD' and clear the phone number.
        strcpy(phone->description, "TBD");
        phone->number[0] = '\0';
    }
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max) {
    FILE* fp = NULL;                                                        // File pointer to read the data file.
    int elements = 0;
    fp = fopen(datafile, "r");                                              // Open the data file for reading.
    if (fp != NULL) {                                                       // Read patient data from the file until the 'max' limit is reached or end of file is encountered.
        while (elements < max && !feof(fp)) {                               // Read patient number, name, description, and phone number using format specifiers.
            fscanf(fp, "%d|", &patients[elements].patientNumber);
            fscanf(fp, "%16[^|]|", patients[elements].name);
            fscanf(fp, "%5[^|]|", patients[elements].phone.description);
            fscanf(fp, "%11[^\n]\n", patients[elements].phone.number);
            elements++;
        }
        fclose(fp);                                                         // Close the file after reading.
    }
    else {
        printf("Failed to open file\n");
    }
    return elements;
}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    FILE* fp = NULL;
    int elements = 0;
    fp = fopen(datafile, "r");
    if (fp != NULL) {                                                       // Read appointment data from the file using format specifiers until EOF is reached or 'max' is reached.
        while (fscanf(fp, "%d,%d,%d,%d,%d,%d\n",
            &appoints[elements].patientNum, &appoints[elements].date.year, &appoints[elements].date.month,
            &appoints[elements].date.day, &appoints[elements].time.hour, &appoints[elements].time.min) != EOF && elements < max) {
            elements++;
        }
        fclose(fp);
    }
    else {
        printf("Failed to open file\n");
    }
    return elements;
}