#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAXNAME 64

// Employee structure definition
struct employee {
    int id;
    char first_name[MAXNAME];
    char last_name[MAXNAME];
    int salary;
};

#endif // EMPLOYEE_H
