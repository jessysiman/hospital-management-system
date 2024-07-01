#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 3
#define MAX_APPOINTMENTS 100

typedef struct {
    char name[100];
    int day;
    int month;
    int year;
    char address[100];
    int phone;
    char bloodtype[10];
    char allergy[100];
    char disease[100];
} Patient;

typedef struct {
    char doctorname[100];
    int hourlyrate;
} Doctor;

typedef struct {
    Patient patient;
    Doctor doctor;
    int appointmentDuration;
    int medicineChoice;
    int medicineCost;
} Appointment;

void clearScreen() {
    system("cls"); // For Linux/macOS
    // system("cls"); // For Windows
}

void printMenu() {
    printf("=== Jesian Hospital Depok ====\n");
    printf("1. Register as a new patient\n");
    printf("2. Schedule an appointment\n");
    printf("3. Pay medical bills\n");
    printf("4. Exit menu\n");
    printf("===============================\n");
}

void addPatient(Patient patients[], int *patientCount) {
    clearScreen();
    Patient newPatient;
    printf("Enter patient name: ");
    scanf(" %[^\n]", newPatient.name);
    printf("Enter patient date of birth (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &newPatient.day, &newPatient.month, &newPatient.year);
    printf("Enter patient address: ");
    scanf(" %[^\n]", newPatient.address);
    printf("Enter patient phone number: ");
    scanf("%d", &newPatient.phone);
    printf("Enter patient blood type: ");
    scanf(" %[^\n]", newPatient.bloodtype);
    printf("Enter patient allergies: ");
    scanf(" %[^\n]", newPatient.allergy);
    printf("Enter patient recent disease: ");
    scanf(" %[^\n]", newPatient.disease);
    printf("Patient added successfully.\n");

    patients[*patientCount] = newPatient;
    (*patientCount)++;
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // Clears the input buffer
    getchar(); // Waits for Enter key press
}

void scheduleAppointment(Appointment appointments[], int *appointmentCount, Patient patients[], int patientCount, Doctor doctors[], int doctorCount) {
    clearScreen();
    if (patientCount == 0) {
        printf("You haven't registered as a patient yet. Please add a patient first.\n");
        printf("\nPress Enter to continue...");
        while (getchar() != '\n'); // Clears the input buffer
        getchar(); // Waits for Enter key press
        return;
    }

    char patientName[100];
    printf("Enter patient name: ");
    scanf(" %[^\n]", patientName);

    int patientIndex = -1;
    int i;
    for (i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].name, patientName) == 0) {
            patientIndex = i;
            break;
        }
    }

    if (patientIndex == -1) {
        printf("Patient not found in the database.\n");
        printf("\nPress Enter to continue...");
        while (getchar() != '\n'); // Clears the input buffer
        getchar(); // Waits for Enter key press
        return;
    }

    printf("Available doctors:\n");
    for (i = 0; i < doctorCount; i++) {
        printf("%d. %s\n", i + 1, doctors[i].doctorname);
    }

    int doctorIndex;
    printf("Enter the doctor's number: ");
    scanf("%d", &doctorIndex);

    if (doctorIndex < 1 || doctorIndex > doctorCount) {
        printf("Invalid doctor number.\n");
        printf("\nPress Enter to continue...");
        while (getchar() != '\n'); // Clears the input buffer
        getchar(); // Waits for Enter key press
        return;
    }

    int appointmentDuration;
    printf("Enter the appointment duration in minutes: ");
    scanf("%d", &appointmentDuration);

    Doctor selectedDoctor = doctors[doctorIndex - 1];
    int hourlyRate = selectedDoctor.hourlyrate;

    int emptySlot = -1;
    for (i = 0; i < MAX_APPOINTMENTS; i++) {
        if (appointments[i].patient.name[0] == '\0') {
            emptySlot = i;
            break;
        }
    }

    if (emptySlot == -1) {
        printf("Cannot schedule more appointments. Database is full.\n");
        printf("\nPress Enter to continue...");
        while (getchar() != '\n'); // Clears the input buffer
        getchar(); // Waits for Enter key press
        return;
    }

    Appointment newAppointment;
    newAppointment.patient = patients[patientIndex];
    newAppointment.doctor = selectedDoctor;
    newAppointment.appointmentDuration = appointmentDuration;
    newAppointment.medicineChoice = 0;
    newAppointment.medicineCost = 0;

    appointments[emptySlot] = newAppointment;
    (*appointmentCount)++;

    printf("Appointment scheduled successfully!\n");
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // Clears the input buffer
    getchar(); // Waits for Enter key press
}

void payMedicalBills(Appointment appointments[], int appointmentCount) {
    clearScreen();
    if (appointmentCount == 0) {
        printf("No appointments found in the database.\n");
        printf("\nPress Enter to continue...");
        while (getchar() != '\n'); // Clears the input buffer
        getchar(); // Waits for Enter key press
        return;
    }

    char patientName[100];
    printf("Enter patient name: ");
    scanf(" %[^\n]", patientName);

    int appointmentIndex = -1;
    int i;
    for (i = 0; i < appointmentCount; i++) {
        if (strcmp(appointments[i].patient.name, patientName) == 0) {
            appointmentIndex = i;
            break;
        }
    }

    if (appointmentIndex == -1) {
        printf("Patient's appointment not found in the database.\n");
        printf("\nPress Enter to continue...");
        while (getchar() != '\n'); // Clears the input buffer
        getchar(); // Waits for Enter key press
        return;
    }

    Appointment selectedAppointment = appointments[appointmentIndex];
    int totalCost = selectedAppointment.doctor.hourlyrate;

    printf("\n==== Appointment Receipt ====\n");
    printf("Patient Name: %s\n", selectedAppointment.patient.name);
    printf("Doctor Name: %s\n", selectedAppointment.doctor.doctorname);
    printf("Appointment Duration: %d minutes\n", selectedAppointment.appointmentDuration);

    char medicineChoice;
    printf("Include cost of medicine? (Y/N): ");
    scanf(" %c", &medicineChoice);

    if (medicineChoice == 'Y' || medicineChoice == 'y') {
        selectedAppointment.medicineChoice = 1;
        printf("Enter medicine cost: ");
        scanf("%d", &selectedAppointment.medicineCost);
        totalCost += selectedAppointment.medicineCost;
    } else {
        selectedAppointment.medicineChoice = 0;
    }

    printf("Total Cost: %d\n", totalCost);
    printf("=============================\n");
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // Clears the input buffer
    getchar(); // Waits for Enter key press
}

int main() {
    Patient patients[MAX_PATIENTS];
    int patientCount = 0;

    Doctor doctors[MAX_DOCTORS] = {
        { "Dr. Jessy", 100 },
        { "Dr. Fabian", 150 },
        { "Dr. Fassy", 200 }
    };
    int doctorCount = sizeof(doctors) / sizeof(doctors[0]);

    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount = 0;

    int choice;
    do {
        clearScreen();
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient(patients, &patientCount);
                break;
            case 2:
                scheduleAppointment(appointments, &appointmentCount, patients, patientCount, doctors, doctorCount);
                break;
            case 3:
                payMedicalBills(appointments, appointmentCount);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("\nPress Enter to continue...");
        while (getchar() != '\n'); // Clears the input buffer
        getchar(); // Waits for Enter key press
    } while (choice != 4);

    return 0;
}
