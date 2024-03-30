#include <stdio.h>
#include <string.h>

#include "employee.h"
#include "readfile.h"

#define MAX_EMPLOYEES 1024

void print_menu();
int handle_user_choice(int choice, struct employee employees[], int* num_employees);
void load_employee_data(const char* filename, struct employee employees[], int* num_employees);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct employee employees[MAX_EMPLOYEES];
    int num_employees = 0;
    
    load_employee_data(argv[1], employees, &num_employees);

    int choice;
    do {
        print_menu();
        scanf("%d", &choice);
    } while (handle_user_choice(choice, employees, &num_employees) != 5);

    return 0;
}

void print_menu() {
    printf("\nEmployee Database Menu:\n");
    printf("1. Print the Database\n");
    printf("2. Lookup employee by ID\n");
    printf("3. Lookup employee by last name\n");
    printf("4. Add an Employee\n");
    printf("5. Quit\n");
    printf("Enter your choice: ");
}


void print_database(struct employee employees[], int num_employees) {
    printf("\nID\tFirst Name\tLast Name\tSalary\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < num_employees; i++) {
        printf("%d\t%s\t\t%s\t\t%d\n", 
            employees[i].id, 
            employees[i].first_name, 
            employees[i].last_name, 
            employees[i].salary);
    }
    printf("-----------------------------------------------------\n");
    printf("Total Employees: %d\n\n", num_employees);
}

void lookup_by_id(struct employee employees[], int num_employees) {
    int id;
    printf("Enter employee ID: ");
    scanf("%d", &id);
    
    for (int i = 0; i < num_employees; i++) {
        if (employees[i].id == id) {
            printf("Employee Found: %d %s %s %d\n", 
                employees[i].id, employees[i].first_name, 
                employees[i].last_name, employees[i].salary);
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

void lookup_by_last_name(struct employee employees[], int num_employees) {
    char last_name[MAXNAME];
    printf("Enter employee's last name: ");
    scanf("%63s", last_name);
    
    for (int i = 0; i < num_employees; i++) {
        if (strcmp(employees[i].last_name, last_name) == 0) {
            printf("Employee Found: %d %s %s %d\n", 
                employees[i].id, employees[i].first_name, 
                employees[i].last_name, employees[i].salary);
            return;
        }
    }
    printf("Employee with last name %s not found.\n", last_name);
}

void add_employee(struct employee employees[], int* num_employees) {
    if (*num_employees >= MAX_EMPLOYEES) {
        printf("Database is full. Cannot add more employees.\n");
        return;
    }
    
    struct employee new_emp;
    printf("Enter new employee details (ID First_name Last_name Salary): ");
    scanf("%d %63s %63s %d", &new_emp.id, new_emp.first_name, new_emp.last_name, &new_emp.salary);
    
    employees[*num_employees] = new_emp;
    (*num_employees)++;
    printf("Employee added successfully.\n");
}


void load_employee_data(const char* filename, struct employee employees[], int* num_employees) {
    if (open_file(filename) != 0) {
        printf("Error opening file.\n");
        return;
    }

    while (*num_employees < MAX_EMPLOYEES &&
        read_int(&employees[*num_employees].id) == 0 &&
        read_string(employees[*num_employees].first_name) == 0 &&
        read_string(employees[*num_employees].last_name) == 0 &&
        read_int(&employees[*num_employees].salary) == 0) {
        (*num_employees)++;
    }

    close_file();
}

int handle_user_choice(int choice, struct employee employees[], int* num_employees) {
    switch (choice) {
        case 1:
            print_database(employees, *num_employees); 
            break;
        case 2:
            lookup_by_id(employees, *num_employees); 
            break;
        case 3:
            lookup_by_last_name(employees, *num_employees); 
            break;
        case 4:
            add_employee(employees, num_employees);
            break;
        case 5:
            printf("Quitting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
    return choice;
}
