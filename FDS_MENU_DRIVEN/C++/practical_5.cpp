/*
================================================================================
Department of AI-DS, DYPCOE, Akurdi, Pune
Fundamentals of Data Structures Laboratory (FDS Lab)
Practical No. 05: Sorting Algorithms (C++)

Problem Statement:
Implement a C++ program to store the percentage of students in an array using
floating-point numbers. Write functions for sorting array of floating-point
numbers in ascending order using:
1. Selection Sort
2. Insertion Sort
3. Bubble Sort
4. Quick Sort

Requirements:
- All four algorithms must be implemented manually without built-in sorting.
- Sort percentages in ascending order.
- Display both original and sorted arrays for every sorting operation.
- Preserve original data when switching between sorting algorithms.
- Include feature to display top scores.
================================================================================
*/

#include <iostream>
#include <iomanip>
#include <limits>

namespace PR5 {

const int MAX_STUDENTS = 100;

// Function to clear input buffer on invalid input
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function to display an array of floating-point percentages
void displayArray(const float arr[], int n, const std::string &label) {
    std::cout << label << " (Total: " << n << "): [ ";
    for (int i = 0; i < n; i++) {
        std::cout << std::fixed << std::setprecision(2) << arr[i] << "%";
        if (i < n - 1) std::cout << ", ";
    }
    std::cout << " ]\n";
}

// Function to copy array from source to destination
// Ensures original array is never mutated by sorting
void copyArray(const float src[], float dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Manual swap utility for floating-point values
void swapValues(float &a, float &b) {
    float temp = a;
    a = b;
    b = temp;
}

// -----------------------------------------------------------------------------
// 1. Selection Sort (Manual Implementation)
// Repeatedly finds the minimum element from the unsorted part
// and places it at the beginning.
// Time Complexity: O(n^2), Space Complexity: O(1)
// -----------------------------------------------------------------------------
void selectionSort(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swapValues(arr[i], arr[minIndex]);
        }
    }
}

// -----------------------------------------------------------------------------
// 2. Insertion Sort (Manual Implementation)
// Builds the sorted array one element at a time by inserting
// each new element into its appropriate position.
// Time Complexity: O(n^2), Space Complexity: O(1)
// -----------------------------------------------------------------------------
void insertionSort(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// -----------------------------------------------------------------------------
// 3. Bubble Sort (Manual Implementation)
// Repeatedly steps through the list, compares adjacent elements,
// and swaps them if they are in the wrong order.
// Time Complexity: O(n^2), Space Complexity: O(1)
// -----------------------------------------------------------------------------
void bubbleSort(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swapValues(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped by inner loop, array is sorted
        if (!swapped) break;
    }
}

// -----------------------------------------------------------------------------
// 4. Quick Sort (Manual Implementation)
// Divide-and-conquer algorithm that selects a pivot, partitions
// elements smaller than pivot to left, greater to right, and recurses.
// Time Complexity: O(n log n) average, O(n^2) worst case, Space: O(log n)
// -----------------------------------------------------------------------------
int partition(float arr[], int low, int high) {
    float pivot = arr[high]; // Choosing last element as pivot
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swapValues(arr[i], arr[j]);
        }
    }
    swapValues(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(float arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to display top scores from a sorted array (in ascending order)
void displayTopScores(const float sortedArr[], int n, int topK = 5) {
    if (n == 0) {
        std::cout << "[Warning] No records available.\n";
        return;
    }
    int countToDisplay = (n < topK) ? n : topK;
    std::cout << "\n--- Top " << countToDisplay << " Student Percentages ---\n";
    int rank = 1;
    for (int i = n - 1; i >= n - countToDisplay; i--) {
        std::cout << "  Rank " << rank++ << ": " 
                  << std::fixed << std::setprecision(2) << sortedArr[i] << "%\n";
    }
}

// Function to input student percentages
void inputPercentages(float arr[], int &n) {
    std::cout << "\nEnter number of students (1 to " << MAX_STUDENTS << "): ";
    while (!(std::cin >> n) || n <= 0 || n > MAX_STUDENTS) {
        std::cout << "Invalid input! Please enter an integer between 1 and " << MAX_STUDENTS << ": ";
        clearInputBuffer();
    }

    std::cout << "Enter percentage for " << n << " students (0.00 to 100.00):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "  Student " << (i + 1) << " Percentage: ";
        while (!(std::cin >> arr[i]) || arr[i] < 0.0f || arr[i] > 100.0f) {
            std::cout << "  Invalid! Enter a percentage between 0 and 100: ";
            clearInputBuffer();
        }
    }
    std::cout << ">> " << n << " student records stored successfully!\n";
}

// Practical 5 Interactive Menu
void practical5_menu() {
    // Initial sample data so the program is directly testable
    float originalPercentages[MAX_STUDENTS] = {78.50f, 62.25f, 91.80f, 85.00f, 54.75f, 96.40f, 82.10f};
    int count = 7;

    // Working array used for sorting without touching original data
    float workingArray[MAX_STUDENTS];
    bool isWorkingArraySorted = false;

    int choice;
    do {
        std::cout << "\n============================================================\n";
        std::cout << "         PRACTICAL 5: STUDENT PERCENTAGE SORTING (C++)\n";
        std::cout << "============================================================\n";
        std::cout << "1. Input / Update Student Percentages\n";
        std::cout << "2. Display Original Percentages\n";
        std::cout << "3. Selection Sort (Ascending)\n";
        std::cout << "4. Insertion Sort (Ascending)\n";
        std::cout << "5. Bubble Sort (Ascending)\n";
        std::cout << "6. Quick Sort (Ascending)\n";
        std::cout << "7. Display Top 5 Scores\n";
        std::cout << "8. Return to Main Menu\n";
        std::cout << "============================================================\n";
        std::cout << "Enter your choice (1-8): ";

        if (!(std::cin >> choice)) {
            std::cout << "[Error] Invalid input! Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                inputPercentages(originalPercentages, count);
                isWorkingArraySorted = false;
                displayArray(originalPercentages, count, "Current Student Percentages");
                break;
            }
            case 2: {
                if (count == 0) {
                    std::cout << "[Warning] No student percentage records available.\n";
                } else {
                    displayArray(originalPercentages, count, "Original Percentages (Unsorted)");
                }
                break;
            }
            case 3: {
                if (count == 0) {
                    std::cout << "[Warning] Record list is empty!\n";
                    break;
                }
                copyArray(originalPercentages, workingArray, count);
                selectionSort(workingArray, count);
                isWorkingArraySorted = true;

                std::cout << "\n--- Selection Sort Result ---\n";
                displayArray(originalPercentages, count, "Original Percentages (Preserved)");
                displayArray(workingArray, count,        "Sorted Percentages (Selection Sort)");
                std::cout << "Algorithm: Selection Sort | Time Complexity: O(n^2)\n";
                break;
            }
            case 4: {
                if (count == 0) {
                    std::cout << "[Warning] Record list is empty!\n";
                    break;
                }
                copyArray(originalPercentages, workingArray, count);
                insertionSort(workingArray, count);
                isWorkingArraySorted = true;

                std::cout << "\n--- Insertion Sort Result ---\n";
                displayArray(originalPercentages, count, "Original Percentages (Preserved)");
                displayArray(workingArray, count,        "Sorted Percentages (Insertion Sort)");
                std::cout << "Algorithm: Insertion Sort | Time Complexity: O(n^2)\n";
                break;
            }
            case 5: {
                if (count == 0) {
                    std::cout << "[Warning] Record list is empty!\n";
                    break;
                }
                copyArray(originalPercentages, workingArray, count);
                bubbleSort(workingArray, count);
                isWorkingArraySorted = true;

                std::cout << "\n--- Bubble Sort Result ---\n";
                displayArray(originalPercentages, count, "Original Percentages (Preserved)");
                displayArray(workingArray, count,        "Sorted Percentages (Bubble Sort)");
                std::cout << "Algorithm: Bubble Sort | Time Complexity: O(n^2)\n";
                break;
            }
            case 6: {
                if (count == 0) {
                    std::cout << "[Warning] Record list is empty!\n";
                    break;
                }
                copyArray(originalPercentages, workingArray, count);
                quickSort(workingArray, 0, count - 1);
                isWorkingArraySorted = true;

                std::cout << "\n--- Quick Sort Result ---\n";
                displayArray(originalPercentages, count, "Original Percentages (Preserved)");
                displayArray(workingArray, count,        "Sorted Percentages (Quick Sort)");
                std::cout << "Algorithm: Quick Sort | Average Time Complexity: O(n log n)\n";
                break;
            }
            case 7: {
                if (count == 0) {
                    std::cout << "[Warning] Record list is empty!\n";
                    break;
                }
                // If working array has not been sorted yet, sort a fresh copy using Quick Sort
                if (!isWorkingArraySorted) {
                    copyArray(originalPercentages, workingArray, count);
                    quickSort(workingArray, 0, count - 1);
                    isWorkingArraySorted = true;
                }
                displayTopScores(workingArray, count, 5);
                break;
            }
            case 8: {
                std::cout << "\nReturning to Main Menu...\n";
                break;
            }
            default: {
                std::cout << "[Error] Invalid option! Please choose between 1 and 8.\n";
                break;
            }
        }
    } while (choice != 8);
}

} // namespace PR5

#ifndef INTEGRATED_MAIN
int main() {
    PR5::practical5_menu();
    return 0;
}
#endif

