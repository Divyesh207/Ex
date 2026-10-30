#include <iostream>
#include <string>
using namespace std;

struct Employee
{
    int id;
    string name;

    Employee *prev;
    Employee *next;
};

Employee *head = NULL;

// Insert Employee
void insertEmployee()
{
    Employee *newNode = new Employee;

    cout << "Enter Employee ID: ";
    cin >> newNode->id;

    cout << "Enter Employee Name: ";
    cin >> newNode->name;

    newNode->prev = NULL;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Employee *temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->prev = temp;
    }

    cout << "\nEmployee inserted successfully!\n";
}

// Display Employees
void displayEmployees()
{
    if (head == NULL)
    {
        cout << "\nNo employee records found!\n";
        return;
    }

    Employee *temp = head;

    cout << "\n--- Employee Records ---\n";

    while (temp != NULL)
    {
        cout << "\nEmployee ID: " << temp->id;
        cout << "\nEmployee Name: " << temp->name << endl;

        temp = temp->next;
    }
}

// Count Employees
void countEmployees()
{
    int count = 0;
    Employee *temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    cout << "\nTotal Employees: " << count << endl;
}

// Delete Employee by ID
void deleteEmployee()
{
    if (head == NULL)
    {
        cout << "\nNo employee records to delete!\n";
        return;
    }

    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    Employee *temp = head;

    // Search for employee
    while (temp != NULL && temp->id != id)
    {
        temp = temp->next;
    }

    // Employee not found
    if (temp == NULL)
    {
        cout << "\nEmployee ID not found!\n";
        return;
    }

    // If employee is the first node
    if (temp == head)
    {
        head = temp->next;
    }

    // Connect previous node to next node
    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }

    // Connect next node to previous node
    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    delete temp;

    cout << "\nEmployee deleted successfully!\n";
}

// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n===== EMPLOYEE DATABASE =====";
        cout << "\n1. Insert Employee";
        cout << "\n2. Display Employees";
        cout << "\n3. Count Employees";
        cout << "\n4. Delete Employee";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";

        cin >> choice;

        switch (choice)
        {
            case 1:
                insertEmployee();
                break;

            case 2:
                displayEmployees();
                break;

            case 3:
                countEmployees();
                break;

            case 4:
                deleteEmployee();
                break;

            case 5:
                cout << "\nExiting program...\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
