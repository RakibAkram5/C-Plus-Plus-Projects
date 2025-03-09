#include <iostream>
using namespace std;

const int MAX_EMP = 100;

struct Employee {
    int id;
    float hoursWorked;
    float hourlyRate;
    float grossSalary;
    float taxDeduction;
    float netSalary;
};

// Calculate the salary values for an employee.
void computeSalary(Employee& emp) {
    emp.grossSalary = emp.hoursWorked * emp.hourlyRate;
    emp.taxDeduction = 0.1f * emp.grossSalary;  // assuming 10% tax
    emp.netSalary = emp.grossSalary - emp.taxDeduction;
}

// Pre-populate sample data (here 5 records; extend as needed)
void prePopulate(Employee employees[], int& count) {
    count = 5;
    employees[0] = { 101, 40, 20.0f, 0, 0, 0 };
    employees[1] = { 102, 35, 15.0f, 0, 0, 0 };
    employees[2] = { 103, 50, 20.0f, 0, 0, 0 };
    employees[3] = { 104, 30, 25.0f, 0, 0, 0 };
    employees[4] = { 105, 60, 10.0f, 0, 0, 0 };
    for (int i = 0; i < count; i++) {
        computeSalary(employees[i]);
    }
}

// Display all employee records in a tabular format.
void displayRecords(const Employee employees[], int count) {
    cout << "\nEmployee ID\tHours Worked\tHourly Rate\tGross Salary\tTax Deduction\tNet Salary\n";
    for (int i = 0; i < count; i++) {
        cout << employees[i].id << "\t\t"
            << employees[i].hoursWorked << "\t\t"
            << employees[i].hourlyRate << "\t\t"
            << employees[i].grossSalary << "\t\t"
            << employees[i].taxDeduction << "\t\t"
            << employees[i].netSalary << "\n";
    }
}

// Swap two employee records.
void swapRecords(Employee& a, Employee& b) {
    Employee temp = a;
    a = b;
    b = temp;
}

// Sort records by Employee ID in ascending order.
void sortByEmployeeIdAscending(Employee employees[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (employees[i].id > employees[j].id) {
                swapRecords(employees[i], employees[j]);
            }
        }
    }
    cout << "\nRecords sorted by Employee ID (Ascending):";
    displayRecords(employees, count);
}

// Sort records by Employee ID in descending order.
void sortByEmployeeIdDescending(Employee employees[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (employees[i].id < employees[j].id) {
                swapRecords(employees[i], employees[j]);
            }
        }
    }
    cout << "\nRecords sorted by Employee ID (Descending):";
    displayRecords(employees, count);
}

// Sort records by Gross Salary in ascending order.
void sortByGrossSalaryAscending(Employee employees[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (employees[i].grossSalary > employees[j].grossSalary) {
                swapRecords(employees[i], employees[j]);
            }
        }
    }
    cout << "\nRecords sorted by Gross Salary (Ascending):";
    displayRecords(employees, count);
}

// Sort records by Gross Salary in descending order.
void sortByGrossSalaryDescending(Employee employees[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (employees[i].grossSalary < employees[j].grossSalary) {
                swapRecords(employees[i], employees[j]);
            }
        }
    }
    cout << "\nRecords sorted by Gross Salary (Descending):";
    displayRecords(employees, count);
}

// Add a new employee record.
void addEmployee(Employee employees[], int& count) {
    if (count >= MAX_EMP) {
        cout << "\nCannot add more employees. Array is full.\n";
        return;
    }
    Employee newEmp;
    cout << "\nEnter new Employee ID: ";
    cin >> newEmp.id;
    // Check for uniqueness.
    for (int i = 0; i < count; i++) {
        if (employees[i].id == newEmp.id) {
            cout << "Employee ID already exists. Cannot add duplicate IDs.\n";
            return;
        }
    }
    cout << "Enter Hours Worked: ";
    cin >> newEmp.hoursWorked;
    cout << "Enter Hourly Rate: ";
    cin >> newEmp.hourlyRate;
    computeSalary(newEmp);
    employees[count] = newEmp;
    count++;
    cout << "Employee added successfully.\n";
}

// Delete an employee record based on Employee ID.
void deleteEmployee(Employee employees[], int& count) {
    int id;
    cout << "\nEnter Employee ID to delete: ";
    cin >> id;
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Employee ID not found.\n";
        return;
    }
    // Shift remaining records.
    for (int i = index; i < count - 1; i++) {
        employees[i] = employees[i + 1];
    }
    count--;
    cout << "Employee deleted successfully.\n";
}

// Filter and display records based on net salary criteria.
// If greaterOrEqual is true, select employees with net salary >= x; otherwise, net salary < x.
// The descending flag determines the sort order.
void displayFilteredRecords(Employee employees[], int count, bool greaterOrEqual, bool descending) {
    float x;
    cout << "\nEnter the value of X: ";
    cin >> x;

    int indices[MAX_EMP];
    int filteredCount = 0;
    for (int i = 0; i < count; i++) {
        if ((greaterOrEqual && employees[i].netSalary >= x) ||
            (!greaterOrEqual && employees[i].netSalary < x)) {
            indices[filteredCount++] = i;
        }
    }

    // Sort indices based on net salary.
    for (int i = 0; i < filteredCount - 1; i++) {
        for (int j = i + 1; j < filteredCount; j++) {
            if (descending) {
                if (employees[indices[i]].netSalary < employees[indices[j]].netSalary)
                    swap(indices[i], indices[j]);
            }
            else {
                if (employees[indices[i]].netSalary > employees[indices[j]].netSalary)
                    swap(indices[i], indices[j]);
            }
        }
    }

    if (filteredCount == 0) {
        cout << "No records found matching the criteria.\n";
        return;
    }

    cout << "\nFiltered Records:\n";
    cout << "Employee ID\tHours Worked\tHourly Rate\tGross Salary\tTax Deduction\tNet Salary\n";
    for (int i = 0; i < filteredCount; i++) {
        int idx = indices[i];
        cout << employees[idx].id << "\t\t"
            << employees[idx].hoursWorked << "\t\t"
            << employees[idx].hourlyRate << "\t\t"
            << employees[idx].grossSalary << "\t\t"
            << employees[idx].taxDeduction << "\t\t"
            << employees[idx].netSalary << "\n";
    }
}

// Update hours worked or hourly rate for an employee based on Employee ID.
void updateEmployee(Employee employees[], int count) {
    int id;
    cout << "\nEnter Employee ID to update: ";
    cin >> id;
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Employee ID not found.\n";
        return;
    }
    int choice;
    cout << "Update:\n1. Hours Worked\n2. Hourly Rate\nEnter your choice: ";
    cin >> choice;
    if (choice == 1) {
        cout << "Enter new Hours Worked: ";
        cin >> employees[index].hoursWorked;
    }
    else if (choice == 2) {
        cout << "Enter new Hourly Rate: ";
        cin >> employees[index].hourlyRate;
    }
    else {
        cout << "Invalid choice.\n";
        return;
    }
    computeSalary(employees[index]);
    cout << "Employee record updated successfully.\n";
}

int main() {
    Employee employees[MAX_EMP];
    int count = 0;
    prePopulate(employees, count);

    char option;
    do {
        cout << "\n\nEmployee Payroll Management System Menu:\n";
        cout << "1. Sort and Display all Records by Employee ID (Ascending)\n";
        cout << "2. Sort and Display all Records by Employee ID (Descending)\n";
        cout << "3. Sort and Display all Records by Gross Salary (Ascending)\n";
        cout << "4. Sort and Display all Records by Gross Salary (Descending)\n";
        cout << "5. Add a New Employee Payroll Record\n";
        cout << "6. Delete an Employee Payroll Record Based on Employee ID\n";
        cout << "7. Display Employees with Net Salary >= X (Descending)\n";
        cout << "8. Display Employees with Net Salary >= X (Ascending)\n";
        cout << "9. Display Employees with Net Salary < X (Descending)\n";
        cout << "10. Display Employees with Net Salary < X (Ascending)\n";
        cout << "11. Update Hours Worked or Hourly Rate for an Employee Based on Employee ID\n";
        cout << "Enter your choice (or 'e' or 'E' to exit): ";
        cin >> option;

        switch (option) {
        case '1':
            sortByEmployeeIdAscending(employees, count);
            break;
        case '2':
            sortByEmployeeIdDescending(employees, count);
            break;
        case '3':
            sortByGrossSalaryAscending(employees, count);
            break;
        case '4':
            sortByGrossSalaryDescending(employees, count);
            break;
        case '5':
            addEmployee(employees, count);
            break;
        case '6':
            deleteEmployee(employees, count);
            break;
        case '7':
            displayFilteredRecords(employees, count, true, true);
            break;
        case '8':
            displayFilteredRecords(employees, count, true, false);
            break;
        case '9':
            displayFilteredRecords(employees, count, false, true);
            break;
        case '10':
            displayFilteredRecords(employees, count, false, false);
            break;
        case '11':
            updateEmployee(employees, count);
            break;
        case 'e':
        case 'E':
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }

    } while (option != 'e' && option != 'E');

    return 0;
}
