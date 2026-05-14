#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float gpa;
} Student;


long* seekPositions = NULL;
int recordCount = 0;


void storeRecordsASCII(const char* filename, Student arr[], int n) {
    FILE* fp = fopen(filename, "w");
    if (!fp) return;
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %s %f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
    fclose(fp);
}

void createIndexTable(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return;
    int count = 0;
    char buffer[200];

    
    while (fgets(buffer, sizeof(buffer), fp)) {
        count++;
    }
    recordCount = count;

    
    seekPositions = (long*)malloc(recordCount * sizeof(long));

    rewind(fp);
    for (int i = 0; i < recordCount; i++) {
        seekPositions[i] = ftell(fp); 
        fgets(buffer, sizeof(buffer), fp); 
    }
    fclose(fp);
}

void displayRecord(const char* filename, int index) {
    if (index < 0 || index >= recordCount) {
        printf("Invalid index.\n");
        return;
    }
    FILE* fp = fopen(filename, "r");
    if (!fp) return;

    Student s;
    fseek(fp, seekPositions[index], SEEK_SET);

    if (fscanf(fp, "%d %49s %f", &s.id, s.name, &s.gpa) == 3) {
        printf("Record %d found at offset %ld: ID= %d, Name= %s, GPA= %.2f\n", 
                index, seekPositions[index], s.id, s.name, s.gpa);
    } else {
        printf("Record not found.\n");
    }
    fclose(fp);
}

int main() {
    const char* filename = "students_ascii.txt";
    Student students[] = {
        {1, "Alice", 3.5},
        {2, "Bob", 3.8},
        {3, "Charlie", 3.2}
    };

    storeRecordsASCII(filename, students, 3);
    createIndexTable(filename);

    int m;
    printf("Enter the record index to retrieve (0 to %d): ", recordCount - 1);
    if (scanf("%d", &m) == 1) {
        displayRecord(filename, m);
    }

    
    if (seekPositions != NULL) {
        free(seekPositions);
    }
    
    return 0;
}
