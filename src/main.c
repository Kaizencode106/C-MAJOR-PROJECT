#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  

struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    char doctor[50];
};

struct Patient *patients = NULL; 
int count = 0;                 

void addPatient();
void displayPatients();
void searchPatient();
void deletePatient();
void saveToFile();
void loadFromFile();

void addPatient() {
    if (count >= MAX) {
        printf("\nPatient limit reached!\n");
        return;
    }

    patients = realloc(patients, (count + 1) * sizeof(struct Patient));

    printf("\nEnter Patient ID: ");
    scanf("%d", &patients[count].id);
    printf("Enter Name: ");
    scanf(" %[^\n]", patients[count].name);
    printf("Enter Age: ");
    scanf("%d", &patients[count].age);
    printf("Enter Gender: ");
    scanf(" %[^\n]", patients[count].gender);
    printf("Enter Disease: ");
    scanf(" %[^\n]", patients[count].disease);
    printf("Enter Assigned Doctor: ");
    scanf(" %[^\n]", patients[count].doctor);

    count++;
    printf("\n Patient added successfully!\n");

    saveToFile(); // Save after adding
}

void displayPatients() {
    if (count == 0) {
        printf("\nNo patients found!\n");
        return;
    }

    printf("\n--- List of Patients ---\n");
    for (int i = 0; i < count; i++) {  // array iteration
        printf("\nPatient ID: %d", patients[i].id);
        printf("\nName: %s", patients[i].name);
        printf("\nAge: %d", patients[i].age);
        printf("\nGender: %s", patients[i].gender);
        printf("\nDisease: %s", patients[i].disease);
        printf("\nDoctor: %s", patients[i].doctor);
        printf("\n----------------------------");
    }
    printf("\n");
}

// Function to search for a patient by ID
void searchPatient() {
    if (count == 0) {
        printf("\nNo records available.\n");
        return;
    }

    int id, found = 0;
    printf("\nEnter Patient ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            printf("\nPatient Found!\n");
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Gender: %s\n", patients[i].gender);
            printf("Disease: %s\n", patients[i].disease);
            printf("Doctor: %s\n", patients[i].doctor);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No patient found with ID %d.\n", id);
}

// Function to delete a patient record
void deletePatient() {
    if (count == 0) {
        printf("\nNo records available.\n");
        return;
    }

    int id, found = 0;
    printf("\nEnter Patient ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            // shift array elements
            for (int j = i; j < count - 1; j++) {
                patients[j] = patients[j + 1];
            }
            count--;
            patients = realloc(patients, count * sizeof(struct Patient));
            printf(" Patient deleted successfully!\n");
            found = 1;
            saveToFile(); // update file
            break;
        }
    }

    if (!found)
        printf("Patient with ID %d not found.\n", id);
}

// Function to save all patient records to a file
void saveToFile() {
    FILE *fp = fopen("patients.txt", "wb"); // binary mode
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(patients, sizeof(struct Patient), count, fp);
    fclose(fp);
}

// Function to load all patient records from file
void loadFromFile() {
    FILE *fp = fopen("patients.txt", "rb");
    if (fp == NULL) {
        return; // no previous file
    }

    fread(&count, sizeof(int), 1, fp);
    patients = malloc(count * sizeof(struct Patient));

    if (patients == NULL && count > 0) {
        printf("Memory allocation failed!\n");
        fclose(fp);
        return;
    }

    fread(patients, sizeof(struct Patient), count, fp);
    fclose(fp);
}

// Main function with menu
int main() {
    int choice;

    loadFromFile(); // load data from file when program starts

    while (1) {
        printf("\n=====================================\n");
        printf("     HOSPITAL MANAGEMENT SYSTEM\n");
        printf("=====================================\n");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: displayPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5:
                saveToFile();
                free(patients); // free memory
                printf("\nExiting... Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
