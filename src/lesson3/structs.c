#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

enum grade {
    FRESHMAN = 1,
    SOPHOMORE = 2,
    JUNIOR = 3,
    SENIOR = 4
};

struct student {
    char* name;
    unsigned int age;
    enum grade grade;
} students[10];

unsigned char num_students = 0;

/* helper function to replace a newline character with null terminator */
void null_terminate(char* buf) {
    char* nl = strchr(buf, '\n');
    if (nl) { *nl = '\0'; }
}

/* helper function to get a one-digit int from user */
int get_int() {
    char buf[8];
    fgets(buf, 8, stdin);
    null_terminate(buf);
    return atoi(buf);
}

void add_student() {
    char* name = malloc(0x10); // allocated on heap, ignore for now
    int age;
    int g;
    enum grade grade;
    if (num_students == 10) {
        printf("Student roster full!\n");
        return;
    }
    printf("Enter a name (less than 16 characters)\n > ");
    fgets(name, 0x10, stdin);
    null_terminate(name);
    printf("Enter an age\n > ");
    age = get_int();
    printf("Enter a grade (FRESH=1, SOPH=2, JUN=3, SEN=4)\n > ");
    g = get_int();
    if (g > (int)SENIOR || g < (int)FRESHMAN) {
        puts("Invalid grade!");
        return;
    }
    grade = (enum grade)g;
    students[num_students++] = (struct student){ name, age, grade };
}

void lookup_student() {
    int idx;
    struct student c;
    printf("Enter a student number (1-10)\n > ");
    idx = get_int();
    if (idx < 0 || idx >= num_students) {
        puts("Invalid index!");
        return;
    }
    c = students[idx];
    printf("Student %d\n", idx);
    printf(" Name: %s\n", c.name);
    printf(" Age: %d\n", c.age);
    printf(" Grade: ");
    switch (c.grade) {
        case FRESHMAN:
            puts("Freshman");
            break;
        case SOPHOMORE:
            puts("Sophomore");
            break;
        case JUNIOR:
            puts("Junior");
            break;
        case SENIOR:
            puts("Senior");
            break;
    }
}

void menu() {
    puts("Please enter a choice:");
    puts(" 1. Enter a student");
    puts(" 2. Look up a student");
    puts(" 3. Quit");
    printf(" > ");
}

int main() {
    char choice;
    int ichoice;
    while (1) {
        menu();
        ichoice = get_int();
        switch (ichoice) {
        case 1:
            add_student();
            break;
        case 2:
            lookup_student();
            break;
        default:
            return 0;
        }
    }
}

