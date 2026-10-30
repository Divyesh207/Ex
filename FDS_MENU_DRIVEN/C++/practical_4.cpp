/*
================================================================================
Department of AI-DS, DYPCOE, Akurdi, Pune
Fundamentals of Data Structures Laboratory (FDS Lab)
Practical No. 04: Searching Algorithms (C++)

Problem Statement:
Implement a C++ program to store employee IDs in an array in random order.
Perform following tasks:
1. Store employee IDs in an array in random order.
2. Search whether a particular employee attended training or not using Linear Search.
3. Search whether a particular employee attended training or not using Binary Search.

Requirements:
- Implement both Linear Search and Binary Search manually without built-in functions.
- Binary Search must operate on a sorted copy of the employee ID array.
- The original employee ID array must remain preserved and unmodified.
- Display whether the employee attended the training or not.
================================================================================
*/

#include <iostream>
#include <limits>

namespace PR4 {

const int MAX_EMPLOYEES = 100;

// Function to safely clear invalid input stream
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function to display an array
void displayArray(const int arr[], int n, const std::string &label) {
    std::cout << label << " (Total: " << n << "): [ ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i];
        if (i < n - 1) std::cout << ", ";
    }
    std::cout << " ]\n";
}

// Function to copy array from source to destination
void copyArray(const int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Function to sort an array in ascending order manually (Bubble Sort)
// Used to create the sorted copy for Binary Search
void manualSortAscending(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Function for Manual Linear Search
// Returns the index if target is found, otherwise returns -1
int linearSearch(const int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i; // Target found at index i
        }
    }
    return -1; // Target not found
}

// Function for Manual Binary Search
// Note: Requires array to be sorted in ascending order
// Returns the index in the sorted array if found, otherwise returns -1
int binarySearch(const int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid; // Target found at index mid
        } else if (arr[mid] < target) {
            low = mid + 1; // Search in the right half
        } else {
            high = mid - 1; // Search in the left half
        }
    }
    return -1; // Target not found
}

// Function to input employee IDs
void inputEmployees(int arr[], int &n) {
    std::cout << "\nEnter number of employees who attended training (1 to " << MAX_EMPLOYEES << "): ";
    while (!(std::cin >> n) || n <= 0 || n > MAX_EMPLOYEES) {
        std::cout << "Invalid input! Please enter an integer between 1 and " << MAX_EMPLOYEES << ": ";
        clearInputBuffer();
    }

    std::cout << "Enter " << n << " employee IDs (in random order):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "  Employee " << (i + 1) << " ID: ";
        while (!(std::cin >> arr[i])) {
            std::cout << "  Invalid input! Enter a valid integer ID: ";
            clearInputBuffer();
        }
    }
    std::cout << ">> " << n << " employee IDs stored successfully!\n";
}

// Practical 4 Interactive Menu
void practical4_menu() {
    // Initial sample data so the program is immediately usable
    int employeeIds[MAX_EMPLOYEES] = {104, 101, 145, 112, 108, 120, 133};
    int count = 7;

    int choice;
    do {
        std::cout << "\n============================================================\n";
        std::cout << "       PRACTICAL 4: EMPLOYEE SEARCHING SYSTEM (C++)\n";
        std::cout << "============================================================\n";
        std::cout << "1. Input / Update Employee IDs\n";
        std::cout << "2. Display Original Employee IDs\n";
        std::cout << "3. Linear Search (on Original Unsorted Array)\n";
        std::cout << "4. Binary Search (on Sorted Copy, Original Preserved)\n";
        std::cout << "5. Return to Main Menu\n";
        std::cout << "============================================================\n";
        std::cout << "Enter your choice (1-5): ";

        if (!(std::cin >> choice)) {
            std::cout << "[Error] Invalid input! Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                inputEmployees(employeeIds, count);
                displayArray(employeeIds, count, "Current Employee IDs");
                break;
            }
            case 2: {
                if (count == 0) {
                    std::cout << "[Warning] No employee IDs available. Please input records first.\n";
                } else {
                    displayArray(employeeIds, count, "Original Employee IDs");
                }
                break;
            }
            case 3: {
                if (count == 0) {
                    std::cout << "[Warning] Employee list is empty!\n";
                    break;
                }
                int target;
                std::cout << "\nEnter Employee ID to search using Linear Search: ";
                while (!(std::cin >> target)) {
                    std::cout << "Invalid input! Enter integer ID: ";
                    clearInputBuffer();
                }

                displayArray(employeeIds, count, "Searching in Original Array");
                int index = linearSearch(employeeIds, count, target);

                std::cout << "\n--- Linear Search Result ---\n";
                if (index != -1) {
                    std::cout << "[ATTENDED] Employee ID " << target 
                              << " attended the training program!\n";
                    std::cout << "           Found at index " << index << " in original list.\n";
                } else {
                    std::cout << "[NOT ATTENDED] Employee ID " << target 
                              << " did NOT attend the training program.\n";
                }
                break;
            }
            case 4: {
                if (count == 0) {
                    std::cout << "[Warning] Employee list is empty!\n";
                    break;
                }
                int target;
                std::cout << "\nEnter Employee ID to search using Binary Search: ";
                while (!(std::cin >> target)) {
                    std::cout << "Invalid input! Enter integer ID: ";
                    clearInputBuffer();
                }

                // Step 1: Create a separate copy of the original array
                int sortedCopy[MAX_EMPLOYEES];
                copyArray(employeeIds, sortedCopy, count);

                // Step 2: Sort the copy array manually
                manualSortAscending(sortedCopy, count);

                std::cout << "\n--- Array Status ---\n";
                displayArray(employeeIds, count, "1. Original Array (Preserved)");
                displayArray(sortedCopy, count,  "2. Sorted Copy (For Binary Search)");

                // Step 3: Perform Binary Search on sorted copy
                int index = binarySearch(sortedCopy, count, target);

                std::cout << "\n--- Binary Search Result ---\n";
                if (index != -1) {
                    std::cout << "[ATTENDED] Employee ID " << target 
                              << " attended the training program!\n";
                    std::cout << "           Found at index " << index << " in sorted copy.\n";
                } else {
                    std::cout << "[NOT ATTENDED] Employee ID " << target 
                              << " did NOT attend the training program.\n";
                }

                // Confirm original list integrity
                std::cout << "Integrity Check: Original array remains intact.\n";
                break;
            }
            case 5: {
                std::cout << "\nReturning to Main Menu...\n";
                break;
            }
            default: {
                std::cout << "[Error] Invalid option! Please choose between 1 and 5.\n";
                break;
            }
        }
    } while (choice != 5);
}

} // namespace PR4

#ifndef INTEGRATED_MAIN
int main() {
    PR4::practical4_menu();
    return 0;
}
#endif

